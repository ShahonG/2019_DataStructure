#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxLenGth 50

void Infix_to_Postfix(char line[] , char post_line[]);
int Calculate(char post_line[]);
int result = 1; //預設為合法輸入

int main(int argc, char const *argv[]) {
    char line[MaxLenGth];
    char post_line[MaxLenGth];
    int num = 0 , ans = 0;
    scanf("%d\n", &num);
    for(int i = 0 ; i < num ; i++){
        result = 1;
        scanf("%s", line);
        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
        Infix_to_Postfix(line , post_line);
        ans = Calculate(post_line);
        if(result == 0)
            printf("0\n");
        else
            printf("1 %s %d\n" , post_line , ans);
    }
    return 0;
}

void Infix_to_Postfix(char line[] , char post_line[]){
    char stack[MaxLenGth];
    int len = strlen(line);
    if(len == 1){
        result = 0;
        return;
    }
    stack[0] = '#';
    for(int i = 0 , top = 0 , iter = 0 ; i < len+1 ; i++){
        switch (line[i]){
            case '\0':
                while(stack[top] != '#'){
                    if(stack[top] == '('){
                        result = 0;
                        return;
                    }
                    post_line[iter] = stack[top];
                    iter++; top--;
                }
                post_line[iter] = '\0';
                break;
            case '(':
                top++;
                stack[top] = line[i];
                break;
            case ')':
                if(stack[top] == '(' && line[i-1] == '('){
                    result = 0;
                    return;
                }
                while(stack[top] != '#' && stack[top] != '('){
                    post_line[iter] = stack[top];
                    iter++; top--;
                }
                if(stack[top] == '#'){
                    result = 0;
                    return;
                }
                top--; //去掉左括號
                break;
            case '+': case '-':
                while(stack[top] != '#' && stack[top] != '('){
                    post_line[iter] = stack[top];
                    iter++;top--;
                }
                top++;
                stack[top] = line[i];
                break;
            case '*': case '/':
                if(stack[top] == '+' || stack[top] == '-'){
                    top++;
                    stack[top] = line[i];
                }
                else if(stack[top] == '*' || stack[top] == '/'){
                    post_line[iter] = stack[top];
                    stack[top] = line[i];
                    iter++;
                }
                else{
                    top++;
                    stack[top] = line[i];
                }
                break;
            default :
                if(isdigit(line[i+1])){
                    result = 0;
                    return;
                }
                post_line[iter] = line[i];
                iter++;
                break;
        }
    }
}

int Calculate(char post_line[]) {
    int iter = 0;
    int stack[MaxLenGth];
    int a = 0 , b = 0;
    int len = strlen(post_line);
    for(int i = 0 ; i < len; i++){
        if(isdigit(post_line[i])){
            stack[iter] = post_line[i] - '0';
            iter++;
        }
        else{
            b = stack[--iter];
            a = stack[--iter];
            switch (post_line[i]) {
                case '+':
                    stack[iter] = a + b;
                    iter++;
                    break;
                case '-':
                    stack[iter] = a - b;
                    iter++;
                    break;
                case '*':
                    stack[iter] = a * b;
                    iter++;
                    break;
                case '/':
                    if(b == 0){
                        result = 0;
                        return -1;
                    }
                    else{
                        stack[iter] = a / b;
                        iter++;
                    }
                    break;
            }
        }
    }
    if(iter - 1 != 0){
        result = 0;
        return -1;
    }
    return stack[0];
}
