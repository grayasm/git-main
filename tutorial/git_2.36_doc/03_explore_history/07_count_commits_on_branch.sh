# https://git-scm.com/docs/user-manual#counting-commits-on-a-branch
#
# Suppose you want to know how many commits you’ve made on a branch since
# it diverged from origin:

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
git branch -D v.2023-04-04_1837

# checkout clean
git switch -c v.2023-04-04_1837 staging/v.2023-04-04_1837

# counting the number of commits on a branch
git log --pretty=oneline main..v.2023-04-04_1837 | wc -l
#2

git rev-list main..v.2023-04-04_1837 | wc -l
#2
