#include "array.h"
#include "graph.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void dispVec(double *vec, fixedInt size) {
  for (fixedInt i = 0; i < size; ++i) {
    printf("%.10e\n", vec[i]);
  }
}

double dist(double *vec1, double *vec2, fixedInt size) {
  double out = 0.;
  for (fixedInt i = 0; i < size; ++i) {
    double diff = vec2[i] - vec1[i];
    out += diff * diff;
  }
  return sqrt(out);
}

void stateTransition(adjacencyArray *g, double alpha, double *vec,
                     double *out) {

  double alphaComplement = 1. - alpha;
  double sumDeadends = 0.;

  for (fixedInt i = 0; i < g->n; ++i) {
    out[i] = 0.;
  }

  for (fixedInt i = 0; i < g->n; ++i) {
    fixedInt degree = g->cd[i + 1] - g->cd[i];

    if (degree != 0) {
      double coeff = alphaComplement * vec[i] / degree;

      for (fixedInt j = g->cd[i]; j < g->cd[i + 1]; ++j) {
        out[g->adj[j]] += coeff;
      }
    } else {
      sumDeadends += vec[i];
    }
  }

  double reg = (alphaComplement * sumDeadends + alpha) / (g->n);
  double sum = 0.;
  for (fixedInt i = 0; i < g->n; ++i) {
    out[i] += reg;
    sum += out[i];
  }
  printf("\nVector sum - 1 : %.10e\n", sum - 1.);
  // normalize
  double shift = (1. - sum) / g->n;
  for (fixedInt i = 0; i < g->n; ++i) {
    out[i] += shift;
  }
}

int main(int argc, char **argv) {
  srand(1);

  adjacencyArray *g = readDirected(argv[1]);
  fixedInt n = g->n;

  double alpha = .15;
  double eps = 1e-5;
  double *vec = malloc(n * sizeof(double));
  double *next = malloc(n * sizeof(double));

  // Generate a random positive vector and normalize it
  double sum = 0.;
  for (fixedInt i = 0; i < n; ++i) {
    next[i] = (double)rand() / RAND_MAX;
    sum += next[i];
  }
  double invSum = 1. / sum;

  for (fixedInt i = 0; i < n; ++i) {
    next[i] *= invSum;
  }

  double d;
  do {
    for (unsigned int i = 0; i < n; ++i) {
      vec[i] = next[i];
    }
    stateTransition(g, alpha, vec, next);
    d = dist(vec, next, n);
    printf("Difference : %.10e\n", d);
  } while (d > eps);
  dispVec(next, 25);

  freeAdjacencyArray(g);
  free(vec);
  free(next);
}
