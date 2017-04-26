# Description :
# Select compiler to be used 
# Be careful. Module only checks if provided file exists. Checking if this file is really a compiler is done by CMake during project set up.

# Input Variables :
# COMPILER_CHANGED : set to true to use a different CXX compiler from the default compiler set to false to use default compiler (default is false)
# COMPILER_FILE : compiler to use instead of default CXX compiler. Used only if COMPILER_CHANGED is set to true (default is empty)

# Once done this will change :
# CMAKE_CXX_COMPILER as cached variable if a new compiler is defined

### Checking Input variables existence. If they don't exist set them to default value ###
if(NOT DEFINED COMPILER_CHANGED)
	set(COMPILER_CHANGED false)
endif()

### Checking compiler to be used ###
if(COMPILER_CHANGED) #If compiler is changed

	if(EXISTS ${COMPILER_FILE})
		message(STATUS "Using ${COMPILER_FILE} as compiler")
		set(CMAKE_CXX_COMPILER ${COMPILER_FILE} CACHE FILEPATH "Select CXX compiler to use") #Compiler is cached so that you can change it if you want
	else()
		message(WARNING "COMPILE_FILE content is not a compiler. Using default compiler")
	
	endif()

endif()

