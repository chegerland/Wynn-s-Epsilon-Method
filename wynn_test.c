#include <stdio.h>
#include <math.h>

#include "wynn.h"


int main (int argc, char *argv[])
{
  size_t N = 7;
  double t[N];
  double sum_accel, err;

  gsl_sum_wynn_workspace * w = gsl_sum_wynn_alloc (N);

  // fill array of partial sums
  t[0] = 0;
  for (int n = 0; n < N; n++)
  {
      t[n] = t[n-1] + 4.0 * pow(-1, n)/(2*n+1);
  }

  gsl_sum_wynn_accel (t, N, 2, w, &sum_accel, &err);

  printf ("\nterm-by-term sum = % .16f\n", t[N-1]);

  printf ("exact value      = % .16f\n", M_PI);
  printf ("accelerated sum  = % .16f\n", sum_accel);
  printf ("estimated error  = % .3e\n", err);
  printf ("actual error     = % .3e\n", fabs(sum_accel - M_PI));


  printf ("\n Printing epsilon table \n");
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N-1; j++)
    {
      printf("%.3e, ", w->eps_table[i][j]);
    }
    printf("%.3e\n", w->eps_table[i][N-1]);
  }


  gsl_sum_wynn_free (w);

    return 0;
};
