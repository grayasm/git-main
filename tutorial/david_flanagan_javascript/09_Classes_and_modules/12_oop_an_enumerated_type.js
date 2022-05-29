/* Cap.9 Classes and Modules
   9.6.2 Example: Enumerated Types

   $ node 12_oop_an_enumerated_type.js

   enum keyword is reserved in JavaScript but unused.
   An enumerated type like in C and derived languages can be implemented like
   in the next example.
*/

function enumeration(namesToValues) {
    var enumeration = function() { throw "Can't Instantiate Enumerations"; };

    var proto = enumeration.prototype = {
        constructor: enumeration,
        toString: function() { return this.name; },
        valueOf: function() { return this.value; },
        toJSON: function() { return this.name; }
    }

    enumeration.values = [];

    for (name in namesToValues) {
        var e = inherit(proto);
        e.name = name;
        e.value = namesToValues[name];
        enumeration[name] = e;
        enumeration.values.push(e);
    }

    enumeration.foreach = function(f,c) {
        for (var i = 0; i < this.values.length; i++)
            f.call(c, this.values[i]);
    }

    return enumeration;
};

// see: 06_Objects/07_property_as_inheritance.js
function inherit(p) {
    if (p == null)
        throw TypeError();          // p must be a non-null object

    if (Object.create)
        return Object.create(p);

    var t = typeof p;
    if (t != "object" && t != "function")
        throw TypeError();

    function f() {}                 // Define a dummy constructor function.
    f.prototype = p;
    return new f();
};

// Define a class to represent a playing card
function Card(suit, rank) {
    this.suit = suit;
    this.rank = rank;
}

// These enumerated types define the suit and rank values
Card.Suit = enumeration({Clubs:1, Diamonds:2, Hearts:3, Spades:4});
Card.Rank = enumeration({Two:2, Three:3, Four:4, Five:5, Six:6,
                         Seven:7, Eight:8, Nine:9, Ten:10,
                         Jack:11, Queen:12, King:13, Ace:14});

// Define a textual representation for a card
Card.prototype.toString = function() {
    return this.rank.toString() + " of " + this.suit.toString();
};

// Compare the value of two cards as you would in poker
Card.prototype.compareTo = function(that) {
    if (this.rank < that.rank) return -1;
    if (this.rank > that.rank) return 1;
    return 0;
};

// A function for ordering cards as you would in poker
Card.orderByRank = function(a,b) { return a.compareTo(b); };

// A function for ordering cards as you would in bridge
Card.orderBySuit = function(a,b) {
    if (a.suit < b.suit) return -1;
    if (a.suit > b.suit) return 1;
    if (a.rank < b.rank) return -1;
    if (a.rank > b.rank) return 1;
    return 0;
};

// Define a class to represent a standard deck of cards
function Deck() {
    var cards = this.cards = [];
    Card.Suit.foreach(function(s) {
        Card.Rank.foreach(function(r) {
            cards.push(new Card(s,r));
        });
    });
}

// Shuffle method: shuffles cards in place and return the deck
Deck.prototype.shuffle = function() {

    // For each element in the array, swap with a randomly chosen lower element
    var deck = this.cards, len = deck.length;
    for (var i = len-1; i > 0; i--) {
        var r = Math.floor(Math.random()*(i+1)), temp;
        temp = deck[i], deck[i] = deck[r], deck[r] = temp;
    }
    return this;
};

// Deal method: returns an array of cards
Deck.prototype.deal = function(n) {
    if (this.cards.length < n) throw "Out of cards";
    return this.cards.splice(this.cards.length-n, n);
};

// Create a new deck of cards, shuffle it, and deal a bridge hand.
var deck = (new Deck()).shuffle();
var hand = deck.deal(13).sort(Card.orderBySuit);

console.log( hand );
/*
[ Card {
    suit: enumeration { name: 'Clubs', value: 1 },
    rank: enumeration { name: 'Two', value: 2 } },
  Card {
    suit: enumeration { name: 'Clubs', value: 1 },
    rank: enumeration { name: 'Six', value: 6 } },
  Card {
    suit: enumeration { name: 'Diamonds', value: 2 },
    rank: enumeration { name: 'Four', value: 4 } },
  Card {
    suit: enumeration { name: 'Diamonds', value: 2 },
    rank: enumeration { name: 'Five', value: 5 } },
  Card {
    suit: enumeration { name: 'Diamonds', value: 2 },
    rank: enumeration { name: 'Eight', value: 8 } },
  Card {
    suit: enumeration { name: 'Diamonds', value: 2 },
    rank: enumeration { name: 'Queen', value: 12 } },
  Card {
    suit: enumeration { name: 'Hearts', value: 3 },
    rank: enumeration { name: 'Two', value: 2 } },
  Card {
    suit: enumeration { name: 'Hearts', value: 3 },
    rank: enumeration { name: 'Four', value: 4 } },
  Card {
    suit: enumeration { name: 'Hearts', value: 3 },
    rank: enumeration { name: 'Five', value: 5 } },
  Card {
    suit: enumeration { name: 'Hearts', value: 3 },
    rank: enumeration { name: 'Ten', value: 10 } },
  Card {
    suit: enumeration { name: 'Hearts', value: 3 },
    rank: enumeration { name: 'Queen', value: 12 } },
  Card {
    suit: enumeration { name: 'Spades', value: 4 },
    rank: enumeration { name: 'Seven', value: 7 } },
  Card {
    suit: enumeration { name: 'Spades', value: 4 },
    rank: enumeration { name: 'Jack', value: 11 } } ]
*/
