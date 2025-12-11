#include "artikli.h"
typedef struct date* PosD;

typedef struct date {
	int day;
	int month;
	int year;
	PosA item;
	PosD next;
} Date;


