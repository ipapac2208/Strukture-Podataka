#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _countryTree* child;
typedef struct _cityList* pos;

typedef struct _countryTree {
	char countryName[50];
	char fileName[50];
	pos citiesByName;
	pos citiesByPopulus;
	child left;
	child right;
}countries;

typedef struct _cityList {
	char name[50];
	int populus;
	pos next;
} cities;

child makeTreeNode(child);
child insertTreeNode(child, child);
child readCityFile(child);
pos insertIntoNameList(pos, pos);
pos insertIntoPopulusList(pos, pos);
int printCountries(child);
int printCities(pos);
int findCountry(child, char[50], int);
int findCities(pos, int);


int main() {
	countries root = { " ", " ", NULL, NULL, NULL, NULL };
	int target;
	char targetCountry[50];
	makeTreeNode(&root);
	printCountries(&root);

	printf("Upisite ime drzave i minimalnu populaciju koju grad mora imati (prvo slovo drzave mora imati veliko pocetno slovo)\n");
	scanf("%s %d", targetCountry, &target);

	findCountry(&root, targetCountry, target);
	return 0;
}

int findCities(pos p, int target)
{
	while (p!= NULL){
		if (p->populus > target)
			printf("%s, %d\n", p->name, p->populus);
		p = p->next;
	}
	return 0;
}
int findCountry(child p, char targetCountry[50], int target) {
	if (strcmp(p->countryName, targetCountry) > 0)
		findCountry(p->right, targetCountry, target);
	if (strcmp(p->countryName, targetCountry) == 0)
		findCities(p->citiesByPopulus, target);
	if (strcmp(p->countryName, targetCountry) < 0)
		findCountry(p->left, targetCountry, target);
	return 0;
}

int printCities(pos p) {
	while (p != NULL)
	{
		printf("%s %d\n", p->name, p->populus);
		p = p->next;
	}
	return 0;
}

int printCountries(child p)
{
	if (p->left != NULL)
		printCountries(p->left);
	printf("%s\n", p->countryName);
	printf("gradovi po imenima:\n");
	printCities(p->citiesByName);
	printf("gradovi po stanovnicima:\n");
	printCities(p->citiesByPopulus);
	if (p->right != NULL)
		printCountries(p->right);
	return 0;
}

pos insertIntoPopulusList(pos p, pos q) {
	if (p == NULL || p->populus > q->populus)
	{
		q->next = p;
		return q;
	}
	else
	if (p->next != NULL) {
		pos curr = p;
		while (curr->next != NULL && q->populus > curr->next->populus)
			curr = curr->next;
		q->next = curr->next;
		curr->next = q;
	}
	else {
		q->next = p->next;
		p->next = q;
	}
	return p;
}

pos insertIntoNameList(pos p, pos q) {
	if (p == NULL || strcmp(p->name, q->name)>0)
	{
		q->next = p;
		return q;
	}
	else
	if (p->next != NULL) {
		pos curr = p;
		while (curr->next != NULL && strcmp(q->name, curr->next->name) > 0)
			curr = curr->next;
		q->next = curr->next;
		curr->next = q;
	}
	else {
		q->next = p->next;
		p->next = q;
	}
	return p;
}

child readCityFile(child p) {
	FILE* fp = fopen(p->fileName, "r");
	if (!fp) return NULL;
	char name[50];
	int populus;
	while (fscanf(fp, "%s %d", name, &populus) == 2) {
		pos q = (pos)malloc(sizeof(cities));
		pos r = (pos)malloc(sizeof(cities));
		if (!q) return NULL;
		if (!r) return NULL;
		strcpy(q->name, name);
		strcpy(r->name, name);
		q->populus = populus;
		r->populus = populus;

		p->citiesByName = insertIntoNameList(p->citiesByName, q);
		p->citiesByPopulus = insertIntoPopulusList(p->citiesByPopulus, r);
	}
	fclose(fp);
	return p;
}

child insertTreeNode(child p, child q) {
	if (p == NULL)
		p = q;
	else
		if (strcmp(p->countryName, q->countryName) > 0)
			p->right = insertTreeNode(p->right, q);
		else
			p->left = insertTreeNode(p->left, q);
	return p;
}

child makeTreeNode(child p) {
	FILE* fp = fopen("drzave.txt", "r");
	if (!fp) return NULL;
	char filename[50];
	char countryname[50];
	while (fscanf(fp, "%s %s", countryname, filename) == 2)
	{
		child q = (child)malloc(sizeof(countries));
		if (!q) return NULL;
		strcpy(q->countryName, countryname);
		strcpy(q->fileName, filename);
		q->left = NULL;
		q->right = NULL;
		q->citiesByName = NULL;
		q->citiesByPopulus = NULL;
		readCityFile(q);
		insertTreeNode(p, q);
	}
	fclose(fp);
	return p;
}
