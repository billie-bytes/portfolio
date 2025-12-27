#ifndef SESSION_H
#define SESSION_H
#define MAX_SESSIONS 4
#define NULL ((void*)0)

typedef struct Session {
    int session_id;
    int current_dir_id;
    int last_exit_code;
} Session;

Session sessions[MAX_SESSIONS];
int session_count = 0;

/**
 * @brief creates a new session starting from root
 * 
 * @return Session* pointer of the new session
 */
Session* new_session();

/**
 * @brief Initializes the first working session
 */
void session_initialize();

#endif