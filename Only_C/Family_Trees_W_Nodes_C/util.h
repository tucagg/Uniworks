#ifndef _UTIL_H_
#define _UTIL_H_

typedef struct Node
{
    char name[50];
    int age;
    struct Node *mother;
    struct Node *father;
} Node;

int anamenu();
int submenucase1(Node **root);
int submenucase2();
int submenucase3(Node **root);
void displayMenu(Node **root);
void listFamilyTrees();
void loadFamilyTree(Node **root, char *filename);
void addPerson(Node **root);
void saveFamilyTree(Node *root, const char *filename);


#endif /* _UTIL_H_ */