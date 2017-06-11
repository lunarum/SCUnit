/*
 *  SCUnit - A Simple C Unit testing framework
 * 
 *  Copyright 2017 Remco van Maanen
 *
 *  This file is part of the SCUnit framework
 * 
 *  SCUnit is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  SCUnit is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. (see file COPYING)
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SCU_ERRORS_H
#define SCU_ERRORS_H

typedef enum {
    SCU_SUCCES                  =   0,  /**< succes; no error */
    
    SCU_ERROR_NO_SUITES         =  -1,  /**< no suites defined */
    SCU_ERROR_NO_TESTS          =  -2,  /**< no tests defined */
    SCU_ERROR_NULL_POINTER      =  -3,  /**< null pointer encountered */
    SCU_ERROR_SETUP_FAILED      = -10,  /**< setup function failed */
    SCU_ERROR_TEARDOWN_FAILED   = -11,  /**< teardown function failed */
    
    SCU_ERROR_FAILED            =   1   /**< test failed */
} SCU_error;

#define SCU_FATAL_ERROR(x) ((x) < 0)
#define SCU_NONFATAL_ERROR(x) ((x) >= 0)

#endif