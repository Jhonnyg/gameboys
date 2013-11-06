#!/usr/bin/env python

# Super shitty asset compiler (c) Gameboys 1998 - 2013
#
# Usage: compile.py assets/*.wav output.h
#

import sys, os, fnmatch

from utils import *

class SoundProcessor:
    def __init__(self):
        self.sox = which("sox") or which("sox.exe") or which("tools/sox.exe")
        if self.sox is None:
            print "I need the sox encoder! http://sox.sourceforge.net/"
            sys.exit(-1)

    def process(self, soundfile):
        import subprocess, struct
        args = [self.sox, soundfile, "-r", "8192", "-b", "8", "-c", "1", "-t", "raw", "-"]
        # convert to 8bit pcm, sox can't use a bit depth of 4
        p = subprocess.Popen(args, stdout=subprocess.PIPE)
        raw8bit = p.communicate()[0]
        samplecount = len(raw8bit)
        def to4(b): return ord(b) / 16
        packed4bit = [to4(b) | (to4(a) << 4) for a, b in grouper(2, raw8bit) if a != None and b != None]
        return struct.pack("%s"%(len(packed4bit)*"B"), *packed4bit), samplecount / 32


    def write(self, asset, raw):
        name = os.path.basename(os.path.splitext(asset)[0])
        enc = hexify(name, raw[0])
        enc += "const UINT16 {0}_len = {1}; // play_sample({0}, {1});\n".format(name, raw[1])
        return enc

class ImageProcessor:
    pass

def setup_processors():
    proc = {}
    proc["wav"] = SoundProcessor()
    return proc

def parseargs(args):
    try:
        source, target = args[0], args[1]
        source, pattern = source.split("/")
        return source, pattern, target
    except:
        print "Usage: compile.py assets/*.wav output.h"
        sys.exit(-1)

def classify_asset(filename):
    if '.' in filename:
        return os.path.splitext(filename)[1][1:]
    else:
        return None

def find_assets(source, pattern):
    assets = []
    for path, dirs, files in os.walk(source):
        for fp in files:
            if fnmatch.fnmatch(fp, pattern):
                ac = classify_asset(fp)
                if ac:
                    assets.append((os.path.join(path, fp), ac))
    return assets

def process_assets(assets, processors):
    compiled = []
    for asset, cls in assets:
        if cls in processors:
            casset = process_asset(asset, processors[cls])
            if casset:
                compiled.append(casset)
    return compiled

def process_asset(asset, processor):
    raw = processor.process(asset)
    enc = processor.write(asset, raw)
    return enc

def write_assets(compiled, target):
    with open(target, "wb") as f:
        for data in compiled:
            f.write("\n")
            f.write(data)
            f.write("\n")

def hexify(name, data):
    chunk_size = len(data)
    hex_chunk = ["0x%02X"%int(byte.encode("hex"), 16) + ("\n\t" if index % 20 == 19 else "") 
                 for index, byte in enumerate(data)]
    hex_data = "const unsigned char %s[] = {\n\t " % name
    hex_data += ",".join(hex_chunk)
    hex_data += "};\n"
    hex_data += "const UINT16 {0}_size = {1};\n".format(name, chunk_size)
    return hex_data

def main(args):
    processors = setup_processors()
    source, pattern, target = parseargs(args)
    assets = find_assets(source, pattern)
    compiled = process_assets(assets, processors)
    write_assets(compiled, target)

if __name__ == '__main__':
    main(sys.argv[1:])
