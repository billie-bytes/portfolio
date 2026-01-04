#ifndef SHELL_H
#define SHELL_H

#define MAX_ARGS 6
#define MAX_CHEX_ADDRESS 131072


#include "session.h"


/**
 * @brief Prints out general help and commands  
 */
void cmd_help();

/**
 * @brief Lists all the files and folder inside the current working directory
 * 
 * @param current_session 
 * @return Error codes: 0 if success, 1 if cwd is NULL
 */
int cmd_ls(Session current_session);

/**
 * @brief changes the current working directory to a folder
 * 
 * @param current_session The session of the current terminal
 * @param path The path of the directory
 * @return 0 if success, 1 if path is not a folder, 2 if path not found
 */
int cmd_cd(Session* current_session, char* path);


/**
 * @brief Prints current working directory
 * 
 * @param current_session The session of the terminal this was written with
 * @return 0 if success, 1 if cwd is NULL
 */
int cmd_pwd(Session current_session);

/**
 * @brief Prints the username
 * 
 * @return 0 if success
 */
void cmd_whoami();

/**
 * @brief Changes the addressed viewed by hexdump
 * 
 * @param address 
 * @return 0 Success, 1 invalid address
 */
int cmd_chexdmp(int address);

#endif