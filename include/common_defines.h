/*!
 * @file common_defines.h
 * @brief Common Macros Definition
 * @author Sign Coding Dwarf
 * @version 1.2
 * @date 10 October 2016
 *
 * Definition of macros common to all designed applications
 *
 */

#ifndef COMMON_DEFINES
#define COMMON_DEFINES

///////////////////////////// Global defines

/*! 
* @def EXEC_SUCCESS
* @brief Execution of a function succeeded
*/
#ifndef EXEC_SUCCESS
#define EXEC_SUCCESS 0 
#endif

/*! 
* @def EXEC_FAILURE
* @brief Execution of a function failed
*/
#ifndef EXEC_FAILURE
#define EXEC_FAILURE 1
#endif

#ifndef DEBUG
/*! 
* @def DEBUG
* @brief Preprocessor to enable debug output
*
* DEBUG is used to perform debug mode specific operations. Set to 1 (default value) to enable and to 0 to disable. Change value in \a common_defines.h or as compiling preprocessor flag (recommended) : \a -DDEBUG=0 <br>
* This macro can be complemented/replaced by NDEBUG macro if needed
*
*/
#define DEBUG 1 // Default behavior is debug enabled
#endif


///////////////////////////// Check the use of features

#if __cplusplus >= 201103L // Compiler supports C++11
#ifndef USE_SHARED_POINTERS
/*! 
* @def USE_SHARED_POINTERS
* @brief Check if shared pointers can be used
*
*  Checking if shared pointers use is allowed is done with \#if USE_SHARED_POINTERS. By default this choice is determined by compiler support of C++11. However a different choice can be specified using compiling preprocessor flag : \a -DUSE_SHARED_POINTERS=\<value\>
*
*/
#define USE_SHARED_POINTERS 1
#endif

#ifndef USE_AUTO_LOOPS
/*! 
* @def USE_AUTO_LOOPS
* @brief Check if auto loops can be used
*
*  Checking if auto loops (i.e. range based syntax and auto keyword in loops) is allowed is done with \#if USE_AUTO_LOOPS. By default this choice is determined by compiler support of C++11. However a different choice can be specified using compiling preprocessor flag : <br>
* \a -DUSE_AUTO_LOOPS=\<value\>
*
*/
#define USE_AUTO_LOOPS 1
#endif

#ifndef USE_LAMBDA_FUNCTIONS
/*! 
* @def USE_LAMBDA_FUNCTIONS
* @brief Check if lambda functions can be used
*
*  Checking if lambda functions (i.e. anonymous inline functions) is allowed is done with \#if USE_LAMBDA_FUNCTIONS. By default this choice is determined by compiler support of C++11. However a different choice can be specified using compiling preprocessor flag : <br>
* \a -DUSE_LAMBDA_FUNCTIONS=\<value\>
*
*/
#define USE_LAMBDA_FUNCTIONS 1
#endif

#else // Compiler does not support C++11

#ifndef USE_SHARED_POINTERS
#define USE_SHARED_POINTERS 0
#endif

#ifndef USE_AUTO_LOOPS
#define USE_AUTO_LOOPS 0
#endif

#ifndef USE_LAMBDA_FUNCTIONS
#define USE_LAMBDA_FUNCTIONS 0
#endif

#endif

#endif

//  ______________________________
// |                              |
// |    ______________________    |       
// |   |                      |   |
// |   |         sign         |   |
// |   |        coding        |   |
// |   |        dw@rf         |   |
// |   |         1.0          |   |
// |   |______________________|   |
// |                              |
// |______________________________|
//               |  |           
//               |  |             
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |  |
//               |__|

