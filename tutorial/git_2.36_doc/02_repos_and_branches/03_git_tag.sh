# https://git-scm.com/docs/user-manual#how-to-check-out
#
# Tags like heads are references into the project's history, and can
# be listed using the git tag command.

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd

printf "\ngit tag -l\n"

git tag -l
