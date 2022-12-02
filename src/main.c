#include "../include/philo.h"
// structure avec les threads




/* Fonction pour le thread du magasin. */

void *fn_manager (void *p_data)
{
   t_data *data = (t_data *) p_data;
   while (1)
   {
	/* Debut de la zone protegee. */
      pthread_mutex_lock(&data->mutex_stock);
      pthread_cond_wait(&data->cond_stock, &data->mutex_stock);

      data->stock = INITIAL_STOCK;
      printf ("Remplissage du stock de %d articles !\n", data->stock);

	   /* Fin de la zone protegee. */
      pthread_cond_signal(&data->cond_philo);
      pthread_mutex_unlock(&data->mutex_stock);
   }

   return NULL;
}


/* Fonction pour les threads des clients. */

void *fn_philo (void *p_data)
{
   t_data *data = (t_data *) p_data;
   //int nb = (int) p_data;

   while (1)
   {
      int val = get_random(6);

      time_t time = get_time_in_ms();


      /* Debut de la zone protegee. */
      pthread_mutex_lock(&data->mutex_stock);
      sleep(get_random(3));

      if (val > data->stock)
      {
         pthread_cond_signal(&data->cond_stock);
         pthread_cond_wait(&data->cond_philo, &data->mutex_stock);
      }

      data->stock = data->stock - val;
      printf("[%ld] philo %ld prend %d du stock, reste %d en stock !\n", time - data->start_time, data->id_t,  val, data->stock);

      pthread_mutex_unlock(&data->mutex_stock);
      /* Fin de la zone protegee. */
   }

   return NULL;
}

void create_philo(t_data *data)
{

      //long i = data->id_t;
      int ret;
      /* Creation du thread du magasin. */
   printf ("Creation du thread du magasin !\n");
   ret = pthread_create (&data->thread_manager, NULL, fn_manager, (void *) data);

   /* Creation des threads des clients si celui du magasin a reussi. */
   if (!ret)
   {
      printf ("Creation des threads clients !\n");
      while(data->id_t <= NB_PHILO)
      {
         ret = pthread_create(&data->thread_philo[data->id_t], NULL, fn_philo, (void *) data);

         if (ret)
         {
            fprintf (stderr, "%s", strerror (ret));
         }
		 data->id_t++;
      }
   }
   else
   {
      fprintf (stderr, "%s", strerror (ret));
   }


   /* Attente de la fin des threads. */
   data->id_t = 1;
   while(data->id_t <= NB_PHILO)
   {
      pthread_join(data->thread_philo[data->id_t], NULL);
	   data->id_t++;
   }
   pthread_join(data->thread_manager, NULL);

}




int main (void)
{

   t_data data;

   init_arg(&data);

   create_philo(&data);

   return EXIT_SUCCESS;
}
