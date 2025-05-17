#include <stdio.h>
#include <string.h>

#define MAX_TXT 80
#define MAX_ACTORS 100
#define MAX_MOVIES 100

typedef struct{
    int id;
    char name[MAX_TXT];
}Actor;

typedef struct{
    char title[MAX_TXT];
    int year;
    char director[MAX_TXT];
    int actors_ids[MAX_ACTORS];
    int nb_actors;
}Movie;


    //TODO: Solicitar el id y nombre del actor y añadirlo al arreglo. Habrá que preguntarle al usuario si se desea
    // añadir más actores al arreglo, en caso contrario volver al menú principal. Se devuelve la cantidad de actores entrados al arreglo.
int addActors(Actor actors[MAX_ACTORS]) {
    int count = 0;
    char more = 'y';
    
    while (more == 'y' || more == 'Y') {
        if (count >= MAX_ACTORS) {
            printf("Maximum number of actors reached.\n");
            break;
        }

        printf("Enter actor ID: ");
        scanf("%d", &actors[count].id);
        getchar(); // Limpiar el salto de línea pendiente

        printf("Enter actor name: ");
        fgets(actors[count].name, MAX_TXT, stdin);
        // Eliminar el salto de línea final de fgets
        size_t len = strlen(actors[count].name);
        if (len > 0 && actors[count].name[len - 1] == '\n') {
            actors[count].name[len - 1] = '\0';
        }

        count++;

        printf("Do you want to add another actor? (y/n): ");
        scanf(" %c", &more);
    }

    return count;
}



    //TODO: Solicitar el título, año de lanzamiento y director de la película y añadirlo al arreglo. Tened en cuenta que
    // también se ha de solicitar el id de los actores que participen en dicha película. Se deberá en todo momento, preguntar si se desean añadir nuevos actores y/o películas.
    // Se devuelve la cantidad de películas entrados al arreglo.
int addMovies(Movie movies[MAX_MOVIES]) {
    int count = 0;
    char moreMovies = 'y';

    while (moreMovies == 'y' || moreMovies == 'Y') {
        if (count >= MAX_MOVIES) {
            printf("Maximum number of movies reached.\n");
            break;
        }

        printf("Enter movie title: ");
        getchar(); // Limpiar salto de línea previo
        fgets(movies[count].title, MAX_TXT, stdin);
        size_t len = strlen(movies[count].title);
        if (len > 0 && movies[count].title[len - 1] == '\n') {
            movies[count].title[len - 1] = '\0';
        }

        printf("Enter release year: ");
        scanf("%d", &movies[count].year);

        getchar(); // Limpiar salto de línea
        printf("Enter director name: ");
        fgets(movies[count].director, MAX_TXT, stdin);
        len = strlen(movies[count].director);
        if (len > 0 && movies[count].director[len - 1] == '\n') {
            movies[count].director[len - 1] = '\0';
        }

        // Añadir actores por ID
        movies[count].nb_actors = 0;
        char moreActors = 'y';
        while ((moreActors == 'y' || moreActors == 'Y') && movies[count].nb_actors < MAX_ACTORS) {
            printf("Enter actor ID: ");
            scanf("%d", &movies[count].actors_ids[movies[count].nb_actors]);
            movies[count].nb_actors++;

            if (movies[count].nb_actors >= MAX_ACTORS) {
                printf("Maximum number of actors for this movie reached.\n");
                break;
            }

            printf("Do you want to add another actor to this movie? (y/n): ");
            scanf(" %c", &moreActors);
        }

        count++;

        printf("Do you want to add another movie? (y/n): ");
        scanf(" %c", &moreMovies);
    }

    return count;
}


    //TODO: Dado un nombre entrado por parámetro, buscar y devolver el id del actor correspondiente al mismo.
int getIdByName(Actor actors[], int num_actors, char name[]) {
    for (int i = 0; i < num_actors; i++) {
        if (strcmp(actors[i].name, name) == 0) {
            return actors[i].id;
        }
    }
    return -1; // Actor no encontrado
}

    //TODO: Dado un id entrado por parámetro, buscar el nombre del actor correspondiente al mismo. La variable name, es donde se depositará el nombre del actor encontrado.
void getNameById(Actor actors[], int num_actors, char name[], int id) {
    for (int i = 0; i < num_actors; i++) {
        if (actors[i].id == id) {
            strcpy(name, actors[i].name);
            return;
        }
    }
    strcpy(name, "Unknown"); // Si no se encuentra el ID
}


    //TODO: Se ha de solicitar el nombre del actor y mostrar el listado de películas que son protegonizadas por el mismo.
void showMoviesByActor(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    char actor_name[MAX_TXT];
    int actor_id, found = 0;

    printf("Enter actor name: ");
    getchar(); // limpiar buffer
    fgets(actor_name, MAX_TXT, stdin);
    actor_name[strcspn(actor_name, "\n")] = '\0'; // eliminar salto de línea

    actor_id = getIdByName(actors, num_actors, actor_name);

    if (actor_id == -1) {
        printf("Actor not found.\n");
        return;
    }

    printf("Movies featuring %s:\n", actor_name);
    for (int i = 0; i < num_movies; i++) {
        for (int j = 0; j < movies[i].nb_actors; j++) {
            if (movies[i].actors_ids[j] == actor_id) {
                printf("- %s (%d), directed by %s\n", movies[i].title, movies[i].year, movies[i].director);
                found = 1;
                break;
            }
        }
    }

    if (!found) {
        printf("No movies found for this actor.\n");
    }
}


void reportActorsByDirector(Movie movies[], int num_movies, Actor actors[], int num_actors) {
    // TODO: Se ha de solicitar el nombre del director y crear un fichero de texto llamado "reportABD.txt" con el nombre
    //  de los actores que participen en las películas dirigidas por dicho director
}

int deleteMovieByYear(Movie movies[], int num_movies) {
    //TODO: Se ha de solicitar el año de la película que se desea eliminar, encontrarlas y quitarlas del arreglo
}

void reportCurrentMovies(Movie movies[], int num_movies) {
    // TODO: Se ha de crear un fichero de binario llamado "reportCM.bin" con las pelñiculas que solo pertenezcan al año actual
}

int main() {
    Actor actors[MAX_ACTORS];
    Movie movies[MAX_MOVIES];
    int num_actors = 0, num_movies = 0;
    int option=0;

    do {
        printf("---- MENU ----\n");
        printf("1. Enter actors \n");
        printf("2. Enter movies \n");
        printf("3. Show movies by actor \n");
        printf("4. Report actors who have worked with x director... \n");
        printf("5. Delete movies by year \n");
        printf("6. Report current movies... \n");
        printf("7. Exit \n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                num_actors = addActors(actors);
                break;
            case 2:
                num_movies = addMovies(movies);
                break;
            case 3:
                showMoviesByActor(movies, num_movies, actors, num_actors);
                break;
            case 4:
                reportActorsByDirector(movies, num_movies, actors, num_actors);
                break;
            case 5:
                num_movies = deleteMovieByYear(movies, num_movies);
                break;
            case 6:
                reportCurrentMovies(movies, num_movies);
                break;
            case 7:
                printf("Program closing...\n");
                break;
        }
        printf("\n");
    }while(option!=7);

    return 0;
}
