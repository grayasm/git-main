# https://git-scm.com/docs/user-manual#checking-for-equal-branches
#
# Use git-rev-list to list the commits objects in the reverse order
# Use git log with ... to select all commits reachable from either
#     one reference or the other, but not both
#
# man git-rev-list
# man git-log

if [ ! -d git-playground ]; then
	git clone  https://github.com/grayasm/git-playground.git
	cd git-playground
	git remote add staging https://github.com/grayasm/git-forkground.git
	git fetch staging
	cd ..
fi

cd git-playground

# switch to main before clean up
git switch main

# delete --force local branch first
git branch -D v.2023-04-04_1837

# checkout clean
git switch -c v.2023-04-04_1837 staging/v.2023-04-04_1837


# Suppose you want to check whether two branches point at the same point in history.
git diff main..v.2023-04-04_1837

# In theory, however, it’s possible that the same project contents
# could have been arrived at by two different historical routes.
# You could compare the object names:
git rev-list main
# 1bf251515f6c17c9f4fd2faae9063b8a68fc0e38
# c1391d9bef4909dedab4df560f442f2bc7151133
# fe218caea78f0b34b4957d40c7c87023618e9dc8
# 604c435e7802cff338159e10cdf2a72fbbd6ee07
# ee5914091ce560174a0d38db16112de93bf9ff64
# 799e5f05dd28ac8fe3273cb198efeb316c0f3994
# da7cdb2d1a37a540983f4c89d17475e10981cc40
# ef91c56422203e4da4db62d4e959aef09dbcc437
# 08488ba193c0e463c8604d29817b0b0f247589f4

git rev-list v.2023-04-04_1837
# 74531c7d48f4cfcdbd6c82777c0929b7542a983d
# 6084408e2fc8bcc0b7de16563342dae20c42aa4d
# 1bf251515f6c17c9f4fd2faae9063b8a68fc0e38 <-- end of equal sequence
# c1391d9bef4909dedab4df560f442f2bc7151133
# fe218caea78f0b34b4957d40c7c87023618e9dc8
# 604c435e7802cff338159e10cdf2a72fbbd6ee07
# ee5914091ce560174a0d38db16112de93bf9ff64
# 799e5f05dd28ac8fe3273cb198efeb316c0f3994
# da7cdb2d1a37a540983f4c89d17475e10981cc40
# ef91c56422203e4da4db62d4e959aef09dbcc437
# 08488ba193c0e463c8604d29817b0b0f247589f4  <-- start of equal sequence

# ... operator selects all commits reachable from either one reference
# or the other but not both; so will return no commits when the two
# branches are equal.
git log main...v.2023-04-04_1837
