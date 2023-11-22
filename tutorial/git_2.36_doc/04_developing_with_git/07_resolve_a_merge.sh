# https://git-scm.com/docs/user-manual#resolving-a-merge
#
#


if [ ! -d git-playground ]; then
    git clone  https://github.com/grayasm/git-playground.git
    cd git-playground
    git remote add staging https://github.com/grayasm/git-forkground.git
    git fetch staging
    cd ..
fi

cd git-playground

# clean up before actual work
git switch main
git checkout .

