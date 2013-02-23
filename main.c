#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "common.h"
#include <sys/time.h>

#ifdef HAVE_OPENMP
#include <omp.h>
#endif
double WallTime();

double WallTime ()
{
#ifdef HAVE_OPENMP
  return omp_get_wtime();
#else
  struct timeval tmpTime;
  gettimeofday(&tmpTime,NULL);
  return tmpTime.tv_sec + tmpTime.tv_usec/1.0e6;
#endif
}


double* powVector(int len){
    double* a = malloc(len*sizeof(double));
    int i;
    #pragma omp parallel for schedule(static)
    for(i=1; i<(len+1); i++){
            a[i-1] = (1.0/pow(i,2));
    }
    return a;
}
double doSum (Vector v){
    double sum;
    int i;
    #pragma omp parallel for schedule(static) reduction(+:sum)
    for(i=0; i<v->length; i++){
        sum = sum + v->data[i];
    }
    return sum;
}

int main(int argc, char** argv)
{
    double time = WallTime();
    double pi = 4*atan(1.0);
    double s = pow(pi,2)/6;
    int size_num;
    double sum;
    double e;
    int i;
    Vector numVector;
    for(i=4; i<15; i++){

        size_num = pow(2,i);
        numVector = createVector(size_num);
        numVector->data = powVector(size_num);

        sum = doSum(numVector);
        e = s-sum;
        printf("Error step - %d :: %lf \n",i, e );
    }
	
	printf("elapsed: %f\n", WallTime()-time);
    return 0;
}
