#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# pag. 250, The filecmp Module
#           The filecmp module supplies functionality to compare files and
#           directories.


#    https://pymotw.com/3/filecmp/
import os
import filecmp
import shutil


def mkfile(filename, body=None):
    with open(filename, 'w') as f:
        f.write(body or filename)
    return


def make_example_dir(top):
    if not os.path.exists(top):
        os.mkdir(top)
    curdir = os.getcwd()
    os.chdir(top)

    os.mkdir('dir1')
    os.mkdir('dir2')

    mkfile('dir1/file_only_in_dir1')
    mkfile('dir2/file_only_in_dir2')

    os.mkdir('dir1/dir_only_in_dir1')
    os.mkdir('dir2/dir_only_in_dir2')

    os.mkdir('dir1/common_dir')
    os.mkdir('dir2/common_dir')

    mkfile('dir1/common_file', 'this file is the same')
    mkfile('dir2/common_file', 'this file is the same')

    mkfile('dir1/not_the_same')
    mkfile('dir2/not_the_same')

    mkfile('dir1/file_in_dir1', 'This is a file in dir1')
    os.mkdir('dir2/file_in_dir1')

    os.chdir(curdir)
    return


if __name__ == '__main__':
    os.chdir(os.path.dirname(__file__) or os.getcwd())
    make_example_dir('example')
    make_example_dir('example/dir1/common_dir')
    make_example_dir('example/dir2/common_dir')

    print(filecmp.cmp('example/dir1/common_file',
                      'example/dir2/common_file'))  # True

    print(filecmp.cmp('example/dir1/common_file',
                      'example/dir2/common_file',
                      shallow=False))               # True

    print(filecmp.cmp('example/dir1/not_the_same',
                      'example/dir2/not_the_same'))  # True
    print(filecmp.cmp('example/dir1/not_the_same',
                      'example/dir2/not_the_same',   # False
                      shallow=False))

    print(filecmp.cmp('example/dir1/file_only_in_dir1',
                      'example/dir1/file_only_in_dir1'))  # True

    # Determine the items that exist in both directories
    d1_contents = set(os.listdir('example/dir1'))
    d2_contents = set(os.listdir('example/dir2'))
    common = list(d1_contents & d2_contents)
    common_files = [
        f
        for f in common
        if os.path.isfile(os.path.join('example/dir1', f))
        ]
    print('Common files:', common_files)  # ['file_in_dir1',
                                          #  'common_file',
                                          #  'not_the_same']
    # Compare the directories
    match, mismatch, errors = filecmp.cmpfiles(
        'example/dir1',
        'example/dir2',
        common_files,
    )
    print('Match       :', match)     # ['common_file', 'not_the_same']
    print('Mismatch    :', mismatch)  # ['file_in_dir1']
    print('Errors      :', errors)    # []

    # Compare directories
    dc = filecmp.dircmp('example/dir1', 'example/dir2')
    dc.report()        # Identical files : ['common_file', 'not_the_same']
                       # Common subdirectories : ['common_dir']
                       # Common funny cases : ['file_in_dir1']

    shutil.rmtree('example')
