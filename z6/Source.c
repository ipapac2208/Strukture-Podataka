#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "racun.h"
#include "artikli.h"
#define FILE_ERROR 404
#define	STRUCT_ERROR -1

typedef Receipt* PosR;

typedef struct receipt {
	char filename[20];
	PosD day;
	PosR next;
} Receipt;

int openMainFile(PosR, PosD, PosA);
int openReceiptFile(char[20], PosD, PosA);
int formReceipt(PosA, FILE);
int printFile(PosD, PosA);
int findItem(PosD, char[50]);

int findItem(PosD pd, char target[50]) {
	int totalAmm = 0;
	double moneySpent = 0.0;
	bool found = false;
	PosD first;
	PosD last;
	while (pd != NULL)
	{
		while (pd->item != NULL)
		{
			if (strcmp(pd->item->name, target) == 0)
			{
				found = true;
				totalAmm = totalAmm + pd->item->ammount;
				moneySpent = moneySpent + pd->item->price;
				if (!first)
					first = pd;
				last = pd;
			}
			pd->item = pd->item->next;
		}
		pd = pd->next;
	}
	if (found) {
		printf("%d %ld€ %d y %d m %d d", &totalAmm, &moneySpent, last->year - first->year, last->month - first->month, last->day - first->day);
	}
	else printf("item not found");
	return 0;
}

int printFile(PosD pd, PosA pa) {
	while (pd != NULL)
	{
		printf("%d-%d-%d", pd->year, pd->month, pd->day);
		while (pa != NULL)
		{
			printf("%s %d %s", pa->name, pa->ammount, pa->price);
			pa = pa->next;
		}
		pd = pd->next;
	}
	return 0;
}

int formReceipt(PosA pa, FILE fp) {
	PosA q = (Article*)malloc(sizeof(Article));
	char name[50];
	char price[10];
	int ammount;

	if (!q)
		return STRUCT_ERROR;

	fscanf(fp, "%s %s %d", &name, &price, &ammount);
	char cmpname[50];
	cmpname = toupper(name);

	q->name = cmpname;
	q->price = price;
	q->ammount = ammount;
	if (pa->next != NULL)
	{
		PosA curr = pa->next;
		while (curr != NULL) {
			if (strcmp(q, curr) != 0)
			{
				q->next = curr->next;
				curr->next = q;
			}
			curr = curr->next;
		}
	}
	else {
		q->next = pa->next;
		pa->next = q;
	}
	return 0;
}

int openReceiptFile(char filename[20], PosD pd, PosA pa) {

	FILE* fp = fopen(filename, "r");
	PosD q = (Date*)malloc(sizeof(Date));

	int year = 0, month = 0, day = 0;

	if (!q)
		return STRUCT_ERROR;
	if (!fp)
		return FILE_ERROR;

	fscanf(fp, "%d %d %d", &year, &month, &day);
	q->day = day;
	q->month = month;
	q->year = year;
	if (pd->next != NULL) {
		PosD curr = pd->next;
		while (curr != NULL) {
			if (q->year > curr->next->year || q->month > curr->next->month || q->day > curr->next->day)
			{
				q->next = curr->next;
				curr->next = q;
			}
			curr = curr->next;
		}
	}
	else
	{
		q->next = pd->next;
		pd->next = q;
	}
	while (!feof(fp)) {
		formReceipt(pa, fp);
	}
	fclose(fp);

	return 0;

}

int openMainFile(PosR p, PosD pd, PosA pa) {
	FILE* fp = fopen("racuni.txt", "r");
	PosR q = (Receipt*)malloc(sizeof(Receipt));

	if (!q)
		return STRUCT_ERROR;
	if (!fp)
		return FILE_ERROR;

	while (!feof(fp)) {
		strcpy(q->filename, fp);
		openReceiptFile(q->filename, pd, pa);
		q->next = p->next;
		p->next = q;
	}
	fclose(fp);
	printFile(pd->next, pa->next);
	return 0;
}