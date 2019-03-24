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

long unsigned int *connectedComponents(adjacencyArray *g) {
  long unsigned int *components = malloc(g->n * sizeof(long unsigned int));
  for (long unsigned int i = 0; i < g->n; ++i) {
    components[i] = -1lu;
  }

  long unsigned int componentIndex = -1lu;
  while (1) {
    ++componentIndex;
    long unsigned int i;
    for (i = 0; i < g->n; ++i) {
      if (components[i] == -1lu)
        break;
    }
    if (i == g->n)
      break;
    components[i] = componentIndex;

    queue list;
    list.node = i;
    list.next = NULL;
    list.last = &list;

    while (list.last != NULL) {
      long unsigned int s = pop(&list);
      for (long long unsigned int j = g->cd[s]; j < g->cd[s + 1]; ++j) {
        if (components[g->adj[j]] == -1) {
          add(&list, g->adj[j]);
          components[g->adj[j]] = componentIndex;
        }
      }
    }
  }
  return components;
}

int main(int argc, char **argv) {
  adjacencyArray *g = readAdjacencyArray(argv[1]);
  long unsigned int *connctedComps = connectedComponents(g);
  int h = 100;
  for (int i = 0; i < h; ++i) {
    printf("%lu ", connctedComps[i]);
  }
  printf("\n");
}
