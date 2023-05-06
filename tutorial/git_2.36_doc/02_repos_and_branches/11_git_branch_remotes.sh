# https://git-scm.com/docs/user-manual#examining-remote-branches
#
# git branch -r    --you can view the remote branches
#
# man git-branch


if [ ! -d git-playground ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList all remote branches with: git branch -r\n"

git branch -r

#  origin/HEAD -> origin/main
#  origin/main
#  origin/v.2022-06-19_1015
#  origin/v.2022-06-19_1040
#  origin/v.2022-06-19_1720
