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

#include <stdio.h>
#include "scu_assert.h"

extern SCU_error SCU_assert(int lineNo, SCU_bool assertion, const char *pMessage, unsigned long realValue) {
    if(SCU_currentTestCase == NULL || pMessage == NULL) {
        return SCU_ERROR_NULL_POINTER;
    }
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE) {
        printf("ASSERT (%04d) %s (%lu) => %s\n",
            lineNo,
            pMessage,
            realValue,
            assertion ? "SUCCES" : "FAILED");
    }
    (SCU_currentTestCase->assertions)++;
    if(assertion) {
        (SCU_currentTestCase->succeeded)++;
        return SCU_SUCCESS;
    }
    (SCU_currentTestCase->failed)++;
    return SCU_FAILED;
}
