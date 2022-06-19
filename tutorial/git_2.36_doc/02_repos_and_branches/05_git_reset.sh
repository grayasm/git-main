# https://git-scm.com/docs/user-manual#how-to-check-out
#
# You can modify the current branch to point to another branch instead
# using git reset

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

printf "\nList current directory:\n" && pwd

git switch -c new "origin/v.2022-06-19_1040"

git reset --hard origin/v.2022-06-19_1015

# Note that if the current branch head was your only reference to a particular
# point in history, then resetting that branch may leave you with no way to find
# the history it used to point to;
# so use this command carefully.
