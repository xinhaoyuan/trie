#include "trie.h"
#include <stdlib.h>
#include <string.h>

typedef struct trie_s {
    unsigned     size;
    const char **strings;
    void       **values;
    unsigned    *weight;
    unsigned    *cp;
} trie_s;

typedef struct trie_cursor_s {
    unsigned level;
    /* next string position */
    unsigned pos;
    unsigned idx;
} trie_cursor_s;

void ta_create(trie_s *ta, const char **strings, void **values, unsigned size) {
    unsigned *weight   = malloc(sizeof(unsigned) * size);

    ta->size    = size;
    ta->strings = strings;
    ta->values  = values;

    /* use O(n^2) sorting */
    for (unsigned i = 0; i < size; ++ i) {
        weight[i] = 1;
    }

    for (unsigned i = 0; i < size - 1; ++ i) {
        unsigned min_idx = i;
        for (unsigned j = i + 1; j < size; ++ j) {
            if (strcmp(strings[j],
                       strings[min_idx]) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            const char *t = strings[i];
            strings[i] = strings[min_idx];
            strings[min_idx] = t;
            void *tt = values[i];
            values[i] = values[min_idx];
            values[min_idx] = tt;
        }
    }

    /* compute weight */
    for (unsigned i = 2; i < size; i <<= 1)
        for (unsigned j = 0; j < size; j += i)
            ++ weight[j];

    unsigned sum = 0;
    for (unsigned i = 0; i < size; ++ i) {
        unsigned o = sum;
        sum += weight[i];
        weight[i] = o;
    }

    unsigned *cp       = malloc(sizeof(unsigned) * sum);
    
    /* compute common prefix for base level */
    for (unsigned i = 0; i < size - 1; ++ i) {
        unsigned _cp = 0;
        while (strings[i][_cp] == strings[i + 1][_cp])
            ++ _cp;
        cp[weight[i]] = _cp;
    }
    cp[weight[size - 1]] = 0;

    unsigned l = 0;
    for (unsigned i = 2; i < size; i <<= 1) {
        ++ l;
        for (unsigned j = 0; j < size; j += i) {
            cp[weight[j] + l] = cp[weight[j] + l - 1];
            unsigned nx = j + (i >> 1);
            if (nx >= size) break;
            if (cp[weight[j] + l] > cp[weight[nx] + l - 1])
                cp[weight[j] + l] = cp[weight[nx] + l - 1];
        }
    }
    
    ta->values  = values;
    ta->weight  = weight;
    ta->cp      = cp;
}

void ta_traverse_init(trie_s *ta, trie_cursor_s *c) {
    c->level = ta->size > 1 ? ta->weight[1] - 1 : 0;
    c->pos = 0;
    c->idx = 0;
}

int ta_traverse(trie_s *ta, trie_cursor_s *c, char ch) {
    char _ch = ta->strings[c->idx][c->pos];
    if (_ch == ch) {
        ++ c->pos;
        return ta->strings[c->idx][c->pos];
    } else if (_ch < ch) {
        while (1) {
            /* need to move right-ward */
            /* failed if cannot move further */
            if (c->idx == ta->size - 1) return -1;

            unsigned nx = c->idx + (1 << c->level);
            if (nx >= ta->size) nx = ta->size - 1;
            
            if (ta->cp[ta->weight[c->idx] + c->level] < c->pos) {
                /* imply new_string is bigger */
                if (c->level == 0)
                    return -1;
                else -- c->level;
            } else {
                /* test next node in the level */
                char nx_ch = ta->strings[nx][c->pos];
                if (nx_ch == ch) {
                    c->idx = nx;
                    ++ c->pos;
                    return ta->strings[c->idx][c->pos];
                } else if (nx_ch < ch) {
                    c->idx = nx;
                } else {
                    if (c->level == 0)
                        return -1;
                    else -- c->level;
                }
            }
        }
    } else {
        while (1) {
            /* need to move left-ward */
            /* failed if cannot move further */
            if (c->idx == 0) return -1;

            unsigned nx = c->idx - (1 << c->level);
            
            if (ta->cp[ta->weight[nx] + c->level] < c->pos) {
                /* imply new_string is smaller */
                if (c->level == 0)
                    return -1;
                else -- c->level;
            } else {
                /* test next node in the level */
                char nx_ch = ta->strings[nx][c->pos];
                if (nx_ch == ch) {
                    c->idx = nx;
                    ++ c->pos;
                    return ta->strings[c->idx][c->pos];
                } else if (nx_ch > ch) {
                    c->idx = nx;
                } else {
                    if (c->level == 0)
                        return -1;
                    else -- c->level;
                }
            }
        }
    }
}

void *ta_get_value(struct trie_s *ta, struct trie_cursor_s *c) {
    return ta->values[c->idx];
}

void ta_destroy(trie_s *ta) {
    free(ta->weight);
    free(ta->cp);
}
