# https://git-scm.com/docs/user-manual#using-bisect
#
# git bisect    --use git-bisect to perform a brute-force search through
#                 the project's history to find the particular commit that
#                 caused the problem
#
# man git-bisect
#
# use:
# git bisect start
# git bisect good 60d7841
# git bisect bad HEAD
# Bisecting: 3 revisions left to test after this (roughly 2 steps)
# [2692282bc66a7ab9014d734316210403064e3412] change - 2022-07-11_1543
# --compile test and if not successful type:
# git bisect bad
# Bisecting: 0 revisions left to test after this (roughly 1 step)
# [ecb6e5c8913b744dda5d45805701ffa595eb54b3] change - 2022-07-11_1542
# --continue to test and repeat until it finds the first bad revision:
# 841857d55bcf16a8762aeb44f04aba9bf06f7479 is the first bad commit
# commit 841857d55bcf16a8762aeb44f04aba9bf06f7479
#
# git bisect reset
#


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
git branch -D v.2022-07-11_1520

# checkout clean
git switch -c v.2022-07-11_1520 staging/v.2022-07-11_1520

git bisect start
git bisect good 60d7841
git bisect bad HEAD
git bisect visualize           # only to see the range in gitk
git bisect bad
git bisect visualize
git bisect bad
git bisect visualize
git bisect bad
git show


# to reset to HEAD:
# git bisect reset
