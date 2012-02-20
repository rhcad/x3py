#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Function:   Create a plugin project based on example project.
            This script has been tested with ActivePython 2.7.

Usage:      python makeplugin.py projname [pkgname] [baseproj] [basepkg]
            or double click the file 'makeplugin.py'.

            projname: name of the new project.
            pkgname: package name of the new project, the default value is 'example'.
            baseproj: project name, the default value is 'pltempl'.
            basepkg: package name of the template project, the default value is 'example'.

Creator:    Zhang Yungui <rhcad@hotmail.com>
Date:       2011.11.14
ChangeList:
    1. Implemented the function: multireplace, copyfiles, makeproj
    2. Auto copy interface files and skip swig files. [2011.12.14]
"""

import os, sys, re, uuid

def multireplace(text, adict):
    rx = re.compile('|'.join(map(re.escape, adict)))
    def xlat(match):
        return adict[match.group(0)]
    return rx.sub(xlat, text)

def copyfiles(srcdir, destdir, pairs, callback=None, needswig=False):
    if ".svn" in srcdir: return
    if not needswig and "swig" in srcdir: return
    if not os.path.exists(destdir):
        os.makedirs(destdir)
    
    for fn in os.listdir(srcdir):
        srcfile = os.path.join(srcdir, fn)
        destfile = os.path.join(destdir, multireplace(fn, pairs))
        
        if os.path.isdir(srcfile):
            copyfiles(srcfile, destfile, pairs, callback, needswig)
        
        if os.path.isfile(srcfile) and not os.path.exists(destfile) \
                and (not callback or callback(fn, pairs)):
            open(destfile, "wb").write(open(srcfile, "rb").read())
            text = open(destfile).read()
            newtext = multireplace(text, pairs)
            if newtext != text:
                open(destfile, 'w').write(newtext)
                print('%s [replaced]' % destfile)
            else:
                print('%s [created]' % destfile)

def makeproj(projname, pkgname, baseproj, basepkg, needswig):
    rootpath = os.path.abspath('..')
    basepath = os.path.join(rootpath, 'source', basepkg, baseproj)
    pkgpath  = os.path.join(rootpath, 'source', pkgname)
    destdir  = os.path.join(pkgpath, projname)
    
    if projname == '':
        raise AttributeError, projname
    if not os.path.exists(basepath):
        print("\nPlease input a valid exists template project name."
              "\n\'%s\' does not exist." % (basepath,))
        raise OSError, basepath
    
    if not os.path.exists(pkgpath):
        os.makedirs(pkgpath)
        srcmk = os.path.join(rootpath, 'source', basepkg, 'Makefile')
        if os.path.exists(srcmk):
            destmk = os.path.join(pkgpath, 'Makefile')
            open(destmk, "w").write(open(srcmk).read())
            print('%s [created]' % destmk)

    pairs = {baseproj:projname, basepkg:pkgname}
    
    def matchfile(filename, pairs):
        if filename.find("_wrap.cxx") > 0 or filename.find("_wrap.h") > 0:
            return False
        return True
    copyfiles(basepath, destdir, pairs, matchfile, needswig)

    basepath = os.path.join(rootpath, 'interface', basepkg, baseproj)
    destdir  = os.path.join(rootpath, 'interface', pkgname, projname)
    intpairs = pairs
    intpairs["78d30c77-e0f0-48a3-a489-dd4327759c27"] = str(uuid.uuid1())
    intpairs["94071767-ba6b-4769-9eb4-2ebf469289f3"] = str(uuid.uuid1())
    copyfiles(basepath, destdir, intpairs, matchfile, needswig)

    def matchproj(filename, pairs):
        if ".user" in filename: return False
        for key in pairs.keys():
            if filename.startswith(key + '_') or \
               filename.startswith(key + '.'): return True
        return False
    projects = os.path.join(rootpath, 'projects')
    copyfiles(projects, projects, pairs, matchproj, needswig)

if __name__=="__main__":
    def inputparam(index, prompt, default=''):
        if len(sys.argv) > index: ret = sys.argv[index]
        else: ret = raw_input(prompt)
        if ret == '': ret = default
        return ret
    
    projname = inputparam(1, 'New project name: ')
    pkgname  = inputparam(2, 'Package name of the new project (default: example): ', 'example')
    baseproj = inputparam(3, 'Template (exists) project name (default: pltempl): ', 'pltempl')
    basepkg  = inputparam(4, 'Package name of the template project (default: example): ', 'example')
    needswig = inputparam(5, 'Need swig (y/n) ? (default: n): ', 'n')
    
    makeproj(projname, pkgname, baseproj, basepkg, 'y' in needswig)
    if len(sys.argv) < 3: raw_input("Press any key to end.")
