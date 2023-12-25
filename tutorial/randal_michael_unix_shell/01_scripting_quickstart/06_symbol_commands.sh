#!/bin/bash

# ( )           Returns the enclosed command in a sub-shell
# (( ))         Evaluates and assigns value to a variable and does math in a shell
# $(( ))        Evaluates the enclosed expression
# [ ]           Same as the test command
# < >           Used for string comparison
# $( )          Command substitution
# `command`     Command substitution


# Explaining the 7 symbols above with help online resources:
# https://tldp.org/LDP/abs/html/subshells.html
n=41                                                    # global variable
( let "n+=1"; echo -e "\$n INSIDE subshell is $n" )     # 42
# global variables are not visible inside a sub-shell
echo -e "\$n OUTSIDE subshell is $n"                    # 41


# https://tldp.org/LDP/abs/html/dblparens.html
n=10
(( t = n<45?7:11))
echo "if $n < 45, then t = 7, else t = 11"
echo "t = $t"


# https://tldp.org/LDP/abs/html/ops.html
n=1
: $((n += 1))       # : prevents Bash interpreting $(( )) as a command
echo -e "\$n was incremented from 1 to $n"


# https://tldp.org/LDP/abs/html/testconstructs.html
# https://dev.to/rpalo/bash-brackets-quick-reference-4eh6
[[ -d /tmp ]]
echo $?             # 0: 0 means true, 1 means false


# https://tldp.org/LDP/abs/html/comparison-ops.html
n="one string"
m=$n
[[ "$n" == "$m" ]]
echo $?             # 0


# https://tldp.org/LDP/abs/html/commandsub.html
list_of_sh_files=$(ls *.sh)
echo -e "\$list_of_sh_files is:\n$list_of_sh_files"


n=`for i in 1 2 3 4 5
do
    echo -n "$i "
done`
echo "\$n substitution is $n"
