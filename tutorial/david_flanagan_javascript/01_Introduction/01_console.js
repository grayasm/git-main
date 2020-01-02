/*
    Cap.1 Introduction to JavaScript, pag.4
    Fig.1-1 The Firebug debugging console for Firefox

    1. start google-chrome
    2. type F12 and switch to console tab
    3. copy-paste this into console
    4. press Enter to run
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
