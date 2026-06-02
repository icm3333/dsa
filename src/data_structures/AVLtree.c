#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>


typedef struct Node{
    int x;
    struct Node *left, *right;
    int8_t factor;
} Node;

Node* root;

Node* create_node(int value){
    Node* new = (Node*) malloc(sizeof(Node));
    new->left = new->right = NULL;
    new->x = value;
    new->factor = 0;
    return new;
}

Node* insert_tree(Node* i, int value){
    if(i == NULL){
        i = create_node(value);
    }else if(value > i->x){
        i->right = insert_tree(i->right, value);
    }else if(i->x > value){
        i->left = insert_tree(i->left, value);
    }else{
        return i;
    }

    return balance_node(i);
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

int get_biggest_element(){
    Node* i;
    if(root != NULL){
        i = root;
    }else{
        return -1;
    }
    while(i->right != NULL) i = i->right;
    return i->x;
}

int get_smallest_element(){
    Node* i;
    if(root != NULL){
        i = root;
    }else{
        return -1;
    }
    while(i->left != NULL) i = i->left;
    return i->x;
}

void inorder(Node* i){
    if(i!=NULL){
        inorder(i->left);
        printf("%d ", i->x);
        inorder(i->right);
    }
}

void print_inorder(){
    inorder(root);
}

int get_height_node(Node* i){
    if(i == NULL) return -1;

    int leftHeight = get_height_node(i->left);
    int rightHeight= get_height_node(i->right);

    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }else{
        return rightHeight +1;
    }
}

int get_height(){
    return get_height_node(root);
}

Node* rotate_left(Node* i){
    Node* rightNode = i->right;
    Node* rightLeftNode = rightNode->left;

    rightNode->left = i;
    i->right = rightLeftNode;

    return rightNode;
}

Node* rotate_right(Node* i){
    Node* leftNode = i->left;
    Node* leftRightNode = leftNode->right;

    leftNode->right = i;
    i->left = leftRightNode;

    return leftNode;
}

Node* rotate_right_left(Node* i){
    i->right = rotate_right(i->right);
    return rotate_left(i);
}

Node* rotate_left_right(Node* i){
    i->left = rotate_left(i->left);
    return rotate_right(i);
}

int update_node_factor(Node* i){
    if(i == NULL) return 0;
    i->factor = get_height_node(i->right) - get_height_node(i->left);
    return i->factor;
}

Node* balance_node(Node* i){
    if(i != NULL){
        int8_t NF = update_node_factor(i); // NF == Node Factor
        if(NF == 2){
            int8_t rightNF = update_node_factor(i->right);
            if(rightNF >= 0){
                return rotate_left(i);
            }else{
                return rotate_right_left(i);
            }
        }else if(NF == -2){
            int8_t leftNF = update_node_factor(i->left);
            if(leftNF <= 0){
                return rotate_right(i);
            }else{
                return rotate_left_right(i);
            }
        }
    }
    return i;
}

void free_tree(Node* i){
    if(i!=NULL){
        free_tree(i->left);
        free_tree(i->right);

        i->right = i->left = NULL;
        free(i);
    }
}