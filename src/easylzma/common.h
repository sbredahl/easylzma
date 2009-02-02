#ifndef __EASYLZMACOMMON_H__ 
#define __EASYLZMACOMMON_H__ 

#include <stdlib.h>

/** error codes */

/** no error */
#define ELZMA_E_OK                               0
/** bad parameters passed to an ELZMA function */
#define ELZMA_E_BAD_PARAMS                      10
/** could not initialize the encode with configured parameters. */
#define ELZMA_E_ENCODING_PROPERTIES_ERROR       11
/** an error occured during compression (XXX: be more specific) */
#define ELZMA_E_COMPRESS_ERROR                  12
/** currently unsupported lzma file format was specified*/
#define ELZMA_E_UNSUPPORTED_FORMAT              13
/** an error occured when reading input */
#define ELZMA_E_INPUT_ERROR                     14
/** an error occured when writing output */
#define ELZMA_E_OUTPUT_ERROR                    15
/** LZMA header couldn't be parsed */
#define ELZMA_E_CORRUPT_HEADER                  16
/** an error occured during decompression (XXX: be more specific) */
#define ELZMA_E_DECOMPRESS_ERROR                17
/** the input stream returns EOF before the decompression could complete */
#define ELZMA_E_INSUFFICIENT_INPUT              18

/** Supported file formats */
typedef enum {
    ELZMA_lzip, /**< the lzip format which includes a magic number and
                 *   CRC check */
    ELZMA_lzma  /**< the LZMA-Alone format, originally designed by
                 *   Igor Pavlov and in widespread use due to lzmautils,
                 *   lacking both aforementioned features of lzip */
/* XXX: future, potentially   ,
    ELZMA_xz 
*/
} elzma_file_format;


/**
 * A callback invoked during elzma_[de]compress_run when the [de]compression
 * process has generated [de]compressed output.
 *
 * the size parameter indicates how much data is in buf to be written.
 * it is required that the write callback consume all data, and a return
 * value not equal to input size indicates and error.
 */
typedef size_t (*elzma_write_callback)(void *ctx, const void *buf,
                                       size_t size);

/**
 * A callback invoked during elzma_[de]compress_run when the [de]compression
 * process requires more [un]compressed input.
 *
 * the size parameter is an in/out argument.  on input it indicates
 * the buffer size.  on output it indicates the amount of data read into
 * buf.  when *size is zero on output it indicates EOF.
 *
 * \returns the read callback should return nonzero on failure.
 */
typedef int (*elzma_read_callback)(void *ctx, void *buf,
                                   size_t *size);


/** pointer to a malloc function, supporting client overriding memory
 *  allocation routines */
typedef void * (*elzma_malloc)(void *ctx, unsigned int sz);

/** pointer to a free function, supporting client overriding memory
 *  allocation routines */
typedef void (*elzma_free)(void *ctx, void * ptr);


#endif
