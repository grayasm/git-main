/* Cap.8 Functions
   8.3.3 Using Object Properties As Arguments

   $ node 08_args_objects.js

   When a function has more than 3 parameters, it becomes difficult to remember
   the correct order. It would be more easy to pass the arguments as
   name:value pairs in any order. To implement this style define the function
   to accept one object.
*/

function arraycopy(/*array*/ arr0, /*index*/ beg, /*index*/ end, /*array*/ arr1)
{
    for(var i=beg; i<end; i++)
        arr1.push(arr0[i]);
}

function easycopy(args){
    arraycopy(args.from, args.start, args.end, args.to);
}

var a = [1,2,3,4], b = [];
easycopy({from:a, to:b, start:0, end:a.length});  // b=[1,2,3,4]
