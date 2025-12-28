#ifndef NEOFETCH_H
#define NEOFETCH_H

#include "utils.h"
#include "filesystem.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define ROW_LENGTH 14
#define COL_LENGTH 25

extern int mask[ROW_LENGTH][COL_LENGTH];

/**
 * @brief Get the logo for each frame
 * 
 * @return Returns the logo and the systems status, including the newlines 
 */
char* get_frame();

#endif