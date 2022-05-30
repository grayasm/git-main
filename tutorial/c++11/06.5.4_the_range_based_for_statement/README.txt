.
    C++11 N3337.pdf pag.128
    6.5.4 The range-based for statement

    There are 2 forms for the range-based for loop:
    1) for ( for-range-declaration : expression ) statement
    2) for ( for-range-declaration : braced-init-list ) statement

    The range-based for loops require that the container implements:
    1) begin() and end() members or standalone methods returning iterator
    2) iterator that implements these operators: *, != and prefix ++

    Loop over a braced-init-list:
    for (int i : { 0, 1, 2, 3})
        cout << i;

    Loop over an int array[10]:
    for (int i : array)
        cout << i;

    Loop over and int *parray[10]:
    for (int *p : parray)
        cout << *p;

    Loop over a vector<string> strvec:
    for (const string& s : strvec)
        cout << s;

    Loop over a map<string, int> smap:
    for (auto it : smap)
        cout << it.first << " " << it.second << endl;


    Can iterate over a list, so it doesn't need to be a continous array.
    Cannot iterate over a pointer, so it requires an array to find it's size.
