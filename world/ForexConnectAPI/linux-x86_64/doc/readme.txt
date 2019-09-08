The ForexConnectAPI is an API designed to trade Forex and CFD instruments. Any 
connection which is compatible with the Trading Station/Marketscope application
or an ForexConnect API is also compatible with this API.

Package contents:

    ForexConnectAPI/
       doc/                 -- Documentation
          readme.txt        -- This file
          license.txt       -- The license
       include/             -- Include files
       lib/                 -- Libraries
       samples/             -- Samples
           cpp/
           java/
           cs/    


You can build samples using the cmake build system (available at http://cmake.org/cmake/resources/software.html).
To build a sample, just run fxbuild.sh from the sample directory.


To use ForexConnect API in your C++ application, you should:

1) Place supporting shared libraries in the same directory where your application program is located.
Or you can place supporting shared libraries in the /usr/lib directory.

2) Add libForexConnect to the list of libraries in the linker options. For example, if you use gcc, the option will be -lForexConnect. 
The path to the directory containing the libraries (e.g. /ForexConnectAPI/lib) can be specified by the -L/ForexConnectAPI/lib option. 

3) Include the header file in your code using the directive #include <ForexConnect.h>.
The path to the directory containing the headers (e.g. /ForexConnectAPI/include) can be specified by the -I/ForexConnectAPI/include option. 

To learn more about the ForexConnect API interface read the online documentation.
The online help is available at http://fxcodebase.com/documents/ForexConnectAPI/web-content.html

See the file license.txt for the license.
