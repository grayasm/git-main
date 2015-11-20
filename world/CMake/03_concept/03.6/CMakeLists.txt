# About variables scope.

cmake_minimum_required (VERSION 2.8)

function (foo)
	message ("foo(): " ${test}) # test is 1 here
	set (test 2)
	message ("foo(): " ${test}) # test is 2 here, but only in this scope
endfunction()


function (bar)
	message ("bar(): " ${test}) # test is 1 here
	set (test 2 PARENT_SCOPE)
	message ("bar(): " ${test}) # test still 1 in this scope
endfunction ()


# --- begin ---
set (test 1)
foo ()
message ("global: " ${test}) # test will still be 1 here
bar ()
message ("global: " ${test}) # test will now be 2 here

# Variables can also represent a list of values. In these cases when the variable
# is expanded it will be expanded into multiple values.

set (items_to_buy apple orange pear beer)
foreach (item ${items_to_buy})
	message ("Don't forget to buy one ${item}")
endforeach()

















