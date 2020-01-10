#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct bucket bucket;
struct bucket{
    char data[100][30];
};

void print(bucket B[] , int iter[]){
    for(int i = 0 ; i < 10 ; i++){
        printf("Bucket %d: " , i);
        if(iter[i] == 0){
            printf("\n");
            continue;
        }
        printf("%s" , B[i].data[0]);
        for(int j = 1 ; j < iter[i] ; j++){
            printf(", %s" , B[i].data[j]);
        }
        printf("\n");
    }
}

void radix_sort(bucket B[] , int iter[]){
    char buf[30];
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ;  j < iter[i] ; j++){
            for(int k = 0 ; k < iter[i] - j - 1 ; k++){
                if(strcmp(B[i].data[k] , B[i].data[k+1]) > 0){
                    strcpy(buf , B[i].data[k]);
                    strcpy(B[i].data[k] , B[i].data[k+1]);
                    strcpy(B[i].data[k+1] , buf);
                }
            }
        }
    }
}

int main(){
    char line[1000];
    bucket B[10];
    int iter[10] = {0};
    char *tok = NULL;
    fgets(line , 1000 , stdin);
    tok = strtok(line , ", ");
    while(tok != NULL){
        char c = tok[0];
        strcpy(B[(int)(c - '0')].data[iter[(int)(c - '0')]++] , tok);
        tok = strtok(NULL , ", ");
    }
    print(B , iter);
    radix_sort(B , iter);
    int output_judge = 0;
    for(int i = 0 ; i < 10 ; i++){
        for(int j = 0 ; j < iter[i] ; j++){
            if(output_judge == 0){
                printf("%s" , B[i].data[j]);
                output_judge = 1;
            }
            else{
                printf(", %s" , B[i].data[j]);
            }
        }
    }
    return 0;
}
