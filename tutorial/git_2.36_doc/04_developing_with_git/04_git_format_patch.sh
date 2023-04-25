# https://git-scm.com/docs/user-manual#creating-good-commit-messages
#
# Use git-commit with a single short (<50 characters) line summarizing
#     the change, followed by a blank line and then a more thorough
#     description.
#
# Use git-format-patch to turn a commit into email, and it uses the title
#     on the Subject line and the rest of the commit in the body.


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

git commit -m 'adding main.cpp

Added main.cpp as an example of how to use:
git commit -m
with a multi line comment.'



# change main.cpp to have new history
sed -i '/printf/a \  printf("%s\\n", "added on 2023-04-06 12:00:00");' main.cpp

# show difference between working tree and the index file
git diff

# create a commit
git add main.cpp
git commit -m 'change main.cpp'

# show the multi line comment
git log

# https://initialcommit.com/blog/git-format-patch
# By default when you run the standard git format-patch <commit>, a patch
# will be created for each commit starting at the one you specified with
# <commit>, up until the current HEAD is reached. Therefore, you'll usually
# end up with more than 1 patch being created, unless you start generating
# at HEAD^, which is the commit previous to the currently checked out HEAD.
git format-patch -1 HEAD^

cat 0001-adding-main.cpp.patch

# clean up
cd ..
# ls -laRv project
rm -rf project
