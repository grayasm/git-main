# https://git-scm.com/docs/user-manual#creating-good-commit-messages
#
# Use git-commit with a single short (<50 characters) line summarizing
#     the change, followed by a blank line and then a more thorough
#     description.


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

# show what wil be committed (HEAD against the index file)
git diff --cached
