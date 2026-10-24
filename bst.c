/* Student Record Search System using Binary Search Tree
   Key = enrolment ID */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[30];
    char dept[20];
};

struct Node {
    struct Student data;
    struct Node *left;
    struct Node *right;
};

int dup = 0;        /* becomes 1 if duplicate ID is found */
int count = 0;      /* counts comparisons during insertion */

struct Node *newNode(int id, char name[], char dept[])
{
    struct Node *n;
    n = (struct Node *)malloc(sizeof(struct Node));
    n->data.id = id;
    strcpy(n->data.name, name);
    strcpy(n->data.dept, dept);
    n->left = NULL;
    n->right = NULL;
    return n;
}

/* Insert: rejects duplicate IDs */
struct Node *insert(struct Node *root, int id, char name[], char dept[])
{
    if (root == NULL)
        return newNode(id, name, dept);

    count++;
    if (id < root->data.id)
        root->left = insert(root->left, id, name, dept);
    else if (id > root->data.id)
        root->right = insert(root->right, id, name, dept);
    else
        dup = 1;
    return root;
}

/* Search by ID */
struct Node *search(struct Node *root, int id)
{
    if (root == NULL || root->data.id == id)
        return root;
    if (id < root->data.id)
        return search(root->left, id);
    return search(root->right, id);
}

/* Smallest node in a subtree */
struct Node *findMin(struct Node *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

/* Delete: leaf, one child, two children */
struct Node *deleteNode(struct Node *root, int id)
{
    struct Node *temp;

    if (root == NULL)
        return NULL;

    if (id < root->data.id)
        root->left = deleteNode(root->left, id);
    else if (id > root->data.id)
        root->right = deleteNode(root->right, id);
    else {
        /* Case 1 and 2: no left child (leaf or only right child) */
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        }
        /* Case 2: only left child */
        if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }
        /* Case 3: two children - use inorder successor */
        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data.id);
    }
    return root;
}

void show(struct Node *n)
{
    printf("%d\t%s\t%s\n", n->data.id, n->data.name, n->data.dept);
}

void inorder(struct Node *root)
{
    if (root != NULL) {
        inorder(root->left);
        show(root);
        inorder(root->right);
    }
}

void preorder(struct Node *root)
{
    if (root != NULL) {
        show(root);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node *root)
{
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        show(root);
    }
}

/* Insert 10 sample records */
struct Node *loadSamples(struct Node *root)
{
    int ids[10] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    char *names[10] = {"Aman", "Simran", "Rahul", "Neha", "Karan",
                       "Jaspreet", "Pooja", "Arjun", "Riya", "Manpreet"};
    char *depts[10] = {"CSE", "AIDS", "CSE", "ECE", "IT",
                       "AIDS", "ME", "CSE", "IT", "ECE"};
    int i;

    for (i = 0; i < 10; i++)
        root = insert(root, ids[i], names[i], depts[i]);
    printf("10 sample records inserted.\n");
    return root;
}

/* Compare balanced-looking order and sorted order */
void compare()
{
    int bal[7] = {4, 2, 6, 1, 3, 5, 7};
    int sor[7] = {1, 2, 3, 4, 5, 6, 7};
    struct Node *t1 = NULL;
    struct Node *t2 = NULL;
    int i;
    int c1, c2;

    count = 0;
    for (i = 0; i < 7; i++)
        t1 = insert(t1, bal[i], "Test", "CSE");
    c1 = count;

    count = 0;
    for (i = 0; i < 7; i++)
        t2 = insert(t2, sor[i], "Test", "CSE");
    c2 = count;

    printf("Balanced order (4,2,6,1,3,5,7) : %d comparisons\n", c1);
    printf("Sorted order   (1,2,3,4,5,6,7) : %d comparisons\n", c2);
}

int main()
{
    struct Node *root = NULL;
    struct Node *res;
    int choice, id;
    char name[30], dept[20];

    do {
        printf("\n===== STUDENT RECORD SYSTEM (BST) =====\n");
        printf("1. Insert\n");
        printf("2. Search\n");
        printf("3. Delete\n");
        printf("4. Inorder (sorted)\n");
        printf("5. Preorder\n");
        printf("6. Postorder\n");
        printf("7. Load 10 sample records\n");
        printf("8. Compare balanced vs sorted insertion\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter ID: ");
            scanf("%d", &id);
            printf("Enter name: ");
            scanf("%s", name);
            printf("Enter department: ");
            scanf("%s", dept);
            dup = 0;
            root = insert(root, id, name, dept);
            if (dup == 1)
                printf("Error: ID %d already exists. Duplicate rejected.\n", id);
            else
                printf("Record inserted.\n");
            break;
        case 2:
            printf("Enter ID to search: ");
            scanf("%d", &id);
            res = search(root, id);
            if (res != NULL) {
                printf("Record found:\n");
                show(res);
            } else
                printf("ID %d not found.\n", id);
            break;
        case 3:
            printf("Enter ID to delete: ");
            scanf("%d", &id);
            if (search(root, id) == NULL)
                printf("ID %d not found. Nothing deleted.\n", id);
            else {
                root = deleteNode(root, id);
                printf("Record deleted.\n");
            }
            break;
        case 4:
            printf("Inorder (sorted by ID):\n");
            inorder(root);
            break;
        case 5:
            printf("Preorder:\n");
            preorder(root);
            break;
        case 6:
            printf("Postorder:\n");
            postorder(root);
            break;
        case 7:
            root = loadSamples(root);
            break;
        case 8:
            compare();
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice.\n");
        }
    } while (choice != 0);

    return 0;
}
