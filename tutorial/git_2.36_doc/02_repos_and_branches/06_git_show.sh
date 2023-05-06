# https://git-scm.com/docs/user-manual#understanding-commits
#
# git show    --to show the most recent commit on the current branch
#               use git show.
#
# man git-show

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd

printf "\nList local branches with: git branch\n"

git branch

printf "\nShow last commit with: git show\n"

git show
