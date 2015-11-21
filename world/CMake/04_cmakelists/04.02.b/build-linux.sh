#!/bin/bash

MAK="Unix Makefiles"
CBN="CodeBlocks - Ninja"               # CodeBlocks project files
CBX="CodeBlocks - Unix Makefiles"      # CodeBlocks project files
ECN="Eclipse CDT4 - Ninja"             # Eclipse CDT 4.0 project files
ECX="Eclipse CDT4 - Unix Makefiles"    # Eclipse CDT 4.0 project files
KD3="KDevelop3"                        # KDevelop 3 project files
K3X="KDevelop3 - Unix Makefiles"       # KDevelop 3 project files
S2N="Sublime Text 2 - Ninja"           # Sublime Text 2 project files
S2X="Sublime Text 2 - Unix Makefiles"  # Sublime Text 2 project files

cmake -G "$MAK" ../04.02/
