# https://git-scm.com/docs/user-manual#detached-head
#
# The "git switch" command normally expects a branch head, but will also
# accept an arbitrary commit when invoked with --detach; for example, you
# can check out the commit referenced by a tag.
#
# man git-switch


if [ ! -d git-playground ]; then
	git clone https://github.com/grayasm/git-playground.git
fi

cd git-playground

# prepare repository first (clean up)
git switch main
git branch -D testing

# detach HEAD from main and point to commit:
# 0b80141b7313659de4bda6ffe13e01188d519f9e
# from branch origin/v.2022-06-19_1720

git switch --detach 0b80141b7313659de4bda6ffe13e01188d519f9e

# git branch
#* (HEAD detached at 0b80141)
#  main
#  v.2022-06-19_1720

# create "testing" branch referencing detached HEAD
git switch -c testing