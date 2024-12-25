#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	int isTerminal;
	struct _Node* children[26];
} Node;

Node* createNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->isTerminal = 0;
	for(int i = 0; i < 26; i++) {
		newNode->children[i] = NULL;
	}
	return newNode;
}

void insert(Node* rootNode, const char* word) {
	Node* currentNode = rootNode;
	while(*word) {
		int index = *word - 'a';
		if(!currentNode->children[index]) {
			currentNode->children[index] = createNode();
		}
		currentNode = currentNode->children[index];
		word++;
	}
	currentNode->isTerminal = 1;
}

void delete(Node* rootNode, const char* word) {
	Node* currentNode = rootNode;
	Node* oneWord[101];
	int count = 0;

	while(*word) {
		int index = *word - 'a';
		if(!currentNode->children[index]) {
			return;
		}
		oneWord[count] = currentNode;
		count++;
		currentNode = currentNode->children[index];
		word++;
	}

	if(currentNode->isTerminal) {
		currentNode->isTerminal = 0;
		for(int i = count - 1; i >= 0; i--) {
			int flag = 0;
			for(int j = 0; j < 26; j++) {
				if(oneWord[i]->children[j]) {
					flag = 1;
					break;
				}
			}
			if(!flag) {
				int parentIndex = *(word - count + i) - 'a';
				free(oneWord[i]->children[parentIndex]);
				oneWord[i]->children[parentIndex] = NULL;
			} else {
				break;
			}
		}
	}
}

void dfsF(Node* newNode, char* oneWord, const char* word, int* find, int* currentIndex, int count) {
	if(!newNode) {
		return;
	}
	if(newNode->isTerminal) {
		oneWord[count] = '\0';
		if(strcmp(oneWord, word) == 0) {
			*find = *currentIndex;
		}
		(*currentIndex)++;
	}

	for(int i = 0; i < 26; i++) {
		if(newNode->children[i]) {
			oneWord[count] = 'a' + i;
			dfsF(newNode->children[i], oneWord, word, find, currentIndex, count + 1);
		}
	}
}

int find(Node* rootNode, const char* word) {
	Node* currentNode = rootNode;
	char oneWord[101];
	int currentIndex = 0;
	int find = -1;

	dfsF(rootNode, oneWord, word, &find, &currentIndex, 0);
	return find;
}

void dfsP(Node* newNode, char* oneWord, int count) {
	if(!newNode) {
		return;
	}
	if(newNode->isTerminal) {
		oneWord[count] = '\0';
		printf("%s ", oneWord);
	}

	for(int i = 0; i < 26; i++) {
		if(newNode->children[i]) {
			oneWord[count] = 'a' + i;
			dfsP(newNode->children[i], oneWord, count + 1);
		}
	}
}

void print(Node* rootNode) {
	char oneWord[101];
	dfsP(rootNode, oneWord, 0);
	printf("\n");
}

int N;

int main() {
	Node* rootNode = createNode();
	scanf("%d", &N);

	while (N--) {
		char op[10];
		char word[101];
		scanf("%s", op);
		if(strcmp(op, "insert") == 0) {
			scanf("%s", word);
			insert(rootNode, word);
		} else if(strcmp(op, "delete") == 0) {
			scanf("%s", word);
			delete(rootNode, word);
		} else if(strcmp(op, "find") == 0) {
			scanf("%s", word);
			int index = find(rootNode, word);
			printf("%d\n", index);
		} else if(strcmp(op, "print") == 0) {
			print(rootNode);
		}
	}
	return 0;
}