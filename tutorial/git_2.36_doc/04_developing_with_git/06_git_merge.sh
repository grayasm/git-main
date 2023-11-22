# https://git-scm.com/docs/user-manual#how-to-merge
#
# git merge <branchname>     -- rejoin two diverging branches of development


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
git branch -D v.2023-05-18_0934_temp
git branch -D v.2023-05-18_0934
git fetch staging

# switch to main at 2023-05-18 09:30:31
git switch --detach 866ce5e4afaefbb71b712647dac62d5bcc96b092

# create a branch at current revision
git checkout -b v.2023-05-18_0934_temp

# merge a branch into current
git merge staging/v.2023-05-18_0934

# last 3 commits are relevant
git log -n 3
