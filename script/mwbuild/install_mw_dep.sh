#!/bin/bash

set -x

if [ `id -u` != 0 ]; then
    echo "you must be root"
    exit
fi

dnf group install "Development Tools"

dnf install subversion-devel    \
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
