/* Cap.3 Types, Values and Variables
   3.1.5 Dates and Times

   The Date object has methods for simple date computations.
*/

var then = new Date(2010, 0, 1);  // 1st day of the 1st month of 2010
var later = new Date(2010, 0, 1, 17, 10, 30); // same day at 5:10:30pm local time
var now = new Date();
var elapsed = now - then;

later.getFullYear();        // 2010
later.getMonth();           // 0    zero-based months
later.getDate();            // 1    one-based days
later.getDay();             // 5    day of week, 0 is Sunday 5 is Friday
later.getHours();           // 17   5pm local time
later.getUTCHours();        // 16   hours in UTC time; depends on timezone.
later.toString();           // "Fri Jan 01 2010 17:10:30 GMT+0100 (Central European Standard Time)"
later.toUTCString();        // "Fri, 01 Jan 2010 16:10:30 GMT"
later.toLocaleDateString(); // "1/1/2010"
later.toLocaleTimeString(); // "5:10:30 PM"
later.toISOString();        // "2010-01-01T16:10:30.000Z"  ECMAScript-5 only.
