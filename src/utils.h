#ifndef UTILS_H
#define UTILS_H

/**
 * @brief compares two strings
 * 
 * @param str1 
 * @param str2 
 * @return 1 if equal, 0 if not equal
 */
int streq(char* str1, char* str2);

/**
 * @brief copies a string to another buffer
 * 
 * @param src buffer of the source string
 * @param dst buffer of the copied string location
 * @return returns 1 if success
 */
int strcpy(char* src, char* dst);

#endif

