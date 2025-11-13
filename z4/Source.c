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
int sumPolynomial(pos);
int mpyPolynomial(pos);
int deleteAll(pos);


int main() {
	Polynomial head = { 0,0,NULL };
	Polynomial head1 = { 0,0,NULL };
	if (readFile(&head, &head1) != NOT_FOUND) {
		sumPolynomial(head.next, head1.next);
		mpyPolynomial(head.next);
	}
	deleteAll(head.next);
	deleteAll(head1.next);

	return 0;
}

int deleteAll(pos p) {
	pos q;
	while (p->next != NULL)
	{
		q = p->next;
		p->next = q->next;
		q->next = NULL;
		free(q);
	}
	p->next = NULL;
	free(p);
	return 0;
}

int mpyPolynomial(pos p) {
	pos q = p->next;
	pos result = (pos)malloc(sizeof(Polynomial));
	
	if (!result) return STRUCT_ERROR;

	result = p;
	while (q != NULL) {
		result->number *= q->number;
		result->power += q->power;
		q = q->next;
	}
	printPolynomial(result);
	deleteAll(result);
	return 0;
}

int sumPolynomial(pos p, pos q) {
	Polynomial result = { 0,0,NULL };
	pos res = &result;
	
	for (pos temp = p; temp != NULL; temp = temp->next)
		insertPolynomial(res, temp->number, temp->power);

	for (pos temp1 = p; temp1 != NULL; temp1 = temp1->next)
		insertPolynomial(res, temp1->number, temp1->power);

	printPolynomial(res->next);
	deleteAll(res->next);

	return 0;
}

int printPolynomial(pos p) {
	while (p != NULL)
	{
		printf("%d * x ^ %d\n", p->number, p->power);
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

	printPolynomial(p->next);
	printPolynomial(q->next);
	return 0;
}

int insertPolynomial(pos p, int tempnum, int temppow) {

	pos q = (pos)malloc(sizeof(Polynomial));
	if (!q)
		return STRUCT_ERROR;

	q->number = tempnum;
	q->power = temppow;


	while (p->next != NULL && p->power > q->power) {
		p = p->next;
	}
	if (p->next != NULL && p->power == q->power) {
		p->number += q->number;
		free(q);
	}
	else {
		q->next = p->next;
		p->next = q;
	}
	return 0;
}