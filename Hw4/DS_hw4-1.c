#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MaxLenGth 1024
typedef struct node node;

struct node{
    int val;
    node* left;
    node* right;
};
int Judge = 0;
int i = 1;

void Create_Tree(node *cur , char line[]);
void Evaluate(node *cur , int target , int answer);

int main() {
    char *line;;
    line = (char*)malloc(sizeof(char) * MaxLenGth);
    while(fgets(line , MaxLenGth , stdin) != NULL){
        int target = 0 , answer = 0;
        Judge = 0; i = 1;
        while(*line != ' '){
            target = 10 * target + (int)(*line++ - '0');
        }
        line++;
        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        node *Root;
        Root = (node*)malloc(sizeof(node));
        Root -> val = 0;
        Root -> left = NULL;
        Root -> right = NULL;
        Create_Tree(Root , line);
        Evaluate(Root , target , answer);
        if(Judge == 0)
            printf("no\n");
        else
            printf("yes\n");
    }
    return 0;
}

void Create_Tree(node *cur , char line[]){
    if(line[i] == '\0' || line[i] == ')')
        return;
    else{
        while(isdigit(line[i])){
            cur -> val = cur -> val * 10 + (int)(line[i] - '0');
            i++;
        }
        if(line[i] == '('){
            if(line[++i] != ')'){
                cur -> left = (node*)malloc(sizeof(node));
                Create_Tree(cur -> left, line);
            }
            else{
                cur -> left = NULL;
                i++;
            }
        }
        if(line[i] == '('){
            if(line[++i] != ')'){
                cur -> right = (node*)malloc(sizeof(node));
                Create_Tree(cur -> right, line);
            }
            else{
                cur -> right = NULL;
                i+=2;
            }
        }
    }
    if(line[i+1] == ' '){
        i+=2;
    }
    return;
}

void Evaluate(node *cur , int target , int answer){
    answer += cur -> val;
    if(cur -> left == NULL && cur -> right == NULL){
        if(answer == target){
            Judge = 1;
        }
        return;
    }
    else{
        if(cur -> left != NULL)
            Evaluate(cur -> left , target , answer);
        if(cur -> right != NULL)
            Evaluate(cur -> right , target , answer);
    }
    return;
}