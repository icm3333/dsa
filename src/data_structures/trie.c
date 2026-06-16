#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

typedef struct Node{
    char c;
    struct Node* child[26];
    bool end;
} Node;

Node* create_node(){
    Node* tmp = (Node*) malloc(sizeof(Node));
    tmp->end = false;
    for(int i=0; i<26; i++) tmp->child[i] = NULL;
    return tmp;
}
int getsize(char *s){int i=0; while(s[i] != '\0')i++; return i;}

void insert(char* s, Node* root){
    Node* node = root;
    for(int i=0; s[i] != '\0'; i++){
        int key = s[i] - 'a';
        if(node->child[key] == NULL){
            node->child[key] = create_node();
            node->c = s[i];
        }
        node = node->child[key];
    }
    node->end = true;
}

bool search(char* s, Node* root){
    Node* tmp = root;
    for(int i=0; s[i] != '\0'; i++){
        int key = s[i] - 'a';
        if(tmp->child[key] == NULL){
            return false;
        }
        tmp = tmp->child[key];
    }
    return (tmp != NULL && tmp->end);
}

void delete(char* s, Node* root){
    // todo   
}

int main(){
    Node* root = create_node();
}
