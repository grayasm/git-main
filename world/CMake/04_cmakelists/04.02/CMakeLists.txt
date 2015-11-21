# KEY: REGEXP REGEX REGX REG
#      regular expressions regular expression regular expr regular exp
#      I am looking at regular expressions aphanumeric characters:
#      ^ $ . [ ] [^ ] [-] * + ? ( )  (|)


cmake_minimum_required (VERSION 2.8)
message ("--------------------------------------------------------------------")

function (match variable regexp)
  if (${variable} MATCHES ${regexp})
	message ("${variable} MATCHES ${regexp}")
  else ()
	message ("${variable} DOES NOT MATCH ${regexp}")
  endif ()
endfunction()


# ^ Matches the beginning of a line or string
set (var1 "Content of a String")
set (reg1 "^Cont")
match (${var1} ${reg1})

# $ Matches the end of a line or string
set (reg1 "ing$")
match (${var1} ${reg1})

# . Matches any single character other than a newline
set (reg1 "of.a.Str")
match (${var1} ${reg1})

# [ ] Matches any character(s) inside the brackets
set (reg1 "[ZYS]")
match (${var1} ${reg1})

# [^ ] Matches any character(s) not inside the brackets
set (reg1 "[^XYZ]")
match (${var1} ${reg1})

# [-]  Matches any character in range of either side of a dash
set (reg1 "[a-c"])
match (${var1} ${reg1})

#  *   Matches preceding pattern zero or more times
set (reg1 "tring*")
match (${var1} ${reg1})

#  +   Matches preceding pattern one or more times
set (reg1 "tring+")
match (${var1} ${reg1})

#  ?   Matches preceding patter zero or once only
set (reg1 "S?")
match (${var1} ${reg1})


# ( )  Matches a matched expression and uses it in a later replacement
set (reg1 "(String$)")
match (${var1} ${reg1})

# (|)  Matches either the left or right side of the bar
set (reg1 "([a-z] | [0-9])")
match (${var1} ${reg1})


message ("--------------------------------------------------------------------")
