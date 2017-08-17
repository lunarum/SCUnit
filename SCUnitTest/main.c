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

#include <string.h>
#include "scunit.h"


SCU_error test_setup() {
    return SCU_SUCCESS;
}

SCU_error test_teardown() {
    return SCU_SUCCESS;
}

SCU_error test_ok() {
    SCU_error error;
    int myVar = 42;
    
    error = SCU_ASSERT(myVar == 42, myVar);
    
    return error;
}

SCU_error test_struct() {
    SCU_error error;
    struct dummy { int var1, var2; } myVar1, myVar2;
    
    error = SCU_ASSERT(&myVar1 == &myVar2, &myVar1);
    if(SCU_FATAL_ERROR(error))
        return error;
    error = SCU_ASSERT(&myVar1 != &myVar2, &myVar1);
    
    return error;
}

SCU_error test_failed() {
    SCU_error error;
    int myVar = 41;
    
    error = SCU_ASSERT(myVar > 100, myVar);
    
    return error;
}

int main(int argc, char **argv)
{
	printf("Simple C Unit test framework\n\n");
 
    for(int n = 1; n < argc; ++n) {
        if(strcmp(argv[n], "-v") == 0 || strcmp(argv[n], "-verbose") == 0)
            SCU_runMode = SCU_RUN_MODE_VERBOSE;
        else if(strcmp(argv[n], "-f") == 0 || strcmp(argv[n], "-failed") == 0)
            SCU_runMode = SCU_RUN_MODE_FAILED;
        else if(strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "-silent") == 0)
            SCU_runMode = SCU_RUN_MODE_SILENT;
    }

    SCU_TestSuite *pSuite = SCU_TestSuite_create("Suite-1", NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-11", test_ok, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-12", test_struct, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-13", test_ok, test_setup, test_teardown);
    pSuite = SCU_TestSuite_create("Suite-2", test_setup, test_teardown);
    SCU_TestCase_create(pSuite, "Case-21", test_ok, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-22", test_failed, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-23", test_ok, test_setup, test_teardown);

    SCU_error error = SCU_executeAllTests();

	return error;
}
