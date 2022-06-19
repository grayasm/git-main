# https://git-scm.com/docs/user-manual#manipulating-branches
#
# To create a new branch named <branch> referencing the same point in history
# as the current branch use: git branch <branch>

if [ ! -d git-playground ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

# switch to main for clean up
git switch main

# delete local branches; will get them from remote
git branch -D v.2022-06-19_1510
git branch -D v.2022-06-19_1040


# create new local branch to track origin/branch
git switch -c v.2022-06-19_1040  origin/v.2022-06-19_1040

# change main.cpp to have new history
sed -i '/printf/a \    printf("%s\\n", "added on 2022-06-19_1440");' main.cpp

# commit the change
git commit -m 'change' main.cpp

# create a new branch referencing the same point in history as the current
# branch
git branch v.2022-06-19_1510

# must switch first to see the content; it does not switch automatically
git switch v.2022-06-19_1510