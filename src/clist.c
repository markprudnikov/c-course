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
void remove_node(intrusive_list_s* ptr_to_list, intrusive_node_s* ptr_to_old_node) {
    /* Get the pointer to the first node */
    intrusive_node_s* ptr_to_node = ptr_to_old_node;
    /* If it's null, then the node isn't in list */
    //while ( ptr_to_node != ptr_to_old_node && ptr_to_node->next != NULL ){
      //  ptr_to_node = ptr_to_node->next;
    //}
    if ( ptr_to_node != NULL ){
        /* Get the pointer to the previous node */
        intrusive_node_s* ptr_prev = ptr_to_node->prev;
        /* Get the pointer to the next node */
        intrusive_node_s* ptr_next = ptr_to_node->next;
        /* If this node is last */
        if( ptr_next == NULL ){
            /*If the current node isn't the last node in the list*/
            if ( ptr_prev != NULL )
                /* Previous node is the last one now */
            ptr_prev->next = NULL;
            else {
                /* List is empty now, last node was removed */
                ptr_to_list->head = NULL;
            }
        }
        /* If this node is first */
        else if ( ptr_prev == NULL ){
            /* Next node is the first one now */
            ptr_next->prev = NULL;
            /* That's why we change the head */
            ptr_to_list->head = ptr_next;
        }
        else{
            /* Connect the previous and the next node around the node to delete */
            ptr_next->prev = ptr_prev;
            ptr_prev->next = ptr_next;
        }
    }
}

int get_length(intrusive_list_s* ptr_to_list){
    /* Get the pointer to the first node */
    intrusive_node_s* ptr_to_node = ptr_to_list->head;
    /* If pointer == NULL, then we don't have nodes, return 0 */
    if ( ptr_to_node == NULL ) return 0;
    int length = 0;
    /* Count till the node.next == NULL */
    while( ptr_to_node != NULL ){
        length++;
        ptr_to_node = ptr_to_node->next;
    }
    return length;
}