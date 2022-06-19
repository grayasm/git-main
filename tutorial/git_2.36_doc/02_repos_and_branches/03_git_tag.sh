# Tags like heads are references into the project's history, and can
# be listed using the git-tab command.

if [ ! -d "git-playground" ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

echo "list current directory" && pwd

echo "git tag -l"
git tag -l
