#include "neofetch.h"

int mask[ROW_LENGTH][COL_LENGTH];
char random_square[ROW_LENGTH][COL_LENGTH];
const char* SAFE_CHARS = "!&()+/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXY]^abcdefghijklmnopqrstuvwxyz{|}~";
const int SAFE_LEN = 80;

// Variables accessed by Javascript
static int res_width = 1920;
static int res_height = 1080;
static char terminal[32] = "0x43-Jawa-Terminal";
static int sys_cores = 1;
static int sys_ram_gb = 4;
static int current_tab_memory_usage = 0;
static int battery = 67;
static char sys_locale[32] = "en_AG.UTF-8";


// Variables not set by Javascript
static int disk = 4*sizeof(FS_node); //Placeholder, will be changed after putting in the portfolio content
static int max_disk = MAX_NODES*sizeof(FS_node);
static int packages = 5; //Also placeholder

static char logo_mask[ROW_LENGTH][COL_LENGTH] = {
    "1111111000000000111111111",
    "1111111110000000111111111",
    "1110000011100000000111000",
    "1110000001110000000111000",
    "1110000001110000000111000",
    "1110000011100000000111000",
    "1111111111000000000000000",
    "1111111110000000000000000",
    "1110000111000000110000011",
    "1110000001111000011000110",
    "1110000000111000001101100",
    "1110000001111000000111000",
    "1111111111100000000111000",
    "1111111110000000000111000"
};


/**
 * @brief Checks if x,y satisfies the equation for the logo
 * 
 * @param x 
 * @param y 
 * @return int 
 */
static int is_inside_logo_equation(int x, int y){
    // The logo is the letter B for Billie :)
    float aspect = 1.8; 

    // The Spine (Left vertical bar)
    // x from 3 to 7, y from 2 to 20
    int spine = (x >= 3 && x <= 7 && y >= 2 && y <= 20);

    // Top Lobe (Ellipse centered at x=5, y=6)
    float t_dx = x - 5;
    float t_dy = (y - 6) * aspect;
    float t_dist = t_dx*t_dx + t_dy*t_dy;
    
    // It is a solid blob if radius < 7.5, but we cut out a hole if radius < 2.5
    int top_lobe = (t_dist <= 56.0) && (t_dist >= 6.0) && (x >= 5);

    // Bottom Lobe (Ellipse centered at x=5, y=16)
    // The bottom lobe is traditionally slightly larger/fatter
    float b_dx = x - 5;
    float b_dy = (y - 16) * aspect;
    float b_dist = b_dx*b_dx + b_dy*b_dy;
    
    int bot_lobe = (b_dist <= 65.0) && (b_dist >= 6.0) && (x >= 5);

    // Combine by doing the logical operation: 
    // Spine OR Top Lobe OR Bottom Lobe
    return spine || top_lobe || bot_lobe;
}

/**
 * @brief Generates a mask of where a character should generate and where it should not
 */
static void init_mask(){
    for(int i = 0; i<ROW_LENGTH; i++){
        for(int j = 0; i<COL_LENGTH; j++){
            mask[i][j] = is_inside_logo(i,j);
        }
    }
}

/**
 * @brief Generates a ROW_LENGTH x COL_LENGTH square made up of random characters
 */
static void generate_random_square(){
    for(int i = 0; i<ROW_LENGTH; i++){
        for(int j = 0; j<COL_LENGTH; j++){
            random_square[i][j] = SAFE_CHARS[rand_range(80)];
        }
    }
}

static char frame_buffer[4096];
static int initialized = TRUE;

void ensure_initialized() {
    if (!initialized) {
        init_mask();
        initialized = TRUE;
    }
}


/*====== API's for Javascript ======*/
/*Remember to keep these alive using Makefile!!!!*/
void set_window_width(int width){res_width = width;}
void set_window_height(int height){res_height = height;}
void set_terminal(char* new_terminal){strcpy(new_terminal, terminal);}
void set_system_memory(int bytes){current_tab_memory_usage = bytes;}
void set_system_cores(int cores){sys_cores = cores;}
void set_system_ram(int gb){sys_ram_gb = gb;}
void set_memory_usage(int memory){current_tab_memory_usage = memory;}
void set_system_battery(int sbattery){battery = sbattery;}
void set_locale(char* new_locale){strcpy(new_locale, sys_locale);}




const char* username = "billie-bytes@portfolio\n";
const char* OS = "BytesOS v1.6.7\n";
const char* host = "Ouran Host Club\n";
const char* kernel = "6.7.0-69-unique\n";
const char* shell = "bush 6.7.1\n";
char* get_frame(){
    ensure_initialized();
    generate_random_square_fixed();
    
    // Clear buffer
    frame_buffer[0] = '\0';
    
    char num_buf[32]; // Buffer for itoa

    for(int i = 0; i < ROW_LENGTH; i++){
        //Logo Segment
        for(int j = 0; j < COL_LENGTH; j++){
            char c[2];
            c[1] = '\0';
            if(mask[i][j]) {
                c[0] = random_square[i][j];
            } else {
                c[0] = ' ';
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
                string_add(frame_buffer, OS); 
                break;
            case 3: 
                string_add(frame_buffer, host); 
                break;
            case 4: 
                string_add(frame_buffer, kernel); 
                break;
            case 5: 
                string_add(frame_buffer, "Uptime: ");
                itoa(num_buf, 0); // Placeholder: No tick system provided in utils yet
                string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "s\n");
                break;
            case 6: 
                string_add(frame_buffer, "Packages: ");
                itoa(num_buf, get_file_count());
                string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " (dpkg)\n");
                break;
            case 7: 
                string_add(frame_buffer, shell); 
                break;
            case 8: 
                string_add(frame_buffer, "Resolution: ");
                itoa(num_buf, res_width); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "x");
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
                itoa(num_buf, sys_cores); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " Cores\n");
                break;
            case 11:
                string_add(frame_buffer, "Memory: ");
                itoa(num_buf, current_tab_memory_usage / 1024 / 1024); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "MB / ");
                itoa(num_buf, sys_ram_gb * 1024); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "MB\n");
                break;
            case 12:
                string_add(frame_buffer, "Disk: ");
                itoa(num_buf, get_node_count()); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " / ");
                itoa(num_buf, MAX_NODES); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, " (Nodes)\n");
                break;
            case 13:
                string_add(frame_buffer, "Battery: ");
                itoa(num_buf, battery); string_add(frame_buffer, num_buf);
                string_add(frame_buffer, "%\n");
                break;
        }
    }
    
    return frame_buffer;
}