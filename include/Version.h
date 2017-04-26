/*!
 * @file Version.h
 * @brief Version information about DwfComm lib 
 * @author Sign Coding Dwarf
 * @version 1.0
 * @date 03 February 2017
 *
 * Definition of DwfComm version constants and numeric form.
 *
 */

/* 
Copyright 2016 SignCodingDwarf

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

/*! 
* @def DWFCOMM_VERSION_MAJOR
* @brief Major version number
*/
#define DWFCOMM_VERSION_MAJOR 1

/*! 
* @def DWFCOMM_VERSION_MINOR
* @brief Minor version number
*/
#define DWFCOMM_VERSION_MINOR 0

/*! 
* @def DWFCOMM_VERSION_REVISION
* @brief Revision version number (not used in our applications)
*
* Not used for this library but kept for compatibility with traditional library versionning
*
*/
#define DWFCOMM_VERSION_REVISION 0

#define DWFVERSION(d,w,f) d * 55776168 + w * 27972 + f * 42 

#define DWFCOMM_VERSION DWFVERSION(DWFCOMM_VERSION_MAJOR,DWFCOMM_VERSION_MINOR,DWFCOMM_VERSION_REVISION)

/*! 
* @def DWFCOMM_VERSION_NUMERIC 
* @brief Version as a numeric constant for compilation purport
*
* To check if library has indeed current version do 
* \a \#if \a DWFCOMM_VERSION_NUMERIC==55776168
*
*/
#define DWFCOMM_VERSION_NUMERIC DWFCOMM_VERSION

