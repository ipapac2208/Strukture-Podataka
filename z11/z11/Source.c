#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _country* pos;
typedef struct _cities* child;
typedef pos* List; 
typedef struct _countryHash* cHash;

typedef struct _country {
	char countryName[50];
	char filename[50];
	pos next;
	child citiesbyname;
	child citiesbypopulus;
} countryList;

typedef struct _cities {
	char name[50];
	int populus;
	child left;
	child right;
}cityTree;

typedef struct _countryHash { 
	int size;
	List hashList; 
}countryHash;

cHash makeHash(cHash);
child insertNameTreeElement(child, child);
child insertPopulusTreeElement(child, child);
int printCountries(cHash);
int printCities(child);
int openCountryFile(pos);
int findCountry(cHash, char[50], int);
int findCities(child, int);
cHash insertCountryInHash(cHash, pos);
pos sortCountryInHash(List, pos);
cHash createHash(int);
int makeHashCode(char[50], int);

int main() {
	cHash h = makeHash(NULL);
	char targetCountry[50];
	int targetPopulus;
	printCountries(h);

	printf("Upisite ime drzave i minimalnu populaciju koju grad mora imati (prvo slovo drzave mora imati veliko pocetno slovo)\n");
	scanf("%s %d", targetCountry, &targetPopulus);
	findCountry(h, targetCountry, targetPopulus);

	deleteList(h);
	return 0;
}

cHash insertCountryInHash(cHash h, pos country) {
	int index = makeHashCode(country->countryName, h->size);
	sortCountryInHash(&h->hashList[index], country);
	return h;
}

pos sortCountryInHash(List head, pos q) {
	if (!(*head))
		*head = q;
	if ((*head)->next != NULL) {
		pos curr = *head;
		while (curr->next != NULL && strcmp(curr->countryName, q->countryName) > 0)
			curr = curr->next;
		q->next = curr->next;
		curr->next = q;
	}
	else {
		q->next = (*head)->next;
		(*head)->next = q;
	}
	return (*head);
}

cHash createHash(int size) {
	cHash h = (cHash)malloc(sizeof(countryHash));
	if (!h) return NULL;
	h->size = size;
	h->hashList = calloc(size, sizeof(pos));
	return h;
}

int makeHashCode(char name[50], int size) {
	int hash = 0;
	for (int i = 0; i < 5 && name[i]!='\0' ; i++)
		hash += name[i];
	return hash % size;
}

int deleteTree(child p) {
	if (p->right != NULL)
		deleteTree(p->right);
	if (p->left != NULL)
		deleteTree(p->left);
	free(p);
	return 0;
}

int deleteList(cHash h) {
	for (int i = 0; i < h->size; i++)
	{
		pos p = h->hashList[i];
		while (p->next != NULL) {
			pos target = p->next;
			deleteTree(target->citiesbyname);
			deleteTree(target->citiesbypopulus);
			p->next = target->next;
			free(target);
		}
	}
	return 0;
}

int findCities(child p, int target) {
	if (p->right != NULL)
		findCities(p->right, target);
	if (p->left != NULL)
		findCities(p->left, target);
	if (p->populus > target)
		printf("%s, %d\n", p->name, p->populus);
	return 0;
}

int findCountry(cHash h, char targetName[50], int target) {
	int index = makeHashCode(targetName, h->size);
	pos p = h->hashList[index];
	while (p != NULL && strcmp(p->countryName, targetName) != 0)
		p = p->next;
	findCities(p->citiesbypopulus, target);
	return 0;
}

int printCities(child p) {
	if (!p) return 0;
	if (p->left != NULL)
		printCities(p->left);
	printf("%s %d\n", p->name, p->populus);
	if (p->right != NULL)
		printCities(p->right);
	return 0;
}

int printCountries(cHash h) {
	if (!h || !h->hashList)
		return 0;
	for (int i = 0; i < h->size; i++) {
		pos p = h->hashList[i];
		while (p != NULL) {
			printf("%s:\n", p->countryName);
			printf("gradovi po imenu:\n");
			printCities(p->citiesbyname);
			printf("gradovi po stanovnicima:\n");
			printCities(p->citiesbypopulus);

			p = p->next;
		}
	}
	return 0;
}

child insertPopulusTreeElement(child p, child q) {
	if (p == NULL)
		p = q;
	else {
		if (q->populus > p->populus)
			p->right = insertPopulusTreeElement(p->right, q);
		else
			p->left = insertPopulusTreeElement(p->left, q);
	}
	return p;
}

child insertNameTreeElement(child p, child q) {
	if (p == NULL)
		p = q;
	else
	{
		if (strcmp(p->name, q->name) < 0)
			if (p->right != NULL)
				p->right = insertNameTreeElement(p->right, q);
			else
				p->right = q;
		else
			if (p->left != NULL)
				p->left = insertNameTreeElement(p->left, q);
			else
				p->left = q;
	}
	return p;
}


int openCountryFile(pos q)
{
	FILE* fp = fopen(q->filename, "r");
	if (!fp) return 0;
	char name[50];
	int populus;
	q->citiesbyname = NULL;
	q->citiesbypopulus = NULL;
	while (fscanf(fp, "%s %d", name, &populus) == 2)
	{

		child c = (child)malloc(sizeof(cityTree));
		if (!c) return 0;
		child r = (child)malloc(sizeof(cityTree));
		if (!r) return 0;

		strcpy(c->name, name);
		strcpy(r->name, name);
		c->populus = populus;
		r->populus = populus;
		c->left = NULL;
		c->right = NULL;
		r->left = NULL;
		r->right = NULL;

		q->citiesbyname = insertNameTreeElement(q->citiesbyname, c);
		q->citiesbypopulus = insertPopulusTreeElement(q->citiesbypopulus, r);
	}
	fclose(fp);
	return 0;
}

cHash makeHash(cHash h) {
	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) return NULL;
	char countryName[50];
	char filename[50];
	h = createHash(11);
	while (fscanf(fp, "%s %s", countryName, filename) == 2) {
		pos q = (pos)malloc(sizeof(countryList));
		if (!q) return NULL;

		strcpy(q->countryName, countryName);
		strcpy(q->filename, filename);
		q->next = NULL;

		openCountryFile(q);
		insertCountryInHash(h, q);

	}
	fclose(fp);
	return h;
}