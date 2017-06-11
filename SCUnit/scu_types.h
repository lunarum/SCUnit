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

#ifndef SCU_TYPES_H
#define SCU_TYPES_H

#include "scu_errors.h"


typedef int SCU_bool;
#define SCU_FALSE (0)
#define SCU_TRUE (!0)

typedef SCU_error (*SCU_SetUpFunc)(void);                       /* setup function of a suite or a test */
typedef SCU_error (*SCU_TearDownFunc)(void);                    /* tear down function of a suite or a test */
typedef SCU_error (*SCU_TestCaseFunc)(void);    /* actual test case(s) function */

typedef struct SCU_TestCase {
    const char *pName;              /* test suite name */
    struct SCU_TestCase *pNext;     /* pointer to next test in a circular single linked list */
    SCU_SetUpFunc fpSetUp;          /* setup function of this suite */
    SCU_TearDownFunc fpTearDown;    /* tear down function of this suite */
    SCU_TestCaseFunc fpTestCase;    /* the actual test case */
    unsigned int assertions;        /* number of assertions run in this suite */
    unsigned int succeeded;         /* number of succeeded assertions */
    unsigned int failed;            /* number of failed assetions */
    SCU_error result;               /* the result of the test case */
} SCU_TestCase;

typedef struct SCU_TestSuite {
    const char *pName;              /* test suite name */
    struct SCU_TestSuite *pNext;    /* pointer to next suite in a circular single linked list */
    SCU_TestCase  *pTestCase;       /* pointer to the last test case */
    SCU_SetUpFunc fpSetUp;          /* setup function of this suite */
    SCU_TearDownFunc fpTearDown;    /* tear down function of this suite */
    unsigned int cases;             /* number of test cases in this suite */
    unsigned int succeeded;         /* number of succeeded test cases */
    unsigned int failed;            /* number of failed test cases */
    SCU_error result;               /* the actual result */
} SCU_TestSuite;

typedef enum {
    SCU_RUN_MODE_SILENT,    /* silent; no output */
    SCU_RUN_MODE_NORMAL,    /* default mode, print only test suite results */
    SCU_RUN_MODE_VERBOSE    /* print everything worth printing */
} SCU_RunMode;

extern SCU_RunMode    SCU_runMode;
extern SCU_TestSuite *SCU_lastTestSuite;
extern SCU_TestSuite *SCU_currentTestSuite;
extern SCU_TestCase  *SCU_currentTestCase;

#endif
