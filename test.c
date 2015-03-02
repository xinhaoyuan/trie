#include "trie_array.c"
#include <stdio.h>
#include <string.h>
#include <assert.h>

const char *strings[] = {
    "def",
    "abeg",
    "abc",
};

void *values[3];

static void print_cursor(trie_cursor_s *c) {
    printf("cursor (%d, %d, %d)\n", c->level, c->pos, c->idx);
}

int main(void) {
    trie_s ta;
    trie_cursor_s c;

    trie_create(&ta, strings, values, 3);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'x') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'a') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'x') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'c') == 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'd') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'g') == 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'a') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'a') > 0);
    assert(trie_traverse(&ta, &c, 'b') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'h') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'd') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'd') < 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'd') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'f') == 0);

    trie_traverse_init(&ta, &c);
    assert(trie_traverse(&ta, &c, 'd') > 0);
    assert(trie_traverse(&ta, &c, 'e') > 0);
    assert(trie_traverse(&ta, &c, 'g') < 0);

    return 0;
}
