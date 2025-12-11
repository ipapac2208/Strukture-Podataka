#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "racun.h"
#define FILE_ERROR 404
#define	STRUCT_ERROR -1

typedef struct receipt* PosR;

typedef struct receipt {
	char filename[20];
	PosD date;
	PosR next;
} Receipt;

int openMainFile(PosR, PosD, PosA);
PosD openReceiptFile(char[20], PosD, PosA);
PosA formReceipt(PosA, FILE*, char[50], int, double);
int printFile(PosR);
int findItem(PosR, char[50]);
int deleteArticle(PosA);
int deleteDate(PosD);

int main() {
	Article headArt = { " ", 0, 0.0, NULL };
	Date headDate = { 0,0,0, NULL , NULL };
	Receipt headRec = { " ", NULL, NULL };
	char target[50];
	char cmptarget[50];

	if (openMainFile(&headRec, &headDate, &headArt) == FILE_ERROR) {
		printf("FILE_ERROR");
		return FILE_ERROR;
	}
	printFile(headRec.next);

	printf("odaberite koji biste artikl zeljeli pronac\n");
	scanf("%s", target);
	for (int i = 0; i < 50; i++)
	{
		cmptarget[i] = toupper(target[i]);
	}
	findItem(headRec.next, cmptarget);

	return 0;
}

int deleteDate(PosD pd) {
	PosD curr;
	curr = pd->next;
	while (pd->next != NULL)
	{
		curr = pd->next;
		pd->next = curr->next;
		free(curr);
	}

	return 0;
}

int deleteArticle(PosA pa) {
	PosA curr;
	curr = pa->next;
	while (pa->next != NULL)
	{
		curr = pa->next;
		pa->next = curr->next;
		free(curr);
	}

	return 0;

}

int findItem(PosR p, char target[50]) {
	int totalAmm = 0;
	double moneySpent = 0.0;
	bool found = false;
	PosD pd = p->date;
	PosD first = NULL;
	PosD last = NULL;
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
		printf("%d %lf€ %d y %d m %d d", totalAmm, moneySpent, last->year - first->year, last->month - first->month, last->day - first->day);
	}
	else printf("item not found");
	return 0;
}

int printFile(PosR p){
	PosD pd = p->date->next;
	PosA pa = pd->item->next;
	while (pd != NULL) {
		printf("%d-%d-%d\n", pd->year, pd->month, pd->day);
		while (pa != NULL)
		{
			printf("%s %d %lf\n", pa->name, pa->ammount, pa->price);
			pa = pa->next;
		}
		pd = pd->next;
	}
	
	return 0;
}

PosA formReceipt(PosA pa, FILE* fp, char name[50], int ammount, double price) {
	PosA q = (Article*)malloc(sizeof(Article));

	if (!q)
		return NULL;

	char cmpname[50];
	for (int i = 0; i < 50; i++)
	{
		cmpname[i] = toupper(name[i]);
		q->name[i] = cmpname[i];
	}
	
	q->price = price;
	q->ammount = ammount;
	PosA curr = pa;
	if (pa->next != NULL)
	{
		curr = pa->next;
		while (curr -> next != NULL && strcmp(q->name, curr->name) > 0)
			curr = curr->next;
		q->next = curr->next;
		curr->next = q;

	}
	else {

		q->next = pa->next;
		pa->next = q;
	}
	
	return pa;
}

PosD openReceiptFile(char filename[20], PosD pd, PosA pa) {

	FILE* fp = fopen(filename, "r");
	PosD q = (Date*)malloc(sizeof(Date));

	int year = 0, month = 0, day = 0;
	char name[50] ="\0";
	double price = 0.0;
	int ammount = 0;
	if (!q)
		return NULL;
	if (!fp)
		return NULL;

	fscanf(fp, "%d %d %d", &year, &month, &day);
	q->day = day;
	q->month = month;
	q->year = year;
	while (!feof(fp)) {
		fscanf(fp, "%s %d %lf", name, &ammount, &price);
		q->item = formReceipt(pa, fp, name, ammount, price);
	}
	if (pd->next != NULL) {
		PosD curr = pd->next;
		while (curr ->next != NULL && (q->year > curr->year || q->month > curr->month || q->day > curr->day)) 
			curr = curr->next;

		q->next = curr->next;
		curr->next = q;
	}
	else
	{
		q->next = pd->next;
		pd->next = q;
	}

	fclose(fp);

	return pd;
}

int openMainFile(PosR p, PosD pd, PosA pa) {
	FILE* fp = fopen("racuni.txt", "r");
	PosR q = (Receipt*)malloc(sizeof(Receipt));

	if (!fp)
		return FILE_ERROR;

	while (!feof(fp)) {
		q = (Receipt*)malloc(sizeof(Receipt));
		if (!q)
			return STRUCT_ERROR;
		fscanf(fp, "%s", q->filename);
		q->date = openReceiptFile(q->filename, pd, pa);
	
		q->next = p->next;
		p->next = q;
		p = p->next;
	}
	fclose(fp);

	return 0;
}