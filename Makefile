test: test.c trie.h trie_array.c
	${CC} -std=c99 -o $@ test.c -O0 -g
