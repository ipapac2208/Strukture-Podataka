/*2. Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct person* Pos;

typedef struct person {
	char name[20];
	char surname[20];
	int birthYear;
	Person* head;
	Person* el;
	Pos Next;
	Pos Prev;
}Person;	//struktura osoba

Person* insertOnBegin();
Person* insertOnEnd();
int printPerson(Person*);
bool findPerson(Person*);
int deletePerson(Person*);
Pos findPrev(char, Pos);

int main() {}

Person* insertOnBegin() {		//unos na pocetak

	Person* o;
	Pos q;
	o = (Pos)malloc(sizeof(Person));
	o = o->head;

	if (!o)
	{
		printf("ERROR: osoba nije pronadena");
		return -1;
	}
	else {
		q->Next = o->Next;
		o->Next = q->el;
	}
	return o;
}

Person* insertOnEnd() {		//unos na kraj
	Person* o;
	Pos q;
	o = o->head;
	o = (Pos)malloc(sizeof(Person));

	if (!o)
	{
		printf("ERROR: osoba nije pronadena");
		return -1;
	}
	else {
		while (o->Next != NULL)
			o = o->Next;
		q->Next = o->Next;
		o->Next = q->el;
	}
	return o;
}

int printPerson(Person* o) {		//print ako nije ocito
	int i = 1;
	while (o[i].el != NULL)
	{
		printf("%s %s %d", o[i].name, o[i].surname, o[i].birthYear);
		i++;
	}
	return 0;
}
bool findPerson(Person p) {

	char targetSurname;
	while (p->el != NULL)
	{
		if (p->el->surname == targetSurname)
			return 0;
		p = p->next;
	}
	return 1;
}

int deletePerson(Person* p) {

	char target;

	while (p->el != NULL)
	{
		if (p->el == target)
		{
			findPrev(target, p);
			p->Prev->Next = p->Next;
			delete p;
		}
	}

}

Pos findPrev(char target, Pos p) {
	p = p->head;

	while (p->el != target)
	{
		p->Prev = p->el;
		p->el = p->Next;
	}
	return p->Prev;
}