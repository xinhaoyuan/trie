#ifndef __TRIE_H__
#define __TRIE_H__

struct trie_s;
struct trie_cursor_s;

void ta_create(struct trie_s *ta, const char **strings, unsigned size);
void ta_traverse_init(struct trie_s *ta, struct trie_cursor_s *c);
int  ta_traverse(struct trie_s *ta, struct trie_cursor_s *c, char ch);

#endif
