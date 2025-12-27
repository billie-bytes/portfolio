#ifndef SHELL_H
#define SHELL_H

#include "session.h"

/**
 * @brief changes the current working directory to a folder
 * 
 * @param current_session The session of the current terminal
 * @param path The path of the directory
 * @return 0 if success, 1 if path is not a folder, 2 if path not found
 */
int cmd_cd(Session current_session, char* path);

int cmd_ls(Session current_session);

int cmd_pwd(Session current_session);

int cmd_whoami();

#endif