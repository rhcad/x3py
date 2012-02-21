#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Function:   Create a plugin project based on example project.
            This script has been tested with ActivePython 2.7.

Usage:      python makeplugin.py prjname [pkgname] [baseprj] [basepkg]
            or double click the file 'makeplugin.py'.

            prjname: name of the new project.
            pkgname: package name of the new project, the default value is 'example'.
            baseprj: project name, the default value is 'pltempl'.
            basepkg: package name of the template project, the default value is 'example'.

Creator:    Zhang Yungui <rhcad@hotmail.com>
Date:       2011.11.14
ChangeList:
    1. Implemented the function: multi_replace, copyfiles, makeproj
    2. Auto copy interface files and skip swig files. [2011.12.14]
"""

import os, sys, re, uuid

def multi_replace(text, adict):
    rx = re.compile('|'.join(map(re.escape, adict)))
    def xlat(match):
        return adict[match.group(0)]
    return rx.sub(xlat, text)

def copyfiles(srcdir, dstdir, pairs, baseprj, callback, needswig=False):
    if ".svn" in srcdir: return
    if not needswig and "swig" in srcdir: return
    has_ifile = not needswig and os.path.exists(os.path.join(srcdir, baseprj + ".i"))
    
    if not os.path.exists(dstdir):
        os.makedirs(dstdir)
    
    for fn in os.listdir(srcdir):
        srcfile = os.path.join(srcdir, fn)
        dstfile = os.path.join(dstdir, multi_replace(fn, pairs))
        
        if os.path.isdir(srcfile):
            copyfiles(srcfile, dstfile, pairs, baseprj, callback, needswig)
            return
        
        if has_ifile and (fn == baseprj + ".i" or fn.startswith("test" + baseprj)): return
        
        if os.path.isfile(srcfile) and not os.path.exists(dstfile) \
                and callback(fn, pairs):
            open(dstfile, "wb").write(open(srcfile, "rb").read())
            text = open(dstfile).read()
            newtext = multi_replace(text, pairs)
            if newtext != text:
                open(dstfile, 'w').write(newtext)
                print('%s [replaced]' % (dstfile,))
            else:
                print('%s [created]' % (dstfile,))

def makeproj(prjname, pkgname, baseprj, basepkg, needswig):
    rootpath = os.path.abspath('..')
    basepath = os.path.join(rootpath, 'source', basepkg, baseprj)
    pkgpath  = os.path.join(rootpath, 'source', pkgname)
    dstdir  = os.path.join(pkgpath, prjname)
    
    if prjname == '':
        raise AttributeError, prjname
    if not os.path.exists(basepath):
        print("\nPlease input a valid exists template project name."
              "\n\'%s\' does not exist." % (basepath,))
        raise OSError, basepath
    
    if not os.path.exists(pkgpath):
        os.makedirs(pkgpath)
        srcmk = os.path.join(rootpath, 'source', basepkg, 'Makefile')
        if os.path.exists(srcmk):
            dstmk = os.path.join(pkgpath, 'Makefile')
            open(dstmk, "w").write(open(srcmk).read())
            print('%s [created]' % (dstmk,))

    pairs = {baseprj:prjname, basepkg:pkgname}
    
    def matchfile(filename, pairs):
        if filename.find("_wrap.cxx") > 0 or filename.find("_wrap.h") > 0:
            return False
        return True
    copyfiles(basepath, dstdir, pairs, baseprj, matchfile, needswig)

    basepath = os.path.join(rootpath, 'interface', basepkg, baseprj)
    dstdir  = os.path.join(rootpath, 'interface', pkgname, prjname)
    intpairs = pairs
    intpairs["78d30c77-e0f0-48a3-a489-dd4327759c27"] = str(uuid.uuid1())
    intpairs["94071767-ba6b-4769-9eb4-2ebf469289f3"] = str(uuid.uuid1())
    intpairs["feefc399-29f2-4354-8eeb-048d4cf56567"] = str(uuid.uuid1())
    copyfiles(basepath, dstdir, intpairs, baseprj, matchfile, needswig)

    def matchproj(filename, pairs):
        if ".user" in filename: return False
        for key in pairs.keys():
            if filename.startswith(key + '_') or \
               filename.startswith(key + '.'): return True
        return False
    projects = os.path.join(rootpath, 'projects')
    copyfiles(projects, projects, pairs, baseprj, matchproj, needswig)

if __name__=="__main__":
    def inputparam(index, prompt, default=''):
        if len(sys.argv) > index: ret = sys.argv[index]
        else: ret = raw_input(prompt)
        if ret == '': ret = default
        return ret
    
    prjname = inputparam(1, 'New project name: ')
    pkgname  = inputparam(2, 'Package name of the new project (default: example): ', 'example')
    baseprj = inputparam(3, 'Template (exists) project name (default: pltempl): ', 'pltempl')
    basepkg  = inputparam(4, 'Package name of the template project (default: example): ', 'example')
    needswig = inputparam(5, 'Need swig (y/n) ? (default: n): ', 'n')
    
    makeproj(prjname, pkgname, baseprj, basepkg, 'y' in needswig)
    if len(sys.argv) < 3: raw_input("Press <ENTER> to end.")
