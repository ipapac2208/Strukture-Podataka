#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct binaryTree* child;

typedef struct binaryTree {
	int el;
	child left;
	child right;
} Tree;

child create(child, int);
child insert(child, child);
int print(child, FILE*);
child replace(child);

int main() {
	FILE* fp = fopen("output.txt", "w");

	Tree root = { 0, NULL, NULL };
	srand(time(NULL));
	int num;

	for (int i = 0; i < 10; i++) {
		num = rand() % 100 + 1;
		create(&root, num);
	}

	fprintf(fp, "dano stablo\n");
	print(root.left, fp);
	replace(root.left);
	fprintf(fp, "stablo sa promjenama\n");
	print(root.left, fp);
	return 0;
}

int print(child p, FILE* fp){
	if (p->left != NULL)
		print(p->left, fp);
	fprintf(fp, "%d\n", p->el);
	if (p->right != NULL)
		print(p->right, fp);
	return 0;
}

child replace(child p) {
	if (p->left != NULL && p->right != NULL)
		p->el = p->left->el + p->right->el;
	else if (p->right != NULL && p->left == NULL)
		p->el = p->right->el;
	else if (p->left != NULL && p->right == NULL)
		p->el = p->left->el;
	else
		p->el = 0;
	if (p->right != NULL)
		replace(p->right);
	if (p->left != NULL)
		replace(p->left);
	
	return p;
}

child insert(child p, child q) {
	if (p == NULL)
		p = q;
	else {
		if (p->el > q->el) {
			if (p->right != NULL)
				insert(p->right, q);
			else p->right = q;
		}
		else {
			if (p->left != NULL)
				insert(p->left, q);
			else
				p->left = q;
		}
	}
	return p;
}

child create(child p, int element) {

	child q = (child)malloc(sizeof(Tree));

	if (!q) return NULL;

	q->el = element;
	q->left = NULL;
	q->right = NULL;

	insert(p, q);

	return p;
}