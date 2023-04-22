# https://git-scm.com/docs/user-manual#making-a-release
#
# Use git-archive to create a tar or zip archive from any
#     version of a project
#
# man git-archive


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
git branch -D v.2023-04-06_0500

# checkout clean
git switch -c v.2023-04-06_0500 staging/v.2023-04-06_0500


# zip the project source code
git archive -o latest.tar.gz --prefix=project/ HEAD

tar -ztf latest.tar.gz 
# project/
# project/.gitignore
# project/LICENSE
# project/README.md
# project/main.cpp

# clean up
rm -v latest.tar.gz

# git versions older than 1.7.7 don't know about tar.gz
# you'll need to use gzip explicitly
git archive --format=tar --prefix=project/ HEAD | gzip >latest.tar.gz

# clean up
rm -v latest.tar.gz

# see the diff between the latest 2 branches
git diff v.2023-04-04_1837 v.2023-04-06_0500

# diff --git a/main.cpp b/main.cpp
# index 8355082..14b9a5d 100644
# --- a/main.cpp
# +++ b/main.cpp
# @@ -8,5 +8,6 @@ int main()
#    printf("%s\n", "main at 2023-04-04 18:37:00");
#    printf("%s\n", "line at 2023-04-04 18:47:00");
#    printf("%s\n", "line at 2023-04-04 18:48:00");
# +  printf("%s\n", "line at 2023-04-06 05:42:00");
#    return 0;
#  }

# gzip and save the diff
git diff v.2023-04-04_1837 v.2023-04-06_0500 | gzip -9 > patch.gz

# clean up
rm patch.gz

# only commits since previous branch
git log --no-merges v.2023-04-06_0500 ^v.2023-04-04_1837

# commit dc4a598e3e826626ed1a14ca330ba065025c701b (HEAD -> v.2023-04-06_0500)
# Author: Mihai Vasilian <grayasm@gmail.com>
# Date:   Thu Apr 6 05:43:01 2023 +0200
#
#     change at 2023-04-06 05:42

# only commits since previous branch (short output)
git shortlog --no-merges v.2023-04-06_0500 ^v.2023-04-04_1837

# Mihai Vasilian (1):
#       change at 2023-04-06 05:42


git diff --stat --summary -M v.2023-04-04_1837 v.2023-04-06_0500

#  main.cpp | 1 +
#  1 file changed, 1 insertion(+)
