# https://git-scm.com/docs/user-manual#how-to-check-out
#
# git branch    --git-branch command shows you the list of branch heads


if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd
printf "\nList local branches with: git branch\n"

git branch

printf "\nList remote branches with: git branch -r\n"

git branch -r
