#include "graph.h"
#include "array.h"
#include "degree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareEdges(const void *a, const void *b) {
  edge *e1 = (edge *)a;
  edge *e2 = (edge *)b;
  return 2 * ((e1->s > e2->s) - (e1->s < e2->s)) +
         ((e1->t > e2->t) - (e1->t < e2->t));
}

void checkOrder(char *input) {
  FILE *file = fopen(input, "r");

  // Count comments
  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = -1;
  FILE *in = fopen(input, "r");

  do {
    getLineResult = getline(&line, &size, in);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  printf("%u comments found.\n", nComments);

  edge old;
  edge new;

  if (!(sscanf(line, "%lu%lu", &(old.s), &(old.t)) == 2))
    scanResult = fscanf(in, "%lu%lu", &(old.s), &(old.t));

  while (fscanf(in, "%lu%lu", &(new.s), &(new.t)) == 2) {
    if (compareEdges(&old, &new) >= 0)
      printf("%lu %lu\n", new.s, new.t);
  }
}

edgeList *readEdgeList(char *input) {
  FILE *file = fopen(input, "r");

  edgeList *g = malloc(sizeof(edgeList));

  if (fscanf(file, "%lu%lu", &(g->n), &(g->e)) != 2)
    return g;

  g->edges = malloc(g->e * sizeof(edge));

  long unsigned int i = 0;
  long unsigned int s = 0;
  long unsigned int t = 0;
  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    g->edges[i].s = s;
    g->edges[i].t = t;
    ++i;
  }

  fclose(file);

  return g;
}

adjacencyMatrix *readAdjacencyMatrix(char *input) {
  FILE *file = fopen(input, "r");
  adjacencyMatrix *g = malloc(sizeof(adjacencyMatrix));

  unsigned char bits[8];
  bits[0] = 1 << 0;
  bits[1] = 1 << 1;
  bits[2] = 1 << 2;
  bits[3] = 1 << 3;
  bits[4] = 1 << 4;
  bits[5] = 1 << 5;
  bits[6] = 1 << 6;
  bits[7] = 1 << 7;

  long unsigned s;
  long unsigned t;

  if (fscanf(file, "%lu%lu", &(g->n), &s) != 2)
    return g;
  g->rows = malloc((g->n) * sizeof(char *));

  long unsigned int nBlocks = ((g->n) >> 3) + 1;
  for (long unsigned int i = 0; i < (g->n); ++i) {
    g->rows[i] = malloc(sizeof(char) * nBlocks);
  }

  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    long unsigned int sBlock = s >> 3;
    long unsigned int tBlock = t >> 3;

    unsigned char sPos = s & 7;
    unsigned char tPos = t & 7;

    g->rows[s][tBlock] |= bits[tPos];
    g->rows[t][sBlock] |= bits[sPos];
  }

  fclose(file);
  return g;
}

adjacencyArray *readAdjacencyArray(char *input) {
  FILE *file = fopen(input, "r");
  adjacencyArray *g = malloc(sizeof(adjacencyArray));
  if (fscanf(file, "%lu%lu", &(g->n), &(g->e)) != 2)
    return g;
  g->cd = malloc((g->n + 1) * sizeof(unsigned long int));
  g->adj = malloc(2 * (g->e) * sizeof(unsigned long int));

  long unsigned s;
  long unsigned t;

  Array *degList = getDegrees(input);
  long unsigned int *degrees = degList->array;

  g->cd[0] = 0ll;
  for (long unsigned int i = 0; i < g->n; ++i) {
    g->cd[i + 1] = g->cd[i] + degrees[i];
    degrees[i] = 0;
  }

  while (fscanf(file, "%lu%lu", &s, &t) == 2) {
    g->adj[g->cd[s] + degrees[s]] = t;
    g->adj[g->cd[t] + degrees[t]] = s;
    ++degrees[s];
    ++degrees[t];
  }
  fclose(file);
  freeDegreeList(degList);
  return g;
}

adjacencyArray *readDirected(char *input) {
  FILE *file = fopen(input, "r");

  // Count lines in input file
  char command[10000];
  strcpy(command, "wc -l ");
  strcat(command, input);
  char buffer[128];
  FILE *fp;
  fp = popen(command, "r");
  long unsigned int nLines;
  if (fgets(buffer, 128, fp) != NULL) {
    nLines = strtoul(buffer, NULL, 10);
  }
  pclose(fp);

  // Count comments
  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = -1;
  FILE *in = fopen(input, "r");

  do {
    getLineResult = getline(&line, &size, in);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  printf("%u comments found.\n", nComments);

  adjacencyArray *g = malloc(sizeof(adjacencyArray));
  g->n = 0;
  g->e = 0;
  g->adj = malloc((nLines - nComments - 1) * sizeof(long unsigned int));

  // We assume there are more nodes than edges, which is valid in the case
  // of the wikipedia dataset.
  g->cd = malloc((nLines - nComments - 1) * sizeof(long unsigned int));
  g->cd[0] = 0;

  long unsigned s, t = 0;
  long unsigned int currentNode = 0;
  long unsigned int cumDegree = 0;

  while (fscanf(in, "%lu%lu", &s, &t) == 2) {
    while (currentNode < s) {
      g->cd[++currentNode] = cumDegree;
    }
    g->n = max3(g->n, s, t);
    g->adj[cumDegree] = t;
    ++cumDegree;
    ++g->e;
  }
  ++g->n;
  while (currentNode < g->n) {
    g->cd[++currentNode] = cumDegree;
  }
  g->adj = realloc(g->adj, g->e * sizeof(long unsigned int));
  g->cd = realloc(g->cd, (g->n + 1) * sizeof(long unsigned int));

  return g;
}

void freeAdjacencyMatrix(adjacencyMatrix *g) {
  for (long unsigned int i = 0; i < g->n; ++i) {
    free(g->rows[i]);
  }
  free(g->rows);
  free(g);
}

void freeAdjacencyArray(adjacencyArray *g) {
  free(g->adj);
  free(g->cd);
  free(g);
}

void freeEdgelist(edgeList *g) {
  free(g->edges);
  free(g);
}
