#include "../include/philo.h"

store_t store =
{
   .stock = INITIAL_STOCK,
   .mutex_stock = PTHREAD_MUTEX_INITIALIZER,
};



/* Fonction pour le thread du magasin. */

void * fn_store (void * p_data)
{
   while (1)
   {
	/* Debut de la zone protegee. */
      pthread_mutex_lock (& store.mutex_stock);
      if (store.stock <= 0)
      {
         store.stock = INITIAL_STOCK;
         printf ("Remplissage du stock de %d articles !\n", store.stock);
      }
	   /* Fin de la zone protegee. */
      pthread_mutex_unlock (& store.mutex_stock);
   }

   return NULL;
}


/* Fonction pour les threads des clients. */

void * fn_clients (void * p_data)
{
   int nb = (int) p_data;

   while (1)
   {
      int val = get_random (6);

	  /* Debut de la zone protegee. */
      pthread_mutex_lock (& store.mutex_stock);

      sleep(get_random (3));

      store.stock = store.stock - val;
      printf (
         "Client %d prend %d du stock, reste %d en stock !\n",
         nb, val, store.stock
      );
	   /* Fin de la zone protegee. */
      pthread_mutex_unlock (& store.mutex_stock);
   }

   return NULL;
}


int main (void)
{
   int i = 0;
   int ret = 0;


   /* Creation du thread du magasin. */
   printf ("Creation du thread du magasin !\n");
   ret = pthread_create (&store.thread_store, NULL, fn_store, NULL);

   /* Creation des threads des clients si celui du magasin a reussi. */
   if (! ret)
   {
      printf ("Creation des threads clients !\n");
      while(i < NB_CLIENTS)
      {
         ret = pthread_create (&store.thread_clients [i], NULL, fn_clients, (void *)(size_t) i);

         if (ret)
         {
            fprintf (stderr, "%s", strerror (ret));
         }
		 i++;
      }
   }
   else
   {
      fprintf (stderr, "%s", strerror (ret));
   }


   /* Attente de la fin des threads. */
   i = 0;
   while(i < NB_CLIENTS)
   {
      pthread_join (store.thread_clients [i], NULL);
	  i++;
   }
   pthread_join (store.thread_store, NULL);


   return EXIT_SUCCESS;
}
