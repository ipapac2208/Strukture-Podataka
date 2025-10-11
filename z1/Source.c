#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct student {
	char ime[50];
	char prezime[50];
	int brojBodova;
	double postotak;
} stud;

int brojStud() {

	FILE* fp = fopen("Studenti.txt", "r");
	int brojac = 1;
	char c;


	if (!fp) {						//provjera jeli file postoji
		printf("GRESKA: file ne postoji");
		return -1;
	}
	else {
		while (!feof(fp)) {					//brojanje studenata
			c = fgetc(fp);
			if (c == '\n')
				brojac++;
		}
	}
	fclose(fp);
	return brojac;
}

stud* studPodatci(int br) {
	stud* student;
	student = (stud*)malloc(br * sizeof(stud));  //alokacija memorije
	int i = 0;
	FILE* fp1 = fopen("Studenti.txt", "r");

	if (!student) {
		printf("GRESKA: Nema studenata");
		return NULL;
	}
	while (!feof(fp1)) {						//zapisivanje u strukturu student
		fscanf(fp1, "%s %s %d", student[i].ime, student[i].prezime, &student[i].brojBodova);
		student[i].postotak = (double)student[i].brojBodova / 100;
		i++;
	}
	fclose(fp1);
	return student;
}


int main() {

	stud* student;
	int br = brojStud();

	printf("Broj studenata: %d\n", br);
	student = studPodatci(br);
	printf("podatci o studentima:\n");
	for (int i = 0; i < br; i++)
		printf("ime: %s\nprezime: %s\nbroj bodova: %d\npostotak: %lf\n", student[i].ime, student[i].prezime, student[i].brojBodova, student[i].postotak*100);

	return 0;
}