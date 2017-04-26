#!/bin/bash

# file :  cmakeUbuntuMake.sh
# author : Sign Coding Dwarf
# version : 1.0
# date : 21 March 2016
# Script to run CMake application and set some compilation and build options

### command line options
##            General Options
# -h or --help : print help and exit
# -c or --clean : clean up CMake temporary directory after compile
##           Compiling Options
# -o=[file] or --compiler=[file] : use the CXX compiler defined by [file] instead of default CXX compiler
# -r or --release : build in release mode
# -u or --userDebug : enable user debug specific operations
##	    Qt Compiling Options
# -4 : set use Qt4 to true
# -5=[path] or --pathQt5=[path] : set QT5 search path to [path]


### Initialization
# Colors
helpCommandColor='\033[1;34m' #Help on command is printed in light blue
helpOptionsColor='\033[1;32m' #Help on options is printed in light green
helpCategoryColor="\033[1;33m" # Help options categories are printed in yellow
statusColor='\033[1;32m' #Status messages are printed in light green
NC='\033[0m' # No Color

# Behavior variables
HELP=false
USE4=false
TCLEAN=false
QT5_PATH=""
PATH_DEF=false
COMPILER_CHANGED=false
COMPILER=""
RELEASE_BUILD=false
USER_DEBUG=false

CMAKE_OPTIONS="" #Variable containing all the CMAKE options. Append new options to this variable

### Parse arguments values : 
for i in "$@" # for every input argument
do
	case $i in
		-h|--help) # if ask to render help
		HELP=true
		;;
		-c|--clean) # remove temporary CMake and compile Files
		TCLEAN=true
		;;
		-o=*|--compiler=*) # use a different CXX compiler from default system compiler
		COMPILER="${i#*=}" # extract CXX compiler 
		COMPILER_CHANGED=true		
		;;
		-r|--release) # compile in release mode
		RELEASE_BUILD=true
		;;
		-u|--userDebug) # enable user debug
		USER_DEBUG=true
		;;
		-4) # use Qt4 instead of Qt5 libraries
		USE4=true
		;;
		-5=*|--pathQt5=*)
		QT5_PATH="${i#*=}" # extract path
		PATH_DEF=true
		;;

		*) #default nothing is done
		;;
	esac

done

### If asked for help, print help then exit
if($HELP)
then
	echo "Usage"
	echo
	echo "${helpCommandColor} sh cmakeUbuntuMake.sh [options]"
	echo
	
	echo "${NC}Options"
	echo "${helpCategoryColor}------ General Options ------"
	echo "${helpOptionsColor}-h ${NC}or ${helpOptionsColor}--help${NC}                   =  Print help and exit"
	echo "${helpOptionsColor}-c ${NC}or ${helpOptionsColor}--clean${NC}                  =  Clean CMake and compiling temporary files after compilation"
	echo "${helpCategoryColor}------ Compiling Options ------"
	echo "${helpOptionsColor}-o=[file] ${NC}or ${helpOptionsColor}--compiler=[file]${NC} =  use the CXX compiler defined by [file] instead of default CXX compiler"
	echo "${helpOptionsColor}-r ${NC}or ${helpOptionsColor}--release${NC}                =  build in release mode"
	echo "${helpOptionsColor}-u ${NC}or ${helpOptionsColor}--userDebug${NC}              =  enable user debug specific operations"
	echo "${helpCategoryColor}------ Qt Compiling Options ------"
	echo "${helpOptionsColor}-4 ${NC}                            =  Set to compile code with Qt4 libraries instead of Qt5 ones"
	echo "${helpOptionsColor}-5=[path] ${NC}or ${helpOptionsColor}--pathQt5=[path]${NC}  =  Set Qt5 search path to [path]"

	exit 0 # Exit after printing help
fi

### Creating storage directory
if [ ! -d "build_dir" ]; then #if temporary directory does not exist
  echo "${statusColor}Creating compile files directory ${NC}"
  mkdir build_dir
fi

### Set CMake options for compiler version
CMAKE_OPTIONS=-DCOMPILER_CHANGED:BOOL=$COMPILER_CHANGED

if $COMPILER_CHANGED
then
	CMAKE_OPTIONS="$CMAKE_OPTIONS -DCOMPILER_FILE:STRING=$COMPILER"
fi

### Set CMake options for build type
CMAKE_OPTIONS="$CMAKE_OPTIONS -DRELEASE_BUILD:BOOL=$RELEASE_BUILD"

### Set CMake options for user debug flags
CMAKE_OPTIONS="$CMAKE_OPTIONS -DUSER_DEBUG:BOOL=$USER_DEBUG"

### Set CMake options for Qt version
CMAKE_OPTIONS="$CMAKE_OPTIONS -DUSE_4:BOOL=$USE4"

if $PATH_DEF
then
	CMAKE_OPTIONS="$CMAKE_OPTIONS -DQT5_PATH:STRING=${QT5_PATH}"
fi

### Running CMake
echo "${statusColor}Running CMake ${NC}"
sudo cmake -H. -Bbuild_dir -G "Unix Makefiles" $CMAKE_OPTIONS #set up cmake and generate makefile

### Compiling
echo "${statusColor}Compiling ${NC}"
cd build_dir
make

### Installing
files=$(ls ../lib*.a -U 2> /dev/null | wc -l)
if [ "$files" != "0" ] # Check if a library has been generated 
then
	echo "${statusColor}Installing library ${NC}" # Install the generated library
	sudo make install
fi

### Cleaning temporary directory
if $TCLEAN
then
	echo "${statusColor}Removing temporary directory ${NC}"
	cd ..
	sudo rm -r build_dir
fi

### Exit program
exit 0


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
