#ifndef NEOFETCH_H
#define NEOFETCH_H

#include "utils.h"
#include "filesystem.h"
#include "text_styling.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define ROW_LENGTH 18
#define COL_LENGTH 44

/**
 * @brief Get the logo for each frame
 * 
 * System stats:
 * Username
 * OS (Not real)
 * Host (Not real)
 * Kernel (Not real)
 * Uptime (Real, using the tick system)
 * Packages (Semi real, the number of file nodes/total nodes)
 * Shell (Not real)
 * Resolution (Real, window.screen.width and window.screen.height)
 * Terminal (Real, navigator.userAgentData.brands)
 * CPU Count (Real, navigator.hardwareConcurrency)
 * RAM (Real, navigator.deviceMemory)
 * Memory Usage (browser tab) (Real, performance.memory)
 * Disk (Semi real, the number of used nodes/total nodes)
 * Battery (Real, navigator.getBattery())
 * Locale (Real, navigator.language)
 * 
 * @return Returns the logo and the systems status, including the newlines 
 */
char* get_frame();

#endif