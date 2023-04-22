# https://git-scm.com/docs/user-manual#telling-git-your-name
#
# Use git-config to introduce yourself to git
#
# man git-config

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


git config --local user.name 'Mihai Vasilian'
git config --local user.email 'grayasm@gmail.com'

# check [user] section
cat .git/config
