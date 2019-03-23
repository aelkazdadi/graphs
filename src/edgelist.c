/*
Maximilien Danisch
September 2017
http://bit.ly/danisch
maximilien.danisch@gmail.com

Info:
Feel free to use these lines as you wish. This program loads a graph in main
memory as a list of edges.

To compile:
"gcc edgelist.c -O9 -o edgelist".

To execute:
"./edgelist edgelist.txt".
"edgelist.txt" should contain the graph: one edge on each line (two unsigned
long (nodes' ID)) separated by a space. The prograph loads the graph in main
memory and then it terminates.

Note:
If the graph is directed (and weighted) with selfloops and you want to make it
undirected unweighted without selfloops, use the following linux command line.
awk '{if ($1<$2) print $1" "$2;else if ($2<$1) print $2" "$1}' net.txt | sort -n
-k1,2 -u > net2.txt

Performance:
Up to 500 million edges on my laptop with 8G of RAM:
Takes more or less 1.6G of RAM and 25 seconds (I have an SSD hardrive) for 100M
edges.
*/

#include <locale.h>
#include <stdio.h>
#include <time.h> //to estimate the runing time
#include "timer.h"
#include "graph.h"

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");

  struct timespec t1, t2;

  edgelist *g;

  printf("Reading edgelist from file %s\n", argv[1]);
  g = readedgelist(argv[1]);

  printf("Number of nodes: %lu\n", g->n);
  printf("Number of edges: %lu\n", g->e);

  free_edgelist(g);

  return 0;
}
