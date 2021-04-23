/* Copyright (c) 2011-2017, NVIDIA CORPORATION. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of NVIDIA CORPORATION nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

enum THCUNN_ERROR
{
    /*********************************************************
     * Flags for status reporting
     *********************************************************/
    THCUNN_OK = 0,
    THCUNN_ERR_CUDA_FAILURE = 5,
    THCUNN_ERR_NOT_IMPLEMENTED = 13, // actually this error includes #3 and #4
};

/********************************************************
 * Prints the error message, the stack trace, and exits
 * ******************************************************/
#define FatalError(s, reason) {                                                 \
  std::stringstream _where;                                                     \
  _where << __FILE__ << ':' << __LINE__;                                        \
  std::stringstream _trace;                                                     \
  printStackTrace(_trace);                                                      \
  cudaDeviceSynchronize();                                                      \
  throw _exception(std::string(s) + "\n", _where.str(), _trace.str(), reason); \
}

#define cusparseCheckError(status) {\
    switch(status) {\
    case CUSPARSE_STATUS_SUCCESS:                   break;\
    case CUSPARSE_STATUS_NOT_INITIALIZED:           FatalError("CUSPARSE_STATUS_NOT_INITIALIZED", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_ALLOC_FAILED:              FatalError("CUSPARSE_STATUS_ALLOC_FAILED", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_INVALID_VALUE:             FatalError("CUSPARSE_STATUS_INVALID_VALUE", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_ARCH_MISMATCH:             FatalError("CUSPARSE_STATUS_ARCH_MISMATCH", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_MAPPING_ERROR:             FatalError("CUSPARSE_STATUS_MAPPING_ERROR", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_EXECUTION_FAILED:          FatalError("CUSPARSE_STATUS_EXECUTION_FAILED", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_INTERNAL_ERROR:            FatalError("CUSPARSE_STATUS_INTERNAL_ERROR", THCUNN_ERR_CUDA_FAILURE);\
    case CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED: FatalError("CUSPARSE_STATUS_MATRIX_TYPE_NOT_SUPPORTED", THCUNN_ERR_NOT_IMPLEMENTED);\
    default:                                        FatalError("unknown CUSPARSE error", THCUNN_ERR_CUDA_FAILURE);\
    }\
}
