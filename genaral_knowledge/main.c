#include <stdio.h>
#include "inc/calculate.h"
#include "inc/mymath.h"

void main()
{
    calculate();
    int a= 7, b=10;
    printf ("%d * %d = %ld\n",a,b,multiple(a,b));
}