#pragma once
#include "clist.h"

typedef struct point {
    int x, y;
    struct intrusive_node node;
} point_t;

void add_point(intrusive_list_t* ptr_to_list , int x, int y);
void remove_point(intrusive_list_t* ptr_to_list, int x, int y);
void show_all_points(intrusive_list_t* ptr_to_list);
void remove_all_points(intrusive_list_t* ptr_to_list);