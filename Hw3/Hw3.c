#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node node;

struct node{
	char name[10];
	node *next;
};

node *First;

void Circular(node *Prev , int n){
	node *cur = First;
	do{
		for(int i = 0 ; i < n ; i++){
			cur = cur -> next;
			Prev = Prev -> next;
		}
		printf("%s died\n" , cur -> name);
		Prev -> next = cur -> next;
		cur = cur -> next;
	}while(cur != cur -> next);
	printf("%s\n" , cur -> name);
	return;
}

node* Odd_Even_Pos(){
	node *odd = First;
	node *even = odd -> next;
	node *evenHead = even;
	node *cur = even -> next;
	int option = 1;
	while(cur != NULL){
		if(option == 1){
			odd -> next = cur;
			option = 0;
			odd = odd -> next;
			cur = cur -> next;
		}
		else{
			even -> next = cur;
			option = 1;
			even = even -> next;
			cur = cur -> next;
		}
	}
	if(option == 0){
		even->next = (node*)malloc(sizeof(node));
		even = even->next;
		strcpy(even->name , "NULL");
	}
	odd -> next = evenHead;

	cur = First;
	printf("%s" , cur -> name);
	cur = cur -> next;
	while(cur -> next != NULL){
		printf(" -> %s" , cur -> name);
		cur = cur -> next;
	}
	printf(" -> %s\n" , cur -> name);
	return cur;
}

node* Rotate(node *Prev , int counter_clockwise){
	node *cur = First;
	for(int i = 0 ; i < counter_clockwise ; i++){
		cur = cur -> next;
		Prev = Prev -> next;
	}
	First = cur;
	char head_str[20];
	strcpy(head_str , cur -> name);
	printf("%s" , cur -> name);
	cur = cur -> next;
	while(strcmp(cur -> name , head_str) != 0){
		printf(" -> %s" , cur -> name);
		cur = cur -> next;
	}
	printf("\n");
	return Prev;
}

node* Change_direction(){
	node *cur = First -> next;
	node *list[200];
	int i = 0;
	while(strcmp(First -> name , cur -> name) != 0){
		list[i] = cur;
		cur = cur -> next;
		i++;
	}
	cur = First;
	for(int j = i - 1 ; j >= 0 ; j--){
		cur -> next = list[j];
		cur = cur -> next;
	}
	cur -> next = First;
	return cur;
}

int main(){
	First = (node*)malloc(sizeof(node));
	First -> next = NULL;
	node *iter = First;
	node *Prev = NULL;
	char line[200];
	int counter_clockwise = 0;
	int direction = 0;
	int skipped = 0;
	scanf("%d\n", &counter_clockwise);
	scanf("%d\n", &direction);
	scanf("%d\n", &skipped);
	while(fgets(line , 200 , stdin) != NULL){
		if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';
		strcpy(iter -> name , line);
		iter -> next = (node*)malloc(sizeof(node));
		Prev = iter;
		iter = iter -> next;
	}
	Prev -> next = NULL;
	iter = First;
	printf("%s" , iter -> name);
	iter = iter -> next;
	while(iter != NULL){
		printf(" -> %s" , iter -> name);
		iter = iter -> next;
	}
	printf("\n");
	Prev = Odd_Even_Pos();
	free(iter);
	Prev -> next = First;
	Prev = Rotate(Prev , counter_clockwise);
	if(direction == 2){
		Prev = Change_direction();
	}
	Circular(Prev , skipped);
	return 0;
}
