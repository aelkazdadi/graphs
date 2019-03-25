#include "array.h"
#include "graph.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE {
  long unsigned int node;
  struct QUEUE *next;
  struct QUEUE *last;
} queue;

void add(queue *q, long unsigned int node) {
  if (q->last) {
    queue *last = malloc(sizeof(queue));
    last->next = NULL;
    last->node = node;
    last->last = last;

    q->last->next = last;
    q->last = last;
  } else {
    q->node = node;
    q->next = NULL;
    q->last = q;
  }
}

long unsigned int pop(queue *q) {
  long unsigned int out;
  out = q->node;
  if (q->next) {
    queue *next = q->next;
    q->node = next->node;
    q->next = next->next;
    free(next);
  } else {
    q->next = NULL;
    q->last = NULL;
  }
  return out;
}

void dispQueue(queue *q) {
  if (q->last) {
    printf("%lu ", q->node);
    if (q->next) {
      dispQueue(q->next);
    }
  }
}

Array connectedComponents(adjacencyArray *g) {
  Array out;
  out.n = g->n;
  long unsigned int *components = malloc(g->n * sizeof(long unsigned int));
  for (long unsigned int i = 0; i < g->n; ++i) {
    components[i] = -1lu;
  }

  long unsigned int componentIndex = -1lu;
  long unsigned int i = 0;
  while (1) {
    ++componentIndex;
    while (i < g->n && components[i] != -1lu)
      ++i;

    if (i == g->n)
      break;
    components[i] = componentIndex;

    queue list;
    list.node = i;
    list.next = NULL;
    list.last = &list;

    while (list.last != NULL) {
      long unsigned int s = pop(&list);
      for (long unsigned int j = g->cd[s]; j < g->cd[s + 1]; ++j) {
        if (components[g->adj[j]] == -1) {
          add(&list, g->adj[j]);
          components[g->adj[j]] = componentIndex;
        }
      }
    }
  }
  out.array = components;
  return out;
}

Array componentSize(Array components) {
  Array sizes;
  long unsigned int m = -1lu;
  long unsigned int M = 0;
  for (unsigned long int i = 0; i < components.n; ++i) {
    unsigned long int k = components.array[i];
    m = (m < k) ? m : k;
    M = (M > k) ? M : k;
  }
  printf("%lu connected components\n", M);
  sizes.n = M + 1;
  sizes.array = calloc(sizes.n, sizeof(long unsigned int));

  for (unsigned long int i = 0; i < components.n; ++i) {
    ++(sizes.array[components.array[i]]);
  }

  return sizes;
}

int main(int argc, char **argv) {
  adjacencyArray *g = readAdjacencyArray(argv[1]);
  Array connectedComps = connectedComponents(g);
  freeAdjacencyArray(g);

  int h = 10;
  printf("Head of component labels\n");
  for (long unsigned int i = 0; (i < h) && (i < connectedComps.n); ++i) {
    printf("%lu : %lu\n", i, connectedComps.array[i]);
  }
  printf("\n");

  Array sizes = componentSize(connectedComps);
  long unsigned max = 0;
  long unsigned maxIndex = 0;
  for (long unsigned i = 0; (i < sizes.n); ++i) {
    if (sizes.array[i] > max) {
      maxIndex = i;
      max = sizes.array[i];
    }
  }
  printf("Largest connected component contains %Lf%% of the nodes\n",
         100 * ((long double)max) / connectedComps.n);
}
