#!/usr/bin/env python3
# -*- coding: utf-8 -*-


'''
sitecustomize is the module that each site’s installation can optionally use
for further site-specific customization beyond site ’s tasks. It is generally
best not to edit site.py, since any Python upgrade or reinstallation might
overwrite such customizations. sitecustomize ’s main task can be to set the
correct default encoding for the site. A Western European site, for example,
may choose to call from sitecustomize sys.setdefaultencoding('iso-8859-1') .
'''
