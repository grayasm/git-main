/*  Cap.8   Data Types
    8.13.   XML Type
    8.13.1  Creating XML Values
    8.13.2  Encoding Handling
    8.13.3  Accessing XML Values

    psql -d mytestdb -U pgmihai
    \i   13.0_xml.sql
    \?
    \qecho '\033[2J'
*/


/*      The xml data type can be used to store XML data. Its advantage over
        storing XML data in a text field is that it checks the input values
        for well-formedness, and there are support functions to perform
        type-safe operations on it.

        The xml type can store well-formed "documents", as defined by XML
        standard, as well as "content" fragments, which are defined by the
        production XMLDecl? content in the XML standard. Roughly, this means
        that content fragments can have more than one top-level element or
        character node. The expression xmlvalue IS DOCUMENT can be used to
        evaluate whether a praticular xml value is full document or only
        a content fragment.
*/

/*      Creating XML Values

        To produce a value of type xml from character data, use the function
        xmlparse:

        XMLPARSE ( {DOCUMENT | CONTENT} value)
*/

SELECT XMLPARSE (DOCUMENT '<?xml version="1.0"?><book><title>Manual</title>'
                          '<chapter>...</chapter></book>');
/*
                         xmlparse
----------------------------------------------------------
 <book><title>Manual</title><chapter>...</chapter></book>
(1 row)
*/

SELECT XMLPARSE (CONTENT 'abc<foo>bar</foo><bar>foo</bar>');
/*
            xmlparse
---------------------------------
 abc<foo>bar</foo><bar>foo</bar>
(1 row)
*/


-- PostgreSQL specific syntaxes:
DROP TABLE IF EXISTS xml_t CASCADE;

CREATE TABLE xml_t (id SERIAL, xml_ XML);

INSERT INTO xml_t(xml_) VALUES (xml '<foo>bar</foo>'),    -- input form
                               ('<foo>bar</foo>'::xml);   -- input form

SELECT * FROM xml_t;
/*
 id |      xml_
----+----------------
  1 | <foo>bar</foo>
  2 | <foo>bar</foo>
(2 rows)
*/

/*      The inverse operation, producing a character string value from xml,
        uses the function xmlserialize

        XMLSERIALIZE ( {DOCUMENT | CONTENT} value AS type )

        type can be character, character varying or text (or an alias of those)
*/
SELECT XMLSERIALIZE (
    DOCUMENT (
        SELECT XMLROOT(
            XMLELEMENT(name root,
                XMLELEMENT(name value, 'test')
                ), version '1.0', standalone yes
            )
        )
        AS text);
/*
------------------------------------------------------------------------
 <?xml version="1.0" standalone="yes"?><root><value>test</value></root>
(1 row)
*/


/*      Encoding Handling

        PostgreSQL converts all character data passed between the client
        and the server to the character encoding of the respective end.
        Encoding declarations contained in character strings presented for input
        to the xml type are ignored, and content is assumed to be in current
        server encoding. Character string of XML data must be sent from the
        client in the current client encoding.

        Needless to say, processing XML data with PostgreSQL will be less
        error-prone and more efficient if the XML data encoding, client encoding
        and server encoding ar the same. Since XML data is internally processed
        in UTF-8, computations will be more efficient if the server encoding
        is also UTF-8.
*/
