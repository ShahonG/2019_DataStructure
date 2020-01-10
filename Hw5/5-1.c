#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct Edge Edge;

struct Edge{
    int pA;
    int pB;
    int len;
};

void sort(Edge *list , int num){
    Edge buf;
    for(int i = 0 ; i < num ; i++)
        for(int j = 0 ; j < num - i - 1 ; j++){
            if(list[j].len > list[j+1].len){
                buf = list[j];
                list[j] = list[j+1];
                list[j+1] = buf;
            }
        }
}

int Kruskal(Edge *list , int *table , int num , int n , int *union_set){
    int val = 0;
    int numofDone = 0;
    int iter = 0;
    int Parent_a = -1;
    int Parent_b = -1;
    while(union_set[0] != n && iter < num){ 
        if(table[list[iter].pA] == table[list[iter].pB]){
            iter++;
            continue;
        }
        Parent_a = table[list[iter].pA];
        Parent_b = table[list[iter].pB];
        if(Parent_a != Parent_b){
            if(Parent_a > Parent_b){
                int tmp = Parent_a;
                Parent_a = Parent_b;
                Parent_b = tmp;
            }
            for(int i = 0 ; i < n ; i++){
                if(table[i] == Parent_b)
                    table[i] = Parent_a;
            }
            union_set[Parent_a] += union_set[Parent_b]; 
        }
        printf("%d %d %d\n" , list[iter].pA , list[iter].pB , list[iter].len);
        val += list[iter].len;
        iter++;
    }
    return val;
}

int main(){
    int n = 0;
    int buf = 0;
    int num = 0;
    int cost = 0;
    scanf("%d" , &n);
    Edge *list;
    list = (Edge*)malloc(sizeof(Edge) * n * n);
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d" , &buf);
            if(j <= i || buf == 0)
                continue;
            else{
                list[num].pA = i;
                list[num].pB = j;
                list[num].len = buf;
                num++;
            }
        }
    }
    sort(list , num);
    int *table;
    int *union_set;
    union_set = (int*)malloc(sizeof(int) * n);
    table = (int*)malloc(sizeof(int) * n);
    for(int i = 0 ; i < n ; i++){ table[i] = i; union_set[i] = 1;}
    cost = Kruskal(list , table , num , n , union_set);
    printf("%d\n" , cost);
    return 0;
}
