#!/usr/bin/env python3
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
# The 'pattern' object contains compiled reg. expressions
# The notation below is p-pattern, m-match, re-module

p = re.compile('ab*')
p = re.compile('ab*', re.IGNORECASE)
p = re.compile('[a-z]+')

# 'match' and 'search' return None or a match object instance
m = p.match("")
print (m)                   # None

m = p.match('tempo')
print (m)                   # <_sre.SRE_Match object at 0x7fa73e754850>
print (m.group())           # tempo
print (m.start())           # 0
print (m.end())             # 5
print (m.span())            # (0, 5)


# If the first character does not match, re.match(..) will return None.
# This means m.start() will always be zero for successul return.
m = p.match('::: message')
print (m)                   # None

m = p.search('::: message')
print (m.group())           # message
print (m.span())            # (4, 11)

# 'findall()' returns a list of matching strings
p = re.compile('\d+')       # \d matches one digit i.e. [0-9]
l = p.findall('12 drummers drumming, 11 pipers piping, 10 lords a-leaping')
print (l)                   # [12, 11, 10]

# 'finditer()' returns a sequence of match object instances
iterator = p.finditer('12 drummers, 11 ... 10 ...')
print (iterator)            # <callable-iterator object at 0x7fd10573e990>

for match in iterator:
    print (match.span())    # (0, 2) (13, 15) (20, 22)

# calling 're' module methods directly, without a pattern object
m = re.match(r'From\s+', 'Fromage amk')
print (m)                   # None

# compilation flags, ex:'VERBOSE'
charref = re.compile(r"""
&[#]                 # start of a numeric entity reference
(
    0[0-7]+          # octal form
  | [0-9]+           # decimal form
  | x[0-9a-fA-F]+    # hexadecimal form
)
;                    # trailing semicolon
""", re.VERBOSE)

# or simple form without VERBOSE
charref = re.compile("&#(0[0-7]+"
                     "|[0-9]+"
                     "|x[0-9a-fA-F]+);")

# more metacharacters
# ^
m = re.search('^From', 'From here to there')
print (m.group())             # From

m = re.search('^From', 'Reciting From Memory')
print (m)                     # None

# $
m = re.search('}$', '{block}')
print (m.group(), m.span())   # } (6, 7)

m = re.search('}$', '{block} ')
print (m)                     # None

m = re.search('}$', '{block}\n')
print (m.group(), m.span())   # } (6, 7)

p = re.compile(r'\bclass\b')
m = p.search('no class at all')
print (m.group(), m.span())   # class (3, 8)

m = p.search('the declassified algorithm')
print (m)                     # None

m = p.search('one subclass is')
print (m)                     # None

# r'\b.....'  - is a raw r'...' string where escape does not have effect
#  '\b.....'  - is a normal string where \b escape is a backspace character
#             - so r'\bword' means empty string at the beginning of the word
p = re.compile('\bclass\b')
m = p.search('no class at all')
print (m)                     # None

m = p.search('\b' + 'class' + '\b')
print (m.group(), m.span())   # clas (0, 7)

# Grouping (...)
p = re.compile('(ab)*')
m = p.match('ababababab')
print (m.group(), m.span())   # ababababab (0, 10)

p = re.compile('(a)b')
m = p.match('ab')
print (m.group(), m.group(0))  # ab ab

p = re.compile('(a(b)c)d')
m = p.match('abcd')
print (m.group(0), m.group(1), m.group(2))  # abcd abc b

t = m.group(0, 1, 2)
print (t)                     # ('abcd', 'abc', 'b')

t = m.groups()
print (t)                     # ('abc', 'b')

# RE detects doubled words in a string
p = re.compile(r'(\b\w+)\s+\1')
m = p.search('Paris in the the spring.')
print (m.group(), m.span())   # the the (9, 16)


# https://docs.python.org/3/howto/regex.html#non-capturing-and-named-groups
# Non-capturing groups (?:...)
m = re.match("([abc])+", "abc")
print (m.groups())            # ('c',)
m = re.match("(?:[abc])+", "abc")
print (m.groups())            # ()

# named group syntax is: (?P<name>...)
p = re.compile(r'(?P<word>\b\w+\b)')
m = p.search('(((( Lots of punctuation )))')
print (m.group('word'))       # Lots
print (m.group(1))            # Lots

# named groups are handy because they let you use easily-remembered names.ex:
InternalDate = re.compile(r'INTERMEDIATE "'
            r'(?P<day>[ 123][0-9])-(?P<mon>[A-Z][a-z][a-z])-'
            r'(?P<year>[0-9][0-9][0-9][0-9])'
            r' (?P<hour>[0-9][0-9]):(?P<min>[0-9][0-9]):(?P<sec>[0-9][0-9])'
            r' (?P<zonen>[-+])(?P<zoneh>[0-9][0-9])(?P<zonem>[0-9][0-9])'
            r'"')

m = InternalDate.match('INTERMEDIATE " 2-Feb-0999 01:01:99 +0020"')
print (m.group())        # INTERMEDIATE " 2-Feb-0999 01:01:99 +0020"
print (m.groups())       # (' 2', 'Feb', '0999', '01', '01', '99', '+', '00', '20')
print (m.group('year'))  # 0999


p = re.compile(r'(?P<word>\b\w+)\s+(?P=word)')
m = p.search('Paris in the the spring')
print (m.group())        # the the

# Splitting String with:
# pattern.split(string [, maxsplit=0])

p = re.compile(r'\W+')
l = p.split('This is a test, short and sweet, of split().')
print (l)   # ['This', 'is', 'a', 'test', 'short', 'and', 'sweet', 'of', 'split', '']

p = re.compile(r'\W+')
p2 = re.compile(r'(\W+)')
l = p.split('This... is a test.')
print (l)   # ['This', 'is', 'a', 'test', '']

l = p2.split('This...is a test.')
print (l)   # ['This', '...', 'is', ' ', 'a', ' ', 'test', '.', '']

# or using re.split()
l = re.split('[\W]+', 'Words, words, words.')
print (l)   # ['Words', 'words', 'words', '']

l = re.split('([\W]+)', 'Words, words, words.')
print (l)   # ['Words', ', ', 'words', ', ', 'words', '.', '']

l = re.split('[\W]+', 'Words, words, words.', 1)
print (l)   # ['Words', 'words, words.']


# Search and Replace
# pattern.sub(replacement, string[, count=0])
p = re.compile('(blue|white|red)')
s = p.sub('colour', 'blue socks and red shoes')
print (s)                     # colour socks and colour shoes

# 'subn'
p = re.compile('(blue|white|red)')
t = p.subn('colour', 'blue socks and red shoes')
print (t)                     # ('colour socks and colour shoes', 2)

t = p.subn('colour', 'no colours at all')
print (t)                     # ('no colours at all', 0)

p = re.compile('x*')
s = p.sub('-', 'abxd')
print (s)                     # -a-b-d-


# changes section into subsection
p = re.compile('section{ ( [^}]* ) }', re.VERBOSE)
s = p.sub(r'subsection{\1}', 'section{First} section{second}')
print (s)                     # subsection{First} subsection{second}

# 3 equivalent substitutions using named groups.
p = re.compile('section{ (?P<name> [^}]* ) }', re.VERBOSE)
s = p.sub(r'subsection{\1}', 'section{First}')
print (s)                     # subsection{First}

s = p.sub(r'subsection{\g<1>}', 'section{First}')
print (s)                     # subsection{First}

s = p.sub(r'subsection{\g<name>}', 'section{First}')
print (s)                     # subsection{First}


# replacement as a function
def hexrepl(match):
    "Return the hex string for a decimal number"
    value = int(match.group())
    return hex(value)

p = re.compile(r'\d+')
s = p.sub(hexrepl, 'Call 65490 for printing, 49152 for user code.')
print (s)                     # Call 0xffd2 for printing, 0xc000 for user code.


# Common Problems

# match() vs search()
print (re.match('super', 'superstition').span())   # (0, 5)
print (re.match('super', 'insuperable'))           # None

print (re.search('super', 'superstition').span())  # (0, 5)
print (re.search('super', 'insuperable').span())   # (2, 7)


# Greedy vs Non-Greedy
s = '<html><head><title>Title</title>'
print (len(s))                   # 32

m = re.match('<.*>', s)
print (m.span())                 # (0, 32)

m = re.match('<.*>', s)
print (m.group())                # <html><head><title>Title</title>

m = re.match('<.*?>', s)
print (m.group())                # <html>


# Using re.VERBOSE - permissive with # comments in syntax
p = re.compile(r"""
\s*                 # Skip leading whitespace
(?P<headers>[^:]+)  # Header name
\s* :               # Whitespace, and a colon
(?P<value>.*?)      # The header's value -- *? used to
                    # lose the following trailing whitespace
\s*$                # Trailing whitespace to end-of-line
""", re.VERBOSE)

# which is more readable than
p = re.compile(r"\s*(?P<header>[^:]+)\s*:(?P<value>.*?)\s*$")
