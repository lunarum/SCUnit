#include "scunit.h"


static void SCU_TestSuite_printAction(SCU_TestSuite *pSuite, const char *pAction, scu_bool printNewline) {
    if(SCU_runMode == SCU_RUN_MODE_VERBOSE) {
        printf("%s suite '%s'", pAction, pSuite->pName);
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
    SCU_error error = SCU_SUCCES;

    if(!pSuite)
        SCU_printError(error = SCU_ERROR_NULL_POINTER);
    if(SCU_NONFATAL_ERROR(error) && pSuite->fpSetUp) {
        SCU_TestSuite_printAction(pSuite, "Setup", SCU_FALSE);
        pSuite->result = error = pSuite->fpSetUp();
        SCU_printError(error);
    }
    if(SCU_NONFATAL_ERROR(error)) {
        SCU_TestSuite_printAction(pSuite, "Running", SCU_TRUE);
        pSuite->succeeded = 0;
        pSuite->failed = 0;
        SCU_TestCase *pCase = pSuite->pTestCase;
        do {
            pCase = pCase->pNext;
            pSuite->result = error = SCU_TestCase_execute(pCase);
            if(error == SCU_SUCCES)
                ++(pSuite->succeeded);
            else {
                ++(pSuite->failed);
                if(SCU_FATAL_ERROR(error))
                    return error;
            }
        } while(pCase != pSuite->pTestCase);
        if(pSuite->failed > 0)
            pSuite->result = error = SCU_ERROR_FAILED;
        if(SCU_runMode == SCU_RUN_MODE_NORMAL)
            printf("%-20s | %04d | %04d | %04d\n",
                pSuite->pName,
                pSuite->cases,
                pSuite->succeeded,
                pSuite->failed);
        else if(SCU_runMode == SCU_RUN_MODE_VERBOSE)
            printf("Suite '%s' => total of %d tests of which %d succeeded and %d failed\n",
                pSuite->pName,
                pSuite->cases,
                pSuite->succeeded,
                pSuite->failed);
    }
    if(SCU_NONFATAL_ERROR(error) && pSuite->fpTearDown) {
        SCU_TestSuite_printAction(pSuite, "Tear down", SCU_FALSE);
        pSuite->result = error = pSuite->fpTearDown();
        SCU_printError(error);
    }

    return error;
}
