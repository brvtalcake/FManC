import os
import sys
from typing import overload

def transform(s: str):
    return s.replace('src', 'obj/cog_processed')

def notdir(s: str):
    return s.split('/')[-1]

def dir(s: str):
    return '/'.join(s.split('/')[:-1])

def search_inc_directives(s: str) -> list:
    includes = []
    for line in s.split('\n'):
        if line.startswith('#include'):
            includes.append(line)
    return includes

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
    for line in s.split('\n'):
        if line.startswith('#include'):
            processed = line.split(' ')[-1].replace('"', '').replace('<', '').replace('>', '')
            if 'chaos' in processed:
                to_search = search_fmc_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
            elif 'metalang99' in processed:
                to_search = search_fmc_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
            else:
                to_search = search_fmc_file(processed)
                deps.append(to_search)
                f = open(to_search, 'r').read()
                deps += get_deps(f)
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
        return self.files

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
        for src_file in self.files:
            if not os.path.exists(dir(self.files[src_file])):
                os.makedirs(dir(self.files[src_file]))
            if os.path.exists(self.files[src_file]):
                os.remove(self.files[src_file])
            if os.path.exists(src_file):
                os.system(f'cog -o {self.files[src_file]} {src_file}')
            else:
                print(f'{src_file} does not exist')

    def __str__(self):
        ret_str = 'List of files for cog to process:\n'
        for src_file in self.files:
            ret_str += f'\t{src_file} --> {self.files[src_file]}\n'
        return ret_str
    
    def __repr__(self):
        return self.__str__()

processor = cog_processor()
processor.get_src_dir_files()

print(processor)
# print cwd
print(os.getcwd())

fmc = 'src/FMC.h'
#print(get_deps(open(fmc, 'r').read()))

print(search_fmc_file('../FMC_ver.h'))