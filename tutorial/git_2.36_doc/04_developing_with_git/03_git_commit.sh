# https://git-scm.com/docs/user-manual#how-to-make-a-commit
#
# git diff --cached    difference between HEAD and the index; what
#                      will be committed if you ran "commit" now
# git diff             difference between the index file and your
#                      working directory; changes that would not
#                      be included if you ran "commit" now
# git diff HEAD        difference between HEAD and working tree; what
#                      would be committed if you ran "commit -a" now
# git status           a brief per-file summary of the above


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

# show what wil be committed (HEAD against the index file)
git diff --cached

# change main.cpp to have new history
sed -i '/printf/a \  printf("%s\\n", "added on 2023-04-06 12:00:00");' main.cpp

# show difference between working tree and the index file
git diff

# create a commit
git add main.cpp
git commit -m 'change main.cpp'


sed -i '/12:00:00/a \  printf("%s\\n", "added on 2023-04-06 12:12:00");' main.cpp

# commit -a  will update the index file and create a commit, e.g.
# git add
# git commit
git commit -a -m 'change main.cpp'


# show the log message and the textual diff
git show


# clean up
cd ..
# ls -laRv project
rm -rf project
