#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int data[100];
int num = 0;

int _min(int a , int b){
    if(a < b)
        return a;
    else
        return b;
}

void Merge_sort(int left , int mid  ,int right){
    int l_size = mid - left + 1; // num of left side
    int r_size = right - mid;    // num of right side
    int *L , *R;
    int i = 0 , j = 0 , iter = left;
    
    L = (int*)malloc(sizeof(int) * l_size);
    R = (int*)malloc(sizeof(int) * r_size);

    for(int k = 0 ; k < l_size ; k++)   // copy data for sorting (left side)
        L[k] = data[left + k];
    for(int k = 0 ; k < r_size ; k++)   // copy data for sorting (right side)
        R[k] = data[k + mid + 1];

    while(i < l_size && j < r_size){    // sorting
        if(L[i] < R[j])
            data[iter++] = L[i++];
        else
            data[iter++] = R[j++];
    }
    
    while(i < l_size)   // if one side is done , copy other side
        data[iter++] = L[i++];

    while(j < r_size)
        data[iter++] = R[j++];

    free(L);
    free(R);
}
void print(int data[]){
    printf("%d" , data[0]);
    for(int i = 1 ; i < num ; i++)
        printf(", %d", data[i]);
    printf("\n");
}

int main(){
    char line[1000];
    char *tok;
    fgets(line , 1000 , stdin);
    tok = strtok(line , ", ");
    while(tok != NULL){
        data[num] = atoi(tok);
        num++;
        tok = strtok(NULL , ", ");
    }

    for(int range = 1 ; range <= num-1 ; range *= 2){   // sorting range
        for(int left = 0 ; left < num-1 ; left = left + 2*range){   // start point (left)
            int right = _min(left + 2*range - 1 , num - 1);
            int mid = _min(left + range - 1 , num - 1);
            Merge_sort(left , mid , right);
        } 
        print(data);
    }
    return 0;
}
