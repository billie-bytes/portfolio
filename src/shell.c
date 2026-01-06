#include "shell.h"
#include "filesystem.h"
#include "utils.h"
#include "text_styling.h"
#define GLOBAL_BUFFER_SIZE 4096

extern char g_output_buffer[GLOBAL_BUFFER_SIZE];
extern char g_input_buffer[GLOBAL_BUFFER_SIZE];
extern void* hexdump_ptr;

/*A javascript function*/
extern void clear();

void cmd_help(){
    g_output_buffer[0] = '\0';
    string_add(g_output_buffer,"Available commands:\n");
    string_add(g_output_buffer,C_WHITE"  help    "C_RESET"- Show this message\n");
    string_add(g_output_buffer,C_WHITE"  clear   "C_RESET"- Clear the terminal\n");
    string_add(g_output_buffer,C_WHITE"  whoami  "C_RESET"- Current user\n");
    string_add(g_output_buffer,C_WHITE"  cd      "C_RESET"- Changes working directory\n");
    string_add(g_output_buffer,C_WHITE"  ls      "C_RESET"- Lists files and directories in current working directory\n");
    string_add(g_output_buffer,C_WHITE"  pwd     "C_RESET"- Prints current working directory\n");
    string_add(g_output_buffer,C_WHITE"  chexdmp "C_RESET"- Changes the memory offset of the hexdump live-view\n");
    string_add(g_output_buffer,C_WHITE"  cat     "C_RESET"- Opens the content of a file as string\n\n");
}


int cmd_ls(Session current_session) {
    g_output_buffer[0] = '\0';
    
    FS_node* cwd = fs_get_node_from_id(current_session.current_dir_id);
    if (cwd == NULL) return 1;

    FS_node* child = cwd->next_inside;

    while (child != NULL) {
        string_add(g_output_buffer, child->name);
        if (child->type == FS_FOLDER) {
            string_add(g_output_buffer, "/");
        }
        string_add(g_output_buffer, "  ");
        child = child->next;
    }
    return 0;
}

int cmd_cd(Session* current_session, char* path) {
    g_output_buffer[0] = '\0';

    if (streq(path, ".")) {
        return 0;
    }

    FS_node* cwd = fs_get_node_from_id(current_session->current_dir_id);
    if (cwd == NULL) return 1;

    if (streq(path, "..")) {
        if (cwd->parent == cwd) {
            return 0; 
        }

        current_session->current_dir_id = fs_get_id_from_node(cwd->parent);
        return 0;
    }

    FS_node* target = get_file_node(cwd, path);
    
    if (target == NULL) {
        string_add(g_output_buffer, "No such file or directory: ");
        string_add(g_output_buffer, path);
        return 2;
    }

    if (target->type != FS_FOLDER) {
        string_add(g_output_buffer, "Not a directory: ");
        string_add(g_output_buffer, path);
        return 1;
    }

    
    current_session->current_dir_id = fs_get_id_from_node(target);
    return 0;
}

int cmd_pwd(Session current_session) {
    g_output_buffer[0] = '\0';
    
    FS_node* cwd = fs_get_node_from_id(current_session.current_dir_id);
    if (cwd == NULL) return 1;

    FS_node* stack[20];
    int depth = 0;
    FS_node* p = cwd;

    while (p->parent != p && depth < 20) {
        stack[depth++] = p;
        p = p->parent;
    }

    string_add(g_output_buffer, "/");
    for (int i = depth - 1; i >= 0; i--) {
        string_add(g_output_buffer, stack[i]->name);
        if (stack[i]->type == FS_FOLDER && i > 0) {
            string_add(g_output_buffer, "/");
        }
    }

    return 0;
}

void cmd_whoami() {
    g_output_buffer[0] = '\0';
    string_add(g_output_buffer, "billie-bytes");
}


int cmd_chexdmp(int address){
    if(address<0){
        return 1; //invalid address
    }
    if(address>MAX_CHEX_ADDRESS-1000){
        return 1; //invalid address
    }

    hexdump_ptr = (void*)address;
    g_output_buffer[0] = '\0';
    char itoh_buff[16];
    itoh_buff[0]='\0';
    itoh(itoh_buff, address);
    string_add(g_output_buffer, "Changed hex view address into "C_WHITE"0x");
    string_add(g_output_buffer, itoh_buff);
    string_add(g_output_buffer, "\n\n"C_RESET);
    string_add(g_output_buffer, "Points of interest:\n"C_WHITE);
    itoh_buff[0]='\0';
    itoh(itoh_buff, (int)g_input_buffer);
    string_add(g_output_buffer, itoh_buff);
    string_add(g_output_buffer, C_RESET);
    string_add(g_output_buffer, " (input buffer)\n");
    itoh_buff[0]='\0';
    itoh(itoh_buff, (int)g_output_buffer);
    string_add(g_output_buffer,C_WHITE);
    string_add(g_output_buffer, itoh_buff);
    string_add(g_output_buffer, C_RESET);
    string_add(g_output_buffer, " (output buffer)\n\n");
    return 0;
}

void cmd_clear(){
    clear();
}

int cmd_cat(Session current_session, const char* path){
    FS_node* parent = fs_get_node_from_id(current_session.current_dir_id);
    if(parent==NULL) return 1;

    FS_node* file = get_file_node(parent, path);
    if(file==NULL) return 2;
    if(file->type==FS_FOLDER) return 3;
    if(file->content==NULL) return 4;

    g_output_buffer[0] = '\0';
    string_add(g_output_buffer,file->content);

    return 0;
}