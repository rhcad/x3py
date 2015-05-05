#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""
Function:   Create a plugin project based on example project.
            This script has been tested with ActivePython 2.7/3.2.

Usage:      python makeplugin.py [prjname [pkgname [srcprj [srcpkg [useswig]]]]]
            or double click the file 'makeplugin.py'.

            prjname: name of the new project.
            pkgname: package name of the new project, the default value is 'example'.
            srcprj:  template (exists) project name, the default value is 'pltempl'.
            srcpkg:  package name of the template project, the default value is 'example'.
            useswig: need swig files or not (y/n), the default value is 'n'.

Creator:    Zhang Yungui <rhcad@hotmail.com>
Date:       2011.11.14
ChangeList:
    1. Implemented the function: multi_replace, copyfiles, makeproj
    2. Auto copy interface files and skip swig files. [2011.12.14]
    3. Auto skip empty folders. [2012.02.21]
"""

import os, sys, re, uuid

def multi_replace(text, adict):
    rx = re.compile('|'.join(map(re.escape, adict)))
    def xlat(match):
        return adict[match.group(0)]
    return rx.sub(xlat, text)

def copyfiles(srcdir, dstdir, pairs, srcprj, callback, noswig):
    if ".svn" in srcdir or not os.path.exists(srcdir): return
    if noswig and "swig" in srcdir: return
    has_i = noswig and os.path.exists(os.path.join(srcdir, srcprj + ".i"))
    
    for fn in os.listdir(srcdir):
        srcfile = os.path.join(srcdir, fn)
        dstfile = os.path.join(dstdir, multi_replace(fn, pairs))
        
        if os.path.isdir(srcfile):
            copyfiles(srcfile, dstfile, pairs, srcprj, callback, noswig)
            continue
        
        if has_i and (fn==srcprj+".i" or fn.startswith("test"+srcprj)): continue
        
        if not os.path.exists(dstfile) and callback(fn, pairs):
            if not os.path.exists(dstdir): os.makedirs(dstdir)
            open(dstfile, "wb").write(open(srcfile, "rb").read())
            isutf8 = False
            
            try:
                text = open(dstfile).read()
            except UnicodeDecodeError:
                try:
                    text = open(dstfile,'r',-1,'utf-8').read()
                    isutf8 = True
                except UnicodeDecodeError:
                    print("* Fail to read '%s' as utf-8 encoding." % (dstfile,))
                    continue
                
            newtext = multi_replace(text, pairs)
            if newtext != text:
                try:
                    if (isutf8):
                        open(dstfile, 'w',-1,'utf-8').write(newtext)
                        print('[replaced] %s [utf-8]' % (dstfile,))
                    else:
                        open(dstfile, 'w').write(newtext)
                        print('[replaced] %s' % (dstfile,))
                except UnicodeDecodeError:
                    open(dstfile, 'w',-1,'utf-8').write(newtext)
                    print('[replaced] %s [utf-8]' % (dstfile,))
            else:
                print('[created] %s' % (dstfile,))

def makeproj(prjname, pkgname, srcprj, srcpkg, noswig):
    rootpath = os.path.abspath('..')
    basepath = os.path.join(rootpath, 'source', srcpkg, srcprj)
    pkgpath  = os.path.join(rootpath, 'source', pkgname)
    dstdir  = os.path.join(pkgpath, prjname)
    
    if prjname == '':
        print("Need input the project name.")
        return
    if not os.path.exists(basepath):
        print("\nPlease input a valid exists template project name."
              "\n\'%s\' does not exist." % (basepath,))
        return
    
    if not os.path.exists(pkgpath):
        os.makedirs(pkgpath)
        srcmk = os.path.join(rootpath, 'source', srcpkg, 'Makefile')
        if os.path.exists(srcmk):
            dstmk = os.path.join(pkgpath, 'Makefile')
            open(dstmk, "w").write(open(srcmk).read())
            print('%s [created]' % (dstmk,))

    pairs = {srcprj:prjname, srcpkg:pkgname}
    
    def matchfile(filename, pairs):
        if filename.find("_wrap.cxx") > 0 or filename.find("_wrap.h") > 0:
            return False
        return True
    copyfiles(basepath, dstdir, pairs, srcprj, matchfile, noswig)

    basepath = os.path.join(rootpath, 'interface', srcpkg, srcprj)
    dstdir  = os.path.join(rootpath, 'interface', pkgname, prjname)
    intpairs = pairs
    intpairs["78d30c77-e0f0-48a3-a489-dd4327759c27"] = str(uuid.uuid1())
    intpairs["94071767-ba6b-4769-9eb4-2ebf469289f3"] = str(uuid.uuid1())
    intpairs["feefc399-29f2-4354-8eeb-048d4cf56567"] = str(uuid.uuid1())
    copyfiles(basepath, dstdir, intpairs, srcprj, matchfile, noswig)

    def matchproj(filename, pairs):
        if ".user" in filename: return False
        for key in pairs.keys():
            if filename.startswith(key + '_') or \
               filename.startswith(key + '.'): return True
        return False
    projects = os.path.join(rootpath, 'projects')
    copyfiles(projects, projects, pairs, srcprj, matchproj, noswig)

if __name__=="__main__":
    def inputparam(index, prompt, default=''):
        if len(sys.argv) > index: ret = sys.argv[index]
        else: ret = raw_input(prompt)
        if ret == '': ret = default
        return ret
    
    prjname = inputparam(1, 'New project name: ')
    pkgname = inputparam(2, 'Package name of the new project (default: example): ', 'example')
    srcprj  = inputparam(3, 'Template (exists) project name (default: pltempl): ', 'pltempl')
    srcpkg  = inputparam(4, 'Package name of the template project (default: example): ', 'example')
    useswig = inputparam(5, 'Need swig (y/n) ? (default: n): ', 'n')
    
    makeproj(prjname, pkgname, srcprj, srcpkg, 'n' in useswig)
    if len(sys.argv) < 3: raw_input("Press <ENTER> to end.")
