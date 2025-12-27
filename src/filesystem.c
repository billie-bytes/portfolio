#include "filesystem.h"

FS_node* alloc_node() {
    if (node_count >= MAX_NODES) return (FS_node*)NULL; // Out of memory
    ++node_count;
    return &node_pool[node_count-1];

}

void fs_initialize(){
    FS_node* root = alloc_node();
    strcpy(".\0",root);
    root->next = NULL;
    root->next_inside = NULL;
    root->parent = root;
    root->content = NULL;
}

void* get_file_content(FS_node* parent, char* filename){
    FS_node* p = parent->next_inside;
    while(p!=NULL){
        if(streq(p->name, filename)){
            return p->content;
        }
    }
    return NULL;
}