#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void output(int data[], int num){
    printf("%d" , data[0]);
    for(int i = 1 ; i < num ; i++)
        printf(", %d" , data[i]);
    printf("\n");
}

void Selection_Sort(int data[] , int num){
    for(int i = 0 ; i < num - 1 ; i++){
        int small = i;
        int buf = 0;
        for(int j = i ; j < num ; j++){
            if(data[j] < data[small])
                small = j;
        }
        buf = data[i];
        data[i] = data[small];
        data[small] = buf;
        output(data , num);
    }
}

int main(){
    int data[100];
    char line[1000];
    char *tok;
    fgets(line , 1000 , stdin);
    tok = strtok(line , ", ");
    int num = 0;
    while(tok != NULL){
        data[num] = atoi(tok);
        num++;
        tok = strtok(NULL , ", ");
    }
    Selection_Sort(data , num);
    return 0;
}
