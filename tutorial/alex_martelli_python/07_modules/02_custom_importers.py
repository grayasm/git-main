#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# *** Custom Importers ***
#     An advanced, rarely needed functionality that Python offers is the
#     ability to change the semantics or some or all import and from
#     statements.

import sys
import types


class ImporterAndLoader(object):
    '''importer and loader functionality is usually in a single class'''
    fake_path = '!dummy!'

    def __init__(self, path):
        '''we only handle our own fake-path marker'''
        if path != self.fake_path:
            raise ImportError

    def find_module(self, fullname):
        '''we don't even try to handle any qualified module-name'''
        if '.' in fullname:
            return None
        return self

    def load_module(self, fullname):
        print ('NOTE: module %r not written yet' % fullname)
        # mod = sys.modules[fullname] = new.module(fullname)
        mod = sys.modules[fullname] = types.ModuleType(fullname)
        mod.__file__ = 'dummy<%s>' % fullname
        mod.__loader__ = self
        return mod


# add the class to the hook and its fake-path marker to the path
sys.path_hooks.append(ImporterAndLoader)
sys.path.append(ImporterAndLoader.fake_path)

if __name__ == '__main__':      # self-test when run as main script
    import missing_module       # import a simple missing module
    print (sys.modules.get('missing_module'))    # ... should succeed
    # check that we don't deal with importing from packages
    try:
        import missing_module.sub_module
    except ImportError:
        pass
    else:
        print ('Unexpected:', sys.modules.get('missing_module.sub_module'))
