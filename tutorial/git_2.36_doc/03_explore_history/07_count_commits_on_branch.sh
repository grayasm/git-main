# https://git-scm.com/docs/user-manual#counting-commits-on-a-branch
#
# git log      <branch>..<branch>
# git rev-list <branch>..<branch>

if [ ! -d git-playground ]; then
    git clone  https://github.com/grayasm/git-playground.git
    cd git-playground
    git remote add staging https://github.com/grayasm/git-forkground.git
    git fetch staging
    cd ..
fi

cd git-playground

# switch away from dirty branch
git switch main

# remove dirty branch
git branch -D v.2022-08-24_1440

git switch -c v.2022-08-24_1440 staging/v.2022-08-24_1440

# show commits on a branch
echo "git log --pretty=oneline main..v.2022-08-24_1440"
git log --pretty=oneline main..v.2022-08-24_1440

# count the commits
echo "count the commits"
git log --pretty=oneline main..v.2022-08-24_1440 | wc -l

# alternativly you may use git rev-list
echo "git rev-list main..v.2022-08-24_1440"
git rev-list main..v.2022-08-24_1440

echo "count the commits"
git rev-list main..v.2022-08-24_1440 | wc -l
