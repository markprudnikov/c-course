#pragma once
#ifndef CLIST_H_
#define CLIST_H_
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct intrusive_node {
  struct intrusive_node* next;
  struct intrusive_node* prev;
} intrusive_node_s;

typedef struct intrusive_list {
  struct intrusive_node* head;
} intrusive_list_s;

void init_list(struct intrusive_list* ptr_to_list);
void add_node(struct intrusive_list* ptr_to_list, struct intrusive_node * ptr_to_new_node);
void remove_node(struct intrusive_list* ptr_to_list, struct intrusive_node* ptr_to_old_node);

int get_length(struct intrusive_list* ptr_to_list);

#endif