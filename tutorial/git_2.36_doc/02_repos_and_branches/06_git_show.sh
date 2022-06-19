# https://git-scm.com/docs/user-manual#understanding-commits
#
# To show the most recent commit on the current branch use git show.

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd

printf "\ngit branch\n"

git branch

printf "\ngit show\n"

git show