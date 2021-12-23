/* Cap.6 Objects
   6.2.1 Objects As Associative Arrays

   $ node 06_property_as_array.js

   The following two JavaScript expressions have the same value:

   object.property
   object["property"]
*/

// This brief example demonstrates the flexibility of using array notation to
// access properties of an object with string expressions.
customer = {
    address0: "address-0",
    address1: "address-1",
    address2: "address-2",
    address3: "address-3"
}

var addr = "";
for (i = 0; i < 4; i++) {
    addr += customer["address" + i] + '\n';
}
console.log(addr); // address-0
                   // address-1
                   // address-2
                   // address-3

// The code above could be rewritten using the dot notation, but there are cases
// in which only the array notation will do.

portofolio = { }
function add_stock(portofolio, stockname, shares) {
    portofolio[stockname] = shares;
}

add_stock(portofolio, "IBM", 200);
add_stock(portofolio, "AAPL", 300);
add_stock(portofolio, "INTC", 500);

console.log(portofolio);  // { IBM: 200, APPL: 300, INTL: 500 }

// Since the user enters stock names at runtime, there is no way that you can
// know the property names ahead of time. So, there is no way you can use the .
// operator to access the properties of the portofolio object.
// You can use the [] operator, however because it uses a string value rather
// than an indentifier to name the property.

quotes = { IBM:104.70, AAPL:130.98, INTC:44.42 }    // 13.11.2021

function get_value(portofolio) {
    var total = 0.0;
    for (stock in portofolio) {                     // for each stock in portofolio
        var shares = portofolio[stock];             // get the number of shares
        var price = quotes[stock];                  // look up share price
        total += shares * price;                    // add stock value to total
    }
    return total;
}

console.log("total value=" + get_value(portofolio));// total value=82444
