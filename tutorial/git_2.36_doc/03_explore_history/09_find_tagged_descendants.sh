# https://git-scm.com/docs/user-manual#finding-tagged-descendants
#
# Use git-name-rev to give a commit a name based on any tag it finds
#     pointing to one of the commit's descendants
#
# Use git-describe to name the revision using a tag on which the
#     given commit is based
#
# Use git-merge-base to verify whether a given tagged version contains
#     a given commit
#
# Use git-show-branch to list all commits reachable from its arguments
#     in a tree like output
#
# man git-name-rev
# man git-describe
# man git-merge-base
# man git-show-branch


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

# list all tags on this branch
git tag -l
# v.2023-04-04_1837_tag

# the tag v.2023-04-04_1837_tag should have been pushed to staging
gitk v.2023-04-04_1837_tag

# You can use git-name-rev[1], which will give the commit a name based
# on any tag it finds pointing to one of the commit’s descendants:
git name-rev --tags 74531c7d48f4cfcdbd6c82777c0929b7542a983d
# 74531c7d48f4cfcdbd6c82777c0929b7542a983d tags/v.2023-04-04_1837_tag


git describe --tags 74531c7d48f4cfcdbd6c82777c0929b7542a983d
# v.2023-04-04_1837_tag


git merge-base 74531c7d48f4cfcdbd6c82777c0929b7542a983d main
# 1bf251515f6c17c9f4fd2faae9063b8a68fc0e38


git log --pretty=oneline
# 74531c7d48f4cfcdbd6c82777c0929b7542a983d (HEAD -> v.2023-04-04_1837, tag: v.2023-04-04_1837_tag) change at 2023-04-04 18:48
# 6084408e2fc8bcc0b7de16563342dae20c42aa4d change at 2023-04-04 18:47
# 1bf251515f6c17c9f4fd2faae9063b8a68fc0e38 (main) 3rd change                 <-- the merge point between main and this branch
# c1391d9bef4909dedab4df560f442f2bc7151133 2nd change at 2023-04-04 18:35:00
# fe218caea78f0b34b4957d40c7c87023618e9dc8 1st change at 2023-04-04 18:34:00
# 604c435e7802cff338159e10cdf2a72fbbd6ee07 main at 2023-04-04
# ee5914091ce560174a0d38db16112de93bf9ff64 (origin/main, origin/HEAD) Update main.cpp
# 799e5f05dd28ac8fe3273cb198efeb316c0f3994 Merge pull request #1 from grayasm/v.2022-06-19_1015
# da7cdb2d1a37a540983f4c89d17475e10981cc40 (origin/v.2022-06-19_1015) change for branch v.2022-06-19_1005
# ef91c56422203e4da4db62d4e959aef09dbcc437 add main.cpp
# 08488ba193c0e463c8604d29817b0b0f247589f4 Initial commit


# This will output all commits after main until 74531.. (main, 74531]
git log main..74531c7d48f4cfcdbd6c82777c0929b7542a983d


git show-branch 74531c7d48f4cfcdbd6c82777c0929b7542a983d main
# ! [74531c7d48f4cfcdbd6c82777c0929b7542a983d] change at 2023-04-04 18:48
#  ! [main] 3rd change
# --
# +  [74531c7d48f4cfcdbd6c82777c0929b7542a983d] change at 2023-04-04 18:48
# +  [74531c7d48f4cfcdbd6c82777c0929b7542a983d^] change at 2023-04-04 18:47
# ++ [main] 3rd change
