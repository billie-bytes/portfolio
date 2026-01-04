#include "content.h"
#include "filesystem.h"

char intro_buffer[512];
char intro2_buffer[32];
unsigned char about_me_ptrs[12];

void init_content(){
    FS_node* parent = fs_get_node_from_id(ROOT_ID);
    new_file(parent, "intro.txt", (void*)&intro_buffer);
    
}