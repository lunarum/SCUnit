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

static void SCU_TestCase_printAction(SCU_TestCase *pTestCase, const char *pAction){
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
        printf("%s test '%s' => ", pAction, pTestCase->pName);
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
    SCU_error error = SCU_SUCCES;

    if(!pTestCase)
        SCU_printError(error = SCU_ERROR_NULL_POINTER);
    if(SCU_NONFATAL_ERROR(error) && pTestCase->fpSetUp) {
        SCU_TestCase_printAction(pTestCase, "Setup");
        pTestCase->result = error = pTestCase->fpSetUp();
        SCU_printError(error);
    }
    if(SCU_NONFATAL_ERROR(error)) {
        SCU_TestCase_printAction(pTestCase, "Running");
        pTestCase->result = error = pTestCase->fpTestCase();
        SCU_printError(error);
    }
    if(SCU_NONFATAL_ERROR(error) && pTestCase->fpTearDown) {
        SCU_TestCase_printAction(pTestCase, "Tear down");
        pTestCase->result = error = pTestCase->fpTearDown();
        SCU_printError(error);
    }

    return error;
}
