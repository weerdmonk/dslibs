
/*
 * dslibs v0.1
 * error handling v0.1
 * weerdmonk Dec2014
 *
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <errno.h>

#define DS_C_ERR(err_str)               perror((err_str))

#define DS_LIB_ERR(err_str)             fprintf(stderr, "DS_LIB_ERROR: %s\n", (err_str))
#define DS_LIB_INFO(info_str)           fprintf(stdout, "DS_LIB_INFO: %s\n", (info_str))

#endif /* ERROR_H */
