--------------------------------------------------------------------------------
                              Git 2.36.1 User Manual
                              https://git-scm.com/docs/user-manual
--------------------------------------------------------------------------------

git clone https://github.com/grayasm/git-playground        # clone a repo

git branch                             # list all local branches
  main
* new

git checkout -b v.2022-06-19_1040      # create and switch to new branch

git switch main                        # switch from local branch back to main

git branch -d v.2022-06-19_1040        # delete local branch

git branch -D v.2022-06-19_1040        # delete local branch with --force

git switch v.2022-06-19_1040           # switch from main to local branch

git commit -m "message" .              # commit changes

git push -u origin v.2022-06-19_1040   # push branch to origin
                                       # use -u to to create branch upstream

git branch -r                          # show remote branches
  origin/HEAD -> origin/main
  origin/main
  origin/v.2022-06-19_1015
  origin/v.2022-06-19_1040

git switch -c v.2022-06-19_1040  origin/v.2022-06-19_1040  # create new local
                                                           # branch and track
                                                           # the origin/branch

git switch -c temp origin/v.2022-06-19_1040                # create new "temp"
                                                           # branch and track
                                                           # the origin/branch

git reset --hard origin/v.2022-06-19_1015                  # reset "temp" branch
                                                           # to point to another
                                                           # origin/branch

git show                               # show the last commit

git branch v.2022-06-19_1500           # create a new branch from current branch
git switch v.2022-06-19_1500           # must switch explicitly to be on it

git switch --detach 0b80141b7313659de4bda6ffe13e01188d519f9e
                                       # set HEAD as detached and checkout
                                       # revision 0b80141 which comes from
                                       # remote  origin/v.2022-06-19_1720

git switch main                        # prepare for git fetch command

git fetch origin                       # update all from remote origin

git status                             # after fetch, status shows you're behind
# origin/HEAD -> origin/main       (up to date)
# origin/main                      (up to date)
# *main                            (behind origin/main by 1 commit)

git merge origin/main                  # merge to be up to date

git pull                               # does git-fetch & git-merge combination

git remote                             # list the remotes repositories whose
                                       # branches you track

git remote -v                          # verbose
origin  https://github.com/grayasm/git-playground.git (fetch)
origin  https://github.com/grayasm/git-playground.git (push)


git log --all --decorate --oneline --graph        # shows a pretty log
                                                  # aliased as "gitlog"

                                                  # add another remote repo
git remote add staging https://github.com/grayasm/git-forkground.git

git fetch staging                      # fetch all branches from staging

git remote -v
origin  https://github.com/grayasm/git-playground.git (fetch)
origin  https://github.com/grayasm/git-playground.git (push)
staging https://github.com/grayasm/git-forkground.git (fetch)
staging https://github.com/grayasm/git-forkground.git (push)


git bisect start                      # start bisecting
git bisect good 60d7841               # one good revision from the past
git bisect bad  HEAD                  # last revision HEAD is bad

Bisecting: 3 revisions left to test after this (roughly 2 steps)
# [2692282bc66a7ab9014d734316210403064e3412] change - 2022-07-11_1543
                                      # compile test and if not successful:
git bisect bad                        # repeat until it find the bad revision:

841857d55bcf16a8762aeb44f04aba9bf06f7479 is the first bad commit

git show                             # to see the bad commit
git bisect reset                     # to go back to HEAD
