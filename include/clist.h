#pragma once
#ifndef CLIST_H_
#define CLIST_H_
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
} intrusive_node_t;

typedef struct intrusive_list {
  struct intrusive_node* head;
} intrusive_list_t;

void init_list(intrusive_list_t* ptr_to_list);
void add_node(intrusive_list_t* ptr_to_list, intrusive_node_t * ptr_to_new_node);
void remove_node(intrusive_list_t* list, intrusive_node_t* node);
int get_length(intrusive_list_t* list);
void apply(intrusive_list_t* list, void (*op)(intrusive_node_t* node, void* data), void* data);

#endif