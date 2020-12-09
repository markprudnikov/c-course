#include "clist.h"
#include <stddef.h>

void init_list(intrusive_list_s* ptr_to_list){
   ptr_to_list->head = NULL;
}

void add_node(intrusive_list_s* ptr_to_list, intrusive_node_s* ptr_to_new_node){
    /* If the list is only initialized (has no nodes yet) */
    if (ptr_to_list->head == NULL){
        ptr_to_list->head = ptr_to_new_node;
        ptr_to_new_node->next = NULL;
        ptr_to_new_node->prev = NULL;

        return;
    }

    /* Get the pointer to the current first node */
    intrusive_node_s* ptr_to_node = ptr_to_list->head;
    /* Set new first node */
    ptr_to_list->head = ptr_to_new_node;
    ptr_to_list->head->prev = NULL;
    ptr_to_list->head->next = ptr_to_node;
    /* Old first node now goes after new first node */
    ptr_to_node->prev = ptr_to_list->head;
}
void remove_node(intrusive_list_s* ptr_to_list, intrusive_node_s* ptr_to_node){
    /* Get the pointers to the next and previous nodes */
    intrusive_node_s* ptr_next = ptr_to_node->next;
    intrusive_node_s* ptr_prev = ptr_to_node->prev;
    
    /* Node placed between two other nodes */
    if (ptr_next != NULL && ptr_prev != NULL){
        ptr_prev->next = ptr_next;
        ptr_next->prev = ptr_prev;
    }

    /* Node is the first in the list */
    if (ptr_next != NULL){
        ptr_next->prev = NULL;
        ptr_to_list->head = ptr_next;

        return;
    }
    
    /* Node is the last in the list */
    if (ptr_prev != NULL){
        ptr_prev->next = NULL;

        return;
    }

    /* There is only one node in the list */
    ptr_to_list->head = NULL;
}

int get_length(intrusive_list_s* ptr_to_list){
    /* Get the pointer to the first node */
    intrusive_node_s* ptr_to_node = ptr_to_list->head;

    int length = 0;
    /* Count while pointer->next != NULL */
    for ( ; ptr_to_node != NULL; ptr_to_node = ptr_to_node->next, length++);

    return length;
}