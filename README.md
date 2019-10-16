# Wynn-s-Epsilon-Method
This is an implementation of Wynn's epsilon algorithm as described in [1].
I wrote it in close similarity to the GSL's implementation of the Levin transform in [gsl_sum.h](https://github.com/ampl/gsl/tree/master/sum).
Unfortunately I did not find a good reference that talks about a good estimation of the rounding error, so in this implementation it is calculated as the difference between the last two terms in the respective Shanks transform.

An example of the usage is given in `wynn_test.c`.


### References
[1] P.R. Graves-Morris, D.E. Roberts, A. Salam,
The epsilon algorithm and related topics,
Journal of Computational and Applied Mathematics,
Volume 122, Issues 1–2,
2000,
Pages 51-80,
ISSN 0377-0427,
https://doi.org/10.1016/S0377-0427(00)00355-1.
