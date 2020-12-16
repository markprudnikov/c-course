#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include "point_list.h"
#include "clist.h"

void add_point(intrusive_list_t* ptr_to_list, int x, int y){
    point_t* point = malloc(sizeof(point_t));
    point->x = x;
    point->y = y;

    add_node(ptr_to_list, &point->node);
}

void remove_point(intrusive_list_t* ptr_to_list, int x, int y){
    intrusive_node_t* ptr_to_node = ptr_to_list->head;

    while (ptr_to_node != NULL){
        point_t* point = container_of(ptr_to_node, point_t, node);
        ptr_to_node = ptr_to_node->next;
        if (point->x == x && point->y == y){
            remove_node(ptr_to_list, &point->node);
            free(point);
        }
    }
}

void show_all_points(intrusive_list_t* ptr_to_list){
    intrusive_node_t* ptr_to_node = ptr_to_list->head;

    while(ptr_to_node != NULL){
        point_t* pointer = container_of(ptr_to_node, point_t, node);
        printf("(%d %d)", pointer->x, pointer->y);

        if (ptr_to_node->next != NULL){
            printf(" ");
        }

        ptr_to_node = ptr_to_node->next;
    }
}

void remove_all_points(intrusive_list_t* ptr_to_list){
    intrusive_node_t* ptr_to_node = ptr_to_list->head;

    while (ptr_to_node != NULL){
        point_t* point = container_of(ptr_to_node, point_t, node);
        ptr_to_node = ptr_to_node->next;

        remove_node(ptr_to_list, &point->node);
        free(point);

    }
}
void apply(intrusive_list_t* list, void (*op)(intrusive_node_t* node, void* data), void* data){
    intrusive_node_t* point_to_node = list->head;
    while (point_to_node->next != NULL){
        point_to_node = point_to_node->next;
    }
    while (point_to_node != NULL){
        op(point_to_node, (void *) data);
        point_to_node = point_to_node->prev;
    }
}