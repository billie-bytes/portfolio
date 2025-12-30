#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define FS_FILE 6767
#define FS_FOLDER 420
#define MAX_NODES 100

#ifndef NULL
#define NULL ((void*)0)
#endif

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


/**
 * @brief Converts a Node Pointer to its ID (Array Index)
 */
int fs_get_id_from_node(FS_node* node);

/**
 * @brief Converts an ID (Array Index) back to a Node Pointer
 */
FS_node* fs_get_node_from_id(int id);

/**
 * @brief Allocates a new filesystem node
 * @return Returns an FS_node pointer for an empty node
 */
FS_node* alloc_node();

/**
 * @brief Readying filesystem for new directories
 */
void fs_initialize();

/**
 * @brief Creates a new directory/folder
 * 
 * @param parent Parent of the new directory/folder
 * @param dir_name Name of the new directory/folder
 * @return Returns the pointer to the new directory
 */
FS_node* new_dir(FS_node* parent, char* dir_name);

/**
 * @brief Creates a new file inside the parent folder
 * 
 * @param parent 
 * @param file_name 
 * @param content_buffer 
 * @return FS_node* 
 */
FS_node* new_file(FS_node* parent, char* file_name, void* content_buffer);

/**
 * @brief Returns the node of the file specified by the filename
 * 
 * @param parent The parent folder of the file
 * @param filename The name of the file
 * @return Returns a pointer to the content buffer pointer of the file. Returns NULL if file not found
 */
FS_node* get_file_node(FS_node* parent, char* filename);

/**
 * @brief Get the number of used node
 * 
 * @return Returns the number of used nodes
 */
int get_node_count();

/**
 * @brief Get the nodes that are files (in this files are assumed to be packages/programs)
 * 
 * @return Returns the number of files
 */
int get_file_count();


#endif