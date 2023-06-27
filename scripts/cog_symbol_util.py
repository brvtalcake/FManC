import string

def fmt_comma_sep_list(xs):
    return ", ".join(xs)

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

default_func_symbol_template = string.Template("""
    #if defined(FMC_BUILD_SO) || defined(FMC_USE_SO)
        extern ${ret_type} ${symbol_name}(${params});
    #endif
    #if !defined(USE_${symbol_name}_VER) || USE_${symbol_name}_VER == ${symbol_ver} || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO))
    // extern ${ret_type} ${symbol_name}(${params});""")

default_func_symbol_template_in_dot_c = string.Template("""
    #if !defined(USE_${symbol_name}_VER) || USE_${symbol_name}_VER == ${symbol_ver} || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO))
    // extern ${ret_type} ${symbol_name}(${params});""")

func_symbol_template = string.Template("""
    #if (defined(USE_${symbol_name}_VER) && USE_${symbol_name}_VER == ${symbol_ver}) || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO)))
    // extern ${ret_type} ${symbol_name}(${params});""")

default_symbol_template = string.Template("""
    #if defined(FMC_BUILD_SO) || defined(FMC_USE_SO)
        extern ${ret_type} ${symbol_name};
    #endif
    #if !defined(USE_${symbol_name}_VER) || USE_${symbol_name}_VER == ${symbol_ver} || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO))
    // extern ${ret_type} ${symbol_name};""")

default_symbol_template_in_dot_c = string.Template("""
    #if !defined(USE_${symbol_name}_VER) || USE_${symbol_name}_VER == ${symbol_ver} || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO))
    // extern ${ret_type} ${symbol_name};""")

symbol_template = string.Template("""
    #if (defined(USE_${symbol_name}_VER) && USE_${symbol_name}_VER == ${symbol_ver}) || (defined(FMC_BUILD_SO) || defined(FMC_USE_SO))
    // extern ${ret_type} ${symbol_name};""")

class Symbol:
    def __init__(self, name, ma, mi, p, ret_type: str = None, params: tuple = None, is_default: bool = False, in_header: bool = True):
        self.name = name
        self.ver = Version(ma, mi, p)
        self.params = params
        self.ret_type = ret_type
        self.is_default = is_default
        self.in_header = in_header
        # if tuple is None, then it is not a function
        if params is not None:
            self.is_func = True
        else:
            self.is_func = False
        if self.is_func:
            if self.is_default:
                if not self.in_header:
                    self.template = default_func_symbol_template_in_dot_c
                else:
                    self.template = default_func_symbol_template
            else:
                self.template = func_symbol_template
        else:
            if self.is_default:
                if not self.in_header:
                    self.template = default_symbol_template_in_dot_c
                else:
                    self.template = default_symbol_template
            else:
                self.template = symbol_template


    def __str__(self):
        return self.Dump()
    
    def __repr__(self):
        return self.__str__()
    
    def Dump(self):
        if self.is_func:
            param_str = f"{', '.join([param for param in self.params])}"
            return self.template.substitute(symbol_name = self.name, symbol_ver = self.ver.FMC_ver(), ret_type = self.ret_type, params = param_str)
        else:
            return self.template.substitute(symbol_name = self.name, symbol_ver = self.ver.FMC_ver(), ret_type = self.ret_type)

def header_dump_default(name, ma, mi, p, ret_type: str = None, params: tuple = None):
    return Symbol(name, ma, mi, p, ret_type, params, True).Dump()

def header_dump_normal(name, ma, mi, p, ret_type: str = None, params: tuple = None):
    return Symbol(name, ma, mi, p, ret_type, params, False).Dump()

def dump_default(name, ma, mi, p, ret_type: str = None, params: tuple = None):
    return Symbol(name, ma, mi, p, ret_type, params, True, False).Dump()

def dump_normal(name, ma, mi, p, ret_type: str = None, params: tuple = None):
    return Symbol(name, ma, mi, p, ret_type, params, False, False).Dump()
