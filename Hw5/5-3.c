#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>

int n = 0 , m = 0;
int adj_matrix[10][10]={0} , visit[10]={0} , low[10]={0} , articulation_point[10]={0}, t = 0;

void DFS(int i , int j){
    visit[j] = low[j] = ++t;

    int ap = 0;
    int num_child = 0;
    
    for(int k = 0 ; k < n ; ++k){
        if(adj_matrix[j][k] && k != i){
            if(visit[k] != 0){  // have back edge (visit[k] == 1 means it is ancestor)

                // find the smaller traversal time t
                if(low[j] < visit[k])
                    low[j] = low[j];
                else
                    low[j] = visit[k];

            }
            else{
                num_child++;
                DFS(j , k); // next node

                if(low[j] < low[k])
                    low[j] = low[j];
                else
                    low[j] = low[k];
                
                if(low[k] >= visit[j])
                    ap = 1;
            }
        }
    }
    if((i == j && num_child > 1) || (i != j && ap == 1)){
        articulation_point[j] = 1;
    }
}

int main(){
    scanf("%d" , &n);   // point num
    scanf("%d" , &m);   // edge num

    // input edge
    int a, b;
    for(int i = 0 ; i < m ; i++){
        scanf("%d %d" , &a , &b);
        adj_matrix[a][b] = 1;
        adj_matrix[b][a] = 1;
    }
    
    DFS(0 , 0);
    int judge = 0;
    for(int i = 0 ; i < n ; i++){
        if(articulation_point[i]){
            printf("%d\n" , i);
            judge = 1; 
        }
    }
    if(judge == 0)
        printf("None\n");
    return 0;
}
