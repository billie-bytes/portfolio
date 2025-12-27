#include "session.h"

Session sessions[MAX_SESSIONS];
int session_count = 0;

Session* alloc_session(){
    if(session_count>=MAX_SESSIONS) return (Session*)NULL;
    ++session_count;
    return &sessions[session_count-1];
}

void dealloc_session(){
    if(session_count<=1) return; // Cannot dealloc the first session
    if (sessions[session_count-1].is_active) {
         if (session_count > 1) {
             set_active_session(session_count - 2);
         }
    }
    --session_count;
}

void session_initialize(){
    new_session();
}


Session* get_active_session(){
    for(int i = 0; i<MAX_SESSIONS; i++){
        if(sessions[i].is_active){
            return &sessions[i];
        }
    }

    sessions[0].is_active = TRUE;
    return &sessions[0]; // default for an unknown error where no session is active
}

void set_active_session(int new_active_session_id){
    for(int i = 0; i<MAX_SESSIONS; i++){
        sessions[i].is_active = FALSE;
    }
    sessions[new_active_session_id].is_active = TRUE;
}

Session* new_session(){
    Session* session = alloc_session();
    if(session==NULL) return NULL;
    session->session_id = session_count-1;
    session->current_dir_id = 0;
    session->last_exit_code = NO_EXIT_CODE;
    session->is_active = TRUE;
    set_active_session(session_count-1);

    return session;
}