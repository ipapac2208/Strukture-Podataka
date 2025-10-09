#define CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char ime[50];
	char prezime[50];
	int brojBodova;
} stud;

int brojStud(){

	FILE* fp;
	fp = fopen("Studenti.txt", "r");

	if (fp == NULL) {
		printf("GRESKA: file ne postoji");
	}
	else {
		while (!feof(fp)) {
		
		}
	}
}

int main() {

}