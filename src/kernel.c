#include "kernel.h"
#include "shell.h"
#include "filesystem.h"
#include "utils.h"
#include "session.h"
#include "text_styling.h"

Session curr_sess = {
    .session_id = 0,
    .current_dir_id = 0,
    .last_exit_code = NO_EXIT_CODE,
    .is_active = TRUE
};


char g_input_buffer[GLOBAL_BUFFER_SIZE];
char g_output_buffer[GLOBAL_BUFFER_SIZE];
static char* g_arguments_buffer[MAX_ARGS];
static int args_num = 0;
void* hexdump_ptr = (void*)&g_input_buffer; //defaults to input buffer

char* get_g_input_buffer(){
    return g_input_buffer;
}

char* get_g_output_buffer(){
    return g_output_buffer;
}

void* get_hexdump_ptr(){
    return hexdump_ptr;
}

void parse_arguments(){
    args_num = 0;
    int i = 0;
    while(g_input_buffer[i]==' '){ // Skips trailing spaces
        i++;
    }

    char* word_ptr = get_next_word(&g_input_buffer[i]);
    while(word_ptr!=NULL){
        
        // Change the space in between strings to null term
        // So each word is a standalone string
        int j = 1;
        while((*(word_ptr-j))==' '){
            (*(word_ptr-j)) = '\0'; 
            j++;
        }

        g_arguments_buffer[args_num] = word_ptr;
        ++args_num;
        word_ptr = get_next_word(word_ptr);
    }
    
}




void exec_cmd(){
    g_output_buffer[0] = '\0';
    
    int i = 0;
    while(g_input_buffer[i]==' '){//skips spaces
        i++;
    }

    if (strleng(g_input_buffer) == 0) {
        return;
    }

    if (strneq(&g_input_buffer[i], "help", 4)) {
        cmd_help();
    }
    else if (strneq(&g_input_buffer[i], "whoami", 6)) {
        cmd_whoami();
    }
    else if (strneq(&g_input_buffer[i], "ls", 2)) {
        cmd_ls(curr_sess);
    }

    else if (strneq(&g_input_buffer[i], "cd", 2)) {
        parse_arguments();
        cmd_cd(&curr_sess, g_arguments_buffer[0]);
    }
    else if(strneq(&g_input_buffer[i], "chexdmp", 7)){
            parse_arguments();
            if(args_num == 0){
                g_output_buffer[0] = '\0';
                string_add(g_output_buffer, "chexdmp must have 1 argument specifying the address");
            }
            else{

                if(g_arguments_buffer[0][0] == '0' && (g_arguments_buffer[0][1] == 'x' || g_arguments_buffer[0][1] == 'X')){
                    cmd_chexdmp(htoi(g_arguments_buffer[0]));
                }
                else{
                    cmd_chexdmp(atoi(g_arguments_buffer[0]));
                }
            }
        }
    else {
        char error_msg[512];
        memset(error_msg, 0, 512);
        
        strcopy("Command not found: " C_WHITE, error_msg);
        string_add(error_msg, g_input_buffer);
        string_add(error_msg, C_RESET);
        
        string_add(g_output_buffer,error_msg);
    }

}

void init_system(){
    fs_initialize();
    session_initialize();
}



