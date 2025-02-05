#include <stdbool.h>

#include <stdio.h>

#include <string.h>




#define ML 40




struct Movie {

   int movie_id;

   char title[ML];

   char genre[ML];

   int year_released;

   bool is_available;

   int number_rents;

};




struct Client {

   int client_id;

   char name[ML];

   int age;

   int number_rents;

};








void AddMovie(struct Movie *movie, struct Movie movies[], int *num_movies) {

   printf("Enter the movie ID: ");

   scanf("%d", &movie->movie_id);




   printf("Enter the movie title: ");

   scanf("%s", movie->title);




   printf("Enter the movie genre: ");

   scanf("%s", movie->genre);




   printf("Enter the year released: ");

   scanf("%d", &movie->year_released);




   movie->is_available = true;

   movie->number_rents = 0;




   movies[*num_movies] = *movie;

   (*num_movies)++;

}




void RemoveMovie(struct Movie *movies, int *num_movies, int movie_id) {

   int i;

   for (i = 0; i < *num_movies; i++) {

       if (movies[i].movie_id == movie_id) {

           break;

       }

   }




   if (i == *num_movies) {

       printf("Movie not found.\n");

       return;

   }




   for (; i < *num_movies - 1; i++) {

       movies[i] = movies[i + 1];

   }




   (*num_movies)--;

}




void UpdateMovie(struct Movie *movies, int num_movies, int movie_id) {

   int i;

   for (i = 0; i < num_movies; i++) {

       if (movies[i].movie_id == movie_id) {

           break;

       }

   }




   if (i == num_movies) {

       printf("Movie not found.\n");

       return;

   }




   printf("Enter the new movie title: ");

   scanf("%s", movies[i].title);




   printf("Enter the new movie genre: ");

   scanf("%s", movies[i].genre);




   printf("Enter the new year released: ");

   scanf("%d", &movies[i].year_released);

}




void SearchMovie(struct Movie *movies, int num_movies, int search_type) {

   int i;

   char search_term[ML];




   if (search_type == 1) {

       printf("Enter the movie ID: ");

       scanf("%d", &search_term);

   } else if (search_type == 2) {

       printf("Enter the movie title: ");

       scanf("%s", search_term);

   } else if (search_type == 3) {

       printf("Enter the movie genre: ");

       scanf("%s", search_term);

   } else {

       printf("Invalid search type.\n");

       return;

   }




   for (i = 0; i < num_movies; i++) {

       if (search_type == 1 && movies[i].movie_id == search_term) {

           printf("Movie found: %d, %s, %s, %d, %d\n", movies[i].movie_id, movies[i].title, movies[i].genre, movies[i].year_released, movies[i].number_rents);

           break;

       } else if (search_type == 2 && strcmp(movies[i].title, search_term) == 0) {

           printf("Movie found: %d, %s, %s, %d, %d\n", movies[i].movie_id, movies[i].title, movies[i].genre, movies[i].year_released, movies[i].number_rents);

           break;

       } else if (search_type == 3 && strcmp(movies[i].genre, search_term) == 0) {

           printf("Movie found: %d, %s, %s, %d, %d\n", movies[i].movie_id, movies[i].title, movies[i].genre, movies[i].year_released, movies[i].number_rents);

           break;

       }

   }




   if (i == num_movies) {

       printf("Movie not found.\n");

   }

}




void ListMovies(struct Movie *movies, int num_movies, bool available_only) {

   int i;

   for (i = 0; i < num_movies; i++) {

       if (!available_only || movies[i].is_available) {

           printf("Movie: %d, %s, %s, %d, %d\n", movies[i].movie_id, movies[i].title, movies[i].genre, movies[i].year_released, movies[i].number_rents);

       }

   }

}




void SaveToFile(struct Movie *movies, int num_movies, char *filename) {

   FILE*fp = fopen(filename, "w");

   int i;

   for (i = 0; i < num_movies; i++) {

       fprintf(fp, "%d,%s,%s,%d,%d,%d\n", movies[i].movie_id, movies[i].title, movies[i].genre, movies[i].year_released, movies[i].is_available, movies[i].number_rents);

   }




   fclose(fp);

}




void LoadFromFile(struct Movie *movies, int *num_movies, char *filename) {

   FILE *fp = fopen(filename, "r");

   *num_movies = 0;




   while (1) {

       struct Movie movie;

       if (fscanf(fp, "%d,%s,%s,%d,%d,%d", &movie.movie_id, movie.title, movie.genre, &movie.year_released, &movie.is_available, &movie.number_rents) == EOF) {

           break;

       }




       movies[*num_movies] = movie;

       (*num_movies)++;

   }




   fclose(fp);

}




int main() {

   struct Movie movies[ML];

   int num_movies = 0;




   int choice = 0;

   while (choice != 9) {

       printf("Movie Rental Database\n-----------------\n");

       printf("1. Add movie.\n");

       printf("2. Remove movie.\n");

       printf("3. Update movie.\n");

       printf("4. Search movie.\n");

       printf("5. List movies.\n");

       printf("6. Save data to file.\n");

       printf("7. Load data from file.\n");

       printf("8. Client Feature.\n");

       printf("9. Quit.\n");

       printf("Enter your choice: ");

       scanf("%d", &choice);




       switch (choice) {

           case 1:

               printf("You chose to add a movie.\n");

               AddMovie(&movies[num_movies], movies, &num_movies);

               break;

           case 2:

               printf("You chose to remove a movie.\n");

               printf("Enter the movie ID: ");

               int movie_id;

               scanf("%d", &movie_id);

               RemoveMovie(movies, &num_movies, movie_id);

               break;

           case 3:

               printf("You chose to update a movie.\n");

               printf("Enter the movie ID: ");

               int update_movie_id;

               scanf("%d", &update_movie_id);

               UpdateMovie(movies, num_movies, update_movie_id);

               break;

           case 4:

               printf("You chose to search for a movie.\n");

               printf("Enter the search type (1: movie_id, 2: title, 3: genre): ");

               int search_type;

               scanf("%d", &search_type);

               SearchMovie(movies, num_movies, search_type);

               break;

           case 5:

               printf("You chose to list the movies.\n");

               printf("List all: ");

               ListMovies(movies, num_movies, false);

               printf("List available only: ");

               ListMovies(movies, num_movies, true);

               break;

           case 6:

               printf("You chose to save data to file.\n");

               char filename[ML];

               printf("Enter the filename: ");

               scanf("%s", filename);

               SaveToFile(movies, num_movies, filename);

               break;

           case 7:

               printf("You chose to load data from file.\n");

               printf("Enter the filename: ");scanf("%s", filename);

               LoadFromFile(movies, &num_movies, filename);

               break;

           case 8:

               printf("You chose Client Feature.\n");

               // Add Similar API's for clients

               break;

           case 9:

               printf("Quitting...\n");

               break;

           default:

               printf("Invalid choice, please try again.\n");

       }

   }




   return 0;

}


