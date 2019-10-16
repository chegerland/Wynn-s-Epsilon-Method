#include <gsl/gsl_errno.h>
#include <string.h>
#include <math.h>

#include "wynn.h"

gsl_sum_wynn_workspace *gsl_sum_wynn_alloc (size_t n)
{
  gsl_sum_wynn_workspace * w;

  if (n == 0)
  {
    GSL_ERROR_VAL ("length n must be positive integer", GSL_EDOM, 0);
  }

  w = (gsl_sum_wynn_workspace *) malloc(sizeof(gsl_sum_wynn_workspace));

  if (w == NULL)
  {
    GSL_ERROR_VAL ("failed to allocate struct", GSL_ENOMEM, 0);
  }

  w->eps_table = (double **) malloc(n * sizeof (double));
  for (int i = 0; i < n; i++)
  {
    w->eps_table[i] = malloc(n * sizeof(double));
  };

  if (w->eps_table == NULL)
  {
    free(w->eps_table);
    free(w) ; /* error in constructor, prevent memory leak */

    GSL_ERROR_VAL ("failed to allocate space for eps_table", GSL_ENOMEM, 0);
  }

  return w;
}

void gsl_sum_wynn_free (gsl_sum_wynn_workspace * w)
{
  free (w->eps_table);
  free (w);
}

int gsl_sum_wynn_accel (const double * array,
                        const size_t n, const size_t order,
                        gsl_sum_wynn_workspace  * w,
                        double * sum_accel, double * abserr)
{
    // check if enough sum terms are given
    if ( n < 2*order + 3)
    {
       GSL_ERROR_VAL ("Not enough terms for this order!", GSL_EDOM, 0);
    };

    // initialize epsilon table
    for (int i = 0; i < n; i++)
    {
        w->eps_table[i][1] = array[i];
    };

    // fill epsilon table
    for (int i = 1; i < n; i++)
    {
        for (int j = 2; j <= i+1; j++)
        {
            w->eps_table[i][j] = w->eps_table[i-1][j-2] + 1.0/(w->eps_table[i][j-1] - w->eps_table[i-1][j-1]);
        };
    };

    // return S^order
    * sum_accel = w->eps_table[n-1][2*order+1];

    // error is calculated with last two iterations of same order
    * abserr = fabs(w->eps_table[n-2][2*order+1] - w->eps_table[n-3][2*order+1]);

    return GSL_SUCCESS;
};
