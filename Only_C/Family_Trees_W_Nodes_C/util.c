#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


void addPerson(Node **root)
{
    Node *newPerson = (Node *)malloc(sizeof(Node));
    newPerson->mother = (Node *)malloc(sizeof(Node));
    newPerson->father = (Node *)malloc(sizeof(Node));
    printf("Enter the person's name: ");
    scanf("%s", newPerson->name);
    printf("Enter the person's age: ");
    scanf("%d", &(newPerson->age));
        char motherName[50];
        char fatherName[50];
        printf("Enter the person's mother's name: ");
        scanf("%s", newPerson->mother->name);
        printf("Enter the person's father's name: ");
        scanf("%s", newPerson->father->name);
    newPerson->mother->mother = NULL;
    newPerson->mother->father = NULL;

    printf("%s has been added to the family tree successfully.\n", newPerson->name);

}

void removePerson(Node **root)
{
    if (*root == NULL)
    {
        printf("Family tree is empty!\n");
        return;
    }

    char name[50];
    printf("Enter the person's name to remove: ");
    scanf("%s", name);

    Node *current = *root;
    Node *parent = NULL;
    Node *person = NULL;

    // Search for the person to remove
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            person = current;
            break;
        }
        parent = current;
        current = current->mother;
    }

    if (person == NULL)
    {
        printf("Person not found in the family tree!\n");
        return;
    }

    // Warn the user if the person has children
    if (person->mother != NULL || person->father != NULL)
    {
        printf("Warning: Removing this person will also remove their children!\n");
        printf("Do you still want to continue? (yes/no): ");
        char choice[4];
        scanf("%s", choice);
        if (strcmp(choice, "yes") != 0)
        {
            printf("Removal aborted!\n");
            return;
        }
    }

    // Remove the person from the family tree
    if (parent == NULL)
    {
        *root = NULL;
    }
    else if (parent->mother == person)
    {
        parent->mother = NULL;
    }
    else if (parent->father == person)
    {
        parent->father = NULL;
    }

    free(person);
    printf("Person removed successfully!\n");
}

Node *loadFamilyTreeFromFile(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Failed to open the file: %s\n", filename);
        return NULL;
    }

    Node *root = NULL;
    int count = 0;
    fscanf(file, "%d\n", &count);

    for (int i = 0; i < count; i++)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        fscanf(file, "%s %d", newNode->name, &(newNode->age));

        char motherName[50];
        char fatherName[50];
        fscanf(file, " %s %s\n", motherName, fatherName);

        newNode->mother = NULL;
        newNode->father = NULL;

        if (root == NULL)
        {
            root = newNode;
        }
        else
        {
            Node *mother = NULL;
            Node *father = NULL;
            Node *current = root;

            while (current != NULL)
            {
                if (strcmp(current->name, motherName) == 0)
                {
                    mother = current;
                }
                else if (strcmp(current->name, fatherName) == 0)
                {
                    father = current;
                }
                current = current->mother;
            }

            if (mother == NULL || father == NULL)
            {
                printf("Mother or father not found in the family tree!\n");
                free(newNode);
                fclose(file);
                return NULL;
            }

            newNode->mother = mother;
            newNode->father = father;
        }
    }

    fclose(file);
    printf("Family tree loaded successfully!\n");
    submenucase1(&root);

    return root;
}

void saveFamilyTree(Node *root, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Failed to open the file: %s\n", filename);
        return;
    }

    int count = 0;
    Node *current = root;

    // Count the number of nodes in the family tree
    while (current != NULL)
    {
        count++;
        current = current->mother;
    }

    fprintf(file, "%d\n", count);

    // Save the family tree to the file
    current = root;
    while (current != NULL)
    {
        fprintf(file, "%s %d", current->name, current->age);
        if (current->mother != NULL)
        {
            fprintf(file, " %s", current->mother->name);
        }
        else
        {
            fprintf(file, " NULL");
        }
        if (current->father != NULL)
        {
            fprintf(file, " %s\n", current->father->name);
        }
        else
        {
            fprintf(file, " NULL\n");
        }
        current = current->mother;
    }

    printf("Family tree saved to %s successfully!\n", filename);

    fclose(file);
}

void listFamilyTrees()
{
    printf("Listing Family Trees:\n");
    // Implement the logic to list available family trees
}

void displayMenu(Node **root)
{
    int choice;
    while (1)
    {
        choice = anamenu();

        switch (choice)
        {
        case 1:
        {   
            int sayi;
            sayi=submenucase1(root);
            while(sayi==1){
                submenucase1(root);
            }
            break;
        }
        case 2:
            submenucase2();
            break;
        case 3:
        {
            submenucase3(root);
            break;
        }
        case 4:
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}

int submenucase3(Node **root)
{
    //listFamilyTrees();
    printf("Enter the name of the txt file of the family tree: ");
    char filename[50];
    scanf("%s", filename);
    *root = loadFamilyTreeFromFile(filename);
}

int submenucase2()
{
    printf("Enter the name of the txt file of the family tree: ");
    char filename[50];
    scanf("%s", filename);
    if (remove(filename) == 0)
    {
        printf("%s has been removed successfully.\n", filename);
    }
    else
    {
        printf("Failed to remove %s.\n", filename);
    }
}

int submenucase1(Node **root)
{
    int choice;
    printf("1-Add person\n");
    printf("2-Remove person\n");
    printf("3-Save Family Tree\n");
    printf("4-Exit\n");
    printf("> ");
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        addPerson(root);
        return 1;
        break;
    case 2:
        removePerson(root);
        return 1;
        break;
    case 3:
        printf("Enter the name of the txt file to save the family tree: ");
        char filename[50];
        scanf("%s", filename);
        saveFamilyTree(*root, filename);
        return 0;
        break;
    case 4:
        exit(0);
        return 0;
        break;
    default:
        printf("Invalid choice. Please try again.\n");
    }
}

int anamenu()
{
    int choice;
    printf("\n***********************\n");
    printf("Family Tree System Menu:\n");
    printf("1-Add Family Tree\n");
    printf("2-Remove Family Tree\n");
    printf("3-Load Family Tree\n");
    printf("4-Exit\n");
    printf("> ");
    scanf("%d", &choice);
    return choice;
}