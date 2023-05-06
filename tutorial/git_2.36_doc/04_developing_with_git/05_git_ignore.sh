# https://git-scm.com/docs/user-manual#ignoring-files
#
# Use .gitignore to tell Git to ignore certain files.
#     It will apply the rules to the directory where it is found and to
#     all subdirectories in the working tree.
#
# Syntax: https://git-scm.com/docs/gitignore


if [ -d project ]; then
	rm -rfv project
fi

# create repo location
mkdir project
cd project
git init

# tell git who you are
git config --local user.name 'Mihai Vasilian'
git config --local user.email 'grayasm@gmail.com'

# add .gitignore in the top level of the working directory
cat >> .gitignore <<EOF
# Lines starting with '#' are considered comments.
# Ignore any file named foo.txt.
foo.txt
# Ignore (generated) html files,
*.html
# except foo.html which is maintained by hand.
!foo.html
# Ignore objects and archives.
*.[oa]
EOF
git add .gitignore

# make some changes
cat >> main.cpp <<EOF
#include <stdio.h>

int main()
{
  printf("%s\n", "main at 2023-04-06 11:45:00");
  return 0;
}

EOF

# update git index
git add main.cpp

git commit -m 'add main.cpp
add .gitignore'


# change main.cpp to have new history
sed -i '/printf/a \  printf("%s\\n", "added on 2023-04-06 12:00:00");' main.cpp

# show difference between working tree and the index file
git diff

# create a commit
git add main.cpp
git commit -m 'change main.cpp'

# show the multi line comment
git log

# clean up
cd ..
# ls -laRv project
rm -rf project
