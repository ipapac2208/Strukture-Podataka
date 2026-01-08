#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct binaryTree* child;

typedef struct binaryTree {
	int el;
	int level;
	child left;
	child right;
} Tree;

typedef struct binaryTreeList* pos;

typedef struct binaryTreeList {
	int el;
	int level;
	pos next;
} treeList;

child createElement(child, int);
child insertElement(child, child);
child printTreeInorder(child);
child printTreePreorder(child);
child printTreePostorder(child);
pos insertTreeIntoList(child, pos);
int printTreelevelOrder(pos);
int deleteTree(child);
int deleteList(pos);


int main() {
	Tree root = { 0, 0, NULL, NULL };
	treeList head = { 0,0,NULL };

	int element = 0;
	char confirm = ' ';
	char compare = ' ';
	char errorControl = ' ';

	while (1) {
		printf("insert an element\n");
		scanf("%d", &element);
		createElement(&root, element);
		printf("would you like to insert another element?\n");
		scanf_s(" %c", &confirm, 1);
		compare = toupper(confirm);
		if (compare == 'N')
			break;
		else if (compare != 'Y' && compare != 'N')
		{
			printf("invalid input, taking it as a no\n");
			break;
		}
	}
	printf("Inorder print:\n");
	printTreeInorder(root.right);
	printf("Preorder print:\n");
	printTreePreorder(root.right);
	printf("Postorder print:\n");
	printTreePostorder(root.right);
	printf("Levelorder print:\n");
	insertTreeIntoList(root.right, &head);
	printTreelevelOrder(head.next);
	deleteTree(root.right);
	deleteList(head.next);
	return 0;
}

int deleteList(pos p) {
	pos curr = p->next;
	pos temp;
	while (curr != NULL)
	{
		temp = curr;
		curr = curr->next;
		free(temp);
	}
	free(p);
	return 0;
}

int deleteTree(child p) {
	if (p->left != NULL) {
		deleteTree(p->left);
		p->left = NULL;
	}
	if (p->right != NULL) {
		deleteTree(p->right);
		p->right = NULL;
	}
	free(p);
	return 0;
}

int printTreelevelOrder(pos p) {

	while (p != NULL)
	{
		printf("%d\n", p->el);
		p = p->next;
	}
	return 0;
}

pos insertTreeIntoList(child c, pos p) {
	pos q = (pos)malloc(sizeof(treeList));
	if (!q) return NULL;
	q->el = c->el;
	q->level = c->level;

	pos curr = p->next;
	if (curr != NULL)
	{
		while (curr != NULL)
		{
			if (q->level > curr->level)
			{
				q->next = curr->next;
				curr->next = q;
			}
			else if (q->level == curr ->level && q->el != curr->el){
				q->next = curr->next;
				curr->next = q;
			}
			p = curr;
			curr = curr->next;
		}
	}
	else {
		q->next = p->next;
		p->next = q;
	}
	if (c->left != NULL)
		insertTreeIntoList(c->left, p);
	if (c->right != NULL)
		insertTreeIntoList(c->right, p);
	return q;
}

child printTreePostorder(child p) {
	if (p->left != NULL)
		printTreePostorder(p->left);
	if (p->right != NULL)
		printTreePostorder(p->right);
	printf("%d\n", p->el);
	return p;
}

child printTreePreorder(child p) {
	printf("%d\n", p->el);
	if (p->left != NULL)
		printTreePreorder(p->left);
	if (p->right != NULL)
		printTreePreorder(p->right);
	return p;
}

child printTreeInorder(child p) {
	if (p->left != NULL)
		printTreeInorder(p->left);
	printf("%d\n", p->el);
	if (p->right != NULL)
		printTreeInorder(p->right);
	return p;
}

child insertElement(child p, child q) {
	if (p == NULL)
		p = q;
	else
		if (p->el > q->el)
		{
			if (p->left != NULL)
				insertElement(p->left, q);
			else
			{
				p->left = q;
				q->level = p->level + 1;
			}
		}
		else {
			if (p->right != NULL)
				insertElement(p->right, q);
			else
			{
				p->right = q;
				q->level = p->level + 1;
			}
		}
	return p;
}

child createElement(child p, int element) {
	child q = (child)malloc(sizeof(Tree));
	if (!q) return NULL;
	q->el = element;
	q->left = NULL;
	q->right = NULL;
	q->level = 0;
	insertElement(p, q);
	return p;
}