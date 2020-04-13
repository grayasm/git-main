/* Cap.3 Types, Values and Variables
   3.2.4 Pattern Matching

   JavaScript defines RegExp() constructor to create textual patterns.
   JavaScript adopts Perl syntax for regular expressions.
   RegExp object API is complex and the grammar is nontrivial.
   The regular expression literal is contained between a pair of shashes /


   Brackets:
   [...]   Any one character between the brackets.
   [^...]  Any one character not between the brackets.
   [0-9]   It matches any decimal digit from 0 through 9.
   [a-z]   It matches any character from lowercase a through lowercase z.
   [A-Z]   It matches any character from uppercase A through uppercase Z.
   [a-Z]   It matches any character from lowercase a through uppercase Z.

   Quantifiers:
   p+      It matches any string containing one or more p's.
   p*      It matches any string containing zero or more p's.
   p?      It matches any string containing at most one p.
   p{N}    It matches any string containing a sequence of N p's.
   p{2,3}  It matches any string containing a sequence of 2 or 3 p's.
   p{2,}   It matches any string containing a seuquence of at least 2 p's.
   p$      It matches any string with p at the end of it.
   ^p      It matches any string with p at the beginning of it.

   Grouping:
   p | q   It matches either p or q.
   (...)   It creates a group of characters. You can combine multiple groups.
           See also the concept of "Capturing Groups".
   (...)?  Optional group.
   (?<name>regexp) It will assign a 'name' to the captured group.
   $1 $2   Each captured group is assigned a number.
   (?:...) Noncapturing group - It will not add the matched string to Array.
   p(?=q)  It matches p only if it is followed by q. It does a lookahead.
   p(?!q)  It matches p only if it is NOT followed by q. It does a lookahead.
   p(?<=q) It matches p only if it is preceeded by q. It does a lookbehind.
   p(?<!q) It matches p only if it is NOT preceeded by q. It does a lookbehind.


   Literal characters:
   alphanumeric Itself
   \0      The NULL character.
   \t      Tab (\u0009)
   \n      Newline (\u000A)
   \v      Vertical tab (\u000B)
   \f      Form feed (\u000C)
   \r      Carriage return (\u000D)
   \xnn    The Latin character specified by the hex number nn. "\x0A" is "\n"
   \uxxxx  The Unicode character specified by the hex number xxxx. "\u0009" is "\t"
   \cX     The control character ^X. "\cJ" is "\n"


   Metacharacters:
   .              A single character.
   \s             A whitespace character (space, tab, newline).
   \S             A non-whitespace character.
   \d             A digit (0-9).
   \D             A non-digit.
   \w             A word character (a-z, A-Z, 0-9, _)
   \W             A non-word character.
   [\b]           A literal backspace (special case).
   [aeiou]        Matches a single character in the given set.
   [^aeiou]       Matches a single character outside the given set.
   (foo|bar|baz)  Matches any of the alternatives specified.
   \b             Matches a set of characters at the beginning or end of a word.
   \B             Matches a set of characters not at the beginning or end of a word.


   Modifiers:
   i       Perform case-insensitive matching.
   m       Specifies that if the string has newline or carriage return
           characters, the ^ and $ operators will now match against a newline
           boundary, instead of a string boundary.
   g       Perform a global match that is, find all matches rather than stopping
           after the first match.
   u       Enables support for unicode (introduced ES6/ES2015)
   s       It causes the . to match new line as characters (introduced ES2018)


   RegExp Properties:
   constructor     The function that creats an object's prototype.
   global          True, if the "g" modifier is set.
   ignoreCase      True, if the "i" modifier is set.
   lastIndex       The index at which to start the next match.
   multiline       Specifies if the "m" modifier is set.
   source          The text of the pattern.

   RegExp Methods:
   exec()          Executes a search for a match in its string parameter.
   test()          Tests for a match in its string parameter.
   toSource()      Returns an object literal representing the specified object.
   toString()      Returns a string representing the specified object.

   String.match(RegExp): similar with RegExp.exec(); This is the concept for
                   Capturing Groups

   Escaping:       The following characters are special.
   \
   /
   [ ]
   ( )
   { }
   ?
   +
   *
   |
   .
   ^
   $
*/


var r1 = new RegExp('[a-z]', 'i');  // first character in range a-z
'012345679'.search(r1);             // -1
'0123a'.search(r1);                 // 4
'0123a'.search(/[a-z]/i);           // 4

var r2 = new RegExp('[0-9]', 'g');  // first digit in range 0-9
'abcdefg'.search(r2);               // -1
'abcde9'.search(r2);                // 5
'abcde9'.search(/[0-9]/g);          // 5

var r3 = new RegExp('[^a-zA-Z]', 'i'); // first not in range a-z,A-Z
'hangar nine'.search(r3);           // 6  (matched the whitespace)

// first character in range a-z, followed by a single character (any),
// followed by a digit in range 0-9
var r4 = new RegExp('[a-z].[0-9]', 'i');
'aaa?999'.search(r4);               // 2
' a?9'.search(r4);                  // 1
' 9?a'.search(r4);                  // -1

/*
  754-3010            Local
  (541) 754-3010      Domestic
  +1-541-754-3010     International
  1-541-754-3010      Dialed in the US
  001-541-754-3010    Dialed from Germany
*/
/^\d{3}-\d{4}$/.test('754-3010');                     // true: Local
/^\(\d{3}\) \d{3}-\d{4}$/.test('(541) 754-3010');     // true: Domestic
/^\+\d-\d{3}-\d{3}-\d{4}$/.test('+1-541-754-3010');   // true: International
/^\d-\d{3}-\d{3}-\d{4}$/.test('1-541-754-3010');      // true: Dialed in the US
/^\d{3}-\d{3}-\d{3}-\d{4}$/.test('001-541-754-3010'); // true: Dialed from DE

//Note: do not use metacharacter \d in RegExp.
var r5 = new RegExp('^[0-9]{3}-[0-9]{4}$', 'i');
r5.test('754-3010');                                  // true: Local

// Capturing Groups: exec will return an Array with each matched group.
var a0 = /^(\+\d)-(\d{3})-(\d{3}-\d{4})$/.exec('+1-541-754-3010');
// ["+1-541-754-3010", "+1", "541", "754-3010"] array has 4 items.

// Capturing Groups: assign a name to each Array's group with ?<name>
var a1 = /^(?<code>\+\d)-(?<area>\d{3})-(?<phone>\d{3}-\d{4})$/.exec('+1-541-754-3010');
// groups: {code: "+1", area: "541", phone: "754-3010"} Array's groups member.
a1.groups["code"]
a1.groups["area"]
a1.groups["phone"]

// Noncapturing Group: (?:...) it will not add the matched string to the result.
var a2 = /^(?:\+\d)-(\d{3})-(\d{3}-\d{4})$/.exec('+1-541-754-3010');
// ["+1-541-754-3010", "541", "754-3010"] array has 3 items.

// Replace parts of a string based on a pattern
"Hello world!".replace('world', 'dog')         // Hello dog!
"Hello world!".replace(/world/, 'dog')         // Hello dog!
"My dog is a good dog!".replace('dog', 'cat')  // My cat is a good dog!
"My dog is a good dog!".replace(/dog/g, 'cat') // My cat is a good cat!
"Hello, world!".replace(/(\w+), (\w+)!/, '$2: $1!!!') // world: Hello!!!

"Hello, world!".replace(/(\w+), (\w+)!/, (matchedString, first, second) => {
    console.log(first);
    console.log(second);
    return `${second.toUpperCase()}: ${first}!!!`
})
// "WORLD: Hello!!!"


// Greediness: a regexp is greedy per default. Use ? to be lazy.
// Lookahead: p(?=q)  true only if p is followed by q.
/red (?=green)/.test('red another red green blue')    // true

// Lookahead negated: p(?!q)   true only if p is not followed by q.
/red (?!green)/.test('red blue green')                // true

// Lookbehind: (?<=p)q         true only if q is preceeded by p.
/(?<=red) green/.test('red green')

// Lookbehind negated: (?<!q)q true only if q is NOT preceeded by p
/(?<!red) green/.test('red blue green')               // true

// Regular expression and Unicode: always use the u flag.
/[🐶-🦊]/u.test('🐺')  // true
/[🐶-🦊]/u.test('🐛')  // false

// Unicode property escapes \p{} and its negation \P{}
/^\p{ASCII}+$/u.test('abc')             // true
/^\p{ASCII_Hex_Digit}+$/u.test('01234') // true
/^\p{Emoji}+$/u.test('🙃🙃')            // true


// https://flaviocopes.com/javascript-regular-expressions
