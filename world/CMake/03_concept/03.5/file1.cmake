
message ("Message from file1.cmake")

if (FOO)
	if (${FOO} LESS 1 OR ${FOO} EQUAL 1)
		set (FOO 10)
		message ("FOO changed to 10")
	endif()
endif()

if (BAR)
	if (${BAR} GREATER 2 OR ${BAR} EQUAL 2)
		set (BAR 20)
		message ("BAR changed to 20")
	endif()
endif()