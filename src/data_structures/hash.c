// TODO: redo this sometime

#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define TABLE_SIZE 15
#define MAX_NAME_SIZE 64

typedef struct Node{
    char* name;
    Node* next;
} Node;

typedef struct Hash{
    Node* head;
} Hash;

Hash table[TABLE_SIZE];

void initialize(){
    for(int i=0; i<TABLE_SIZE; i++){
        table[i].head = (Node*) malloc(sizeof(Node));
        table[i].head->name = "DUMMY";
        table[i].head->next = NULL;
    }
}

int get_hash_key(char* s){
    int hashKey = 0;
    for(int i=0; s[i] != '\0'; ++i) hashKey += (int)s[i];
    return hashKey % TABLE_SIZE;
}

void insert(char* s){
    int key = get_hash_key(s);
    Node* tmp = table[key].head;
    while(tmp->next != NULL) tmp = tmp->next;
    Node* a = (Node*) malloc(sizeof(Node));
    a->name = (char*) malloc(sizeof(char)*MAX_NAME_SIZE);
    strcpy(a->name, s);
    a->next = NULL;
    tmp->next = a;
}

bool search_list(char* s, Node* i){
    if(i == NULL) return false;
    if(strcmp(s, i->name) == 0){
        return true;
    }else{
        return search_list(s, i->next);
    }
}

bool search(char* s, Hash* table){
    int id = get_hash_key(s);
    return search_list(s, table[id].head);
}

void clear_list(Node* i){
    if(i == NULL) return;
    clear_list(i->next);

    if(strcmp(i->name, "DUMMY") != 0){
        free(i->name);
    }
    free(i);
}

void clear(){
    for(int i=0; i<TABLE_SIZE; i++){
        clear_list(table[i].head);
        table[i].head = NULL;
    }
}





