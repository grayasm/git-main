# https://git-scm.com/docs/user-manual#how-to-check-out
#
# git-branch command shows you the list of branch heads


if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd
printf "\ngit branch\n"

git branch

printf "\ngit branch -r\n"

git branch -r