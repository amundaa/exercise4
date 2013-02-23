typedef struct {
  double* data;
  int length;
} vector_t;

typedef vector_t* Vector;

Vector createVector(int len);

void freeVector(Vector vec);
