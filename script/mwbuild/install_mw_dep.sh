#!/bin/bash

set -x

yum group install "Development Tools"

yum install subversion-devel    \
            subversion-tools    \
            gcc                 \
            gcc-c++             \
            curl                \
            doxygen             \
            mesa-libGL-devel    \
            mesa-libGLU-devel   \
            xorg-x11-server-devel \
            freeglut-devel      \
            boost-devel         \
            glew-devel          \
            fontconfig-devel    \
            libXi-devel         \
            freetype-devel      \
            libXrandr-devel     \
            libXinerama-devel   \
            libXcursor-devel    \
            libXt-devel         \
            procps-ng-devel
