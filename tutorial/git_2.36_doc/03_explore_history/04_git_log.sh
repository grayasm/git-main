# https://git-scm.com/docs/user-manual#browsing-revisions
#
# git log can show a list of commits.

# man git-log


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

# show commits since stable-1 tag (exclusive) up to HEAD
git log stable-1..


# show commits between tags stable-1 (exclusive) and stable-2 (inclusive).
git log stable-1..stable-2

# show commits from the last 2 weeks
git log --since="2 weeks ago"

# show only commits that modified file main.cpp
git log main.cpp

# show also the patches (see --pretty)
git log -p
