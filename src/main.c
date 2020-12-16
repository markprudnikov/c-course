#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include "clist.h"
#include "point_list.h"

int count_lines(char* file_name){
    FILE* file = fopen(file_name, "r");
    if (file == NULL)
        return 0;
    int line = 0;
    int c;
    while ( (c = getc(file)) != EOF ){
        if (c == '\n'){
            line++;
        }
    }
    fclose(file);
    return line;
}

void count_op(intrusive_node_t* node, void* data){
    (void) node;
    (*(int*)data)++;
}

void print_op(intrusive_node_t* node, void* data){
    point_t* point = container_of(node, point_t, node);
    printf((char*) data, point->x, point->y);
}

void out_op(intrusive_node_t* node, void* data){
    point_t *point;
    point = container_of(node, point_t, node);
    fprintf((FILE*)data, "%d %d\n", point->x, point->y);
}

void int_to_little(int n, unsigned char* buf){
    for (int i = 0; i < 3; i++){
        buf[i] = (unsigned char)((n >> 8*i) & 0xFF);
    }
}

void little_to_int(int* n, unsigned char* buf){
    *n = 0;
    for (int i = 0; i < 3; i++){
        *n |= ((int)buf[i]) << 8*i;
    }
}

void bin_out_op(intrusive_node_t* node, void* data){
    point_t *point;
    point = container_of(node, point_t, node);
    unsigned char buf[3];
    int_to_little(point->x, buf);
    fwrite(buf, 3, 1, (FILE*) data);
    int_to_little(point->y, buf);
    fwrite(buf, 3, 1, (FILE*) data);
}

int main(int argc, char** argv){
    (void) argc;
    intrusive_list_t l;
    init_list(&l);

    /* Working with txt file */
    if (strcmp(argv[1], "loadtext") == 0){
        FILE* txt_file = fopen(argv[2], "rt");
        int a, b;
        while(1){
            fscanf(txt_file, "%d %d", &a, &b);

            if(feof(txt_file)){
                break;
            }

            add_point(&l, a, b);
        }
        fclose(txt_file);
    }
    
    /* Working with bin file */
    if (strcmp(argv[1], "loadbin") == 0){
        FILE* bin_file = fopen(argv[2], "rb");
        int* x = malloc(sizeof(int));
        int* y = malloc(sizeof(int));

        while(1){
            unsigned char buf1[3];
            unsigned char buf2[3];

            fread(buf1, 1, 3, bin_file);
            fread(buf2, 1, 3, bin_file);

            if(feof(bin_file)){
                break;
            }

            little_to_int(x, buf1);
            little_to_int(y, buf2);

            add_point(&l, *x, *y);
        }
        free(x);
        free(y);
        fclose(bin_file);
    }

    /* If file was empty */
    if(get_length(&l) == 0)
        return 0;
    
    /* Working with filled intrusive list */
    if (strcmp(argv[3], "count") == 0){
        int* count = malloc(sizeof(int));
        *count = 0;
        apply(&l, count_op, (void *) count);
        printf("%d\n", *count);
        free(count);
    }

    if (strcmp(argv[3], "print") == 0){
        apply(&l, print_op, (void *)argv[4]);
        printf("\n");
    }

    if (strcmp(argv[3], "savetext") == 0){
        FILE* file = fopen((char*)argv[4], "w+");
        apply(&l, out_op, (void *)file);
        fclose(file);
    }

    if (strcmp(argv[3], "savebin") == 0){
        FILE* file = fopen((char*)argv[4], "wb");
        apply(&l, bin_out_op, (void*) file);
        fclose(file);
    }

    /* Clear memory */
    remove_all_points(&l);
    return 0;
}