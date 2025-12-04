#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define NOT_FOUND 404
#define STRUCT_ERROR 67

typedef struct polynomial* pos;

typedef struct polynomial {
	int number;
	int power;
	pos next;
} Polynomial;

int readFile(pos, pos);
int insertPolynomial(pos, int, int);
int printPolynomial(pos);
pos sumPolynomial(pos);
int mpyPolynomial(pos, pos);
int deleteAll(pos);


int main() {
	Polynomial head = { 0,0,NULL };
	Polynomial head1 = { 0,0,NULL };
	
	if (readFile(&head, &head1) != NOT_FOUND) {
	 sumPolynomial(head.next, head1.next);
	deleteAll(head.next);
	deleteAll(head1.next);
	}
	if (readFile(&head, &head1) != NOT_FOUND) {
		mpyPolynomial(head.next, head1.next);
		deleteAll(head.next);
		deleteAll(head1.next);
	}

	return 0;
}

int deleteAll(pos p) {
	pos temp = p;
	pos q;
	while (temp->next != NULL)
	{
		q = temp->next;
		temp->next = q->next;
		q->next = NULL;
		free(q);
	}
	temp->next = NULL;
	
	return 0;
}

int mpyPolynomial(pos p, pos q) {
	pos result = p;
	
	if (!result) return STRUCT_ERROR;

	while (p != NULL && q != NULL && result != NULL) {
		result->number = p->number * q->number;
		result->power = p->power + q->power;
		p = p->next;
		q = q->next;
		result = result->next;
	}
	printf("Umnozak:\n");
	printPolynomial(result);
	return 0;
}

pos sumPolynomial(pos p, pos q) {
	Polynomial result = { 0,0,NULL };
	pos res = &result;
	
	for (pos temp = p; temp != NULL; temp = temp->next)
		insertPolynomial(res, temp->number, temp->power);

	for (pos temp1 = q; temp1 != NULL; temp1 = temp1->next)
		insertPolynomial(res, temp1->number, temp1->power);
	printf("Zbroj:\n");
	printPolynomial(res->next);
	return res;
}

int printPolynomial(pos p) {
	while (p != NULL)
	{
		printf("%d * x ^ %d \n", p->number, p->power);
		p = p->next;
	}
	return 0;
}

int readFile(pos p, pos q) {
	FILE* fp = fopen("number.txt", "r");
	FILE* fp1 = fopen("power.txt", "r");
	FILE* fp2 = fopen("number1.txt", "r");
	FILE* fp3 = fopen("power1.txt", "r");

	int tmpnum = 0;
	int tmppow = 0;

	if (!fp || !fp1)
		return NOT_FOUND;
	
	while(!feof(fp)&& !feof(fp1)){
		fscanf(fp, "%d", &tmpnum);
		fscanf(fp1, "%d", &tmppow);
		insertPolynomial(p, tmpnum, tmppow);
	}
	
	while (!feof(fp2) && !feof(fp3)) {
		fscanf(fp2, "%d", &tmpnum);
		fscanf(fp3, "%d", &tmppow);
		insertPolynomial(q, tmpnum, tmppow);
	}
	printf("Prvi polinom:\n");
	printPolynomial(p->next);
	printf("drugi polinom:\n");
	printPolynomial(q->next);
	return 0;
}

int insertPolynomial(pos p, int tempnum, int temppow) {

	pos q = (pos)malloc(sizeof(Polynomial));
	if (!q)
		return STRUCT_ERROR;

	q->number = tempnum;
	q->power = temppow;

	pos curr = p;

	if (p->next != NULL) {
		curr = p->next;

		while (curr->next != NULL && curr->power < q->power) {
			curr = curr->next;
		}
		if (curr != NULL) {
			if (curr->power == q->power) {
				curr->number = curr->number + tempnum;
				free(q);
			}
			else {
				q->next = curr->next;
				curr->next = q;
			}
		}
	}
	else {
		q->next = p->next;
		p->next = q;
	}
	return 0;
}