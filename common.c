#include <stdlib.h>
#include "common.h"


Vector createVector(int len)
{
  Vector result = (Vector)malloc(sizeof(vector_t));
  result->data = malloc(len*sizeof(double));
  result->length = len;

  return result;
}

void freeVector(Vector vec)
{
  free(vec->data);
  free(vec);
}
