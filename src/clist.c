#include <stddef.h>
#include "clist.h"
#include "point_list.h"

void init_list(intrusive_list_t* ptr_to_list){
    ptr_to_list->head = NULL;
}

void add_node(intrusive_list_t* ptr_to_list, intrusive_node_t* ptr_to_new_node){
    /* If the list is only initialized (has no nodes yet) */
    if (ptr_to_list->head == NULL){
        ptr_to_list->head = ptr_to_new_node;
        ptr_to_new_node->next = NULL;
        ptr_to_new_node->prev = NULL;

        return;
    }

    /* Get the pointer to the current first node */
    intrusive_node_t* ptr_to_node = ptr_to_list->head;
    /* Set new first node */
    ptr_to_list->head = ptr_to_new_node;
    ptr_to_list->head->prev = NULL;
    ptr_to_list->head->next = ptr_to_node;
    /* Old first node now goes after new first node */
    ptr_to_node->prev = ptr_to_list->head;
}

void remove_node(intrusive_list_t* list, intrusive_node_t* node){
    if (node->next)
        node->next->prev = node->prev;

    if (node->prev)
        node->prev->next = node->next;

    if (node == list->head)
        list->head = node->next; 

    node->next = NULL;
    node->prev = NULL;
}

int get_length(intrusive_list_t* list){
    /* Get the pointer to the first node */
    intrusive_node_t* node = list->head;

    int length = 0;
    /* Count while pointer != NULL */
    for ( ; node != NULL; node = node->next, length++);

    return length;
}