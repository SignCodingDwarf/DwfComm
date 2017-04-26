# Description :
# Find Xerces library content
# Based on
# https://code.google.com/p/libcitygml/source/browse/trunk/CMakeModules/FindXerces.cmake?r=95

# Input Variables : 
# XERCESC_INCLUDE_DIR : set the path to Xerces include directory if it is not standard
# XERCESC_LIBRARY_DIR : set the path to Xerces lib directory if it is not standard

# Once done this will define :
# XERCESC_FOUND : set to true if Xerces-C is defined  
# XERCESC_INCLUDE : set the path to the Xerces-C include directory
# XERCESC_LIBRARY : set the path to the Xerces-C library
# XERCESC_VERSION : set the Xerces-C version number
# XERCESC_STATIC : set to true if static library is used and to false if dynamic library is used

message(STATUS "Locating Xerces-c library")

### Check if data are already stored in cache ###
if(DEFINED XERCESC_INCLUDE AND DEFINED XERCESC_LIBRARY)
	set(XERCESC_FIND_QUIETLY true)
else()
	set(XERCESC_FIND_QUIETLY false)
endif()

#############################################################################

### Choose library compilation type ###
set(XERCESC_STATIC false) # true to use .a library, false to use .so
if(NOT DEFINED XERCESC_WAS_STATIC OR NOT ${XERCESC_WAS_STATIC} STREQUAL ${XERCESC_STATIC})
	unset(XERCESC_LIBRARY CACHE)
	unset(XERCESC_LIBRARY_DEBUG CACHE)
	set(XERCESC_FIND_QUIETLY false) # We have to find back xerces with the new library
endif()

set(XERCESC_WAS_STATIC ${XERCESC_STATIC} CACHE INTERNAL "Set to true to use static library (.a)" ) # Store previous library choice in cache

#############################################################################

### Find include directory path ###
if(NOT XERCESC_FIND_QUIETLY) # If it was not already found, search for Xerces include folder
	find_path(XERCESC_INCLUDE NAMES xercesc/util/XercesVersion.hpp # Find version path
	PATHS
	$ENV{XERCESC_INCLUDE_DIR} # Custom search paths as an environment variable
	${XERCESC_INCLUDE_DIR} # Custom search paths as a CMake variable
	/usr/local/include # Default search paths
	/usr/include
	)
endif()

#############################################################################

### Find library file ###
if(NOT XERCESC_FIND_QUIETLY) # If it was not already found, search for Xerces library file
	if(XERCESC_STATIC)
		FIND_LIBRARY(XERCESC_LIBRARY NAMES xerces-c_static_3 libxerces-c.a xerces-c
		PATHS
		$ENV{XERCESC_LIBRARY_DIR}
		${XERCESC_LIBRARY_DIR}
		/usr/lib
		/usr/local/lib
		)
	else()
		FIND_LIBRARY(XERCESC_LIBRARY NAMES xerces-c-3.1 xerces-c
		PATHS
		$ENV{XERCESC_LIBRARY_DIR}
		${XERCESC_LIBRARY_DIR}
		/usr/lib
		/usr/local/lib
		)
	endif()
endif()

MARK_AS_ADVANCED(XERCESC_INCLUDE XERCESC_LIBRARY)

#############################################################################

### Set find flag ###
if(XERCESC_INCLUDE AND XERCESC_LIBRARY)
	set(XERCESC_FOUND true)
else()
	set(XERCESC_FOUND false)
endif()

#############################################################################

### Identify library version ###
if(XERCESC_FOUND)
	FIND_PATH(XERCESC_XVERHPPPATH NAMES XercesVersion.hpp # Find Header containing Xerces Version
	PATHS
	${XERCESC_INCLUDE}
	PATH_SUFFIXES xercesc/util)

	if(${XERCESC_XVERHPPPATH} STREQUAL XERCESC_XVERHPPPATH-NOTFOUND)
		message(WARNING "   Could not find XercesVersion.hpp, please check your Xerces installation.")
		set(XERCES_VERSION "0") # Being unable to identify library version is not considered as a critical failure
	else()
		file(READ ${XERCESC_XVERHPPPATH}/XercesVersion.hpp XVERHPP) # Read file content

		# Locate version Ids
		string(REGEX MATCHALL "\n *#define XERCES_VERSION_MAJOR +[0-9]+" XVERMAJ ${XVERHPP}) # Find major version Id
		string(REGEX MATCH "\n *#define XERCES_VERSION_MINOR +[0-9]+" XVERMIN ${XVERHPP}) # Find minor version Id
		string(REGEX MATCH "\n *#define XERCES_VERSION_REVISION +[0-9]+" XVERREV ${XVERHPP}) # Find revision Id

		# Insulate Ids numbers
		STRING(REGEX REPLACE "\n *#define XERCES_VERSION_MAJOR +" "" XVERMAJ ${XVERMAJ})
		STRING(REGEX REPLACE "\n *#define XERCES_VERSION_MINOR +" "" XVERMIN ${XVERMIN})
		STRING(REGEX REPLACE "\n *#define XERCES_VERSION_REVISION +" "" XVERREV ${XVERREV})

		# Assemble version number
		SET(XERCESC_VERSION ${XVERMAJ}.${XVERMIN}.${XVERREV})
	endif()
endif()

#############################################################################

### Display library informations or error messages ###
if(XERCESC_FOUND)
	message(STATUS "   Found Xerces-C : ${XERCESC_LIBRARY}")
	message(STATUS "   Include Directory : ${XERCESC_INCLUDE}")
	message(STATUS "   Version : ${XERCESC_VERSION}")
else()
	message(FATAL_ERROR "\n   Could not find Xerces-C !
   Please visit http://xerces.apache.org/xerces-c/
   for further information and install instructions \n")
endif()

#############################################################################

#  ______________________________
# |                              |
# |    ______________________    |       
# |   |                      |   |
# |   |         sign         |   |
# |   |        coding        |   |
# |   |        dw@rf         |   |
# |   |         1.0          |   |
# |   |______________________|   |
# |                              |
# |______________________________|
#               |  |           
#               |  |             
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |  |
#               |__|
