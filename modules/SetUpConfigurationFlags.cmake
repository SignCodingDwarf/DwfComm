# Description :
# Set up build configuration and compilation flags

# Input Variables :
# RELEASE_BUILD : set to true to compile in release mode (default is false)
# USER_DEBUG : set to true to enable user debug operation (default is false)

# Once done this will change :
# CMAKE_BUILD_TYPE as cached variable
# Defined flags (via add definitions)

# Select Build mode
if(RELEASE_BUILD)
	set(CMAKE_BUILD_TYPE RELEASE)
else()
	set(CMAKE_BUILD_TYPE DEBUG)
endif()

# Check user debug mode
if(USER_DEBUG)
	add_definitions(-DDEBUG=1)
else()
	add_definitions(-DDEBUG=0)
endif()

# Check if C++11 is available
include(CheckCXXCompilerFlag) # Module allowing to check compiler flags
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11) # Check if C++11 flags are supported
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # Enable the use of C++11 flag
    	add_definitions(-DUSE_SHARED_POINTERS=1)  # Enable shared pointers use
	add_definitions(-DUSE_AUTO_LOOPS=1)  # Enable range-based syntax use
	add_definitions(-DUSE_LAMBDA_FUNCTIONS=1)  # Enable anonymous functions
    	## Add other C++11 features management here
elseif(COMPILER_SUPPORTS_CXX0X)
    	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    	add_definitions(-DUSE_SHARED_POINTERS=1)
	add_definitions(-DUSE_AUTO_LOOPS=1)
	add_definitions(-DUSE_LAMBDA_FUNCTIONS=1)
	## Add other C++11 features management here
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Disabling C++11 features")
	add_definitions(-DUSE_SHARED_POINTERS=0) # Disable shared pointers because unsupported by compiler
	add_definitions(-DUSE_AUTO_LOOPS=0) # Disable range-based syntax use because unsupported by compiler
	add_definitions(-DUSE_LAMBDA_FUNCTIONS=0)  # Enable anonymous functions because unsupported by compiler
	## Add other C++11 features management here
endif()

