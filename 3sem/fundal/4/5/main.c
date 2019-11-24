


#include <stdlib.h>
#include <memory.h>
#include <stdio.h>

typedef struct TreeNode {
    struct TreeNode* left;
    struct TreeNode* right;
    int count;
    char* data;
} TreeNode;

TreeNode* createTreeNode(char* data) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->data = data;
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

int cmpChar(char *a, char *b) {
    char* aPtr = a;
    char* bPtr = b;

    for (int i = 0; i < strlen(a); ++i) {
        if (*aPtr > *bPtr) return 1;
        if (*aPtr < *bPtr) return -1;
        aPtr++;
        bPtr++;
    }
    if (strlen(a) < strlen(b)) return -1;
    return 0;
}

void insertInTree(TreeNode** root, char* data) {

    if (*root == NULL) {
        *root = createTreeNode(data);
        return;
    } else {
        if (strcmp((*root)->data, data) == 0) {
            (*root)->count++;
            return;
        } else {
            if (cmpChar((*root)->data, data) > 0) {
                insertInTree(&(*root)->right, data);
            } else if (cmpChar((*root)->data, data) < 0) {
                insertInTree(&(*root)->left, data);
            }
        }
    }
}

void printInfo(TreeNode *root) {
    if (root == NULL) return;

    printf("%s %d\n", root->data, root->count);
    printInfo(root->right);
    printInfo(root->left);
}

void fillArrWithTree(TreeNode** arr, TreeNode* root) {
    if (root == NULL) return;
    int i = 0;
    while (arr[i]) i ++;
    arr[i] = root;
    fillArrWithTree(arr, root->left);
    fillArrWithTree(arr, root->right);
}

int deep = 0;
void treeDeep(TreeNode* root, int i) {
    if (root == NULL) return;
    i++;
    if (i > deep) deep = i;
    treeDeep(root->right, i);
    treeDeep(root->left, i);
}

void treeToFile(FILE* file, TreeNode* root) {
    if (root == NULL)
        return;
    fprintf(file, "%s %d ", root->data, root->count);
    if (root->left) {
        fprintf(file, "1 ");
//        treeToFile(file, root->left);
    } else {
        fprintf(file, "0 ");
    }

    if (root->right) {
        fprintf(file, "1 ");
//        treeToFile(file, root->right);
    } else {
        fprintf(file, "0 ");
    }

    treeToFile(file, root->left);
    treeToFile(file, root->right);
}

TreeNode* fileToTree(FILE* file, TreeNode* tree) {
    if (!(feof(file))) {
        if (tree == NULL) {
            tree = malloc(sizeof(TreeNode));
            char strBuf[250];
            int count;
            fscanf(file, "%s %d", strBuf, &count);
            char *str = malloc(sizeof(char) * (strlen(strBuf) + 1));
            strcpy(str, strBuf);
            tree->left = NULL;
            tree->right = NULL;
            tree->count = count;
            tree->data = str;
        }
        int l,r;
        fscanf(file, "%d %d", &l, &r);
        if (l) tree->left = fileToTree(file, tree->left);
        if (r) tree->right = fileToTree(file, tree->right);
        return tree;
    }
}

int treeSize = 0;

void getTreeSize(TreeNode* root) {
    if (root == NULL) return;
    treeSize ++;
    getTreeSize(root->left);
    getTreeSize(root->right);

}

int main(int argc, char* argv[]) {
    int action = 0;
    int size = 0;
    TreeNode *root;
    while (action != 4) {
        treeSize = 0;
        printf("1. Load text and build tree\n"
               "2. Print info\n"
               "3. Find and print deep of tree\n"
               "4. Save tree to file\n"
               "5. Load tree from file\n");
        scanf("%d", &action);

        switch (action) {
            case 1: {
                FILE *file;
                if (argc < 2 || !(file = fopen(argv[1], "r"))) {
                    exit(-1);
                }
                char buf[250];
                root = NULL;

                while (!(feof(file))) {
                    fscanf(file, "%s", buf);
                    size++;
                    char *data = malloc(sizeof(char) * (strlen(buf) + 1));
                    strcpy(data, buf);
                    insertInTree(&root, data);
                }
                printf("Text loaded, tree built\n\n");

                fclose(file);

            }
            break;

            case 2: {
                getTreeSize(root);
                size = treeSize;
                printInfo(root);

                TreeNode *arr[size];
                for (int j = 0; j < size; ++j) {
                    arr[j] = NULL;
                }
                fillArrWithTree(arr, root);

                int l;
                for (l = 0; l < size; ++l) {
                    if (arr[l] == NULL) {

                        break;
                    }
                }

                size = l;

                for (int k = 0; k < size; ++k) {
                    for (int i = size - 1; i > k; --i) {
                        if (arr[i]->count > arr[k]->count) {
                            TreeNode *tmp = arr[i];
                            arr[i] = arr[k];
                            arr[k] = tmp;
                        }
                    }
                }

                int n;
                printf("Enter n\n");
                scanf("%d", &n);

                for (int i = 0; i < n; ++i) {
                    printf("%s %d\n", arr[i]->data, arr[i]->count);
                }

                int min;
                int max;
                char *cMin = arr[0]->data;
                char *cMax = arr[0]->data;

                for (int m = 0; m < size; ++m) {
                    if (strlen(arr[m]->data) > strlen(cMax)) {
                        cMax = arr[m]->data;
                    }

                    if (strlen(arr[m]->data) < strlen(cMin)) {
                        cMin = arr[m]->data;
                    }
                }
                printf("Max %s Min %s\n", cMax, cMin);
                break;
            }


            case 3:
                deep = 0;
                treeDeep(root, 0);
                printf("Deep %d\n", deep);
                break;

            case 4:
                printf("Enter name of file\n");
                char nameBuf[250];
                scanf("%s", nameBuf);

                FILE* saveFile;
                if (!(saveFile = fopen(nameBuf, "w"))) {
                    printf("Couldn't open %s\n", nameBuf);
                } else {
                    treeToFile(saveFile, root);
                }
                fclose(saveFile);
                break;

            case 5:
                printf("Enter name of file\n");

                scanf("%s", nameBuf);

                FILE* loadFile;
                if (!(loadFile = fopen(nameBuf, "r"))) {
                    printf("Couldn't open %s\n", nameBuf);
                } else {
                    root = fileToTree(loadFile, root);
                }
                fclose(loadFile);
                break;
        }
    }

}