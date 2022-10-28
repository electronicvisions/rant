#!/usr/bin/env python
import sys, os
from waflib.extras.test_base import summary
from waflib.extras.symwaf2ic import get_toplevel_path

def depends(dep):
    dep('code-format')

def options(opt):
    opt.load('doxygen')
    opt.load('test_base')
    opt.recurse('test')

def configure(cfg):
    cfg.load('doxygen')
    cfg.load('test_base')
    cfg.recurse('test')

def build(bld):
    # install headers
    bld.install_files(
        dest = '${PREFIX}/include',
        files = bld.path.ant_glob('**/*.(h|hpp)', excl='test'),
        name = 'rant_header',
        relative_trick = True
    )

    # only export include path, header only lib.
    bld(target          = 'rant',
        export_includes = '.',
        depends_on = 'rant_header',
    )

    # build documentation
    bld(features='doxygen',
        doxyfile=bld.root.make_node(os.path.join(get_toplevel_path(), "code-format/doxyfile")),
        install_path='doc/rant',
        pars={
            "PROJECT_NAME": "\"Ranged Number Types\"",
            "INPUT": os.path.join(get_toplevel_path(), "rant/rant")
                     + " " + os.path.join(get_toplevel_path(), "rant/doc")
        })

    bld.recurse('test')

    bld.add_post_fun(summary)
