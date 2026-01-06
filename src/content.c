#include "content.h"
#include "utils.h"
#include "filesystem.h"
#include "shell.h"
#include "text_styling.h"


#define GLOBAL_BUFFER_SIZE 4096
extern char g_output_buffer[GLOBAL_BUFFER_SIZE];
const char intro_buffer[] =
    C_CYAN
    "\n88  88 888888 88     88      dP\"Yb         \n88  88 88__   88     88     dP   Yb        \n888888 88\"\"   88  .o 88  .o Yb   dP        \n88  88 888888 88ood8 88ood8  YbodP"
    C_RESET
    "\n\n"
    "Yb        dP  dP\"Yb  88\"\"Yb 88     8888b. \n Yb  db  dP  dP   Yb 88__dP 88      8I  Yb\n  YbdPYbdP   Yb   dP 88\"Yb  88  .o  8I  dY\n   YP  YP     YbodP  88  Yb 88ood8 8888Y\" "
    "\n\n\n"
    "This website is my portfolio contained in a small but functional web operating system.\n"
    "Type" C_WHITE" \"./about_me\" "C_RESET "and press enter to get started. Type" C_WHITE" \"help\" " C_RESET "for more commands.\n";

const char about_me_buffer[] =
    "   db    88\"\"Yb  dP\"Yb  88   88 888888     8b    d8 888888\n  dPYb   88__dP dP   Yb 88   88   88       88b  d88 88__  \n dP__Yb  88\"\"Yb Yb   dP Y8   8P   88       88YbdP88 88\"\"  \ndP\"\"\"\"Yb 88oodP  YbodP  `YbodP'   88       88 YY 88 888888\n\n"
    C_CYAN L_GITHUB "Github" L_RESET C_RESET "   "  C_CYAN L_LINKED "LinkedIn" L_RESET C_RESET "   " C_CYAN L_EMAIL "Email" L_RESET " ---------------------------------" C_RESET  "\n\n\n"    
    "My name is" C_WHITE " Billie Bhaskara Wibawa. " C_RESET "I'm currently an undergraduate student majoring in Informatics Engineering at" C_WHITE" Bandung Institute of Technology (ITB). "C_RESET"My passion lies in the intersection of hardware and software, from CPU logic and memory architecture to kernel design. This deep dive into low-level concepts naturally bridged into cybersecurity, where I actively compete in CTFs with a focus on binary exploitation. I am driven to build, break, and optimize the systems that power modern computing.\n\n"
    "From what I have written it can be concluded that I'm aspiring to be a systems software engineer. But more than that, I'm a lifelong learner forever intrigued and excited to learn about all things computer.\n\n"
    "For my projects, type " C_WHITE "\"cd projects\"" C_RESET " and then type " C_WHITE"\"./readme\"" C_RESET " to get started. Alternatively, use" C_WHITE" \"ls\" " C_RESET"and explore other folders as you wish!\n\n\n";


const char projects_buff[] = "Projects placeholder";

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
    FS_node* projects_folder = new_dir(parent, "projects");
    new_file(projects_folder,"readme.txt",(void*)projects_buff,FS_FILE);
    FS_node* test = new_dir(projects_folder, "test");
    
}