# Description :
# Find DwfCOMM library content

# Input Variables : 
# DWFCOMM_INCLUDE_DIR : set the path to Xerces include directory if it is not standard
# DWFCOMM_LIBRARY_DIR : set the path to Xerces lib directory if it is not standard

# Once done this will define :
# DWFCOMM_FOUND : set to true if Xerces-C is defined  
# DWFCOMM_INCLUDE : set the path to the Xerces-C include directory
# DWFCOMM_LIBRARY : set the path to the Xerces-C library
# DWFCOMM_VERSION : set the Xerces-C version number
# DWFCOMM_STATIC : set to true if static library is used and to false if dynamic library is used

message(STATUS "Locating DwfComm library")

### Check if data are already stored in cache ###
if(DEFINED DWFCOMM_INCLUDE AND DEFINED DWFCOMM_LIBRARY)
	set(DWFCOMM_FIND_QUIETLY true)
else()
	set(DWFCOMM_FIND_QUIETLY false)
endif()

#############################################################################

### Choose library compilation type ###
set(DWFCOMM_STATIC false) # true to use .a library, false to use .so
if(NOT DEFINED DWFCOMM_WAS_STATIC OR NOT ${DWFCOMM_WAS_STATIC} STREQUAL ${DWFCOMM_STATIC})
	unset(DWFCOMM_LIBRARY CACHE)
	unset(DWFCOMM_LIBRARY_DEBUG CACHE)
	set(DWFCOMM_FIND_QUIETLY false) # We have to find back xerces with the new library
endif()

set(DWFCOMM_WAS_STATIC ${DWFCOMM_STATIC} CACHE INTERNAL "Set to true to use static library (.a)" ) # Store previous library choice in cache

#############################################################################

### Find include directory path ###
if(NOT DWFCOMM_FIND_QUIETLY) # If it was not already found, search for Xerces include folder
	find_path(DWFCOMM_INCLUDE NAMES Version.h # Find version path
	PATHS
	$ENV{DWFCOMM_INCLUDE_DIR} # Custom search paths as an environment variable
	${DWFCOMM_INCLUDE_DIR} # Custom search paths as a CMake variable
	/usr/local/include # Default search paths
	/usr/local/include/DwfComm
	/usr/include
	/usr/include/DwfComm
	)
endif()

#############################################################################

### Find library file ###
if(NOT DWFCOMM_FIND_QUIETLY) # If it was not already found, search for Xerces library file
	if(DWFCOMM_STATIC)
		FIND_LIBRARY(DWFCOMM_LIBRARY NAMES DwfComm_static
		PATHS
		$ENV{DWFCOMM_LIBRARY_DIR}
		${DWFCOMM_LIBRARY_DIR}
		/usr/lib
		/usr/lib/DwfComm
		/usr/local/lib
		/usr/local/lib/DwfComm
		)
	else()
		FIND_LIBRARY(DWFCOMM_LIBRARY NAMES DwfComm
		PATHS
		$ENV{DWFCOMM_LIBRARY_DIR}
		${DWFCOMM_LIBRARY_DIR}
		/usr/lib
		/usr/lib/DwfComm
		/usr/local/lib
		/usr/local/lib/DwfComm
		)
	endif()
endif()

MARK_AS_ADVANCED(DWFCOMM_INCLUDE DWFCOMM_LIBRARY)

#############################################################################

### Set find flag ###
if(DWFCOMM_INCLUDE AND DWFCOMM_LIBRARY)
	set(DWFCOMM_FOUND true)
else()
	set(DWFCOMM_FOUND false)
endif()

#############################################################################

### Identify library version ###
if(DWFCOMM_FOUND)
	FIND_PATH(DWFCOMM_VERHPATH NAMES Version.h # Find Header containing Xerces Version
	PATHS
	${DWFCOMM_INCLUDE}
	PATH_SUFFIXES DWFCOMM)

	if(${DWFCOMM_VERHPATH} STREQUAL DWFCOMM_VERHPATH-NOTFOUND)
		message(WARNING "   Could not find Version.h, please check your DwfComm installation.")
		set(DWFCOMM_VERSION "0") # Being unable to identify library version is not considered as a critical failure
	else()
		file(READ ${DWFCOMM_VERHPATH}/Version.h VERH) # Read file content

		# Locate version Ids
		string(REGEX MATCHALL "\n *#define DWFCOMM_VERSION_MAJOR +[0-9]+" XVERMAJ ${VERH}) # Find major version Id
		string(REGEX MATCH "\n *#define DWFCOMM_VERSION_MINOR +[0-9]+" XVERMIN ${VERH}) # Find minor version Id
		string(REGEX MATCH "\n *#define DWFCOMM_VERSION_REVISION +[0-9]+" XVERREV ${VERH}) # Find revision Id

		# Insulate Ids numbers
		string(REGEX REPLACE "\n *#define DWFCOMM_VERSION_MAJOR +" "" XVERMAJ ${XVERMAJ})
		string(REGEX REPLACE "\n *#define DWFCOMM_VERSION_MINOR +" "" XVERMIN ${XVERMIN})
		string(REGEX REPLACE "\n *#define DWFCOMM_VERSION_REVISION +" "" XVERREV ${XVERREV})

		# Assemble version number
		set(DWFCOMM_VERSION ${XVERMAJ}.${XVERMIN}.${XVERREV})
	endif()
endif()

#############################################################################

### Display library informations or error messages ###
if(DWFCOMM_FOUND)
	message(STATUS "   Found DwfCOMM : ${DWFCOMM_LIBRARY}")
	message(STATUS "   Include Directory : ${DWFCOMM_INCLUDE}")
	message(STATUS "   Version : ${DWFCOMM_VERSION}")
else()
	message(FATAL_ERROR "\n   Could not find DwfComm library !
   Please visit https://github.com/SignCodingDwarf/DwfComm
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
