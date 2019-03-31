#include "array.h"
#include "graph.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QUEUE {
  fixedInt node;
  struct QUEUE *next;
  struct QUEUE *last;
} queue;

void add(queue *q, fixedInt node) {
  if (q->last) {
    queue *last = malloc(sizeof(queue));
    last->next = NULL;
    last->node = node;

    q->last->next = last;
    q->last = last;
  } else {
    q->node = node;
    q->next = NULL;
    q->last = q;
  }
}

fixedInt pop(queue *q) {
  fixedInt out = q->node;
  if (q->next) {
    queue *next = q->next;
    q->node = next->node;
    q->next = next->next;
    free(next);
    if (q->next == NULL) {
      q->last = q;
    }
  } else {
    q->next = NULL;
    q->last = NULL;
  }
  return out;
}

void dispQueue(queue *q) {
  if (q->last) {
    printf("%u ", q->node);
    if (q->next) {
      dispQueue(q->next);
    }
  }
}

Array connectedComponents(adjacencyArray *g) {
  Array out;
  out.n = g->n;
  fixedInt *components = malloc(g->n * sizeof(fixedInt));
  for (fixedInt i = 0; i < g->n; ++i) {
    components[i] = -1u;
  }

  fixedInt componentIndex = -1u;
  fixedInt i = 0;
  while (1) {
    ++componentIndex;
    while (i < g->n && components[i] != -1u)
      ++i;

    if (i == g->n)
      break;
    components[i] = componentIndex;

    queue list;
    list.node = i;
    list.next = NULL;
    list.last = &list;

    while (list.last != NULL) {
      fixedInt s = pop(&list);
      for (fixedInt j = g->cd[s]; j < g->cd[s + 1]; ++j) {
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
  fixedInt m = -1u;
  fixedInt M = 0;
  for (fixedInt i = 0; i < components.n; ++i) {
    fixedInt k = components.array[i];
    m = (m < k) ? m : k;
    M = (M > k) ? M : k;
  }
  printf("%u connected components\n", M);
  sizes.n = M + 1;
  sizes.array = calloc(sizes.n, sizeof(fixedInt));

  for (fixedInt i = 0; i < components.n; ++i) {
    ++(sizes.array[components.array[i]]);
  }

  return sizes;
}

fixedInt getDiameter(adjacencyArray *g, fixedInt start) {
  fixedInt diam = 0;
  fixedInt old_diam;

  unsigned int *visited = malloc(g->n * sizeof(unsigned int));
  unsigned int c = 3;
  do {
    --c;
    old_diam = diam;

    queue list;
    list.node = start;
    list.next = NULL;
    list.last = &list;

    diam = 0;
    fixedInt diamCounter = 1;
    fixedInt nextDiamCounter = 0;

    fixedInt nodesReached = 0;

    for (fixedInt i = 0; i < g->n; ++i) {
      visited[i] = 0;
    }
    visited[start] = 1;

    while (list.last != NULL) {
      fixedInt s = pop(&list);
      start = s;
      ++nodesReached;

      for (fixedInt j = g->cd[s]; j < g->cd[s + 1]; ++j) {
        fixedInt v = g->adj[j];
        if (visited[v] == 0) {
          visited[v] = 1;
          add(&list, g->adj[j]);
          ++nextDiamCounter;
        }
      }

      --diamCounter;
      if (diamCounter == 0) {
        diamCounter = nextDiamCounter;
        if (nextDiamCounter != 0)
          ++diam;
        nextDiamCounter = 0;
      }
    }
  } while (diam != old_diam);
  printf("Diameter lower bound: %u\n", diam);
  return diam;
}

int main(int argc, char **argv) {
  adjacencyArray *g = readAdjacencyArray(argv[1]);
  Array connectedComps = connectedComponents(g);

  Array sizes = componentSize(connectedComps);
  fixedInt max = 0;
  fixedInt maxIndex = 0;

  for (fixedInt i = 0; (i < sizes.n); ++i) {
    if (sizes.array[i] > max) {
      maxIndex = i;
      max = sizes.array[i];
    }
  }
  printf("Largest connected component contains %Lf%% of the nodes\n",
         100 * ((long double)max) / connectedComps.n);

  fixedInt index;
  for (fixedInt i = 0; i < connectedComps.n; ++i) {
    if (connectedComps.array[i] == maxIndex) {
      index = i;
      break;
    }
  }
  free(connectedComps.array);
  free(sizes.array);

  fixedInt diameter = getDiameter(g, index);
  freeAdjacencyArray(g);
}
