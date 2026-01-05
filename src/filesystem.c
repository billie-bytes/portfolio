#include "filesystem.h"
#include "utils.h"
#include "content.h"

FS_node node_pool[MAX_NODES];
int node_count = 0;

int fs_get_id_from_node(FS_node* node) {
    if (node == NULL) return -1;
    return (int)(node - node_pool); 
}

FS_node* fs_get_node_from_id(int id) {
    if (id < 0 || id >= node_count) return NULL;
    return &node_pool[id];
}
 
FS_node* alloc_node() {
    if (node_count >= MAX_NODES) return (FS_node*)NULL; // Out of memory
    ++node_count;
    return &node_pool[node_count-1];

}

void fs_initialize(){
    FS_node* root = alloc_node();
    strcopy(".",root->name);
    root->type = FS_FOLDER;
    root->next = NULL;
    root->next_inside = NULL;
    root->parent = root;
    root->content = NULL;

    init_content();
}

FS_node* new_dir(FS_node* parent, char* dir_name){
    FS_node* p = parent->next_inside;
    FS_node* last_node = NULL;
    while(p!=NULL){
        if(p->next==NULL){
            last_node = p;
        }
        p = p->next;
    }

    FS_node* dir = alloc_node();
    
    if(last_node!=NULL) last_node->next = dir;
    else parent->next_inside = dir;
    strcopy(dir_name, dir->name);
    dir->next = NULL;
    dir->next_inside = NULL;
    dir->parent = parent;
    dir->type = FS_FOLDER;

    return dir;
}

FS_node* new_file(FS_node* parent, const char* file_name, void* content_buffer, int file_type){
    if (parent == NULL) return NULL;
    FS_node* p = parent->next_inside;
    FS_node* last_node = NULL;
    while(p!=NULL){
        last_node = p;
        p = p->next;
    }
    
    FS_node* file = alloc_node();
    if(file==NULL) return NULL;

    if(last_node!=NULL) last_node->next = file;
    else parent->next_inside = file;
    
    strcopy(file_name,file->name);
    file->next = NULL;
    file->next_inside = NULL;
    file->parent = parent;
    file->type = file_type;
    file->content = content_buffer;

    return file;
}

FS_node* get_file_node(FS_node* parent, const char* filename){
    FS_node* p = parent->next_inside;
    while(p!=NULL){
        if(streq(p->name, filename)){
            return p;
        }
        p = p->next;
    }
    return NULL;
}

int get_node_count(){
    return node_count;
}

int get_file_count(){
    int file_nums = 0;
    for(int i = 0; i<node_count; i++){
        if(node_pool[i].type==FS_FILE){
            ++file_nums;
        }
    }
    return file_nums;
}

// int write(FS_request request){
//     if(request.type==FS_FOLDER){
//         new_dir
//     }
// }