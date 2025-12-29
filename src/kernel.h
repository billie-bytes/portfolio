#ifndef KERNEL_H
#define KERNEL_H

#include "shell.h"
#include "filesystem.h"
#include "session.h"

#define GLOBAL_INPUT_BUFFER_SIZE 4096

/**
 * Technically a lot of the functions below
 * does not need a header declaration because
 * they are exported directly through the Makefile
 * for the Javascript layer to access. But I
 * still write them here for clarity purposes.
 */


/**
 * @brief Get the pointer to the input buffer (accessed by Javascript)
 * 
 * @return Pointer to the global input buffer
 */
char* get_g_input_buffer();




#endif