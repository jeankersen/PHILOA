#include "../include/philo.h"
// structure avec les threads




/* Fonction pour le thread du magasin. */

void *fn_store (void *p_data)
{
   t_store *store = (t_store *) p_data;
   while (1)
   {
	/* Debut de la zone protegee. */
      pthread_mutex_lock (&store->mutex_stock);
      pthread_cond_wait (&store->cond_stock, &store->mutex_stock);

      store->stock = INITIAL_STOCK;
      printf ("Remplissage du stock de %d articles !\n", store->stock);

	   /* Fin de la zone protegee. */
      pthread_cond_signal(&store->cond_clients);
      pthread_mutex_unlock(&store->mutex_stock);
   }

   return NULL;
}


/* Fonction pour les threads des clients. */

void *fn_clients (void *p_data)
{
   t_store *store = (t_store *) p_data;
   //int nb = (int) p_data;

   while (1)
   {
      int val = get_random(6);


      sleep(get_random(3));

      /* Debut de la zone protegee. */
      pthread_mutex_lock(&store->mutex_stock);

      if (val > store->stock)
      {
         pthread_cond_signal(&store->cond_stock);
         pthread_cond_wait(&store->cond_clients, &store->mutex_stock);
      }

      store->stock = store->stock - val;
      printf("Client d prend %d du stock, reste %d en stock !\n", val, store->stock);

      pthread_mutex_unlock(&store->mutex_stock);
      /* Fin de la zone protegee. */
   }

   return NULL;
}

void create_philo(t_store *store)
{

      //long i = store->id_t;
      int ret;
      /* Creation du thread du magasin. */
   printf ("Creation du thread du magasin !\n");
   ret = pthread_create (&store->thread_store, NULL, fn_store, (void *) store);

   /* Creation des threads des clients si celui du magasin a reussi. */
   if (!ret)
   {
      printf ("Creation des threads clients !\n");
      while(store->id_t < NB_CLIENTS)
      {
         ret = pthread_create(&store->thread_clients[store->id_t], NULL, fn_clients, (void *) store);

         if (ret)
         {
            fprintf (stderr, "%s", strerror (ret));
         }
		 store->id_t++;
      }
   }
   else
   {
      fprintf (stderr, "%s", strerror (ret));
   }


   /* Attente de la fin des threads. */
   store->id_t = 0;
   while(store->id_t < NB_CLIENTS)
   {
      pthread_join(store->thread_clients[store->id_t], NULL);
	  store->id_t++;
   }
   pthread_join(store->thread_store, NULL);

}




int main (void)
{

   t_store store;

   store.stock = INITIAL_STOCK;
   store.id_t = 0;
   pthread_mutex_init(&store.mutex_stock, 0);
	pthread_cond_init(&store.cond_stock, 0);
	pthread_cond_init(&store.cond_clients, 0);
   create_philo(&store);


   return EXIT_SUCCESS;
}
