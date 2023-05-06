# https://git-scm.com/docs/user-manual#manipulating-branches
#
# git branch -D <branch>    --delete the branch <branch> irrespective of
#                             its merged status.
#
# man git-branch


if [ ! -d git-playground ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

# prepare repository first (clean up)
git switch main
git branch -D v.2022-06-19_1040

# create new local branch to track origin/branch
git switch -c v.2022-06-19_1040  origin/v.2022-06-19_1040

# change main.cpp to increase history
sed -i '/printf/a \    printf("%s\\n", "added on 2022-06-19_1440");' main.cpp

# commit but don't push
git commit -m 'change' main.cpp

# you cannot delete the current branch; must switch away first; use -f to force;
git switch main

# force delete a local branch
git branch -D v.2022-06-19_1040
