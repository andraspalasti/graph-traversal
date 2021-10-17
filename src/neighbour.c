#include "neighbour.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* Instantiates a new neighbour
*/
Neighbour *init_neighbour(Node *n) {
    Neighbour *neighbour = (Neighbour *)malloc(sizeof(Neighbour));
    assert(neighbour != NULL);
    neighbour->node = n;
    neighbour->next_node = NULL;
    return neighbour;
}

/*
* Frees the memory allocated by the neighbour
*/
void free_neighbour(Neighbour *neighbour) {
    if (neighbour == NULL)
        return;

    free_neighbour(neighbour->next_node);
    free(neighbour);
}

/*
* Prints the neighbours to the console
*/
void print_neighbour(Neighbour *neighbour) {
    printf("[");
    while (neighbour != NULL) {
        printf("%s%s", neighbour->node->name, neighbour->next_node != NULL ? ", " : "");
        neighbour = neighbour->next_node;
    }
    printf("]\n");
}
