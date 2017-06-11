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

#include "scunit.h"

static void SCU_TestCase_printAction(SCU_TestCase *pTestCase, const char *pAction, SCU_bool printNewline){
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE) {
        printf("%s test case '%s'", pAction, pTestCase->pName);
        if(printNewline)
            putchar('\n');
        else
            printf(" => ");
    }
}

SCU_TestCase *SCU_TestCase_create(SCU_TestSuite *pTestSuite, const char *pName, SCU_TestCaseFunc fpTestCase, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown) {
    SCU_TestCase *pTestCase = NULL;

    /* suite, name and test-function must be filled */
    if(pTestSuite && pName && fpTestCase) {
        pTestCase = malloc(sizeof(SCU_TestCase));
        if(pTestCase) {
            if(pTestSuite->pTestCase) {
                pTestCase->pNext = pTestSuite->pTestCase->pNext;
                pTestSuite->pTestCase->pNext = pTestCase;
            } else
                pTestCase->pNext = pTestCase;
            pTestSuite->pTestCase = pTestCase;
            pTestSuite->cases++;
            pTestCase->pName = pName;
            pTestCase->fpTestCase = fpTestCase;
            pTestCase->fpSetUp = fpSetUp;
            pTestCase->fpTearDown = fpTearDown;
        }
    }

    return pTestCase;
}

SCU_error SCU_TestCase_execute(SCU_TestCase *pTestCase) {
    SCU_error error = SCU_SUCCESS;

    if(!pTestCase) {
        SCU_printError(SCU_ERROR_NULL_POINTER);
        return SCU_ERROR_NULL_POINTER;
    }
    
    if(pTestCase->fpSetUp) {
        SCU_TestCase_printAction(pTestCase, "Setup", SCU_FALSE);
        error = pTestCase->fpSetUp();
        SCU_printError(error);
        if(SCU_FATAL_ERROR(error))
            return (pTestCase->result = error);
    }

    SCU_TestCase_printAction(pTestCase, "Running", SCU_TRUE);
    pTestCase->assertions = 0;
    pTestCase->succeeded = 0;
    pTestCase->failed = 0;
    error = pTestCase->fpTestCase();
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
        printf("Case '%s' => total of %d assertions of which %d succeeded and %d failed\n",
            pTestCase->pName,
            pTestCase->assertions,
            pTestCase->succeeded,
            pTestCase->failed);
    SCU_TestCase_printAction(pTestCase, "Result", SCU_FALSE);
    SCU_printError(error);
    if(SCU_FATAL_ERROR(error))
        return (pTestCase->result = error);

    if(pTestCase->fpTearDown) {
        SCU_TestCase_printAction(pTestCase, "Tear down", SCU_FALSE);
        error = pTestCase->fpTearDown();
        SCU_printError(error);
        if(SCU_FATAL_ERROR(error))
            return (pTestCase->result = error);
    }

    pTestCase->result = (pTestCase->failed > 0) ? SCU_FAILED : SCU_SUCCESS;
    return pTestCase->result;
}
