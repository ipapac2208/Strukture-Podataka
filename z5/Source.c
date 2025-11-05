#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define OPERATIONS_ERROR 10
#define FILE_AND_OR_STRUCT_ERROR 404

typedef struct postfix* Pos;
typedef struct postfix { 
	double number;
	Pos Next;
} Postfix;

int push(Pos, double);
int calc(Pos, char);
int readFile(Pos);
int pop(Pos);

int main() {
	Postfix Head = { 0,NULL };
	if (readFile(&Head) == FILE_AND_OR_STRUCT_ERROR)
	{
		printf("FILE AND/OR STRUCT ERROR\n");
		return -1;
	}

	return 0;
}

int readFile(Pos p) {
	FILE* fp = fopen("postfix.txt", "r");
	if (!fp) return FILE_AND_OR_STRUCT_ERROR;

	char check[20];
	double num = 0.0;
	int i = 0;

	while (fscanf(fp, "%s", check) == 1) {
		if (isdigit(check[0]))
		{
			num = atof(check);
			push(p, num);
		}
		else if (isblank(check[0]))
			continue;
		else {
			if (calc(p, check[0]) == FILE_AND_OR_STRUCT_ERROR)
				return FILE_AND_OR_STRUCT_ERROR;
		}
	
	}

	printf("result from file: %f", p->Next->number);


	return 0;
}

int push(Pos p, double num) {

	Pos	q = (Pos)malloc(sizeof(Postfix));
	if (!q) return FILE_AND_OR_STRUCT_ERROR;
	q->number = num;
	q->Next = p->Next;
	p->Next = q;

	return 0;
}

int calc(Pos p, char op) {

	double num1 = p->Next->number;
	double num2 = p->Next->Next->number;
	double result = 0.0;
	switch (op) {
	case '+':result = num2 + num1;
			break;
	case '-':
			result = num2 - num1;
			break;
	case '*':
			result = num2 * num1;
			break;
	case '/':
		if (!num1)
		{
			printf("CAN'T DIVIDE WITH NON-EXISTING ELEMENT");
			return FILE_AND_OR_STRUCT_ERROR;
		}
		else
			result = num2 / num1;
		break;
	default:
		printf("UNKNOWN OPERATION\n");
		return FILE_AND_OR_STRUCT_ERROR;
	}
	pop(p);
	p->Next->number = result;

	return 0;
}

int pop(Pos p) {

	Pos q = p->Next;
	p->Next = q->Next;
	free(q);

	return 0;

}