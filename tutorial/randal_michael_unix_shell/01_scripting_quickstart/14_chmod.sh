#!/bin/bash

# chmod permission options

# 4000      Sets user ID on execution (binaries only, not shell scripts)
# 2000      Sets group ID on execution (binaries only, not shell scripts)
# 1000      Sets the link permission to directories or sets the save-text
#           attribute for files
# 0400      Permits read by owner
# 0200      Permits write by owner
# 0100      Permits execute or search by owner
# 0040      Permits read by group
# 0020      Permits write by group
# 0010      Permits execute or search by group
# 0004      Permits read by others
# 0002      Permits write by others
# 0001      Permits execute or search by others


# Example
if [ -f test.sh ]
then
    rm -v test.sh                   # remove before creating again
fi

cat  > test.sh << EOF
#!/bin/bash
echo "User indentification:"
id
EOF

chmod u+rwx,g+rx,o+r test.sh        # owner:rwx, group:rx, others: can read
chmod 6755 test.sh                  # set a  program to always execute as
                                    # both the file owner and the
                                    # file owner's group as long as the program
                                    # is not script (good enough for now)

ls -l test.sh                       # -rwsr-sr-x. 1 mihai mihai   44 Dec 27 00:42 test.sh
                                    #    ^  ^      <- the sticky bits

source test.sh                      # uid=1000(mihai) gid=1000(mihai) groups=1000(mihai)...

rm -v test.sh                       # clean up
