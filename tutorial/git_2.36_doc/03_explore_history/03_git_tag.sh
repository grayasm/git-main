# https://git-scm.com/docs/user-manual#creating-tags
#
# git tag <tagname> <commit>    --use git tag to create, list, delete or verify
#                                 a tag object signed with GPG
#
# man git-tag


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


# create 2 tags
git tag stable-1 b33d6f7611
git tag stable-2 6ea4aed6e6

# show the tags
git log --oneline --all --decorate --graph
