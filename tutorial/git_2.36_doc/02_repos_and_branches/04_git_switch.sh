# https://git-scm.com/docs/user-manual#how-to-check-out
#
# Create a new branch head pointing to one of these versions and check it out
# using git switch
#
# man git-switch

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd

git switch -c new "origin/v.2022-06-19_1040"