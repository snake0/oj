//
// Created by N on 2021/7/21.
//
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <i386/limits.h>

#define NTHREADS 1024
#define C_DEBUG
//#define DO_PRINT
//#define C_USEMAX

int num_nodes = 4, cliques_size;

struct clique {
    int pids[NTHREADS];
    int size;
    enum {
        C_VALID, C_REUSE, C_INVALID
    } flag;
} cliques[NTHREADS];


int link_sched_comm[NTHREADS][NTHREADS];

/* = {
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
}; */

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

int clique_distance(struct clique *c1, struct clique *c2) {
    // printf("[%s]\n", __FUNCTION__);
    int ret = 0, i, j;
    if (c1 && c2) {
#ifndef C_USEMAX
        for (i = 0; i < c1->size; ++i) {
            for (j = 0; j < c2->size; ++j) {
                ret += link_sched_comm[c1->pids[i]][c2->pids[j]];
            }
        }
#else
        for (i = 0; i < c1->size; ++i) {
            for (j = 0; j < c2->size; ++j) {
                if (ret < link_sched_comm[c1->pids[i]][c2->pids[j]]) {
                    ret = link_sched_comm[c1->pids[i]][c2->pids[j]];
                }
            }
        }
#endif
    } else {
        printf("clique_distance: NULL pointer\n");
        ret = -1;
    }
    return ret;
}

void init_cliques(void) {
    // printf("[%s]\n", __FUNCTION__);
    int i;
    for (i = 0; i < NTHREADS; ++i) {
        cliques[i].pids[0] = i;
        cliques[i].size = 1;
        cliques[i].flag = C_VALID;
    }
    cliques_size = NTHREADS;
}

void print_clique(struct clique *c) {
#ifdef DO_PRINT
    int j;
//    switch (c->flag) {
//        case C_VALID:
//            printf("VALID ");
//            break;
//        case C_REUSE:
//            printf("REUSE ");
//            break;
//        case C_INVALID:
//            printf("INVALID ");
//            break;
//    }
    if (c->flag == C_VALID) {
        printf("{");
        for (j = 0; j < c->size; ++j) {
            printf("%d ", c->pids[j]);
        }
        printf("}\n");
    }
#endif
}

void print_cliques(void) {
    // printf("[%s]\n", __FUNCTION__);
#ifdef DO_PRINT
    int i;
    printf("-------------------------------------------------------\n");
    for (i = 0; i < NTHREADS; ++i) {
        print_clique(cliques + i);
    }
#endif
}

void merge_clique(struct clique *c1, struct clique *c2) {
    // printf("[%s]\n", __FUNCTION__);
    if (c1 && c2) {
#ifdef DO_PRINT
        printf("Merging: ");
        print_clique(c1);
        print_clique(c2);
        printf("\n");
#endif
        memcpy(c1->pids + c1->size, c2->pids, sizeof(int) * c2->size);
        c1->size = c1->size + c2->size;
        c1->flag = C_REUSE;
        c2->flag = C_INVALID;
        cliques_size -= 2;
    } else {
        printf("merge_clique: NULL pointer\n");
    }
}

struct clique *get_first_valid(void) {
    // printf("[%s]\n", __FUNCTION__);
    struct clique *ret = cliques;
    while (ret->flag != C_VALID) {
        ret++;
        if (ret == cliques + NTHREADS) {
            printf("get_first_valid: NO valid clique\n");
            return NULL;
        }
    }
    return ret;
}

struct clique *find_neighbor(struct clique *c1) {
    // printf("[%s]\n", __FUNCTION__);
    struct clique *c2, *temp = cliques;
    int distance = -1, temp_int;
    while (temp < cliques + NTHREADS) {
        if (temp != c1 && temp->flag == C_VALID) {
            temp_int = clique_distance(c1, temp);
            if (temp_int > distance) {
                distance = temp_int;
                c2 = temp;
            }
        }
        temp++;
    }
    return c2;
}

void reset_cliques(void) {
    // printf("[%s]\n", __FUNCTION__);
    struct clique *temp = cliques;
    while (temp < cliques + NTHREADS) {
        if (temp->flag == C_REUSE) {
            temp->flag = C_VALID;
            ++cliques_size;
        }
        temp++;
    }
}

void init_matrix(void) {
    int i, j;
    srand((unsigned) time(NULL));
    for (i = 0; i < NTHREADS; ++i) {
        for (j = 0; j < NTHREADS; ++j) {
            link_sched_comm[i][j] = rand() % 10000;
        }
    }
}

int main() {
    struct clique *c1, *c2;
#ifdef C_DEBUG
    clock_t start, stop;
#endif
    init_matrix();
#ifdef DO_PRINT
    link_sched_print_matrix(link_sched_comm);
#endif
    init_cliques();
#ifdef C_DEBUG
    print_cliques();
    start = clock();
#endif
    while (cliques_size > num_nodes) {
        while (cliques_size > 0) {
            c1 = get_first_valid();
            c2 = find_neighbor(c1);
            merge_clique(c1, c2);
        }
        reset_cliques();
#ifdef C_DEBUG
        print_cliques();
#endif
    }
#ifdef C_DEBUG
    stop = clock();
    printf("Time consumed: %f\n", (double) (stop - start) / CLK_TCK);
#endif
}