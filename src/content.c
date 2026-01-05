#include "content.h"
#include "utils.h"
#include "filesystem.h"
#include "shell.h"
#include "text_styling.h"


#define GLOBAL_BUFFER_SIZE 4096
extern char g_output_buffer[GLOBAL_BUFFER_SIZE];
const char intro_buffer[] =
    "888        888          888                                           \n"
    "888   o    888          888                                           \n"
    "888  d8b   888          888                                           \n"
    "888 d888b  888  .d88b.  888  .d8888b .d88b.  88888b.d88b.    .d88b.  \n"
    "888d88888b888 d8P  Y8b 888 d88P\"    d88\"\"88b 888 \"888 \"88b d8P  Y8b \n"
    "88888P Y88888 88888888 888 888      888  888 888  888  888 88888888  \n"
    "8888P    Y8888 Y8b.      888 Y88b.    Y88..88P 888  888  888 Y8b.      \n"
    "888P      Y888  \"Y8888  888  \"Y8888P \"Y88P\"  888  888  888  \"Y8888  \n"
    "\n"
    "This website is my portfolio contained in a small but functional web operating system.\n"
    "Type \"./about_me\" and press enter to get started. Type 'help' for more commands.\n";

const char about_me_buffer[] =
    "   db    88\"\"Yb  dP\"Yb  88   88 888888     8b    d8 888888\n  dPYb   88__dP dP   Yb 88   88   88       88b  d88 88__  \n dP__Yb  88\"\"Yb Yb   dP Y8   8P   88       88YbdP88 88\"\"  \ndP\"\"\"\"Yb 88oodP  YbodP  `YbodP'   88       88 YY 88 888888\n\n\n"
    "My name is" C_WHITE " Billie Bhaskara Wibawa. " C_RESET "I'm currently an undergraduate student majoring in Informatics Engineering at" C_WHITE" Bandung Institute of Technology (ITB). "C_RESET"My passion lies in the intersection of hardware and software, from CPU logic and memory architecture to kernel design. This deep dive into low-level concepts naturally bridged into cybersecurity, where I actively compete in CTFs with a focus on binary exploitation. I am driven to build, break, and optimize the systems that power modern computing.\n\n"
    "From what I have written it can be concluded that I'm aspiring to be a systems software engineer. But more than that, I'm a lifelong learner forever intrigued and excited to learn about all things computer.\n\n"
    "For my projects, type " C_WHITE "\"cd projects\"" C_RESET " and then type " C_WHITE"\"./readme\"" C_RESET " to get started. Alternatively, use" C_WHITE" \"ls\" " C_RESET"and explore other folders as you wish!\n\n\n";

int about_me(){
    g_output_buffer[0] = '\0';
    strcopy(about_me_buffer,g_output_buffer);
    return 1;
}

const void* about_me_ptrs[] = {
    &cmd_clear,
    &about_me,
    NULL
};

void init_content(){
    FS_node* parent = fs_get_node_from_id(ROOT_ID);
    new_file(parent, "intro.txt", (void*)intro_buffer, FS_FILE);
    new_file(parent, "about_me", about_me_ptrs, FS_PROGRAM);
    
}