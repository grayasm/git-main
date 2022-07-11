# https://git-scm.com/docs/user-manual#naming-commits
#
# Use git-show to show various type of objects (commits)
#
# man git-show



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


git show HEAD~3           # 3rd revision behind HEAD "change - 2022-07-11_1544"
git show HEAD~2           # 2nd revision behind HEAD "change - 2022-07-11_1545"
git show HEAD~1           # 1st revision behind HEAD "change - 2022-07-11_1546"
git show HEAD             # show HEAD revision       "change - 2022-07-11_1547"

git show ec97f63          # show HEAD revision       "change - 2022-07-11_1547"