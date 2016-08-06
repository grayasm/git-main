
message ("Message from dir2/CMakeLists.txt")

# check "FOO" variable
if (FOO)
	message ("FOO is: " ${FOO})
else()
	message ("FOO is undefined")
endif()

# check "BAR" variable
if (BAR)
	message ("BAR is: " ${BAR})
else()
	message ("BAR is undefined")
endif()