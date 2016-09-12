cmake_minimum_required(VERSION 3.2)
project(02_proj2)

set(SRC samclass.cpp
		StdAfx.h
		resource.h
		samclass.rc
		samclass.ico
		samclass.def)
		
add_library(samclass SHARED ${SRC})

target_compile_definitions(samclass PRIVATE 
		_CRT_SECURE_NO_WARNINGS)