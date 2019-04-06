#include "graph.h"
#include "timer.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int compare(const void* a, const void* b)
{
    double* double_a = (double*)a;
    double* double_b = (double*)b;

    // an easy expression for comparing
    return (double_a < double_b) - (double_a > double_b);
}

void dispVec(double* vec, fixedInt size)
{
    for (fixedInt i = 0; i < size; ++i)
    {
        printf("%.10e\n", vec[i]);
    }
}

double dist(double* vec1, double* vec2, fixedInt size)
{
    double out = 0.;
    for (fixedInt i = 0; i < size; ++i)
    {
        double diff = vec2[i] - vec1[i];
        out += diff * diff;
    }
    return sqrt(out);
}

void stateTransition(adjacencyArray* g, double alpha, double* vec, double* out)
{
    double alphaComplement = 1. - alpha;
    double sumDeadends = 0.;

    for (fixedInt i = 0; i < g->n; ++i)
    {
        out[i] = 0.;
    }

    for (fixedInt i = 0; i < g->n; ++i)
    {
        fixedInt degree = g->cd[i + 1] - g->cd[i];

        if (degree != 0)
        {
            double coeff = alphaComplement * vec[i] / degree;

            for (fixedInt j = g->cd[i]; j < g->cd[i + 1]; ++j)
            {
                out[g->adj[j]] += coeff;
            }
        }
        else
        {
            sumDeadends += vec[i];
        }
    }

    double reg = (alphaComplement * sumDeadends + alpha) / (g->n);
    double sum = 0.;
    for (fixedInt i = 0; i < g->n; ++i)
    {
        out[i] += reg;
        sum += out[i];
    }
    // normalize
    double shift = (1. - sum) / g->n;
    for (fixedInt i = 0; i < g->n; ++i)
    {
        out[i] += shift;
    }
}

void save_degrees(adjacencyArray* g, char* indeg_filename,
                  char* outdeg_filename)
{
    fixedInt* indeg_array = calloc(g->n, sizeof(fixedInt));

    for (fixedInt i = 0; i < g->n; ++i)
    {
        for (fixedInt j = g->cd[i]; j < g->cd[i + 1]; ++j)
        {
            ++indeg_array[g->adj[j]];
        }
    }
    FILE* outdeg_file = fopen(outdeg_filename, "w");
    FILE* indeg_file = fopen(indeg_filename, "w");

    for (fixedInt i = 0; i < g->n; ++i)
    {
        fprintf(indeg_file, "%u\n", indeg_array[i]);
        fprintf(outdeg_file, "%u\n", g->cd[i + 1] - g->cd[i]);
    }

    free(indeg_array);
    pclose(outdeg_file);
    pclose(indeg_file);
}

void save_array(double* array, fixedInt n, char* filename)
{
    FILE* file = fopen(filename, "w");
    for (fixedInt i = 0; i < n; ++i)
    {
        fprintf(file, "%.15f\n", array[i]);
    }
    pclose(file);
}

double* pagerank(adjacencyArray* g, double alpha)
{
    fixedInt n = g->n;
    fixedInt n_iter = 0;
    double eps = 1e-5;
    double* vec = malloc(n * sizeof(double));
    double* next = malloc(n * sizeof(double));

    // Generate a random positive vector and normalize it
    double sum = 0.;
    for (fixedInt i = 0; i < n; ++i)
    {
        next[i] = (double)rand() / RAND_MAX;
        sum += next[i];
    }
    double invSum = 1. / sum;

    for (fixedInt i = 0; i < n; ++i)
    {
        next[i] *= invSum;
    }

    double d;
    do
    {
        ++n_iter;
        for (unsigned int i = 0; i < n; ++i)
        {
            vec[i] = next[i];
        }
        stateTransition(g, alpha, vec, next);
        d = dist(vec, next, n);
    } while (d > eps);
    printf("%u iterations for convergence\n", n_iter);

    free(vec);
    return next;
}

void save_pagerank(adjacencyArray* g, double alpha, char* alpha_str,
                   char* dirname)
{
    char buffer[4096];
    snprintf(buffer, sizeof(buffer), "%s/%s.dat", dirname, alpha_str);
    double* vec = pagerank(g, alpha);
    save_array(vec, g->n, buffer);
    free(vec);
}

int main(int argc, char** argv)
{
    srand(0);
    adjacencyArray* g = readDirected(argv[1]);

    // Create directory if it doesn't exist
    struct stat st = {0};
    if (stat(argv[2], &st) == -1)
    {
        mkdir(argv[2], 0700);
    }

    save_pagerank(g, .15, "15", argv[2]);
    save_pagerank(g, .1, "10", argv[2]);
    save_pagerank(g, .2, "20", argv[2]);
    save_pagerank(g, .5, "50", argv[2]);
    save_pagerank(g, .9, "90", argv[2]);

    char indeg_filename[4096];
    char outdeg_filename[4096];

    snprintf(indeg_filename, sizeof(indeg_filename), "%s/indeg.dat", argv[2]);
    snprintf(outdeg_filename, sizeof(outdeg_filename), "%s/outdeg.dat",
             argv[2]);

    save_degrees(g, indeg_filename, outdeg_filename);

    freeAdjacencyArray(g);
}
