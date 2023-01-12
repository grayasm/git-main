# https://git-scm.com/docs/user-manual#viewing-old-file-versions
#
# You can always view and old version of a file by just checking out the
# correct revision first. But sometimes it is more convenient to be able
# to view it with this command:
#
# man git-show

if [ ! -d git-playground ]; then
    git clone  https://github.com/grayasm/git-playground.git
    cd git-playground
    git remote add staging https://github.com/grayasm/git-forkground.git
    git fetch staging
    cd ..
fi

cd git-playground

# switch to main before clean up
git switch main

# this needs new branch here ---
# delete --force local branch first
git branch -D v.2022-08-24_1440

# checkout clean
git switch -c v.2022-08-24_1440 staging/v.2022-08-24_1440

# Before the colon may be anything that names a commit, and after it
# may be any path to a file tracked by Git.
git show b33d6f761181:main.cpp
git show 65da2cf11a8d:main.cpp
git show HEAD:main.cpp
