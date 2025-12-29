#include "neofetch.h"


char random_square[ROW_LENGTH][COL_LENGTH];
const char* SAFE_CHARS = "!123456789:;<=>?@ACDEFGHIJKLMNOPQRSTUVWY]^acdefghijklmnopqrstuvwyz{|}";
const int SAFE_LEN = 69;
const char* COLORS[] = {C_RED, C_GREEN, C_YELLOW, C_BLUE, C_MAG, C_CYAN};

// Variables accessed by Javascript
static int res_width = 1920;
static int res_height = 1080;
static char terminal[128] = "0x43-Jawa-Terminal";
static int sys_cores = 1;
static int sys_ram_gb = 4;
static int current_tab_memory_usage = 0;
static int battery = 67;
static char sys_locale[64] = "en_AG.UTF-8";
static char uptime[64] = "67 years";



// Variables not set by Javascript
static int disk = 4*sizeof(FS_node); //Placeholder, will be changed after putting in the portfolio content
static int max_disk = MAX_NODES*sizeof(FS_node);
static int packages = 5; //Also placeholder


static char frame_buffer[8192];
static int initialized = TRUE;

static char logo_mask[ROW_LENGTH][COL_LENGTH+1] = {

"M@@@@@@@M=             .    :+*@@@@@@@MM@@@@",
"@@@@@@M#-                 .. :++@@@@@@#M@@@@",
"@@@@@#M:                  ..  .:=@@@@@##M@@@",
"@@@@@+-                   :*:   +M@@@@@**@@@",
"@@@@@@                    +=-+-..*@@@@@+#@@@",
"@@@@@#            .       .:-**: +@@@M*+****",
"@@@@@=           -+--: .-=:--::- :#M**+++++*",
"@@@@M:          -MM#-.=*=@M#*: -.:#*++++++++",
"@@@M-           .::-=+=-.+@+=#=::=#****###**",
"@@@*.          -#+*:--.  =MM@@+  -MMM@@@MMMM",
"@@#-           ..  --  .++M+#*M  -@@@@@@@@@@",
"@+-.          .:-:     .-*@M#M- .=@@@@@@@@@@",
"@+.           . =#=-.  :*@#*#*   -@@@@@@@@@@",
"#-.     .     ::.+@@#+++@@#-+-   :M@@@@@@@@@",
"+-::          .: --@@@@@@@#.+-    *@@@@@@@@@",
":=++-          .:#M#@@@@@@M:++  .*#@@@@@@@@@",
"#..=:::      ..  =@@@@@#@@*.    =*-*@@@@@@@@",
"@@M*=:-*.        .:@@@**#@M:   :##=M@@@@@@@@",

};



/**
 * @brief Generates a ROW_LENGTH x COL_LENGTH square made up of random characters
 */
static void generate_random_square(){
    for(int i = 0; i<ROW_LENGTH; i++){
        for(int j = 0; j<COL_LENGTH; j++){
            random_square[i][j] = SAFE_CHARS[rand_range(SAFE_LEN)];
        }
    }
}




/*====== API's for Javascript ======*/
/*Remember to keep these alive using Makefile!!!!*/
void set_window_width(int width){res_width = width;}
void set_window_height(int height){res_height = height;}
void set_terminal(char* new_terminal){strcopy(new_terminal, terminal);}
void set_system_memory(int bytes){current_tab_memory_usage = bytes;}
void set_system_cores(int cores){sys_cores = cores;}
void set_system_ram(int gb){sys_ram_gb = gb;}
void set_memory_usage(int memory){current_tab_memory_usage = memory;}
void set_system_battery(int sbattery){battery = sbattery;}
void set_locale(char* new_locale){strcopy(new_locale, sys_locale);}
void set_uptime(char* new_uptime){strcopy(new_uptime, uptime);}




const char* username = "billie-bytes@portfolio\n";
const char* OS = "BytesOS v1.6.7\n";
const char* host = "Ouran H.C. 67-ecc\n";
const char* kernel = "6.7.0-69-unique\n";
const char* shell = "bush 6.7.1\n";
char* get_frame(){
    generate_random_square();
    
    // Clear buffer
    memset(frame_buffer, 0, 8192);
    

    
    char num_buf[64]; // Buffer for itoa

    for(int i = 0; i < ROW_LENGTH; i++){
        //Logo Segment
        for(int j = 0; j < COL_LENGTH; j++){
            char c[2];
            c[1] = '\0';
            if(logo_mask[i][j]=='+'||logo_mask[i][j]=='@') {
                c[0] = random_square[i][j];
            } else {
                c[0] = logo_mask[i][j];
            }
            string_add(frame_buffer, c);
        }

        string_add(frame_buffer, "   ");
        switch(i) {
            case 0: 
                string_add(frame_buffer, username); 
                break;
            case 1: 
                string_add(frame_buffer, "----------------------\n"); 
                break;
            case 2: 
                string_add(frame_buffer, "OS: "); 
                string_add(frame_buffer, OS); 
                break;
            case 3: 
                string_add(frame_buffer, "Host: "); 
                string_add(frame_buffer, host); 
                break;
            case 4: 
                string_add(frame_buffer, "Kernel: "); 
                string_add(frame_buffer, kernel); 
                break;
            case 5: 
                string_add(frame_buffer, "Uptime: ");
                string_add(frame_buffer, uptime);
                string_add(frame_buffer, "\n");
                break;
            case 6: 
                string_add(frame_buffer, "Packages: ");
                num_buf[0] = '\0';
                itoa(num_buf, get_file_count());
                string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " (dpkg)\n");
                break;
            case 7: 
                string_add(frame_buffer, "Shell: ");
                string_add(frame_buffer, shell); 
                break;
            case 8: 
                string_add(frame_buffer, "Resolution: ");
                num_buf[0] = '\0';
                itoa(num_buf, res_width); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "x");
                num_buf[0] = '\0';
                itoa(num_buf, res_height); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "\n");
                break;
            case 9: 
                string_add(frame_buffer, "Terminal: ");
                string_add(frame_buffer, terminal);
                string_add(frame_buffer, "\n");
                break;
            case 10:
                string_add(frame_buffer, "CPU: ");
                num_buf[0] = '\0';
                itoa(num_buf, sys_cores); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " Cores\n");
                break;
            case 11:
                string_add(frame_buffer, "Memory: ");
                num_buf[0] = '\0';
                itoa(num_buf, current_tab_memory_usage / 1024 / 1024); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "MB / ");
                num_buf[0] = '\0';
                itoa(num_buf, sys_ram_gb * 1024); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "MB\n");
                break;
            case 12:
                string_add(frame_buffer, "Disk: ");
                num_buf[0] = '\0';
                itoa(num_buf, get_node_count()); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " / ");
                num_buf[0] = '\0';
                itoa(num_buf, MAX_NODES); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " (Nodes)\n");
                break;
            case 13:
                string_add(frame_buffer, "Battery: ");
                num_buf[0] = '\0';
                itoa(num_buf, battery); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "%\n");
                break;
            default:
                string_add(frame_buffer, "\n");

        }
    }
    
    return frame_buffer;
}