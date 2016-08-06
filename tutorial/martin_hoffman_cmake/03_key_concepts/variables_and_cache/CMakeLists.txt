
cmake_minimum_required (VERSION 2.8)

# create a variable USE_JPEG and put it into the cache.
option (USE_JPEG "Do you want to use the jpeg library?")

# create a variable USE_TIFF in the cache using set command with CACHE option.
set (USE_TIFF ON CACHE BOOL "include tiff support?")

# create other cache variables
set (USE_browse_for_a_file          "file.txt"         CACHE FILEPATH "")
set (USE_browse_for_a_directory     "dir"              CACHE PATH     "")
set (USE_a_string                   "arbitrary string" CACHE STRING   "")
set (USE_bool                        ON                CACHE BOOL     "")
set (USE_internal                    20                CACHE INTERNAL "")

# options with a list of strings
set (CRYPTOBACKEND                  "OpenSSL"          CACHE STRING   "Select a cryptography backend")
set_property (CACHE CRYPTOBACKEND PROPERTY STRINGS "OpenSSL" "LibTomCrypt" "LibDES")

# assume that FOO is set to ON in the cache
set (FOO OFF)
# sets FOO to OFF for processing this CMakeLists file and subdirectories.
# the value in the cache stays ON