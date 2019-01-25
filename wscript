#!/usr/bin/env python
import sys, os
from waflib.extras.test_base import summary

def options(opt):
    opt.load('test_base')

def configure(cfg):
    cfg.load('test_base')

def build(bld):
    # only export include path, header only lib.
    bld(target          = 'rant',
        export_includes = '.')

    # install headers
    for header in bld.path.ant_glob('rant/**/*.(h)'):
        bld.install_as('${PREFIX}/include/%s' % header.path_from(bld.path), header)

    bld.add_post_fun(summary)
