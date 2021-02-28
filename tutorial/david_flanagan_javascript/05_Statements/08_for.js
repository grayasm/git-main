/* Cap.5 Statements
   5.5.3 for

   $ node 08_for.js

   The loop syntax is:

   for(initialize; test; increment)
       statement
*/

for(var count = 0; count < 10; count++)
    console.log(count);

var i, j, sum = 0;
for(i = 0, j = 0; i < 10; i++, j--)
    sum += i * j;
console.log(sum); // -285


function tail(o) {
    for(; o.next; o = o.next) /*empty*/;
    return o;
}

// create a single-linked-list
var node = {}
var head = node;
for(var i = 0; i < 10; i++)
{
    node.next = {}
    node.val = i;
    node = node.next;
}
node.next = null;


console.log('node=', node);  // node= { next: null }
console.log('head=', head);  // head= { next: { next: { next: [Object], val: 2 }, val: 1 }, val: 0 }
var last = tail(head);
console.log('last=', last);  // last= { next: null }
