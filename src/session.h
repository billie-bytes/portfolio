#ifndef SESSION_H
#define SESSION_H
#define MAX_SESSIONS 4
#define NO_EXIT_CODE 6969 //For newly created sessions

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL ((void*)0)
#endif

typedef struct Session {
    int session_id; //Ranges from 0 to 3
    int current_dir_id; //The offset of the directory inside the fs_node array
    int last_exit_code; //Last exit code of a command run from this session
    int is_active; //To know if this is the active terminal
} Session;

extern Session sessions[MAX_SESSIONS];
extern int session_count;

/**
 * @brief creates a new session starting from root
 * 
 * @return Session* pointer of the new session
 */
Session* alloc_session();

/**
 * @brief deallocs a session starting from the last session made
 * 
 */
void dealloc_session();

/**
 * @brief Initializes the first working session
 */
void session_initialize();

/**
 * @brief Get the active session
 * 
 * @return Returns the pointer of the active session. If for some unknown reason no session is active, defaults to the first session.
 */
Session* get_active_session();

/**
 * @brief Set the active session and deactivates every other session
 * 
 */
void set_active_session(int new_active_session_id);

/**
 * @brief Create a new session (effectively a new terminal)
 * 
 */
Session* new_session();


#endif