#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

typedef struct point {
	int x, y;
	struct intrusive_node node;
} point_s;

void add_point(intrusive_list_s* ptr_to_list, int x, int y){
	point_s* point = malloc(sizeof(point_s));
	point->x = x;
	point->y = y;

	add_node(ptr_to_list, &point->node);
}

void remove_point(intrusive_list_s* ptr_to_list, int x, int y){
	intrusive_node_s* ptr_to_node = ptr_to_list->head;

	while (ptr_to_node != NULL){
		point_s* point = container_of(ptr_to_node, point_s, node);
		ptr_to_node = ptr_to_node->next;
		if (point->x == x && point->y == y){
			remove_node(ptr_to_list, &point->node);
			free(point);
		}
	}
}

void show_all_points(intrusive_list_s* ptr_to_list){
	intrusive_node_s* ptr_to_node = ptr_to_list->head;

	while(ptr_to_node != NULL){
		point_s* pointer = container_of(ptr_to_node, point_s, node);
		printf("(%d %d)", pointer->x, pointer->y);

		if (ptr_to_node->next != NULL){
			printf(" ");
		}

		ptr_to_node = ptr_to_node->next;
	}
}

void remove_all_points(intrusive_list_s* ptr_to_list){
	intrusive_node_s* ptr_to_node = ptr_to_list->head;

    while (ptr_to_node != NULL){
    	point_s* point = container_of(ptr_to_node, point_s, node);
		ptr_to_node = ptr_to_node->next;
		
		remove_node(ptr_to_list, &point->node);
		free(point);
		
    }
}

int main(void){
	intrusive_list_s l;
	init_list(&l);

	while(1){
		char buf[239];
		scanf("%239s", buf);

		if (strcmp(buf, "len") == 0){
			printf("%d\n", get_length(&l));

		} else if(strcmp(buf, "exit") == 0){
			remove_all_points(&l);

			exit(0);

		} else if(strcmp(buf, "print") == 0){
			show_all_points(&l);
			printf("\n");

		} else if (strcmp(buf, "rma") == 0){
			remove_all_points(&l);

		} else if(strcmp(buf, "add") == 0){
			int x,y;
			scanf("%d %d", &x, &y);

			add_point(&l, x, y);

		} else if(strcmp(buf, "rma") == 0){
			remove_all_points(&l);

		} else if(strcmp(buf, "rm") == 0){
			int x,y;
			scanf("%d %d", &x, &y);

			remove_point(&l, x, y);

		} else {
			printf("Unknown command\n");
		}
	}
}