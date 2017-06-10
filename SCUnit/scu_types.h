#ifndef SCU_TYPES_H
#define SCU_TYPES_H

#include "scu_errors.h"


typedef int scu_bool;
#define SCU_FALSE (0)
#define SCU_TRUE (!0)

typedef SCU_error (*SCU_SetUpFunc)(void);       /**< setup function of a suite or a test */
typedef SCU_error (*SCU_TearDownFunc)(void);    /**< tear down function of a suite or a test */
typedef SCU_error (*SCU_TestCaseFunc)(void);    /**< actual test case(s) function */

typedef struct SCU_TestCase {
    const char *pName;              /**< test suite name */
    struct SCU_TestCase *pNext;     /**< pointer to next test in a circular single linked list */
    SCU_SetUpFunc fpSetUp;          /**< setup function of this suite */
    SCU_TearDownFunc fpTearDown;    /**< tear down function of this suite */
    SCU_TestCaseFunc fpTestCase;    /**< the actual test case */
    SCU_error result;               /**< the result of the test case */
} SCU_TestCase;

typedef struct SCU_TestSuite {
    const char *pName;              /**< test suite name */
    struct SCU_TestSuite *pNext;    /**< pointer to next suite in a circular single linked list */
    SCU_TestCase  *pTestCase;       /**< pointer to the last test case */
    SCU_SetUpFunc fpSetUp;          /**< setup function of this suite */
    SCU_TearDownFunc fpTearDown;    /**< tear down function of this suite */
    unsigned int cases;             /**< number of test cases in this suite */
    unsigned int succeeded;         /**< number of succeeded test cases */
    unsigned int failed;            /**< number of failed test cases */
    SCU_error result;               /**< the actual result */
} SCU_TestSuite;

typedef enum {
    SCU_RUN_MODE_SILENT,
    SCU_RUN_MODE_NORMAL,
    SCU_RUN_MODE_VERBOSE
} SCU_RunMode;

extern SCU_RunMode SCU_runMode;
extern SCU_TestSuite *SCU_lastTestSuite;

#endif
