#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

const char *delim = " \t\r\n";
struct vertex* root = NULL;

struct edge {
	struct vertex* p_dest;
	struct edge* next;

	struct edge* pair;
};

struct vertex {
	int self;
	
	struct vertex* next;
	int deg;

	struct edge* edge_head;
};

struct vertex* search_vertex(struct vertex** p_root, int target) {
	struct vertex* cur = *p_root;
	while(cur != NULL) {
		if (cur->self == target)
			return cur;
		cur = cur->next;
	}
	return NULL;
}

void add_vertex(struct vertex** p_root, int num) {
	while(*p_root != NULL) {
		if ((**p_root).self == num)
			return;
		p_root = &((*p_root)->next);
	}
	*p_root = (struct vertex*)calloc(1, sizeof(struct vertex));
	struct vertex* cur = *p_root;
	cur->self = num;
}

void remove_vertex(struct vertex** p_root, int num) {
	while(*p_root != NULL) {
		if ((**p_root).self == num) {
			*p_root = (*p_root)->next;
			return;
		}
		p_root = &((*p_root)->next);
	}
}

struct edge* add_edge(struct vertex** p_root, int src, int dest) {
	struct vertex* a = search_vertex(p_root, src);
	struct vertex* b = search_vertex(p_root, dest);
	if (a == NULL || b == NULL)
		printf("vertex doesn't exist");
	struct edge** cur = &(a->edge_head);
	while(*cur != NULL) {
		cur = &((*cur)->next);
	}
	*cur = (struct edge*)calloc(1, sizeof(struct edge));
	(*cur)->p_dest = b;
	a->deg++;
	return *cur;
}

void remove_selfloop(struct vertex* a, struct vertex* b) {
	struct edge** cur = NULL;

	cur = &(b->edge_head);
	while (*cur != NULL) {
		(*cur)->pair->p_dest = a;
		cur = &((*cur)->next);
	}

	cur = &(b->edge_head);
	while (*cur != NULL) {
		if ((*cur)->p_dest == a || (*cur)->p_dest == b) {
			*cur = (*cur)->next;
			b->deg--;
		}
		else 
			cur = &((*cur)->next);
	}
	cur = &(a->edge_head);
	while (*cur != NULL) {
		if ((*cur)->p_dest == b || (*cur)->p_dest == a) {
			*cur = (*cur)->next;
			a->deg--;
		}
		else 
			cur = &((*cur)->next);
	}
	
}

void concat_edge(struct vertex* a, struct vertex* b) {
	struct edge** cur = NULL;
	cur = &(a->edge_head);
	while(*cur != NULL) {
		cur = &((*cur)->next);
	}
	*cur = b->edge_head;
	a->deg += b->deg;
}

void merge_vertices(struct vertex** p_root, struct vertex* a, struct vertex* b) {
	if (a == NULL || b == NULL)
		printf("vertex doesn't exist");
	remove_selfloop(a, b);	
	concat_edge(a, b);
	remove_vertex(p_root, b->self);	
}

void print_graph(struct vertex** p_root) {
	while(*p_root != NULL) {
		printf("%d\n", (*p_root)->self);
		struct edge** cur = NULL;
		cur = &((*p_root)->edge_head);
		while(*cur != NULL) {
			printf("%d - %d\n", (*p_root)->self, (*cur)->p_dest->self);
			cur = &((*cur)->next);
		}
		p_root = &((*p_root)->next);
	}
}

struct vertex* get_vertex(struct vertex** p_root, int vertex_idx) {
	while(vertex_idx--) {
		p_root = &((*p_root)->next);
	}
	return *p_root;
}

struct edge* get_edge(struct vertex* s, int edge_idx) {
	struct edge* cur = s->edge_head;
	while(edge_idx--) {
		cur = cur->next;
	}
	return cur;
}

void add_biedge(int a_idx, int b_idx) {
	struct edge* a_edge = add_edge(&root, a_idx, b_idx);
	struct edge* b_edge = add_edge(&root, b_idx, a_idx);
	a_edge->pair = b_edge;
	b_edge->pair = a_edge;
}

void compute_minimum_cut(struct vertex** p_root, int vertex_cnt) {
	struct vertex *a, *b;
	struct edge* e;
	srand((unsigned)time(NULL));

	while(vertex_cnt != 2) {
		do {
			int a_idx = rand() % vertex_cnt;
			a = get_vertex(p_root, a_idx);
		} while(a->deg == 0);

		int edge_idx = rand() % a->deg;
		e = get_edge(a, edge_idx);

		b = e->p_dest;

		merge_vertices(p_root, a, b);
		vertex_cnt--;
	}
	struct edge** cur = NULL;
	int cnt = 0;
	cur = &(a->edge_head);
	while(*cur != NULL) {
		cur = &((*cur)->next);
		cnt++;
	}
	printf("%d\n", a->deg / 2);
}

int main(void) {
	char buffer[1010];
	FILE *p_file;
	p_file = fopen("hw4.data", "r");
	int vertex_cnt = 0;

	while(fgets(buffer, 1000, p_file) != NULL) {
		vertex_cnt++;
		int s_vertex = 0,  e_vertex = 0;
		char *token;
		token = strtok(buffer, delim);
		sscanf(token, "%d", &s_vertex);
		add_vertex(&root, s_vertex);

		token = strtok(NULL, delim);
		while(token != NULL) {
			sscanf(token, "%d", &e_vertex);
			add_vertex(&root, e_vertex);
			add_biedge(s_vertex, e_vertex);	
			token = strtok(NULL, delim);
		}
	}
	compute_minimum_cut(&root, vertex_cnt);
}
