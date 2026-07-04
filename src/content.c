#include "content.h"
#include "utils.h"
#include "filesystem.h"
#include "shell.h"
#include "text_styling.h"


#define GLOBAL_BUFFER_SIZE 4096
extern char g_output_buffer[GLOBAL_BUFFER_SIZE];

const char about_me_buffer[] =
    "   db    88\"\"Yb  dP\"Yb  88   88 888888     8b    d8 888888\n  dPYb   88__dP dP   Yb 88   88   88       88b  d88 88__  \n dP__Yb  88\"\"Yb Yb   dP Y8   8P   88       88YbdP88 88\"\"  \ndP\"\"\"\"Yb 88oodP  YbodP  `YbodP'   88       88 YY 88 888888\n\n"
    C_CYAN L_GITHUB "Github" L_RESET C_RESET "   "  C_CYAN L_LINKED "LinkedIn" L_RESET C_RESET "   " C_CYAN L_EMAIL "Email" L_RESET " ---------------------------------" C_RESET  "\n\n\n"    
    "My name is" C_WHITE " Billie Bhaskara Wibawa. " C_RESET "I'm currently an undergraduate student majoring in Informatics Engineering at" C_WHITE" Bandung Institute of Technology (ITB). "C_RESET"I specialize in distributed systems and low level softwares such as operating systems and PLC programming. I'm also a binary exploitation enthusiast (PWN) that loves to participate in CTFs. \n\n"
    "For my projects, type " C_WHITE "\"cd projects\"" C_RESET " and then type " C_WHITE"\"./readme\"" C_RESET " to get started. Alternatively, type" C_WHITE" \"help\" " C_RESET"and explore all the commands as you like.\n\n\n";

const char project_readme_buff[] =
    "This folder holds all the projects I have worked on. Run " C_WHITE "\"./<project-name>\"" C_RESET
    " for further information about that specific project. For example, type "C_WHITE "\"./hobby-OS\"" C_RESET
    " and press enter.";

const char hobby_os_buff[] =
    "A hobby " C_WHITE " operating system project. " C_RESET "This operating system uses the EXT2 filesystem "
    "and with every single aspect of tbe operating system from the system calls, process management, and" 
    "scheduler being written from scratch.\n\n"
    L_OS"Project Link"L_RESET
    ;

const char network_sim_buff[] =
    "A network simulator inspired by Cisco's network simulator with complete protocols up to layer 7. "
    "This network simulator also uses UDP for communication between components of the software. Each "
    "components are run on a docker container and is synchronized by the UDP communication mentioned "
    "earlier.\n\n"
    L_NS"Project Link"L_RESET
    ;

const char arion_buff[] =
    "A custom language interpreter. I personally have contributed on tokenization, intermediate code "
    "generation, and the interpreter of said intermediate code complete with error handling such as "
    "segfaults and stack overflows."
    "\n\n"
    L_AC"Project Link"L_RESET
    ;

const char gd3d_buff[] =
    "3D renderer inside the 2D game Geometry Dash. This renderer uses a quaternion based approach for "
    "proof of concept since this was originally an academic project. This project uses a custom language "
    "called 'SPWN' that was created by the person known as 'Spu7nix' online."
    "\n\n"
    L_GD"Project Link"L_RESET
    ;
const char automata_buff[] =
    "This projects main function is for traversing DOM from webpages and a CSS selector for said webpages. "
    "This project uses Golang for the backend and for the webcrawler itself. Ultimately this project is hosted "
    "using Microsoft Azure running a docker container with the backend and the frontend hosted on different" 
    "docker containers as well."
    "\n\n"
    L_PO"Project Link"L_RESET
    ;
int about_me(){
    g_output_buffer[0] = '\0';
    strcopy(about_me_buffer,g_output_buffer);
    return 1;
}

int projects_readme(){
    g_output_buffer[0] = '\0';
    strcopy(project_readme_buff,g_output_buffer);
    return 1;
}

int os(){
    g_output_buffer[0] = '\0';
    strcopy(hobby_os_buff,g_output_buffer);
    return 1;
}

int networksim(){
    g_output_buffer[0] = '\0';
    strcopy(network_sim_buff,g_output_buffer);
    return 1;
}

int arion(){
    g_output_buffer[0] = '\0';
    strcopy(arion_buff,g_output_buffer);
    return 1;
}

int gd3d(){
    g_output_buffer[0] = '\0';
    strcopy(gd3d_buff,g_output_buffer);
    return 1;
}

int automata(){
    g_output_buffer[0] = '\0';
    strcopy(automata_buff,g_output_buffer);
    return 1;
}

const void* about_me_ptrs[] = {
    &cmd_clear,
    &about_me,
    NULL
};

const void* projects_readme_ptrs[] = {
    &cmd_clear,
    &projects_readme,
    NULL
};

const void* os_ptrs[] = {
    &cmd_clear,
    &os,
    NULL
};

const void* networksim_ptrs = {
    &cmd_clear,
    &networksim,
    NULL
};

const void* arion_ptrs = {
    &cmd_clear,
    &arion,
    NULL
};


const void* gd3d_ptrs = {
    &cmd_clear,
    &gd3d,
    NULL
};

const void* automata_ptrs = {
    &cmd_clear,
    &automata,
    NULL
};






// const void* projects

void init_content(){
    FS_node* parent = fs_get_node_from_id(ROOT_ID);
    new_file(parent, "about_me", about_me_ptrs, FS_PROGRAM);
    FS_node* projects_folder = new_dir(parent, "projects");
    // new_file(projects_folder,"readme.txt",(void*)projects_buff,FS_FILE);
    new_file(projects_folder,"readme",projects_readme_ptrs,FS_PROGRAM);
    new_file(projects_folder,"hobby-OS",os_ptrs,FS_PROGRAM);
    new_file(projects_folder,"custom-programming-language",arion_ptrs,FS_PROGRAM);
    new_file(projects_folder,"network-simulator",networksim_ptrs,FS_PROGRAM);
    new_file(projects_folder,"3d-renderer-geometry-dash",gd3d_ptrs,FS_PROGRAM);
    new_file(projects_folder,"azure-hosted-DOM-analyzer",automata_ptrs,FS_PROGRAM);
    // FS_node* test = new_dir(projects_folder, "test");
    
}