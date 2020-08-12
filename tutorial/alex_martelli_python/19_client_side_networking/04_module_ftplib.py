#!/usr/bin/env python3
# -*- coding: utf-8 -*-


# https://docs.python.org/3/library/ftplib.html#module-ftplib
from ftplib import FTP


ftp = FTP('vasilian.net')       # connect to host, default port
ftp.login()                     # user anonymous, passwd anonymous@

ftp.cwd('Gtk-Engines')          # change into "debian" directory
ftp.retrlines('LIST')           # list directory contents

ftp.retrbinary('RETR README', open('README', 'wb').write)

ftp.quit()
