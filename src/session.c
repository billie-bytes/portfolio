#include "session.h"

Session* new_session(){
    if(session_count>=MAX_SESSIONS) return (Session*)NULL;
    ++session_count;
    return &sessions[session_count-1];
}

void session_initialize(){
    
}