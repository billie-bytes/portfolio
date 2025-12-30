#ifndef KERNEL_H
#define KERNEL_H



#define GLOBAL_BUFFER_SIZE 4096

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

/**
 * @brief Get the pointer to the output buffer (accessed by Javascript)
 * 
 * @return Pointer to the global output buffer
 */
char* get_g_output_buffer();

/**
 * @brief Get the hexdump ptr for viewing
 * 
 * @return Pointer to whatever address is specified by hexdump_ptr
 */
void* get_hexdump_ptr();

/**
 * @brief Set the hexdump ptr object
 * 
 * @param address The new address that proceeds to be viewed
 */
void set_hexdump_ptr(int address);

/**
 * @brief Executes cmd from the front end
 * 
 * @param cmd The command given (in string)
 */
void exec_cmd();

/**
 * @brief Initializes all that needs initializing :p
 */
void init_system();



#endif