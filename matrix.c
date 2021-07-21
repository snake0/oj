//
// Created by N on 2021/7/21.
//
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 32

static int num_nodes = 4;

int link_sched_comm[NTHREADS][NTHREADS] = {
        {0,  12, 5,  3,  0,  1,  1,  1,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  1, 0, 0, 0, 1,  0,  0,  0,  0,  1,  0,  1,  4,  11},
        {12, 0,  12, 2,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  1,  0,  1,  0},
        {5,  12, 0,  12, 1,  4,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  1,  1},
        {3,  2,  12, 0,  5,  1,  1,  1,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  1,  0,  0,  1},
        {0,  0,  1,  5,  0,  10, 0,  1,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {1,  0,  4,  1,  10, 0,  15, 3,  1, 0,  2,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {1,  0,  0,  1,  0,  15, 0,  18, 0, 1,  1,  0,  0,  1,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {1,  0,  0,  1,  1,  3,  18, 0,  8, 3,  2,  2,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  1,  0,  8,  0, 6,  3,  2,  0,  0,  0, 1,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  1,  3,  6, 0,  12, 2,  1,  2,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  2,  1,  2,  3, 12, 0,  10, 1,  1,  0, 1,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  2,  2, 2,  10, 0,  8,  3,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 1,  1,  8,  0,  16, 1, 3,  3,  0,  1, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  1,  0,  0, 2,  1,  3,  16, 0,  6, 2,  3,  1,  0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  1,  6,  0, 8,  0,  0,  2, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  1, 0,  1,  0,  3,  2,  8, 0,  11, 1,  0, 0, 0, 1, 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  3,  3,  0, 11, 0,  12, 5, 1, 2, 0, 0,  0,  1,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  1,  0, 1,  12, 0,  9, 0, 1, 1, 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {1,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  1,  0,  2, 0,  5,  9,  0, 7, 5, 0, 1,  0,  0,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  1,  0,  7, 0, 7, 1, 0,  0,  3,  0,  0,  0,  1,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  2,  1,  5, 7, 0, 9, 1,  2,  2,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 1,  0,  1,  0, 1, 9, 0, 8,  0,  2,  0,  0,  0,  0,  0,  0,  0},
        {1,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 1,  0,  1,  1, 0, 1, 8, 0,  10, 3,  0,  0,  0,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 2, 0, 10, 0,  14, 2,  0,  1,  0,  0,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  1,  0,  0, 3, 2, 2, 3,  14, 0,  12, 0,  1,  2,  2,  0,  2},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  2,  12, 0,  16, 2,  2,  2,  0,  0},
        {0,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  16, 0,  5,  1,  1,  0,  0},
        {1,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  1,  1,  2,  5,  0,  10, 4,  4,  1},
        {0,  1,  0,  1,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 1, 0, 0, 0,  0,  2,  2,  1,  10, 0,  10, 1,  1},
        {1,  0,  0,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  2,  2,  1,  4,  10, 0,  15, 2},
        {4,  1,  1,  0,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  0,  0,  0,  4,  1,  15, 0,  13},
        {11, 0,  1,  1,  0,  0,  0,  0,  0, 0,  0,  0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0,  0,  2,  0,  0,  1,  1,  2,  13, 0}
};

static void link_sched_print_matrix(int k[][NTHREADS]) {
    int i, j;
    printf("======[ matrix ]======\n");
    for (i = 0; i < NTHREADS; ++i) {
        for (j = 0; j < NTHREADS; ++j) {
            printf("%2d ", k[i][j]);
        }
        printf("\n");
    }
    printf("======[ matrix ]======\n");
}

typedef struct {
    int *pids;
    size_t size;
} clique_t;

typedef struct {
    clique_t **csp;
    size_t size;

} cliques_t;

void print_clique(clique_t *c) {
    size_t size, i;
    if (c) {
        size = c->size;
        printf("{");
        for (i = 0; i < size; ++i) {
            printf("%d ", c->pids[i]);
        }
        printf("}\n");
    } else {
        printf("NULL in print_clique!\n");
    }
}

void print_cliques(cliques_t *cliques) {
    size_t size, i;
    if (cliques) {
        size = cliques->size;
        printf("--Begin Cliques\n");
        for (i = 0; i < size; ++i) {
            print_clique(cliques->csp[i]);
        }
        printf("--End Cliques\n");
    } else {
        printf("NULL in print_cliques!\n");
    }
}

int clique_distance(clique_t *c1, clique_t *c2) {
    int distance = 0, i, j;
    if (c1 && c2) {
        for (i = 0; i < c1->size; ++i) {
            for (j = 0; j < c2->size; ++j) {
                distance += link_sched_comm[c1->pids[i]][c2->pids[j]];
            }
        }
    } else {
        printf("NULL in clique_distance!\n");
    }
    return distance;
}

clique_t *malloc_clique(void) {
    clique_t *ret = (clique_t *) malloc(sizeof(clique_t));
    if (!ret) {
        printf("Malloc error in malloc_clique\n");
        return NULL;
    }
    ret->size = NTHREADS;
    ret->pids = (int *) malloc(sizeof(int) * ret->size);
    if (!ret->pids) {
        printf("Malloc error in malloc_clique\n");
        free(ret);
        return NULL;
    }
    return ret;
}

void free_clique(clique_t *clique) {
    if (clique) {
        free(clique->pids);
        free(clique);
    }
    else {
        printf("NULL in free_clique\n");
    }
}

cliques_t *init_cliques(void) {

}

int main() {
//    int i;
//    cliques_t *cliques;
//
//    cliques = (cliques_t *) malloc(sizeof(cliques_t));
//    link_sched_print_matrix(link_sched_comm);
//
//    cliques->size = NTHREADS;
//    cliques->csp = (clique_t **) malloc(cliques->size * sizeof(clique_t *));
//
//    for (i = 0; i < NTHREADS; ++i) {
//        cliques->csp[i] = (clique_t *) malloc(sizeof(clique_t));
//        cliques->csp[i]->pids = (int *)
//                malloc(sizeof(int) * (NTHREADS / num_nodes));
//        cliques->csp[i]->pids[0] = i;
//        cliques->csp[i]->size = 1;
//    }
//    print_cliques(cliques);
//
////    while (cliques->size > num_nodes) {
////        print_cliques(cliques);
////
////    }
//
//    for (i = 0; i < NTHREADS; ++i) {
//        free(cliques->csp[i]->pids);
//        cliques->csp[i]->pids = NULL;
//        free(cliques->csp[i]);
//    }
//    free(cliques->csp);
//    free(cliques);
int *p = malloc(10);
}
