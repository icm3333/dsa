#include<stdlib.h>
#include<stdbool.h>

typedef struct{
    int x;
    struct Node *left, *right;    
} Node;

Node* root;

Node* create_node(int value){
    Node* new = (Node*) malloc(sizeof(Node));
    new->left = new->right = NULL;
    new->x = value;
    return new;
}

Node* insert_tree(Node* i, int value){
    if(i == NULL){
        i = create_node(value);
    }else if(value > i->x){
        i->right = insert_tree(i->right, value);
    }else if(i->x > value){
        i->left = insert_tree(i->left, value);
    }
    return i;
}

void insert(int value){
    root = insert_tree(root, value);
}

bool search_tree(int value, Node* i){
    if(i == NULL){
        return false;
    }else if(i->x == value){
        return true;
    }else if(value > i->x){
        return search_tree(value, i->right);
    }else{
        return search_tree(value, i->left);
    }
}

bool search(int value){
    return search_tree(value, root);
}

void free_tree(Node* i){
    if(i!=NULL){
        free_tree(i->left);
        free_tree(i->right);

        i->right = i->left = NULL;
        free(i);
    }
}