#include <stdlib.h>

typedef struct
{
  double **eps_table;
}
gsl_sum_wynn_workspace;

gsl_sum_wynn_workspace *gsl_sum_wynn_alloc (size_t n);
void gsl_sum_wynn_free (gsl_sum_wynn_workspace * w);

int gsl_sum_wynn_accel (const double * array,
                        const size_t n, const size_t order,
                        gsl_sum_wynn_workspace  * w,
                        double * sum_accel, double * abserr);
