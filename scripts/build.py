import os
import sys
import re
import threading
import subprocess
from typing import overload

def transform(s: str):
    return s.replace('src', 'obj/cog_processed')

def notdir(s: str):
    return s.split('/')[-1]

def dir(s: str):
    return '/'.join(s.split('/')[:-1])

def delete_comments(text):
    def replacer(match):
        s = match.group(0)
        if s.startswith('/'):
            return " " # note: a space and not an empty string
        else:
            return s
    pattern = re.compile(
        r'//.*?$|/\*.*?\*/|\'(?:\\.|[^\\\'])*\'|"(?:\\.|[^\\"])*"',
        re.DOTALL | re.MULTILINE
    )
    return re.sub(pattern, replacer, text)


def search_inc_directives(s: str) -> list:
    includes = []
    for line in s.split('\n'):
        if line.startswith('#include'):
            includes.append(line)
    return includes

def search_std_include(s: str) -> str:
    sys.stderr.write(f'searching for {s}\n')
    for root, _, files in os.walk('/usr/include/'):
        for file in files:
            realpath = os.path.join(root, file).replace('\\', '/')
            if s.replace('../', '').replace('./', '').replace('..\\', '').replace('.\\', '') in realpath:
                return os.path.join(root, file).replace('\\', '/')
    for root, _, files in os.walk('/usr/lib/'):
        for file in files:
            realpath = os.path.join(root, file).replace('\\', '/')
            if s.replace('../', '').replace('./', '').replace('..\\', '').replace('.\\', '') in realpath:
                return os.path.join(root, file).replace('\\', '/')
    return ''

def search_chaospp_file(s: str) -> str:
    sys.stderr.write(f'searching for {s}\n')
    for root, _, files in os.walk('./third_party_libs/chaos_pp/'):
        for file in files:
            realpath = os.path.join(root, file).replace('\\', '/')
            if s.replace('../', '').replace('./', '').replace('..\\', '').replace('.\\', '') in realpath:
                return os.path.join(root, file).replace('\\', '/')
    return ''

def search_metalang99_file(s: str) -> str:
    sys.stderr.write(f'searching for {s}\n')
    for root, _, files in os.walk('./third_party_libs/metalang99/include/'):
        for file in files:
            realpath = os.path.join(root, file).replace('\\', '/')
            if s.replace('../', '').replace('./', '').replace('..\\', '').replace('.\\', '') in realpath:
                return os.path.join(root, file).replace('\\', '/')
    return ''

def search_fmc_file(s: str) -> str:
    sys.stderr.write(f'searching for {s}\n')
    for root, _, files in os.walk('./src/'):
        for file in files:
            realpath = os.path.join(root, file).replace('\\', '/')
            if s.replace('../', '').replace('./', '').replace('..\\', '').replace('.\\', '') in realpath:
                return os.path.join(root, file).replace('\\', '/')
    return ''

def get_deps(s: str) -> list:
    deps = []
    processed = ''
    s = delete_comments(s)
    for line in s.split('\n'):
        if line.startswith('#include'):
            processed = line.split(' ')[-1].replace('"', '').replace('<', '').replace('>', '')
            if 'chaos' in processed:
                to_search = search_chaospp_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
            elif 'metalang99' in processed:
                to_search = search_metalang99_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
            elif 'FMC' in processed:
                to_search = search_fmc_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
            else:
                to_search = search_std_include(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
    # remove duplicates
    deps = list(set(deps))
    return deps

class cog_processor:
    files: dict = {}

    @overload
    def __init__(self, src_file: str):
        if (src_file not in self.files) and (os.path.isfile(src_file)):
            self.files[src_file] = transform(src_file)
        return self.files

    @overload
    def __init__(self, src_files: list):
        for src_file in src_files:
            if (src_file not in self.files) and (os.path.isfile(src_file)):
                self.files[src_file] = transform(src_file)
        return self.files

    def __init__(self):
        return None

    def get_src_dir_files(self):
        for root, _, files in os.walk('./src'):
            for file in files:
                src_file = os.path.join(root, file)
                if (src_file not in self.files)                 \
                    and (os.path.isfile(src_file))              \
                    and ((notdir(src_file).endswith('.c'))      \
                        or (notdir(src_file).endswith('.h'))    \
                        or (notdir(src_file).endswith('.cpp'))  \
                        or (notdir(src_file).endswith('.hpp'))):
                    self.files[src_file] = transform(src_file)
        return self

    def get_files(self):
        return self.files
    
    def get_src_files(self):
        return list(self.files.keys())
    
    def get_obj_files(self):
        return list(self.files.values())
    
    def get_obj_file(self, src_file: str):
        return self.files[src_file]
    
    def get_src_file(self, obj_file: str):
        for src_file in self.files:
            if self.files[src_file] == obj_file:
                return src_file
        return None
    
    def process(self):
        def subprocesses_func(src_f: str):
            if not os.path.exists(dir(self.files[src_f])):
                os.makedirs(dir(self.files[src_f]))
            if os.path.exists(self.files[src_f]):
                os.remove(self.files[src_f])
            if os.path.exists(src_f):
                sys.stderr.write(f'cog -d -o {self.files[src_f]} {src_f}')
                #os.system(f'cog -d -o {self.files[src_f]} {src_f}')
                subprocess.run(['cog', '-d', '-o', self.files[src_f], src_f])
            else:
                sys.stderr.write(f'{src_f} does not exist')
            return self
        
        class processing_thread(threading.Thread):
            def __init__(self, src_file: str, nb):
                threading.Thread.__init__(self, name=f'processing_thread_{nb}')
                self.src_file = src_file

            def run(self):
                subprocesses_func(self.src_file)

        running_threads = []
        for src_file in self.files:
            t = processing_thread(src_file, len(running_threads))
            t.start()     
            running_threads.append(t)
        for t in running_threads:
            t.join()
        return self

    def __str__(self):
        ret_str = 'List of files for cog to process:\n'
        for src_file in self.files:
            ret_str += f'\t{src_file} --> {self.files[src_file]}\n'
        return ret_str
    
    def __repr__(self):
        return self.__str__()

def main():
    processor = cog_processor()
    processor.get_src_dir_files()
    print(processor)
    processor.process()
    print(f'make -j{sys.argv[1]} {sys.argv[2]}')
    os.system(f'make -j{sys.argv[1]} {sys.argv[2]}')
#    subprocess.run(['make', '-j', sys.argv[1], sys.argv[2]])

main()