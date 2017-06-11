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

SCU_RunMode SCU_runMode = SCU_RUN_MODE_NORMAL;
SCU_TestSuite *SCU_lastTestSuite = 0;


void SCU_printError(SCU_error error) {
    if(SCU_FATAL_ERROR(error))
        fprintf(stderr, "FATAL ERROR %d\n", error);
    else
        if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
            if(error == SCU_SUCCES)
                printf("SUCCESS\n");
            else
                printf("ERROR %d\n", error);
}

SCU_error SCU_executeAllTests() {
    SCU_error error = SCU_SUCCES;
    int cases = 0, succeeded = 0, failed = 0;
    
    if(SCU_lastTestSuite) {
        if(SCU_runMode == SCU_RUN_MODE_NORMAL)
            printf("Test Suite           | Cases| Succ | Fail\n"\
                   "---------------------+------+------+------\n");
        SCU_TestSuite *pSuite = SCU_lastTestSuite;
        do {
            pSuite = pSuite->pNext;
            error = SCU_TestSuite_execute(pSuite);
            cases += pSuite->cases;
            succeeded += pSuite->succeeded;
            failed += pSuite->failed;
            if(SCU_FATAL_ERROR(error))
                return error;
        } while(pSuite != SCU_lastTestSuite);
        if(SCU_runMode == SCU_RUN_MODE_NORMAL)
            printf("---------------------+------+------+------\n"\
                "%-20s | %04d | %04d | %04d\n",
                "TOTAL",
                cases,
                succeeded,
                failed);
        else if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
            printf("Unit test composed of %d tests of which %d succeeded and %d failed\n",
                cases,
                succeeded,
                failed);

        if(failed > 0)
            error = SCU_ERROR_FAILED;
    } else {
        SCU_printError(error = SCU_ERROR_NO_SUITES);
    }
    
    return error;
}