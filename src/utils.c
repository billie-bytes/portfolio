#include "utils.h"

int streq(char* str1, char* str2){
    int i = 0;
    while(str1[i] != '\0' && str2[i] != '\0'){
        if(str1[i]!=str2[i]) return 0;
        ++i;
    }
    if(str1[i]!=str2[i]) return 0;
    else return 1;
}

int strcpy(char* src, char* dst){
    int i = 0;
    while(src[i]!='\0'){
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return 1;
}


