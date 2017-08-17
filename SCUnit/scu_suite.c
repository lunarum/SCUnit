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


static void SCU_TestSuite_printAction(SCU_TestSuite *pSuite, const char *pAction, SCU_bool printNewline) {
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE) {
        printf("%s test suite '%s'", pAction, pSuite->pName);
        if(printNewline)
            putchar('\n');
        else
            printf(" => ");
    }
}

SCU_TestSuite *SCU_TestSuite_create(const char *pName, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown) {
    SCU_TestSuite *pSuite = 0;

    /* name must be filled */
    if(pName) {
        pSuite = malloc(sizeof(SCU_TestCase));
        if(pSuite) {
            if(SCU_lastTestSuite) {
                pSuite->pNext = SCU_lastTestSuite->pNext;
                SCU_lastTestSuite->pNext = pSuite;
            } else
                pSuite->pNext = pSuite;
            SCU_lastTestSuite = pSuite;
            pSuite->pName = pName;
            pSuite->fpSetUp = fpSetUp;
            pSuite->fpTearDown = fpTearDown;
            pSuite->pTestCase = 0;
            pSuite->cases = 0;
        }
    }

    return pSuite;
}

SCU_error SCU_TestSuite_execute(SCU_TestSuite *pSuite) {
    SCU_error error = SCU_SUCCESS;

    if(!pSuite) {
        SCU_printError(SCU_ERROR_NULL_POINTER);
        return SCU_ERROR_NULL_POINTER;
    }
    if(pSuite->fpSetUp) {
        SCU_TestSuite_printAction(pSuite, "Setup", SCU_FALSE);
        error = pSuite->fpSetUp();
        SCU_printError(error);
        if(SCU_FATAL_ERROR(error))
            return (pSuite->result = error);
    }
    
    SCU_TestSuite_printAction(pSuite, "Running", SCU_TRUE);
    pSuite->succeeded = 0;
    pSuite->failed = 0;
    SCU_currentTestCase = pSuite->pTestCase;
    do {
        SCU_currentTestCase = SCU_currentTestCase->pNext;
        error = SCU_TestCase_execute(SCU_currentTestCase);
        if(error == SCU_SUCCESS)
            ++(pSuite->succeeded);
        else {
            ++(pSuite->failed);
            if(SCU_FATAL_ERROR(error))
                return (pSuite->result = error);
        }
    } while(SCU_currentTestCase != pSuite->pTestCase);
    SCU_currentTestCase = NULL;

    if(SCU_runMode == SCU_RUN_MODE_NORMAL)
        printf("%-20s | %04d | %04d | %04d\n",
            pSuite->pName,
            pSuite->cases,
            pSuite->succeeded,
            pSuite->failed);
    else if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
        printf("Suite '%s' => total of %d testcases of which %d succeeded and %d failed\n",
            pSuite->pName,
            pSuite->cases,
            pSuite->succeeded,
            pSuite->failed);

    if(pSuite->fpTearDown) {
        SCU_TestSuite_printAction(pSuite, "Tear down", SCU_FALSE);
        error = pSuite->fpTearDown();
        SCU_printError(error);
        if(SCU_FATAL_ERROR(error))
            return (pSuite->result = error);
    }
    
    pSuite->result = (pSuite->failed > 0) ? SCU_FAILED : SCU_SUCCESS;
    return pSuite->result;
}
