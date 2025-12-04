
typedef Article* PosA;
typedef struct article {
	char name[50];
	int ammount;
	char price[10];
	PosA next;
} Article;
