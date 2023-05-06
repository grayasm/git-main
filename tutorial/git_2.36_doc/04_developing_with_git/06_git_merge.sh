# https://git-scm.com/docs/user-manual#how-to-merge
#
# Continue from here.....




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
git branch -D v.2022-07-11_1520

# checkout clean
git switch -c v.2022-07-11_1520 staging/v.2022-07-11_1520

