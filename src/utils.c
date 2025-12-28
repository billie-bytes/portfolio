#include "utils.h"

int streq(const char* str1, const char* str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i]!=str2[i]) return 0;
        ++i;
    }
    if(str1[i]!=str2[i]) return 0;
    else return 1;
}

int strcpy(const char* src, char* dst){
    int i = 0;
    while(src[i]!='\0'){
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return 1;
}

int strlen(const char* str){
    int i = 0;
    while (str[i] != '\0') {
        i++;
    }
    return i;
}

static unsigned int rng_state = 12345;

void srand(unsigned int seed){
    if (seed == 0) seed = 12345; // default case
    rng_state = seed;
}

unsigned int rand(){
    unsigned int x = rng_state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng_state = x;
    return x;
}

unsigned int rand_range(unsigned int max){
    return rand() % max;
}

void string_add(char* buffer, const char* string){
    int i = 0;
    while(buffer[i]!='\0'){
        i++;
    }
    int j = 0;
    while(string[j]!='\0'){
        buffer[i] = string[j];
        i++; j++;
    }
    buffer[i] = '\0';
}

int atoi(const char* string){
    int i = 0;
    int sign = 1;
    int number = 0;

    if(string[i]=='-'){
        i = 1;
        sign = -1;
    }

    while(string[i]!='\0'){
        number*=10;
        number+=(int)(string[i]-'0');
        i++;
    }

    return number*sign;
}

void itoa(char* buffer, int number){
    char temp[32];
    temp [31] = '\0';
    int i = 30;

    if(number == 0){
        temp[i] = '0';
        i--;
    }

    bool negative = FALSE;
    unsigned int unsigned_val;
    if (number < 0){
        negative = TRUE;
        unsigned_val = (unsigned int)(0 - number); 
    } 
    else{
        unsigned_val = (unsigned int)number;
    }

    while(unsigned_val > 0){
        temp[i] = (char)('0'+(unsigned_val%10));
        unsigned_val /= 10;
        i--;
    }

    if(negative){
        temp[i] = '-';
        i--;
    }

    string_add(buffer, &temp[i+1]);
}