#include <stdio.h>
#include <stdlib.h>
#include"scanf.h"

void better_scan(char *message, void *buffer, char type) {
    int ret_var = 0;
    while (ret_var != 1) {
        printf("%s", message);
        if (type == 'f') {
            ret_var = scanf("%f", (float *)buffer);
        } else if (type == 'd') {
            ret_var = scanf("%d", (int *)buffer);
        } else if (type == 's') {
            ret_var = scanf("%s", (char *)buffer);
            ret_var = 1; 
        }
        while (getchar() != '\n') {}
    }
}