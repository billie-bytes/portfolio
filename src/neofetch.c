#include "neofetch.h"

int mask[ROW_LENGTH][COL_LENGTH];
char random_square[ROW_LENGTH][COL_LENGTH];
const char* SAFE_CHARS = "!&()+/0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXY]^abcdefghijklmnopqrstuvwxyz{|}~";
const int SAFE_LEN = 80;

// Variables accessed by Javascript
static int current_tab_memory_usage = 0;
static int sys_cores = 1;
static int sys_ram_gb = 4;
static int sys_net_speed = 0;

static char logo_mask[ROW_LENGTH][COL_LENGTH] = {
    "1111111000000001111111110",
    "1111111110000001111111110",
    "1110000011100000001110000",
    "1110000001110000001110000",
    "1110000001110000001110000",
    "1110000011100000001110000",
    "1111111111000000000000000",
    "1111111110000000000000000",
    "1110000111000001100000110",
    "1110000001111000110001100",
    "1110000000111000011011000",
    "1110000001111000001110000",
    "1111111111100000001110000",
    "1111111110000000001110000"
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
        for(int j = 0; i<COL_LENGTH; j++){
            random_square[i][j] = SAFE_CHARS[rand_range(80)];
        }
    }
}

/*====== API's for Javascript ======*/
void set_system_memory(int bytes){current_tab_memory_usage = bytes;}
void set_system_cores(int cores){sys_cores = cores;}
void set_system_ram(int gb){sys_ram_gb = gb;}
void set_system_net(int mbps){sys_net_speed = mbps;}




const char* username = "billie-bytes@portfolio\n";
const char* OS = "BytesOS v1.6.7\n";
const char* host = "Ouran Host Club\n";
const char* kernel = "6.7.0-69-unique\n";
const char* shell = "bush 6.7.1\n";
char* get_frame(){

}