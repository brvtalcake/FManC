import string

class Version:
    def __init__(self, major, minor, patch):
        self.major = major
        self.minor = minor
        self.patch = patch

    def __str__(self):
        return f"{self.major}_{self.minor}_{self.patch}"
    
    def __repr__(self):
        return self.__str__()
    
    def __eq__(self, other):
        return self.major == other.major and self.minor == other.minor and self.patch == other.patch
    
    def __ne__(self, other):
        return not self.__eq__(other)
    
    def __lt__(self, other):
        if self.major < other.major:
            return True
        elif self.major == other.major:
            if self.minor < other.minor:
                return True
            elif self.minor == other.minor:
                if self.patch < other.patch:
                    return True
        return False
    
    def __le__(self, other):
        return self.__lt__(other) or self.__eq__(other)
    
    def __gt__(self, other):
        return not self.__le__(other)
    
    def __ge__(self, other):
        return not self.__lt__(other)
    
    def FMC_ver(self):
        return f"FMC_MK_VER_NUM({self.major}, {self.minor}, {self.patch})"

default_symbol_template = string.Template("""
    #if !defined(USE_${symbol_name}_VER) || USE_${symbol_name}_VER == ${symbol_ver} || defined(FMC_BUILD_SO) || defined(FMC_USE_SO)""")

symbol_template = string.Template("""
    #if defined(USE_${symbol_name}_VER) && USE_${symbol_name}_VER == ${symbol_ver} && !(defined(FMC_BUILD_SO) || defined(FMC_USE_SO)))""")

class Symbol:
    def __init__(self, name, ma, mi, p, is_default = False):
        self.name = name
        self.ver = Version(ma, mi, p)
        self.is_default = is_default
    
    def __str__(self):
        return f"{self.name} v{self.ver}"
    
    def __repr__(self):
        return self.__str__()
    
    def Dump(self):
        if self.is_default:
            return default_symbol_template.substitute(symbol_name = self.name, symbol_ver = self.ver.FMC_ver())
        else:
            return symbol_template.substitute(symbol_name = self.name, symbol_ver = self.ver.FMC_ver())

def dump_default(name, ma, mi, p):
    return Symbol(name, ma, mi, p, True).Dump()

def dump_normal(name, ma, mi, p):
    return Symbol(name, ma, mi, p).Dump()
