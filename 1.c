#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    struct Contact *left, *right;
};

struct Contact* createNode(char name[], char phone[]) {
    struct Contact* newNode = (struct Contact*)malloc(sizeof(struct Contact));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Contact* insert(struct Contact* root, char name[], char phone[]) {
    if (root == NULL)
        return createNode(name, phone);

    if (strcasecmp(name, root->name) < 0)
        root->left = insert(root->left, name, phone);
    else if (strcasecmp(name, root->name) > 0)
        root->right = insert(root->right, name, phone);
    else
        printf("\nContact already exists!\n");

    return root;
}

struct Contact* search(struct Contact* root, char name[]) {
    if (root == NULL || strcasecmp(root->name, name) == 0)
        return root;

    if (strcasecmp(name, root->name) < 0)
        return search(root->left, name);
    else
        return search(root->right, name);
}

void display(struct Contact* root) {
    if (root != NULL) {
        display(root->left);
        printf("%s : %s\n", root->name, root->phone);
        display(root->right);
    }
}

int main() {
    struct Contact* root = NULL;
    int choice;
    char name[50], phone[15];

    do {
        printf("\n--- PHONE DIRECTORY ---\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Display All Contacts\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); 

        switch (choice) {
            case 1:
                printf("Enter Name: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                printf("Enter Phone Number: ");
                fgets(phone, sizeof(phone), stdin);
                phone[strcspn(phone, "\n")] = '\0';
                root = insert(root, name, phone);
                break;

            case 2:
                printf("Enter Name to Search: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                struct Contact* found = search(root, name);
                if (found)
                    printf("Found: %s - %s\n", found->name, found->phone);
                else
                    printf("Contact not found!\n");
                break;

            case 3:
                printf("\nAll Contacts (A-Z):\n");
                display(root);
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 4);

    return 0;
}