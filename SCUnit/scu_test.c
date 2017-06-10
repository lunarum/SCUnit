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
