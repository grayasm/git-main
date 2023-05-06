# https://git-scm.com/docs/user-manual#Finding-commits-With-given-Content
#
# See:
# man git-log
# man git-diff-tree
# man git-hash-object


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
git branch -D v.2023-04-06_0500

# checkout clean
git switch -c v.2023-04-06_0500 staging/v.2023-04-06_0500



git log --raw --abbrev=40 --pretty=oneline | grep -B 1 `git hash-object main.cpp`
# dc4a598e3e826626ed1a14ca330ba065025c701b change at 2023-04-06 05:42
# :100644 100644 83550823426ab681bfafe5145bf81bbc054cce4f 14b9a5d85a91f6c68f2f4350fd4be6d474837a28 M	main.cpp
