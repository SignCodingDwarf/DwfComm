# Description :
# Checks if the OS is linux

#https://cmake.org/cmake/help/v2.8.11/cmake.html#section_VariablesThatDescribetheSystem

# Input Variables :
# 

# Once done this will define :
# 

message(STATUS "Checking Operating System")

if(NOT CMAKE_HOST_UNIX)

	message(STATUS "Windows User Detected")
	message(FATAL_ERROR "Hey Windows User, this project currently only supports Linux-based Operating Systems !!!")

else()
	if(CMAKE_HOST_APPLE)
		message(STATUS "Mac OSX User Detected")
		message(FATAL_ERROR "Hey Apple User, this project currently only supports Linux-based Operating Systems !!!")
	elseif(CMAKE_HOST_CYGWIN)
		message(STATUS "Cygwin User Detected")
		message(FATAL_ERROR "Hey Windows Cygwin User, this project currently only supports Linux-based Operating Systems !!!")
	else()
		message(STATUS "Linux User Detected, installation proceeding")
	endif()
endif()

