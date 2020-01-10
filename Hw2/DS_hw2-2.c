#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxLenGth 1024
typedef struct Orange_pos Orange_pos;
struct Orange_pos{
    int row;
    int col;
};
void Search(int map[][200] , int height , int width);
int Check(int map[][200] , int height , int width);

Orange_pos queue[200];
int iter = 0 , top = 0 , time_stamp = 0; // iter -> store data , top -> pop data , time_stamp -> calculate rot time

int main(){
    int map[200][200];
    int height = 0 , width = 0;
    scanf("%d\n", &height);
    scanf("%d\n", &width);
    for(int i = 0 ; i < height ; i++)
        for(int j = 0 ; j < width ; j++){
            scanf("%d", &map[i][j]);
            if(map[i][j] == 2){
                queue[iter].row = i;
                queue[iter].col = j;
                printf("en(%d, %d)\n" , queue[iter].row , queue[iter].col);
                iter++;
            }
        }
    queue[iter].row = queue[iter].col = -1;
    printf("en(-1, -1)\n");
    iter++;
    Search(map , height , width);
    printf("%d\n" , time_stamp);
    printf("%d\n" , Check(map , height , width));
    return 0;
}


void Search(int map[][200] , int height , int width){
    while(top != iter){
        map[queue[top].row][queue[top].col] = -1;
        if(queue[top].row == -1 && queue[top].col == -1){
            if(top + 1 == iter){    // this condition is to check there is more Orange can be rot or not
                printf("de(-1, -1)\n");
                break;
            }
            queue[iter].row = queue[iter].col = -1;
            printf("de(-1, -1)\n");     // when you get (-1, -1) , time_stamp++ and push (-1, -1) in queue
            printf("en(-1, -1)\n");
            time_stamp++; iter++; top++;
            continue;
        }
        printf("de(%d, %d)\n" , queue[top].row , queue[top].col);
        if(queue[top].row - 1 >= 0 && map[queue[top].row - 1][queue[top].col] == 1){    // Check 4 direction have orange or not
            queue[iter].row = queue[top].row - 1;
            queue[iter].col = queue[top].col;
            map[queue[top].row - 1][queue[top].col] = 2;
            printf("en(%d, %d)\n" , queue[iter].row , queue[iter].col);
            iter++;
        }
        if(queue[top].row + 1 < height && map[queue[top].row + 1][queue[top].col] == 1){
            queue[iter].row = queue[top].row + 1;
            queue[iter].col = queue[top].col;
            map[queue[top].row + 1][queue[top].col] = 2;
            printf("en(%d, %d)\n" , queue[iter].row , queue[iter].col);
            iter++;
        }
        if(queue[top].col - 1 >= 0 && map[queue[top].row][queue[top].col - 1] == 1){
            queue[iter].row = queue[top].row;
            queue[iter].col = queue[top].col - 1;
            map[queue[top].row][queue[top].col - 1] = 2;
            printf("en(%d, %d)\n" , queue[iter].row , queue[iter].col);
            iter++;
        }
        if(queue[top].col + 1 < width && map[queue[top].row][queue[top].col + 1] == 1){
            queue[iter].row = queue[top].row;
            queue[iter].col = queue[top].col + 1;
            map[queue[top].row][queue[top].col + 1] = 2;
            printf("en(%d, %d)\n" , queue[iter].row , queue[iter].col);
            iter++;
        }
        if(++top == 200) top = 0;
        if(iter == 200) iter = 0;
    }
    return;
}

int Check(int map[][200] , int height , int width){
    for(int i = 0 ; i < height ; i++)
        for(int j = 0 ; j < width ; j++)
            if(map[i][j] == 1)
                return 0;
    return 1;
}
