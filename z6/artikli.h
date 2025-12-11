typedef struct article* PosA;
typedef struct article {
	char name[50];
	int ammount;
	double price;
	PosA next;
} Article;

