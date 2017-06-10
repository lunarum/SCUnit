#ifndef SCU_ERRORS_H
#define SCU_ERRORS_H

typedef enum {
    SCU_SUCCES                  =   0,  /**< succes; no error */
    
    SCU_ERROR_NO_SUITES         =  -1,  /**< no suites defined */
    SCU_ERROR_NO_TESTS          =  -2,  /**< no tests defined */
    SCU_ERROR_NULL_POINTER      =  -3,  /**< null pointer encountered */
    SCU_ERROR_SETUP_FAILED      = -10,  /**< setup function failed */
    SCU_ERROR_TEARDOWN_FAILED   = -11,  /**< teardown function failed */
    
    SCU_ERROR_FAILED            =   1   /**< test failed */
} SCU_error;

#define SCU_FATAL_ERROR(x) ((x) < 0)
#define SCU_NONFATAL_ERROR(x) ((x) >= 0)

#endif