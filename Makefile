test: test.c trie.h trie_array.c
	${CC} -o $@ test.c -O0 -g
