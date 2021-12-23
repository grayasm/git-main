/* Cap.6 Objects
   6.2 Querying and Setting Properties

   $ node 05_property_get_and_set.js
*/

// To obtain the value of a property, use the dot (.) or square braket ([]) operators.
book = {
    "main title": "Book Title",
    author: {
        name: "Name",
        surname: "Surname"
    },
    edition:0
};

var author = book.author;
var name = author.surname;
var title = book["main title"];

console.log(author);     // { name: 'Name', surname: 'Surname' }
console.log(name);       // Surname
console.log(title);      // Book Title

// To create or set a property, use a dot or square brackets as you would to
// query the property, but put them on the left-hand side of an assignment
// expression.
book.edition = 6;
book["main title"] = "ECMAScript";

console.log(book.edition);          // 6
console.log(book["main title"]);    // ECMAScript
