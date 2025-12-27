#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "utils.h"

#define FS_FILE 0
#define FS_FOLDER 1
#define MAX_NODES 100
#define NULL ((void*)0)

typedef struct FS_node {
    char name[32];
    int type;

    //points to the next node inside the directory
    struct FS_node* next;

    /*points to the first object inside this directory 
    (if this node itself is a directory). Null if not a directory*/
    struct FS_node* next_inside; 

    //points to the parent folder of this node
    struct FS_node* parent;

    //contents of a file. Null if this node is a folder
    void* content;
} FS_node;

FS_node node_pool[MAX_NODES];
int node_count = 0;

/**
 * @brief allocates a new filesystem node
 * @return an FS_node pointer for an empty node
 */
FS_node* alloc_node();

/**
 * @brief readying filesystem for new directories
 */
void fs_initialize();

/**
 * @brief Returns the buffer for the content of a file node
 * 
 * @param parent The parent folder of the file
 * @param filename The name of the file
 * @return Returns a pointer to the content buffer pointer of the file. Returns NULL if file not found
 */
void* get_file_content(FS_node* parent, char* filename);


#endif