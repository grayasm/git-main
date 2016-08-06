
message ("Message from file2.cmake")

if (FOO)
	if (${FOO} LESS 10 OR ${FOO} EQUAL 10)
		set (FOO 100)
		message ("FOO changed to 100")
	endif()
endif()

if (BAR)
	if (${BAR} GREATER 20 OR ${BAR} EQUAL 20)
		set (BAR 200)
		message ("BAR changed to 200")
	endif()
endif()