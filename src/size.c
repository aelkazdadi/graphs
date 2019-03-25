#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long unsigned int getSize(char *input) {
  FILE *file = fopen(input, "r");
  char *line = NULL;
  size_t size = 0;
  ssize_t getLineResult;
  int scanResult;

  unsigned int nComments = 0;
  long unsigned int nEdges = 0;

  if (file == NULL)
    return 0;

  do {
    getLineResult = getline(&line, &size, file);
    ++nComments;
  } while (getLineResult > 0 && line[0] == '#');
  --nComments;

  unsigned long s, t = 0;

  scanResult = sscanf(line, "%lu%lu", &s, &t);
  while (scanResult == 2) {
    ++nEdges;
    scanResult = fscanf(file, "%lu%lu", &s, &t);
  }
  fclose(file);

  return nEdges;
}

int main(int argc, char **argv) {
  setlocale(LC_ALL, "");
  printf("%lu edges.\n", getSize(argv[1]));
}
