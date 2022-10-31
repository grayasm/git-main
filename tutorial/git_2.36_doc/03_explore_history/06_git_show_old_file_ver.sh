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

# delete --force local branch first
git branch -D v.2022-08-24_1440

# checkout clean
git switch -c v.2022-08-24_1440 staging/v.2022-08-24_1440

# git diff 2 branches
git diff staging/main..staging/v.2022-08-24_1440
