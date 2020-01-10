#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void output(int data[] , int num){
    printf("%d" , data[0]);
    for(int i = 1 ; i < num ; i++)
        printf(", %d" , data[i]);
    printf("\n");
}

void Insertion_Sort(int data[] , int num){
    for(int i = 0 ; i < num ; i++){
        int tmp = data[i];
        int j;
        for(j = i ; tmp < data[j-1] && j > 0 ; j--){
            data[j] = data[j-1];    // move right
        }
        data[j] = tmp;
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
    Insertion_Sort(data , num);
    return 0;
}
