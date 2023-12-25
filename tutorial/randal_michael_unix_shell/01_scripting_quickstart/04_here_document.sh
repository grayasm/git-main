#!/bin/bash

# https://tldp.org/LDP/abs/html/here-docs.html

# A 'here document' is a shell script inside a shell script

a_here_doc=$(cat <<EOF
    echo "echo from inside a here document"
EOF
)

eval $a_here_doc
