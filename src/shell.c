#include "shell.h"
#include "filesystem.h"
#include "utils.h"

static char shell_buffer[4096];

char* get_shell_output() {
    return shell_buffer;
}

int cmd_ls(Session current_session) {
    shell_buffer[0] = '\0';
    
    FS_node* cwd = fs_get_node_from_id(current_session.current_dir_id);
    if (cwd == NULL) return 1;

    FS_node* child = cwd->next_inside;

    while (child != NULL) {
        string_add(shell_buffer, child->name);
        if (child->type == FS_FOLDER) {
            string_add(shell_buffer, "/");
        }
        string_add(shell_buffer, "  ");
        child = child->next;
    }
    return 0;
}

int cmd_cd(Session current_session, char* path) {
    shell_buffer[0] = '\0';

    if (streq(path, ".")) {
        return 0;
    }

    FS_node* cwd = fs_get_node_from_id(current_session.current_dir_id);
    if (cwd == NULL) return 1;

    if (streq(path, "..")) {
        if (cwd->parent == cwd) {
            return 0; 
        }

        Session* active = get_active_session();
        if (active != NULL) {
            active->current_dir_id = fs_get_id_from_node(cwd->parent);
        }
        return 0;
    }

    FS_node* target = get_file_node(cwd, path);
    
    if (target == NULL) {
        string_add(shell_buffer, "cd: no such file or directory: ");
        string_add(shell_buffer, path);
        return 2;
    }

    if (target->type != FS_FOLDER) {
        string_add(shell_buffer, "cd: not a directory: ");
        string_add(shell_buffer, path);
        return 1;
    }

    Session* active = get_active_session();
    if (active != NULL) {
        active->current_dir_id = fs_get_id_from_node(target);
    }

    return 0;
}

int cmd_pwd(Session current_session) {
    shell_buffer[0] = '\0';
    
    FS_node* cwd = fs_get_node_from_id(current_session.current_dir_id);
    if (cwd == NULL) return 1;

    FS_node* stack[20];
    int depth = 0;
    FS_node* p = cwd;

    while (p->parent != p && depth < 20) {
        stack[depth++] = p;
        p = p->parent;
    }

    string_add(shell_buffer, "/");
    for (int i = depth - 1; i >= 0; i--) {
        string_add(shell_buffer, stack[i]->name);
        if (stack[i]->type == FS_FOLDER && i > 0) {
            string_add(shell_buffer, "/");
        }
    }

    return 0;
}

int cmd_whoami() {
    shell_buffer[0] = '\0';
    string_add(shell_buffer, "billie-bytes");
    return 0;
}