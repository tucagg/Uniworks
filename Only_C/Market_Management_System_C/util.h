#ifndef _UTIL_H_
#define _UTIL_H_

#define MAX_PRODUCTS 100
#define MAX_TYPE 20
#define MAX_NAME 50
#define MAX_BRAND 20

#define MAX_STOCKS 100
#define MAX_TYPE 20
#define MAX_NAME 50
#define MAX_BRAND 20

struct product {
    int pID;
    char type[MAX_TYPE];
    char name[MAX_NAME];
    char brand[MAX_BRAND];
    double price;
};

struct stock{
    int sID;
    int pID1;
    char branch[MAX_BRAND];
    int current_stock;
};


int menu();
int file_operations();
void addProduct(struct product *products, int *count);
void addStock(struct stock *stocks, int *count1);
void deleteProduct(struct product *products, int *count);
void deleteStock(struct stock *stocks, int *count1);


#endif /* _UTIL_H_ */