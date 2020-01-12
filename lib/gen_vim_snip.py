import os
import re
import fnmatch
from pathlib import Path

START = "SNIPPETS_START"
END = "SNIPPETS_END"

HOME = str(Path.home())
OUT = HOME + "/.vim_runtime/sources_non_forked/vim-snippets/snippets/cpp/"
SNIP = ".snippets"

def to_snippets(addr):
    try:
        with open(addr, 'r') as rf:
            while True:
                line = rf.readline()
                # EOF
                if not line:
                    print(addr + " NO snip.")
                    break
                # process
                if START not in line:
                    continue
                short_cut = line.split(START, 1)[1].strip()
                to = OUT + short_cut + SNIP
                # write
                with open(to, 'w+') as wf:
                    wf.write("snippet ")
                    wf.write(short_cut + "\n")
                    while True:
                        line = rf.readline()
                        if END in line:
                            break
                        wf.write('\t' + line)
                # print(short_cut + SNIP + " is done!", flush=True)
                break
    except:
        print("read \"%s\" file not found" %(addr))

# generate all snip recursively
def to_all():
    includes = ['*.h']
    includes = r'|'.join([fnmatch.translate(x) for x in includes])
    for root, dirs, files in os.walk("."):
        for x in files:
            addr = os.path.join(root, x)
            if re.match(includes, addr):
                to_snippets(addr)
            else:
                print(addr)

def main():
    addr = input()
    #addr = "./math/crt.h"
    if addr == "ALL":
        to_all()
    else:
        to_snippets(addr)

if __name__ == "__main__":
    main()

