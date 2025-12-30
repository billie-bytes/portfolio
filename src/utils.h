#ifndef UTILS_H
#define UTILS_H



#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL (void*)0
#endif

typedef unsigned long size_t;
typedef int bool;
/**
 * @brief compares two strings
 * 
 * @param str1 
 * @param str2 
 * @return 1 if equal, 0 if not equal
 */
bool streq(const char* str1, const char* str2);

/**
 * @brief Compares string up to a certain number of characters
 * If any of the string ends before the specified amount, returns 0
 * immediatelys
 * 
 * @param str1 
 * @param str2 
 * @param num 
 * @return 1 if equal, 0 if not equal
 */
bool strneq(const char* str1, const char* str2, int num);

/**
 * @brief copies a string to another buffer
 * 
 * @param src buffer of the source string
 * @param dst buffer of the copied string location
 * @return returns 1 if success
 */
int strcopy(const char* src, char* dst);

/**
 * @brief Calculates the length of a string
 * 
 * @param str The string to be calcualted
 * @return The length of the string
 */
int strleng(const char* str);

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


/**
 * @brief Converts hex format string (e.g. 0xA) into unsigned integer
 * 
 * @param str 
 * @return unsigned int 
 */
unsigned int htoi(const char* str);

/**
 * @brief Changes int into hex string
 * 
 * @param buffer 
 * @param number 
 */
void itoh(char* buffer, int number);

/**
 * @brief Sets the first num bytes of the block of memory pointed by ptr to the specified value
 */
void* memset(void* ptr, int value, size_t num);


/**
 * @brief Copies num bytes from src to dst
 */
void* memcpy(void* dst, const void* src, size_t num);

/**
 * @brief Get the next word separated by space in a string
 * 
 * @param str A string where str[0] is NOT a space
 * @return Returns the pointer to the next word. If there is no next word returns nullptr
 */
char* get_next_word(char* str);

#endif

