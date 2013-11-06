def grouper(n, iterable, fillvalue=None):
    "grouper(3, 'ABCDEFG', 'x') --> ABC DEF Gxx"
    import itertools
    args = [iter(iterable)] * n
    return list(itertools.izip_longest(*args, fillvalue=fillvalue))

def which(program):
    """ Find program in PATH
        as suggested here http://stackoverflow.com/a/377028
    """
    import os
    def is_exe(fpath):
        return os.path.exists(fpath) and os.access(fpath, os.X_OK)

    fpath, fname = os.path.split(program)
    if fpath:
        if is_exe(program):
            return program
    else:
        for path in os.environ["PATH"].split(os.pathsep)+['.']:
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                return exe_file