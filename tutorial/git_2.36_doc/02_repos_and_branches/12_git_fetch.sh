# https://git-scm.com/docs/user-manual#Updating-a-repository-With-git-fetch
#
# git fetch    --the git-fetch command, with no arguments, will update all of
#                the remote tracking branches to the latest version found in
#                the original repository.
#                It will not touch any of your own branches - not even the
#                "master" branch that was created for you on clone.
#
# man git-fetch


if [ ! -d git-playground ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

# prepare repository first (clean up)
git switch main


# update
git fetch origin


# to see the repo names that can be fetched use
git remote -v
