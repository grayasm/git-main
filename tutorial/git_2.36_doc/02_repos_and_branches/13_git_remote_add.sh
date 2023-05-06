# https://git-scm.com/docs/user-manual#fetching-branches
#
# git remote add <name> <.git address>    --to add a remote repository
#
# git remote remove <name>                --to remove a remote repository
#
#
# Important: You can also track branches from repositories other than the one
#            you cloned from, using git-remote.
#
# man git-remote


if [ ! -d git-playground ]; then
    git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

# prepare repository first (clean up)
git switch main

# remove git-forkground.git if added previously
git remote remove staging

# track branches from repositories other than the one you cloned from
git remote add staging https://github.com/grayasm/git-forkground.git

# list remote branches
git branch -r

# update the remote-tracking branches
git fetch staging
