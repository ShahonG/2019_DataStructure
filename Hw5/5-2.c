#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
typedef struct Edge Edge;

int **dmap , *visit , *dist , *parent;

void Dijkstra(int n){
    for(int i = 0 ; i < n ; i++){
        int p = -1;
        int lenth = INT_MAX;
        for(int j = 0 ; j < n ; j++){           // pick smallest weight every time
            if(!visit[j] && dist[j] < lenth){   // and it must not visit yet
                p = j;
                lenth = dist[j];
            }
        }
        if(p == -1)
            break;
        visit[p] = 1;
        for(int k = 0 ; k < n ; k++){
            if(!visit[k] && dist[p] + dmap[p][k] < dist[k] && dmap[p][k] != 0){
                dist[k] = dist[p] + dmap[p][k];
                parent[k] = p;
            }
        }
    }
}

void Path(int cur){
    printf("<-%d" , cur);
    if(cur != parent[cur]){
        Path(parent[cur]);
    }
}

int main(){
    int n = 0;
    int start = 0;
    scanf("%d" , &n);
    dmap = (int**)malloc(sizeof(int*) * n); 
    for(int i = 0 ; i < n ; i++)
        dmap[i] = (int*)malloc(sizeof(int) * n);
    for(int i = 0 ; i < n ; i++)
        for(int j = 0 ; j < n ; j++)
            scanf("%d" , &dmap[i][j]);
    scanf("%d" , &start);
    visit = (int*)malloc(sizeof(int) * n);
    dist = (int*)malloc(sizeof(int) * n);
    parent = (int*)malloc(sizeof(int) * n);
    for(int i = 0 ; i < n ; i++){
        dist[i] = INT_MAX; 
        visit[i] = 0;
        parent[i] = i;
    }
    dist[start] = 0;
    Dijkstra(n);
    for(int i = 0 ; i < n ; i++){
        if(i != start && parent[i] == i)
            printf("%d INF None\n" , i);
        else if(i == start)
            printf("%d 0 %d\n" , i , i);
        else{
            printf("%d %d %d" , i , dist[i] , i);
            Path(parent[i]);
            printf("\n");
        }
    }
    return 0;
}
