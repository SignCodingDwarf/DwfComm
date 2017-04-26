# Description :
# Find Qt content for Qt4 or Qt5 Software versions

# Input Variables :
# USE_4 : set to true to use directly QT4, set to false to use QT5 (default is false)
# QT5_PATH : set the path to Qt5Config.cmake (default is "$ENV{HOME}/Qt/5.3/gcc_64/lib/cmake/Qt5/")

# Once done this will define :
# QT_INCLUDES : Qt include files list
# QT_DEFINITIONS : Qt Definitions list
# QT_LIBRARIES : Qt libraries list

# Allow automatic generation of Qt moc files
set(CMAKE_AUTOMOC ON)

# Checking Input variables existence. If they don't exist set them to default value
if(NOT DEFINED USE_4)
	message(WARNING "Qt4 use preferences not specified")
	set(USE_4 false)
endif()

if(NOT USE_4 AND NOT DEFINED QT5_PATH) #If Qt4 is used no need to set QT5_PATH since it won't be used
	set(QT5_PATH "$ENV{HOME}/Qt/5.3/gcc_64/lib/cmake/Qt5/")
endif()


# Search for QT and set required variables
if(NOT USE_4) # If Qt4 use is not favored, try to find Qt5

	message(STATUS "Trying to Find Qt5")

	list(APPEND CMAKE_PREFIX_PATH "${QT5_PATH}")
	
	if(EXISTS "${QT5_PATH}Qt5Config.cmake" OR EXISTS "${QT5_PATH}/Qt5Config.cmake") #If Qt5 is installed and well located, Qt5Config.cmake should exist

		find_package(Qt5 REQUIRED Core Gui Widgets) #!#!# Add other Qt components here #!#!#
		if(Qt5Core_FOUND AND Qt5Gui_FOUND)

			message(STATUS "Qt5 found")
			set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS})
			list(APPEND QT_INCLUDES ${Qt5Gui_INCLUDE_DIRS})
			list(APPEND QT_INCLUDES ${Qt5Widgets_INCLUDE_DIRS}) #!#!# Add other include directories here #!#!#
			set(QT_LIBRARIES ${Qt5Core_LIBRARIES})
			list(APPEND QT_LIBRARIES ${Qt5Gui_LIBRARIES})
			list(APPEND QT_LIBRARIES ${Qt5Widgets_LIBRARIES}) #!#!# Add other libraries here #!#!#

			message(STATUS ${QT_INCLUDES})
			message(STATUS ${QT_DEFINITIONS})
			message(STATUS ${QT_LIBRARIES})

			set(QT5_FOUND true)
		else()

			set(QT5_FOUND false)

		endif()

	else() #If not, try to install using QT4

		set(QT5_FOUND false)

	endif()	
endif()


if(USE_4 OR NOT QT5_FOUND) # If Qt4 use is favored or if Qt5 was not found, try to find Qt4

	message(STATUS "Trying to Find Qt4")
	find_package(Qt4 REQUIRED QtCore QtGui) #!#!# Add other Qt components here #!#!#
	if(NOT QT_FOUND)
		message(FATAL_ERROR "Could not find Qt. You must install Qt !!!!!!")
	endif()

	include(${QT_USE_FILE})

	#Variables are defined automatically by FindQt4. Nothing else to do
endif()
