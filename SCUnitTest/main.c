#include <string.h>
#include "scunit.h"


SCU_error test_setup() {
    return SCU_SUCCES;
}

SCU_error test_teardown() {
    return SCU_SUCCES;
}

SCU_error test_ok() {
    return SCU_SUCCES;
}

SCU_error test_failed() {
    return SCU_ERROR_FAILED;
}

int main(int argc, char **argv)
{
	printf("Simple C Unit test framework\n\n");
 
    for(int n = 1; n < argc; ++n) {
        if(strcmp(argv[n], "-v") == 0 || strcmp(argv[n], "-verbose") == 0)
            SCU_runMode = SCU_RUN_MODE_VERBOSE;
        else if(strcmp(argv[n], "-s") == 0 || strcmp(argv[n], "-silent") == 0)
            SCU_runMode = SCU_RUN_MODE_SILENT;
    }

    SCU_TestSuite *pSuite = SCU_TestSuite_create("Suite-1", NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-11", test_ok, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-12", test_ok, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-13", test_ok, test_setup, test_teardown);
    pSuite = SCU_TestSuite_create("Suite-2", test_setup, test_teardown);
    SCU_TestCase_create(pSuite, "Case-21", test_ok, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-22", test_failed, NULL, NULL);
    SCU_TestCase_create(pSuite, "Case-23", test_ok, test_setup, test_teardown);

    SCU_error error = SCU_executeAllTests();

	return error;
}
