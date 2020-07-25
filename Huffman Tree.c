#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 150

typedef struct node{
	
	char letter;
	int frequency;
	struct node *left, *right, *next;
}NODE;

NODE *letterFind(char);				// Find letter in the linked list.
NODE *newNode(char);				// Create new node with parameter letter and set its frequency to 1.
NODE *newNodeWithoutLetter(int);	// Create new node without letter element and set its frequency to parameter number.
NODE *getNode(int);					// Get i'th element of the linked list of nodes.
int getIndex(char);					// Get index of parameter letters node in the linked list.
int getListLength();				// Get size of the linked list.
void addNode(NODE*);				// Add parameter node to end of the linked list.
void insertionSort();				// Sort linked list nodes depending on their frequency by using insertion sort.
void tree();						// Create a huffman tree by using the linked lists elements.
void write(NODE *);					// Write the tree.

static NODE *topleft;				// First element of the linked list.


int main(){
	
	NODE *p;
	char *sentence = malloc(MAX);
	
	printf("Enter the sentence: ");
	fgets(sentence, MAX, stdin);
	
	int i;
	for(i = 0; i<strlen(sentence) - 1; i++){
		p = newNode(sentence[i]);
		if(p != NULL){
			addNode(p);
		}
		
	}
	for(p = topleft; p != NULL; p =p->next){
		printf("%c, %d \n", p->letter, p->frequency);
	}
	
	insertionSort();
	tree();
	printf("===========================\n");
	p = getNode(getListLength() - 1);
	write(p);
	return 0;
}

NODE *letterFind(char h){
	
	NODE *p = topleft;
	while(p != NULL){
		if(p->letter == h){
			return p;
		}
		p =p->next;	
	}

	return NULL;
}

NODE *newNode(char h){
	
	NODE *p;
	if(topleft != NULL && letterFind(h) != NULL){
		
		p = letterFind(h);
		p->frequency++;
		return NULL;
	}
	else{
		
		p = (NODE*) malloc (sizeof(NODE));
		if(p == NULL){
			printf("Malloc failed.\n");
			exit(1);
		}
		p->frequency = 1;
		p->letter = h;
		p->left = NULL;
		p->right = NULL;
		p->next = NULL;
		return p;
	}
}

NODE *newNodeWithoutLetter(int freq){

	NODE *p;
	p = (NODE*) malloc (sizeof(NODE));
	if(p == NULL){
		printf("Malloc failed.\n");
		exit(1);
	}
	p->frequency = freq;
	p->letter = '\0';
	p->left = NULL;
	p->right = NULL;
	p->next = NULL;
	return p;
}

void addNode(NODE *e){

	if(topleft == NULL){
		topleft = e;
	}
	else{

		NODE *p;
		for(p = topleft; p->next != NULL; p =p->next){
		}
		p->next = e;
	}
}

NODE *getNode(int i){

	NODE *p = topleft;
	int j;
	for(j = 0; j<i; j++){
		p = p->next;
	}
	return p;
}

int getIndex(char c){

	NODE *p;
	int i = 0;
	p = topleft;
	while(p->letter != c){
		p = p->next;
		i++;
	}
	return i;
}

int getListLength(){

	int i = 1;
	NODE* p;
	for(p = topleft; p->next != NULL; p =p->next){
		i++;
	}
	return i;
	
}

void insertionSort(){
	
	NODE *p;
	NODE *p2;
	NODE *tmp;
	int i, j;
	
	for(i=0; i<getListLength(); i++){
		for(j=0; j<i; j++){
			
			p = getNode(i);
			p2 = getNode(j);
			
			if(p->frequency < p2->frequency){
				
				tmp = getNode(getIndex(p->letter) - 1);
				tmp->next = p->next;
				p->next = p2;
				if(p2 == topleft){
					topleft = p;
				}else{
					tmp = getNode(getIndex(p2->letter) - 1);
					tmp->next = p;
				}
			}
		}
	}
}

void tree(){
	
	NODE *p;
	NODE *q;
	NODE *tmp;
	NODE *tmp2;
	NODE *tmp2prev;
	int sum;
	
	p = topleft;
	
	while(p->next != NULL){
		
		q = p->next;
		sum = p->frequency + q->frequency;
		tmp = newNodeWithoutLetter(sum);
		tmp->left = p;
		tmp->right = q;
		tmp2 = q;
		
		while(tmp2 != NULL && tmp->frequency >= tmp2->frequency){
			tmp2prev = tmp2;
			tmp2 = tmp2->next;
		}
		tmp2prev->next = tmp;
		tmp->next = tmp2;
		p = p->next->next;
	}
}

void write(NODE *p){
	
	int i = 0;
	int sp = 1;
	int last = 0;
	static NODE *stack[MAX];			
	stack[i] = p;
	
	while(i != last + 1 || i < 1){
	
		if(stack[i] != NULL){
			p = stack[i];
			if(p->left != NULL){
				stack[sp] = p->left;
				stack[sp + 1] = p->right;
				last = sp + 1;
				sp = sp + 2;
				i++;
			}
			else{
				stack[sp] = p->left;
				stack[sp + 1] = p->right;
				sp = sp + 2;
				i++;
			}
		}else{
			i++;
			stack[sp] = NULL;
			stack[sp + 1] = NULL;
			sp = sp + 2;
		}
	}
	
	i = 0;
	while(i<sp){
		int j;
		for(j = i; j< i*2+1; j++){
			if(stack[j] != NULL){
				if(stack[j]->letter != '\0'){
					printf("%d(%c) ", stack[j]->frequency, stack[j]->letter);
				}else{
					printf("%d ", stack[j]->frequency);
				}
			}else{
				printf("|   ");
			}
		}
		printf("\n");
		i = 2*i+1;
	}
}






