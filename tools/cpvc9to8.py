#!/usr/bin/env python
"""
Function:   Copy *_vc90.vcproj to *_vc80.vcproj.
Creator:    Zhang Yungui <rhcad@hotmail.com>
Date:       2011.11.14
"""

import os, sys, re

def multireplace(text, adict):
    rx = re.compile('|'.join(map(re.escape, adict)))
    def xlat(match):
        return adict[match.group(0)]
    return rx.sub(xlat, text)

def copyvcfiles(dir, pairs):
    for fn in os.listdir(dir):
        srcfile = os.path.join(dir, fn)
        if os.path.isdir(srcfile):
            copyvcfiles(srcfile, pairs)
        elif (fn.find("_vc90.vcproj") > 0 or fn.find("_vc90.sln") > 0) \
            and fn.find(".user") < 0:
            destfile = srcfile.replace("_vc90.", "_vc80.")
            oldtext = open(destfile).read() if os.path.exists(destfile) else ''
            text = multireplace(open(srcfile).read(), pairs)
            if text != oldtext:
                open(destfile, 'w').write(text)
                print(destfile)

if __name__=="__main__":
    pairs = { "Format Version 10.00" : "Format Version 9.00",   \
        "Visual Studio 2008" : "Visual Studio 2005",    \
        "_vc90." : "_vc80.", "Version=\"9.00" : "Version=\"8.00" }
    copyvcfiles(os.path.abspath('../projects'), pairs)
