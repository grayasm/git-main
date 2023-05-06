# https://git-scm.com/docs/user-manual#showing-commits-unique-to-a-branch
#
# Use git-show-ref to list all heads (branches) in a repository
#
# man git-show-ref

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

# list all heads in this repository
git show-ref --heads
# 1bf251515f6c17c9f4fd2faae9063b8a68fc0e38 refs/heads/main
# 74531c7d48f4cfcdbd6c82777c0929b7542a983d refs/heads/v.2023-04-04_1837
# 74531c7d48f4cfcdbd6c82777c0929b7542a983d refs/heads/v.2023-04-06_0500

# remove main from output with the help of cut and grep
git show-ref --heads | cut -d' ' -f2 | grep -v '^refs/heads/main'
# refs/heads/v.2023-04-04_1837
# refs/heads/v.2023-04-06_0500
