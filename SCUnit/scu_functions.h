#ifndef SCU_FUNCTIONS_H
#define SCU_FUNCTIONS_H

extern SCU_TestSuite *SCU_TestSuite_create(const char *pName, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown);
extern SCU_error SCU_TestSuite_execute(SCU_TestSuite *pSuite);
extern SCU_TestCase *SCU_TestCase_create(SCU_TestSuite *pTestSuite, const char *pName, SCU_TestCaseFunc fpTest, SCU_SetUpFunc fpSetUp, SCU_TearDownFunc fpTearDown);
extern SCU_error SCU_TestCase_execute(SCU_TestCase *pTestCase);
extern SCU_error SCU_executeAllTests();

void SCU_printError(SCU_error error);

#endif