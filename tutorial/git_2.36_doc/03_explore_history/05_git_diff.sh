# https://git-scm.com/docs/user-manual#generating-diffs
#
# Generate diffs between any two revision using git-diff
#
# man git-diff
# man git-format-patch


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
git diff staging/v.2022-07-11_1520..staging/v.2022-08-24_1440

# generate instead a set of patches using git-format-patch
git format-patch staging/v.2022-07-11_1520..HEAD

# patch files should not be commited
echo -e "\n!!!!! DO NOT COMMIT THESE .patch FILES !!!!!\n"
git status .

# clean up
rm -v 00*.patch
