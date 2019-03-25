#include "array.h"
#include "graph.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

void dispVec(double *vec, long unsigned int size) {
  for (unsigned long int i = 0; i < size; ++i) {
    printf("%10e  ", vec[i]);
  }
  printf("\n");
}

void stateTransition(adjacencyArray *g, double alpha, double *vec,
                     double *out) {
  double alphaComplement = 1. - alpha;
  double sumDeadends = 0;

  for (long unsigned int i = 0; i < g->n; ++i) {
    out[i] = 0.;
  }

  for (long unsigned int i = 0; i < g->n; ++i) {
    long unsigned int degree = g->cd[i + 1] - g->cd[i];

    if (degree != 0) {
      double degreeInv = 1. / degree;

      for (long unsigned j = g->cd[i]; j < g->cd[i + 1]; ++j) {
        out[g->adj[j]] += alphaComplement * vec[i] * degreeInv;
      }
    } else {
      sumDeadends += vec[i];
    }
  }

  double reg = (alphaComplement * sumDeadends + alpha) / (g->n);
  double sum = 0.;
  for (long unsigned int i = 0; i < g->n; ++i) {
    out[i] += reg;
    sum += out[i];
  }
  // normalize
  double shift = (1. - sum) / g->n;
  for (long unsigned int i = 0; i < g->n; ++i) {
    out[i] += shift;
  }
}

int main(int argc, char **argv) {
  struct timespec clock[10];
  getTime(clock);
  adjacencyArray *g = readDirected(argv[1]);
  getTime(clock + 1);
  long unsigned int n = g->n;

  double alpha = 0.;
  double *vec = malloc(n * sizeof(double));
  double *next = malloc(n * sizeof(double));
  for (long unsigned int i = 0; i < n; ++i)
    vec[i] = 0.;
  vec[0] = 1.;

  dispVec(vec, 5);
  getTime(clock + 2);
  stateTransition(g, alpha, vec, next);
  getTime(clock + 3);
  dispVec(next, 5);

  dispTime(clock, 2);


  freeAdjacencyArray(g);
  free(vec);
  free(next);
}
