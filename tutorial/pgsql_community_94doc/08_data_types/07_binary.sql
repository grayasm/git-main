/*  Cap.8   Data Types
    8.4     Binary Data Types

    psql -d mytestdb -U pgmihai
    \i 07_binary.sql
*/

/*
      Name        Storage Size                   Description
    ------------+-----------------------------+------------------------------
      bytea       1 or 4 bytes plus              variable-length binary string
                  the actual binary string
    --------------------------------------------------------------------------

     Binary strings allow storing octets of value zero and other "non-printable"
     octets (outside range 32 to 126). Character string disallow zero octets,
     or any other octet values that are invalid according to the DB's selected
     character set encoding.
     Operations on binary strings process the actual bytes, whereas for strings
     depends on locale settings.
     Binary strings are appropriate for storing data as "raw bytes".

*/