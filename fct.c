#include "../include/philo.h"


/* Fonction pour tirer un nombre au sort entre 0 et max. */

int get_random (int max)
{
   double val;

   val = (double) max * rand ();
   val = val / (RAND_MAX + 1.0);

   return ((int) val);
}
