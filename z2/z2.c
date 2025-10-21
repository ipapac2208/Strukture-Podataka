#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define STRUCT_ERROR -1
#define NOT_FOUND 404

typedef struct person* Pos;

typedef struct person {
	char name[20];
	char surname[20];
	int birthYear;
	Pos Next;
}Person;	//struktura osoba

int insertOnBegin(char[], char[], int, Pos);
int insertOnEnd(char[], char[], int, Pos);
int printPerson(Pos);
Pos findPerson(char[], Pos);
int deletePerson(char[], Pos);

int main() {

	Person head = { "", "", 0, NULL };

	insertOnBegin("Nikola", "Roguljic", 2004, &head);
	printPerson(head.Next);
	printf("\n");
	insertOnBegin("Petar", "Males", 2004, &head);
	printPerson(head.Next);
	printf("\n");
	insertOnEnd("Jakov", "Markic", 2005, &head);
	printPerson(head.Next);
	Pos temp = findPerson("Roguljic", head.Next);
	printf("Attempting to find inserted person\n");
	if (temp == NULL)
		printf("PERSON NOT FOUND\n");
	else
		printf("Person exists\n");
	printf("Attempting to delete inserted person\n");
	if (deletePerson("Milardovic", &head) == NOT_FOUND) printf("COULDN'T DELETE PERSON (DOESN'T EXIST)\n");
	else
		printf("Person deleted successfully\n");
	printf("\n");
	printPerson(head.Next);

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
		printf("ERROR: STRUCT NOT FOUOND");
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
