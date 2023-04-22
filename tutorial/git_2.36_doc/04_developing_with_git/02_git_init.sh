# https://git-scm.com/docs/user-manual#creating-a-new-repository
#
# Use git-init to create a new repository


if [ -d project ]; then
	rm -rfv project
fi

mkdir project
cd project
git init

cd ..
ls -laRv project
rm -rfv project
