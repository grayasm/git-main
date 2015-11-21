cmake_minimum_required (VERSION 2.8)
project (Hello)

message ("--------------------------------------------------------")

# if()/endif()
if (VAR)
	message ("VAR is defined as: " ${VAR})
endif (VAR)


# NOT
if (NOT VAR)
	message ("VAR is undefined : " ${VAR})
endif (NOT VAR)


# AND
if (var1 AND var2)
	message ("var1 AND var2 evaluates to true")
else ()
	message ("var1 AND var2 evaluates to false")
endif (var1 AND var2)


# OR
set (var1 0)
set (var2 1)
if (var1 OR var2)
	message ("one of var1: ${var1} or var2: ${var2} is valid")
else()
	message ("neither var1: ${var1} or var2: ${var2} is valid")
endif (var1 OR var2)


# COMMAND
if (COMMAND include)
	message ("COMMAND include    evaluates to true")
else ()
	message ("COMMAND include    evaluates to false")
endif ()


# DEFINED
if (DEFINED WIN32)
	message ("WIN32 is defined")
else ()
	message ("WIN32 is not defined")
endif()


# EXISTS
if (EXISTS ../04.01/CMakeLists.txt)
	message ("Filename ../04.01/CMakeLists.txt exists")
else ()
	message ("Filename ../04.01/CMakeLists.txt does not exist")
endif ()


# IS_DIRECTORY
if (IS_DIRECTORY ../04.01)
	message ("Directory ../04.01 exists")
else ()
	message ("Directory ../04.01 does not exist")
endif ()


# IS_NEWER_THAN
if (../04.01/CMakeLists.txt IS_NEWER_THAN build-win.bat)
	message ("Filename ../04.01/CMakeLists.txt IS_NEWER_THAN build-win.bat")
else ()
	message ("Filename ../04.01/CMakeLists.txt is not newer than build-win.bat")
endif ()


# MATCHES
set (var3 "../04.01/CMakeLists.txt")
set (regex1 "CMakeLists.txt$")

if (${var3} MATCHES ${regex1})
	message ("var3: ${var3} MATCHES regex1: ${regex1}")
else ()
	message ("var3: ${var3} does not matches regex1: ${regex1}")
endif ()


# FOREACH + math
set(count 0)
foreach (i A B C)
	message ("i: ${i}    count: ${count}")
	math(EXPR count "${count} + 1")
endforeach ()

# variable expansion
foreach (i "vector" "string" "list")
	message ("foreach: ${i}.hpp ${i}.cpp")
endforeach ()


# WHILE
set (count 3)
while (count GREATER 0)
	message ("count in while: ${count}")
	math (EXPR count "${count} - 1")
endwhile ()


# FUNCTION  (push and pop a new variable scope)
function (GetTime var)
	set (${var} "1:20:45" PARENT_SCOPE)  # PARENT_SCOPE for upper scope
endfunction ()

set (current_time 0)
GetTime (current_time)
if (DEFINED current_time)
	message (STATUS "The time is now: ${current_time}")
endif ()


# MACRO  (does not push/pop a new scope)
macro (M_GETTIME var)
	set (${var} "2:20:45")   # no PARENT_SCOPE, we are in the upper scope
endmacro ()

set (current_time 0)
M_GETTIME (current_time)
if (DEFINED current_time)
	message (STATUS "The time is now: ${current_time}")
endif ()


# ARGC ARGV0  ARGV1  ARGV ARGN
# concatenate and expand variable names
function (PrintParams)
	message ("current ARGC: ${ARGC}")
	message ("current ARGN: ${ARGN}")
	message ("current ARGV: ${ARGV}")
	foreach (argv ${ARGV})
		message ("current in ARGV: ${argv}")
	endforeach()

	set (count 0)
	while (count LESS ${ARGC})
		message ("expand ARGV${count}: ${ARGV${count}}")
		math (EXPR count "${count}+1")
	endwhile ()
endfunction ()
PrintParams (10 20 30)


# BREAK  a while/foreach command
set (count 0)
while (count LESS 5)
	message ("while (${count} < 5) this message;")
	if (count EQUAL 2)
		message ("break")
		break ()
	endif ()
	math (EXPR count "${count}+1")
endwhile ()


# RETURN   from a function
function (Count maxim)
	message ("Count to ${maxim}")
	set (i 0)
	while (${i} LESS ${maxim})
		message ("counter is: ${i}")
		if (i EQUAL 4)
			message ("return")
			return ()
		endif ()
		math (EXPR i "${i}+1") # increment
	endwhile ()
endfunction ()

Count (10)


message ("--------------------------------------------------------")
