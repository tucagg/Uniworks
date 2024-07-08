#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int menu(){
    int menu_choice;
    menu_choice=0;
    while(menu_choice!=5 || menu_choice<1||menu_choice>5){
    printf("Welcome operator, please select an option to continue: \n");
    printf("1-File Operations\n");
    printf("2-Query products\n");
    printf("3-Check stock status\n");
    printf("4-Stock control by brand\n");
    printf("5-Export report\n");
    scanf("%d",&menu_choice);
    switch(menu_choice){
        case 1:
        file_operations();
        break;
        case 2:
            int case2chose;
            printf("1.List all products\n2.Filter products by brand, type, price, or a user-defined feature\n3.Back to main menu.\n");
            scanf("%d",&case2chose);
            switch(case2chose){
                case 1:
                FILE *fp;
                struct product products[MAX_PRODUCTS];
                int count = 0, choice;

                fp = fopen("products.txt", "r");

                if (fp == NULL) {
                    printf("Dosya acilamadi!\n");
                    return 1;
                }

                while (!feof(fp) && count < MAX_PRODUCTS) {
                    struct product p;
                    if (fscanf(fp, "%d,%[^,],%[^,],%[^,],%lf", &p.pID, p.type, p.name, p.brand, &p.price) == 5) {
                        products[count] = p;
                        count++;
                    }
                }

                fclose(fp);
                for (int i = 0; i < count; i++) {
                    printf("Product %d: %s %s %s %.2lf\n", products[i].pID, products[i].type, products[i].name, products[i].brand, products[i].price);
                }
                break;
                case 2:
                printf("unable now.\n");
                break;
                case 3:
                menu();
                break;
            }
        break;
        case 3:
        //buraya yaz
        break;
        case 4:
        //buraya yaz
        break;
        case 5:
    }
    }
}
void addProduct(struct product *products, int *count) {
    if (*count >= MAX_PRODUCTS) {
        printf("Maksimum urun sayisina ulasildi!\n");
        return;
    }

    struct product p;

    printf("Urun ozelliklerini girin:\n");
    p.pID = (*count) + 1; // Otomatik olarak artan pID ataması
    printf("Type: ");
    scanf("%s", p.type);
    printf("Name: ");
    scanf("%s", p.name);
    printf("Brand: ");
    scanf("%s", p.brand);
    printf("Price: ");
    scanf("%lf", &p.price);

    products[*count] = p;
    (*count)++;

    FILE *fp;
    fp = fopen("products.txt", "a");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }
    fprintf(fp, "%d,%s,%s,%s,%.2lf\n", p.pID, p.type, p.name, p.brand, p.price);
    fclose(fp);

    printf("Urun basariyla eklendi!\n");
}

void addStock(struct stock *stocks, int *count1) {
    if (*count1 >= MAX_STOCKS) {
        printf("Maksimum urun sayisina ulasildi!\n");
        return;
    }

    struct stock s;

    printf("Urun ozelliklerini girin:\n");
    s.sID = (*count1) + 1; // Otomatik olarak artan pID ataması
    printf("pID: ");
    scanf("%d", &s.pID1);
    printf("Branch: ");
    scanf("%s", s.branch);
    printf("Current Stock: ");
    scanf("%d", &s.current_stock);

    stocks[*count1] = s;
    (*count1)++;

    FILE *fp1;
    fp1 = fopen("stocks.txt", "a");
    if (fp1 == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }
    fprintf(fp1, "%d,%d,%s,%d\n", s.sID, s.pID1, s.branch, s.current_stock);
    fclose(fp1);

    printf("Urun basariyla eklendi!\n");
}


void deleteProduct(struct product *products, int *count) {
    if (*count == 0) {
        printf("Hicbir urun kayitli degil!\n");
        return;
    }

    int pID;
    printf("Silmek istediginiz urunun ID'sini girin: ");
    scanf("%d", &pID);

    int found = 0;
    for (int i = 0; i < *count; i++) {
        if (products[i].pID == pID) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                products[j] = products[j + 1];
                products[j].pID--; // pID'leri güncelle
            }
            (*count)--;
            break;
        }
    }

    if (found) {
        FILE *fp;
        fp = fopen("products.txt", "w");
        if (fp == NULL) {
            printf("Dosya acilamadi!\n");
            return;
        }
        for (int i = 0; i < *count; i++) {
            fprintf(fp, "%d,%s,%s,%s,%.2lf\n", products[i].pID, products[i].type, products[i].name, products[i].brand, products[i].price);
        }
        fclose(fp);

        printf("Urun basariyla silindi!\n");
    } else {
        printf("ID'si %d olan urun bulunamadi!\n", pID);
    }
}
void deleteStock(struct stock *stocks, int *count1) {
    if (*count1 == 0) {
        printf("Hicbir urun kayitli degil!\n");
        return;
    }

    int sID;
    printf("Silmek istediginiz urunun ID'sini girin: ");
    scanf("%d", &sID);

    int found1 = 0;
    for (int i1 = 0; i1 < *count1; i1++) {
        if (stocks[i1].sID == sID) {
            found1 = 1;
            for (int j1 = i1; j1 < *count1 - 1; j1++) {
                stocks[j1] = stocks[j1 + 1];
                stocks[j1].sID--; // sID'leri güncelle
            }
            (*count1)--;
            break;
        }
    }

    if (found1) {
        FILE *fp1;
        fp1 = fopen("stocks.txt", "w");
        if (fp1 == NULL) {
            printf("Dosya acilamadi!\n");
            return;
        }
        for (int i1 = 0; i1 < *count1; i1++) {
            fprintf(fp1, "%d,%d,%s,%d\n", stocks[i1].sID, stocks[i1].pID1, stocks[i1].branch, stocks[i1].current_stock);
        }
        fclose(fp1);

        printf("Urun basariyla silindi!\n");
    } else {
        printf("ID'si %d olan urun bulunamadi!\n", sID);
    }
}
int file_operations() {
    FILE *fp;
    struct product products[MAX_PRODUCTS];
    int count = 0, choice;

    fp = fopen("products.txt", "r");

    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    while (!feof(fp) && count < MAX_PRODUCTS) {
        struct product p;
        if (fscanf(fp, "%d,%[^,],%[^,],%[^,],%lf", &p.pID, p.type, p.name, p.brand, &p.price) == 5) {
            products[count] = p;
            count++;
        }
    }

    fclose(fp);

    FILE *fp1;
    struct stock stocks[MAX_STOCKS];
    int count1 = 0;

    fp1 = fopen("stocks.txt", "r");

    if (fp1 == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    while (!feof(fp1) && count1 < MAX_STOCKS) {
        struct stock s;
        if (fscanf(fp1, "%d,%d,%[^,],%d", &s.sID, &s.pID1, s.branch, &s.current_stock) == 4) {
            stocks[count1] = s;
            count1++;
        }
    }

    fclose(fp1);

    // seçenekli işlemler
    printf("1- Add a new product\n2- Delete a product\n3- Update a product\n4- Add a feature to product\n5- Add a new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n8- Back to main menu\nSecim: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            addProduct(products, &count);
            break;
        case 2:
            deleteProduct(products, &count);
            break;
        case 3:
            printf("\nsu an icin olmuyo.\n");
            break;
        case 4:
            printf("\nsu an icin olmuyo.\n");
            break;
        case 5:
            addStock(stocks, &count1);
            break;
        case 6:
            deleteStock(stocks, &count1);
            break;
        case 7:
            printf("\nsu an icin olmuyo.\n");
            break;
        case 8:
            menu();
            break;
        default:
            printf("Gecersiz secim!\n");
            break;
    }

    if(choice==1|| choice==2){
        for (int i = 0; i < count; i++) {
            printf("Product %d: %s %s %s %.2lf\n", products[i].pID, products[i].type, products[i].name, products[i].brand, products[i].price);
        }
    }
    if(choice==5|| choice==6){
        for (int i1 = 0; i1 < count1; i1++) {
            printf("Stock %d: %d %s %d\n", stocks[i1].sID, stocks[i1].pID1, stocks[i1].branch, stocks[i1].current_stock);
        }
    }

    file_operations();
}