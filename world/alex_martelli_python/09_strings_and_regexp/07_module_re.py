#!/usr/bin/python -tt
# -*- coding: utf-8 -*-

#
# Regular Expressions and the re Module
#
import re

# 'compile' - builds a RE object from a pattern string
# RE object - searches for matches
#           - substitutes a string

# *** Pattern-String Syntax ***
'''
.        - any character except \n
^        - start of string
$        - end of string
*        - zero or more cases of previous RE (greedy, as many as possible)
+        - one or more cases of previous RE (greedy, as many as possible)
?        - zero or one case of previous RE (greedy, as many as possible)
*?,+?,?? - nongreedy versions of *,+ and ? (as few as possible)

{m,n}    - m to n cases of previous RE (greedy)
{m,n}?   - m to n cases of previous RE (nongreedy)
[...]    - any one of a set of characters contained within brackets
|        - either preceding or the following expression
(...)    - matches the RE within the paranthesis and indicates a group

(?iLmsux) - alternate way to set optional flags
(?:...)  - like (...) but does not indicate a group
(?P<id>...) - like (...) but the group also gets the name id
(?#...)  - content of the paranthesis is a comment; no effect on match
(?=...)  - matches if RE ... matches what's next but does not consume it
(?!...)  - matches if RE ... does not match what's next, does not consume it
(?<=...) - matches if there is a match ending at the current position
(?<!...) - matches if there is no match ending at the current position
\number  - maches whatever was previously matched by group numbered number
\A       - empty string at the start of the whole string
\b       - empty string at the start or end of a word
\B       - an empty string, but not at the start or end of a word
\d       - one digit, like set [0-9]
\D       - one nondigit, like the set [^0-9]
\s       - a whitespace character like the set [\t\n\r\f\v]
\S       - a nonwhite space character like the set [^\t\n\r\f\v]
\w       - one alphanumeric character, like [a-zA-Z0-9_]
\W       - one nonalphanumeric character, the reverse of \w
\Z       - one empty string, but only at the end of the whole string
\\       - one backslash character
'''

# *** Common Regular Expressions Idioms ***

# *** Set of Characters ***

# *** Alternatives ***

# *** Groups ***

# *** Optional Flags ***

# *** Match Versus Search ***

# *** Anchoring at String Start and End ***

# *** Regular Expression Objects ***

# *** Match Objects ***


# *** Functions of RE Module ***

'''
compile(pattern, flag=0)
escape(s)
'''

# https://docs.python.org/3/howto/regex.html
# compiling regular expressions
p = re.compile('ab*')
p = re.compile('ab*', re.IGNORECASE)
p = re.compile('[a-z]+')

# 'match' and 'search' return None or a match object instance
m = p.match("")
print m                      # None

m = p.match('tempo')
print m                      # <_sre.SRE_Match object at 0x7fa73e754850>
print m.group()              # tempo
print m.start()              # 0
print m.end()                # 5
print m.span()               # (0, 5)


# If the first character does not match, re.match(..) will return None.
# This means m.start() will always be zero for successul return.
m = p.match('::: message')
print m                      # None

m = p.search('::: message')
print m.group()              # message
print m.span()               # (4, 11)

# 'findall' returns a list of matching strings
p = re.compile('\d+')        # \d matches one digit i.e. [0-9]
l = p.findall('12 drummers drumming, 11 pipers piping, 10 lords a-leaping')
print l                      # [12, 11, 10]
