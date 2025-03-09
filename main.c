#include <stdio.h>
#include <stdlib.h>

#define TRIE_SIZE 26

static char line[256];

typedef struct trie_node trie_node;

struct trie_node {
	trie_node *children[TRIE_SIZE];
	int terminal;
};

trie_node* trie_alloc(void) {
	trie_node *node = malloc(sizeof *node);
	if (node == NULL)
		return NULL;

	for (size_t i = 0; i < TRIE_SIZE; i++)
		node->children[i] = NULL;
	node->terminal = 0;

	return node;
}

size_t trie_index(char value) {
	return value - 'a';
}

/*
void trie_insert(trie_node **node, char *data, size_t size) {
	if (node == NULL || *node == NULL)
		return;

	for (size_t i = 0; i < size; i++) {
		size_t index = trie_index(data[i]);
		trie_node *child = (*node)->children[index];

		if (child == NULL) {
			cihld = trie_alloc();

			if (child == NULL) {
				trie_free(node);
				*node = NULL;
				return;
			}
		}

		*node = (*node)->children[index];
			
	}
}
*/

void trie_free(trie_node** node) {
	if (node == NULL || *node == NULL)
		return;

	// Dereferencing trie_node *node == NULL is defined
	for (size_t i = 0; i < TRIE_SIZE; i++)
		trie_free(&(*node)->children[i]);

	free(*node);
	*node = NULL;
}

size_t strlen(char* str) {
	size_t size = 0;
	while (str[size] != '\0')
		size++;
	return size;
}

int main(void) {

	trie_node *node = trie_alloc();	
	if (node == NULL) {
		fprintf(stderr, "Failed to create a trie_node\n");
		return 1;
	}

	trie_free(&node);

	FILE* fin = fopen("words_alpha.txt", "r");
	if (fin == NULL)
		return 1;
	
	size_t line_size = 0, max_line_size = 0;
	while(fgets(line, sizeof(line), fin)) {
		line_size = strlen(line);
		if (line_size > max_line_size)
			max_line_size = line_size;
	}

	printf("\nThe maximum line length is %zu\n", max_line_size);

	fclose(fin);

	return 0;
}
