#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STRUCT_ERROR -1
#define NOT_FOUND 404

typedef struct person* Pos;

typedef struct person {
	char name[20];
	char surname[20];
	int birthYear;
	Pos Next;
}Person;	//struktura osoba

int insertOnBegin(char[20], char[20], int, Pos);
int insertOnEnd(char[20], char[20], int, Pos);
int printPerson(Pos);
Pos findPerson(char[20], Pos);
int deletePerson(char[20], Pos);
int insertAfter(Pos, char[20], char[20], char[20], int);
int insertBefore(Pos, char[20], char[20], char[20], int);
int sortPerson(Pos);
int printPersonInFile(Pos);
int printFile();
int deleteAll(Pos);

int main() {

	Person head = { "", "", 0, NULL };

	char name[20], N[20];
	char surname[20], S[20];
	int birthyear;
	char confirm, C;
	char target[20], T[20];

	printf("Please insert a person's name, surname and their year of birth\n");
	scanf("%s %s %d", name, surname, &birthyear);
	for (int i = 0; i < 20; i++) {
		N[i] = toupper(name[i]);
		S[i] = toupper(surname[i]);
	}
	insertOnBegin(N, S, birthyear, &head);
	printPerson(head.Next);
	printf("\n");

	printf("Would you like to add another person to the beginning of the list?\n Y = yes N = no\n");
	
	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert a person's name, surname and their year of birth\n");
		scanf("%s %s %d", name, surname, &birthyear);
		for (int i = 0; i < 20; i++) {
			N[i] = toupper(name[i]);
			S[i] = toupper(surname[i]);
		}
		insertOnBegin(N, S, birthyear, &head);
		printPerson(head.Next);
		printf("\n");

		printf("Would you like to add another person to the beginning of the list?\n Y = yes N = no\n");
	}
	
	printf("Would you like to add another person to the end of the list?\n Y = yes N = no\n");

	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert a person's name, surname and their year of birth\n");
		scanf("%s %s %d", name, surname, &birthyear);
		for (int i = 0; i < 20; i++) {
			N[i] = toupper(name[i]);
			S[i] = toupper(surname[i]);
		}
		insertOnEnd(N, S, birthyear, &head);
		printPerson(head.Next);
		printf("Would you like to add another person to the end of the list?\n Y = yes N = no\n");
	}
	
	printf("Would you like to add a person after a person in the list?\n Y = yes N = no\n");
	
	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert the target person's surname and the desired person's name, surname and their year of birth\n");
		scanf("%s %s %s %d", target, name, surname, &birthyear);
		for (int i = 0; i < 20; i++) {
			N[i] = toupper(name[i]);
			S[i] = toupper(surname[i]);
			T[i] = toupper(target[i]);
		}
		insertAfter(head.Next, T, N, S, birthyear);
		printPerson(head.Next);
		printf("\n");
		printf("Would you like to add a person after a person in the list?\n Y = yes N = no\n");
	}
	printf("Would you like to add a person before a person in the list?\n Y = yes N = no\n");

	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert the target person's surname and the desired person's name, surname and their year of birth\n");
		scanf("%s %s %s %d", target, name, surname, &birthyear);
		for (int i = 0; i < 20; i++) {
			N[i] = toupper(name[i]);
			S[i] = toupper(surname[i]);
			T[i] = toupper(target[i]);
		}
		insertBefore(head.Next, T, N, S, birthyear);
		printPerson(head.Next);
		printf("\n");
		printf("Would you like to add a person before a person in the list?\n Y = yes N = no\n");
	}
	
	printf("Would you like to check if a person is in the list?\n Y = yes N = no\n");

	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert the target person's surname\n");
		for (int i = 0; i < 20; i++) {
			T[i] = toupper(target[i]);
		}
		Pos temp = findPerson(T, head.Next);
		printf("Attempting to find inserted person\n");
		if (temp == NULL)
			printf("PERSON NOT FOUND\n");
		else
			printf("Person exists\n");
		free(temp);
		printf("Would you like to check if a person is in the list?\n Y = yes N = no\n");
	}
	printf("Would you like delete a person in the list?\n Y = yes N = no\n");

	while (1)
	{
		scanf(" %c", &confirm);
		C = toupper(confirm);
		if (C == 'N') break;
		printf("Please insert the target person's surname\n");
		for (int i = 0; i < 20; i++) {
			T[i] = toupper(target[i]);
		}
		printf("Attempting to delete inserted person\n");
		if (deletePerson(T, &head) == NOT_FOUND) printf("COULDN'T DELETE PERSON (DOESN'T EXIST)\n");
		else
			printf("Person deleted successfully\n");
		printf("Would you like to delete a person in the list?\n Y = yes N = no\n");
	}
	printf("\n");

	sortPerson(&head);

	printf("\n");

	printPerson(head.Next);

	printPersonInFile(head.Next);

	printf("\n");

	printFile();

	deleteAll(head.Next);

	return 0;
}

int insertOnBegin(char name[20], char surname[20], int birthYear, Pos p) {		//unos na pocetak

	Pos q;
	q = (Pos)malloc(sizeof(Person));

	if (!q)
	{
		printf("ERROR: STRUCT NOT FOUND");
		return STRUCT_ERROR;
	}
	else {
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birthYear = birthYear;
		q->Next = p->Next;
		p->Next = q;

	}
	return 0;
}

int insertOnEnd(char name[20], char surname[20], int birthYear, Pos p) {		//unos na kraj
	Pos q;
	q = (Pos)malloc(sizeof(Person));

	if (!q)
	{
		printf("ERROR FORMING A STRUCT");
		return STRUCT_ERROR;
	}
	else {
		while (p->Next != NULL)
			p = p->Next;
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birthYear = birthYear;
		p->Next = q;
		q->Next = NULL;
	}
	return 0;
}

int printPerson(Pos o) {		//print ako nije ocito
	while (o != NULL) {
		printf("%s %s %d \n", o->name, o->surname, o->birthYear);
		o = o->Next;
	}
	return 0;
}

Pos findPerson(char target[20], Pos p) {	//pronalazenje osobe

	while (p != NULL)
	{
		if (strcmp(p->surname, target) == 0)
			return p;
		p = p->Next;
	}
	return p;
}

int deletePerson(char target[20], Pos p) {		//brisanje osobe
	Pos t = findPerson(target, p);
	if (!t) {
		printf("ERROR: PERSON DOESN'T EXIST\n");
		return NOT_FOUND;
	}
	while (p->Next != t)
	{
		p = p->Next;
	}
	p->Next = t->Next;
	free(t);
	return 0;
}

int insertAfter(Pos p, char target[20], char name[20], char surname[20], int birthYear) {

	Pos q = (Pos)malloc(sizeof(Person));
	p = findPerson(target, p);

	if (!q)
	{
		printf("ERROR FORMING A STRUCT");
		return STRUCT_ERROR;
	}
	if (!p) {
		printf("ERROR: PERSON DOESN'T EXIST\n");
		return NOT_FOUND;
	}
	else {
		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birthYear = birthYear;

		q->Next = p->Next;
		p->Next = q;
	}
	return 0;
}
int insertBefore(Pos p, char target[20], char name[20], char surname[20], int birthYear) {

	Pos q = (Pos)malloc(sizeof(Person));
	Pos t = findPerson(target, p);
	if (!q)
	{
		printf("ERROR FORMING A STRUCT");
		return STRUCT_ERROR;
	}
	if (!t) {
		printf("ERROR: PERSON DOESN'T EXIST\n");
		return NOT_FOUND;
	}
	else {
		while (p->Next != t)
			p = p->Next;

		strcpy(q->name, name);
		strcpy(q->surname, surname);
		q->birthYear = birthYear;

		q->Next = p->Next;
		p->Next = q;
	}
	return 0;
}
int sortPerson(Pos p) {
	Pos temp1 = p;
	Pos temp2 = p->Next;
	if (!temp2->Next) {
		return NOT_FOUND;
	}
	Pos temp3 = p->Next->Next;
	Pos temp = NULL;
	Pos end = NULL;
	while (end!=p->Next->Next)
	{
		temp1 = p;
		temp2 = p->Next;
		temp3 = p->Next->Next;
		temp = NULL;
		while(temp2->Next!=end)
			if (strcmp(temp2->surname, temp3->surname) >= 0)
			{
				temp = temp2;
				temp->Next = temp3->Next;
				temp3->Next = temp;
				temp1->Next = temp3;

				temp1 = temp1->Next;
				temp3 = temp2->Next;
			}
			else {
				temp1 = temp1->Next;
				temp2 = temp2->Next;
				temp3 = temp3->Next;
			}
		end = temp2;
	}
	return 0;
}
int printPersonInFile(Pos p) {
	FILE* fp = fopen("person.txt", "w");
	if (!fp)
	{
		printf("ERROR: FILE NOT FOUND!!!");
		return NOT_FOUND;
	}
	else {
		while (p != NULL)
		{
			fprintf(fp,"%s %s %d\n", p->name, p->surname, p->birthYear);
			p = p->Next;
		}
	}
	fclose(fp);
	return 0;
}

int printFile() {
	FILE* fp1 = fopen("person.txt", "r");
	Person head = { "","",0,NULL };

	char name[20];
	char surname[20];
	int birthyear;
	if (!fp1)
	{
		printf("ERROR: FILE NOT FOUND!!!");
		return NOT_FOUND;
	}
	else {
		while (!feof(fp1))
		{
			fscanf(fp1, "%s %s %d", name, surname, &birthyear);
			insertOnEnd(name, surname, birthyear, &head);
		}
		fclose(fp1);
		printPerson(head.Next);
	}
	
	return 0;
}

int deleteAll(Pos p) {
	while (p->Next != NULL)
	{
		Pos temp = p->Next;
		p->Next = temp->Next;
		
		free(temp);
	}
	return 0;
}