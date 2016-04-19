#
#
cmake_minimum_required (VERSION 2.8)

message ("--------------------------------------------------------")

# cap 4.7 Policies
cmake_policy (VERSION 2.6)
cmake_policy (SET CMP0002 OLD)

# For example, policy CMP0003 removes extra link directories that used
# to be included when new behavior is used. While incrementally updating
# a project it may be difficult to build a particular target with
# the new behavior but all other targets are okay.

cmake_policy (PUSH)
cmake_policy (SET CMP0003 OLD) # use old-style link for now
add_executable (app1  file1.c)
cmake_policy (POP)

# For a warning about a policy one may check whether this is the case
# by adding: cmake_policy (SET CMP<NNNN> NEw)

# One may suppress all instances of a warning CMP<NNNN> by adding:
# cmake_policy (SET CMP<NNNN> OLD)



message ("--------------------------------------------------------")
