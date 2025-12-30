#include "utils.h"

bool streq(const char* str1, const char* str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i]!=str2[i]) return 0;
        ++i;
    }
    if(str1[i]!=str2[i]) return 0;
    else return 1;
}

bool strneq(const char* str1, const char* str2, int num){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0' && i<num){
        if(str1[i]!=str2[i]) return 0;
        ++i;
    }
    if(i==num) return 1;
    else return 0;
}

int strcopy(const char* src, char* dst){
    int i = 0;
    while(src[i]!='\0'){
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return 1;
}

int strleng(const char* str){
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
    while(buffer[i] != '\0') {
        i++;
    }
    
    int j = 0;
    while(string[j] != '\0'){
        buffer[i] = string[j];
        i++; 
        j++;
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

unsigned int htoi(const char* str) {
    unsigned int value = 0;
    int i = 0;
    
    // Skip "0x"
    if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')) {
        i = 2;
    }

    while (str[i] != '\0') {
        char c = str[i];
        int digit;

        if (c >= '0' && c <= '9') digit = c - '0';
        else if (c >= 'a' && c <= 'f') digit = c - 'a' + 10;
        else if (c >= 'A' && c <= 'F') digit = c - 'A' + 10;
        else break; 

        value = (value * 16) + digit;
        i++;
    }
    return value;
}

void itoa(char* buffer, int number){
    char temp[32];
    int i = 0;

    if (number == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    int n = number;
    if (number < 0) n = -number;

    while (n > 0) {
        temp[i++] = (n % 10) + '0';
        n /= 10;
    }

    if (number < 0) temp[i++] = '-';

    temp[i] = '\0';

    int buf_len = 0;
    while(buffer[buf_len] != '\0') buf_len++;

    for (int j = 0; j < i; j++) {
        buffer[buf_len++] = temp[i - 1 - j];
    }
    buffer[buf_len] = '\0';
}

void itoh(char* buffer, int number){
    char temp[32];
    int i = 0;
    unsigned int n = (unsigned int)number; // Treat as unsigned for Hex

    if (number == 0) {
        int buf_len = 0;
        while(buffer[buf_len] != '\0') buf_len++;
        
        buffer[buf_len++] = '0';
        buffer[buf_len] = '\0';
        return;
    }

    while (n > 0) {
        int digit = n % 16;
        if (digit < 10) {
            temp[i++] = digit + '0';
        } else {
            temp[i++] = (digit - 10) + 'A';
        }
        n /= 16;
    }

    temp[i] = '\0';

    int buf_len = 0;
    while(buffer[buf_len] != '\0') buf_len++;

    for (int j = 0; j < i; j++) {
        buffer[buf_len++] = temp[i - 1 - j];
    }
    buffer[buf_len] = '\0';
}

void* memset(void* ptr, int value, size_t num){
    unsigned char* p = (unsigned char*)ptr;
    for(size_t i = 0; i < num; i++){
        p[i] = (unsigned char)value;
    }
    return ptr;
}

void* memcpy(void* dst, const void* src, size_t num){
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;
    for(size_t i = 0; i < num; i++){
        d[i] = s[i];
    }
    return dst;
}

char* get_next_word(char* str){
    int i = 0;
    while(str[i]!=' '&&str[i]!='\0') i++;
    while(str[i]==' '&&str[i]!='\0') i++;
    if(str[i]=='\0') return NULL;
    else return &str[i];
}