#!/usr/bin/env python
import sys, os

def options(opt):
    pass

def configure(cfg):
    pass

def build(bld):
    # only export include path, header only lib.
    bld(target          = 'rant',
        export_includes = '.')

    # install headers
    for header in bld.path.ant_glob('rant/**/*.(h)'):
        bld.install_as('${PREFIX}/include/%s' % header.path_from(bld.path), header)
