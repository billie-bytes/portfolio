#ifndef UTILS_H
#define UTILS_H



#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif


typedef int bool;
/**
 * @brief compares two strings
 * 
 * @param str1 
 * @param str2 
 * @return 1 if equal, 0 if not equal
 */
int streq(const char* str1, const char* str2);

/**
 * @brief copies a string to another buffer
 * 
 * @param src buffer of the source string
 * @param dst buffer of the copied string location
 * @return returns 1 if success
 */
int strcpy(const char* src, char* dst);

/**
 * @brief Calculates the length of a string
 * 
 * @param str The string to be calcualted
 * @return The length of the string
 */
int strlen(const char* str);

/**
 * @brief Changes the seed of the RNG
 * 
 * @param seed The new seed
 */
void srand(unsigned int seed);

/**
 * @brief Generates a random unsigned integer
 * 
 * @return Returns an unsigned integer
 */
unsigned int rand();

/**
 * @brief 
 * 
 * @param max 
 * @return Returns an unsigned int that is less than max
 */
unsigned int rand_range(unsigned int max);


/**
 * @brief Adds two strings together into the buffer
 * 
 * @param buffer This acts as string 1 and as the buffer where the new added string is stored
 * @param string The string 2 that is added to the string 1 in the buffer
 */
void string_add(char* buffer, const char* string);

/**
 * @brief Converts a string representing a number into an integer
 * 
 * @param string 
 * @return The converted string into an integer
 */
int atoi(const char* string);

/**
 * @brief Turns a number into a string and add it to a buffer. If buffer is not empty will concatenate the new string in the buffer.
 * 
 * @param buffer The buffer where the converted string is stored or concatenated
 * @param number The number that is going to be converted into string
 */
void itoa(char* buffer, int number);

#endif

