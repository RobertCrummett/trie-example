#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRIE_CHILDREN 26

static char line[256];

typedef struct trie_node trie_node;

struct trie_node {
	trie_node* child[TRIE_CHILDREN];
	int terminal;
};

trie_node* trie_node_malloc(void) {
	trie_node *node = malloc(sizeof *node);
	if (node == NULL)
		return NULL;

	node->terminal = 0;
	for (size_t i = 0; i < TRIE_CHILDREN; i++)
		node->child[i] = NULL;
	return node;
}

void trie_insert(trie_node *head, char *str) {
	if (head == NULL || str == NULL)
		return;

	for ( ; *str != '\0'; str++) {
		trie_node* child = head->child[(*str) - 'a'];

		if (child == NULL)
			child = trie_node_malloc();
		
		if (child == NULL)
			abort();

		head = child;
	}

	head->terminal++;
}

int main(void) {
	trie_node *head = trie_node_malloc();
	if (head == NULL)
		return 1;
	
	FILE* fin = fopen("words_alpha.txt", "r");
	if (fin == NULL)
		return 1;
	
	size_t line_size = 0, max_line_size = 0;
	while(fgets(line, sizeof(line), fin)) {
		line_size = strlen(line);
		if (line_size > max_line_size)
			max_line_size = line_size;
		trie_insert(head, line);
	}

	printf("\nThe maximum line length is %zu\n", max_line_size);

	fclose(fin);

	free(head);

	return 0;
}
