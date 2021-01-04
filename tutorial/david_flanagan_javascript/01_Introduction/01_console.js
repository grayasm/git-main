/*
  The browser debugging console:

  1. start google-chrome.
  2. type F12 and switch to console tab.
  3. copy-paste the js text into console.
  4. press Enter to run.

  The Node.js interpreter:

  1. open Linux terminal
  2. node 01_console.js
*/

function factorial(n)
{
    var p = 1;
    for(var i = 2; i <= n; i++)
        p *= i;
    return p;
}

console.log(factorial(4));
console.log(factorial(5));
console.log(factorial(6));
