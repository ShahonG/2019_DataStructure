#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MaxLenGth 15
typedef struct node node;

struct node{
	char name[MaxLenGth];
	int height;
	node *left;
	node *right;
};

int Maxheight = -1;
int sub_height = -1;

void Insert(node *cur , char line[]);
node* find_str(node *cur , char line[]);
void Inorder(node *cur);
void subtree(node *cur);

int main(){
	int n = 0;
	char line[100];
	node *Root;
	Root = (node*)malloc(sizeof(node));
	scanf("%d" , &n);
	for(int i = 0 ; i < n ; i++){
		scanf("%s" , line);
		if(i == 0){
			strcpy(Root -> name , line);
			Root -> height = 0;
			continue;
		}
		Insert(Root , line);
	}
	int option = -1;
	scanf("%d\n" , &n);
	for(int i = 0 ; i < n ; i++){
		fgets(line , 100 , stdin);
		int j = 0;
		while(line[j] != '\0' && line[j] != '\n' && line[j] != '\r')	j++;
		line[j] = '\0';
		char *tok;
		tok = strtok(line , " ");
		option = atoi(tok);
		node *sub;
		switch(option){
			case 1:
				tok = strtok(NULL , " ");
				printf("Inserted %s.\n" , tok);
				Insert(Root , tok);
				break;
			case 2:
				tok = strtok(NULL , " ");
				sub = (node*)malloc(sizeof(node));
				sub = find_str(Root , tok);
				if(sub != NULL)
					printf("%s is present.\n" , tok);
				else
					printf("%s is not present.\n" , tok);
				break;
			case 3:
				printf("The height is %d.\n" , Maxheight);
				break;
			case 4:
				tok = strtok(NULL , " ");
				sub = (node*)malloc(sizeof(node));
				sub = find_str(Root , tok);
				if(sub != NULL){
					sub_height = -1;
					subtree(sub);
					printf("The height of the subtree at %s is %d.\n" , tok , sub_height - sub -> height);
				}
				else{
					printf("%s is not present.\n" , tok);
				}
				break;
			case 5:
				Inorder(Root);
				printf("\n");
				break;
		}
	}
	return 0;
}

void Insert(node *cur , char line[]){
	while(1){
		if(strcmp(cur -> name , line) > 0){
			if(cur -> left == NULL){
				cur -> left = (node*)malloc(sizeof(node));
				cur -> left -> height = cur -> height + 1;
				cur = cur -> left;
				break;
			}
			else
				cur = cur -> left;
		}
		else{
			if(cur -> right == NULL){
				cur -> right = (node*)malloc(sizeof(node));
				cur -> right -> height = cur -> height + 1;
				cur = cur -> right;
				break;
			}
			else{
				cur = cur -> right;
			}
		}
	}
	strcpy(cur -> name , line);
	cur -> left = NULL;
	cur -> right = NULL;
	if(cur -> height > Maxheight)
		Maxheight = cur -> height;
	return;
}

node* find_str(node *cur , char line[]){
	while(cur != NULL){
		if(strcmp(cur -> name , line) == 0)
			return cur;
		else if(strcmp(cur -> name , line) > 0)
			cur = cur -> left;
		else if(strcmp(cur -> name , line) < 0)
			cur = cur -> right;
	}
	return NULL;
}

void Inorder(node *cur){
	if(cur != NULL){
		Inorder(cur -> left);
		printf("%s " , cur -> name);
		Inorder(cur -> right);
	}
	return;
}

void subtree(node *cur){
	if(cur != NULL){
		subtree(cur -> left);
		if(cur -> height > sub_height)
			sub_height = cur -> height;
		subtree(cur -> right);
	}
}
