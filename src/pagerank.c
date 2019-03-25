#include "array.h"
#include "graph.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void dispVec(double *vec, long unsigned int size) {
  for (unsigned long int i = 0; i < size; ++i) {
    printf("%10e\n", vec[i]);
  }
}

double dist(double *vec1, double *vec2, long unsigned int size) {
  double out = 0.;
  for (unsigned long int i = 0; i < size; ++i) {
    double diff = vec2[i] - vec1[i];
    out += diff * diff;
  }
  return sqrt(out);
}


void stateTransition(adjacencyArray *g, double alpha, double *vec,
                     double *out) {
  double alphaComplement = 1. - alpha;
  double sumDeadends = 0.;

  for (long unsigned int i = 0; i < g->n; ++i) {
    out[i] = 0.;
  }

  for (long unsigned int i = 0; i < g->n; ++i) {
    long unsigned int degree = g->cd[i + 1] - g->cd[i];

    if (degree != 0) {
      double alphaCompDegreeInv = alphaComplement / degree;

      for (long unsigned j = g->cd[i]; j < g->cd[i + 1]; ++j) {
        out[g->adj[j]] += alphaCompDegreeInv * vec[i];
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
  printf("Sum before normalization: %f\n", sum);
  // normalize
  double shift = (1. - sum) / g->n;
  for (long unsigned int i = 0; i < g->n; ++i) {
    out[i] += shift;
  }
}

int main(int argc, char **argv) {
  srand(1);

  adjacencyArray *g = readDirected(argv[1]);
  long unsigned int n = g->n;

  double alpha = .15;
  double eps = 1e7;
  double *vec = malloc(n * sizeof(double));
  double *next = malloc(n * sizeof(double));

  // Generate a random positive vector and normalize it
  double sum = 0.;
  for (long unsigned int i = 0; i < n; ++i) {
    next[i] = (double)rand() / RAND_MAX;
    sum += next[i];
  }
  sum = 1 / sum;
  for (long unsigned int i = 0; i < n; ++i) {
    next[i] *= sum;
  }

  double d;
  do {
    for (unsigned int i = 0; i < n; ++i) {
      vec[i] = next[i];
    }
    dispVec(vec, 5);
    stateTransition(g, alpha, vec, next);
    d = dist(vec, next, n);
    printf("Difference : %10e\n", d);
  } while (d > eps);
  dispVec(next, 500);

  freeAdjacencyArray(g);
  free(vec);
  free(next);
}
