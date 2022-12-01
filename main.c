#include "../include/philo.h"
#include<pthread.h>
// structure avec les threads
typedef struct store_t
{
   int stock;

   pthread_t thread_store;
   pthread_t thread_clients [NB_CLIENTS];

   pthread_mutex_t mutex_stock;


   pthread_cond_t cond_stock;
   pthread_cond_t cond_clients;
} store_t;



store_t store =
{
   .stock = INITIAL_STOCK,
   .mutex_stock = PTHREAD_MUTEX_INITIALIZER,
   .cond_stock = PTHREAD_COND_INITIALIZER,
   .cond_clients = PTHREAD_COND_INITIALIZER,
};



/* Fonction pour le thread du magasin. */

void * fn_store (void * p_data)
{
   while (1)
   {
	/* Debut de la zone protegee. */
      pthread_mutex_lock (&store.mutex_stock);
      pthread_cond_wait (&store.cond_stock, &store.mutex_stock);
      if (store.stock <= 0)
      {
         store.stock = INITIAL_STOCK;
         printf ("Remplissage du stock de %d articles !\n", store.stock);
      }
	   /* Fin de la zone protegee. */
      pthread_cond_signal (&store.cond_clients);
      pthread_mutex_unlock (&store.mutex_stock);
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


      sleep(get_random(3));

      /* Debut de la zone protegee. */
      pthread_mutex_lock (& store.mutex_stock);

      if (val > store.stock)
      {
         pthread_cond_signal (& store.cond_stock);
         pthread_cond_wait (& store.cond_clients, & store.mutex_stock);
      }

      store.stock = store.stock - val;
      printf (
         "Client %d prend %d du stock, reste %d en stock !\n",
         nb, val, store.stock
      );

      pthread_mutex_unlock (&store.mutex_stock);
      /* Fin de la zone protegee. */
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
