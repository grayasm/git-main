# Create a new branch head pointing to one of these versions and check it out
# using git-switch.

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

echo "\nList current directory" && pwd


echo "\nCreate local <branch> tracking origin/<branch>"

git switch -c new "origin/v.2022-06-19_1040"