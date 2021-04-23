enum THCUNN_ERROR
{
    /*********************************************************
     * Flags for status reporting
     *********************************************************/
    THCUNN_OK = 0,
    THCUNN_ERR_CUDA_FAILURE = 5,
    THCUNN_ERR_NOT_IMPLEMENTED = 13, // actually this error includes #3 and #4
};

