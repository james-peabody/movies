#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>    // bool type
#include <string.h>     // strtok_r
#include <sys/stat.h>   // stat
#include <pwd.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include "movies_by_year.h"
#define PREFIX "movies_"



bool does_file_exists(const char* filename) {
    struct stat buffer;
    return (stat(filename, &buffer) == 0);
}
/*
void high_rated_movies_by_year(struct movie* movie) {
    int first_year = UINT_MAX, last_year = 0;
    float rating = 0.;
    char title[BUFSIZ];

    for(struct movie* movies = movie; movies != NULL; movies = movies->next) {
        if (movie->year < first_year) first_year = movie->year;
        if (movie->year > last_year) last_year = movie->year;
    }

    for(int year = first_year; year <= last_year; year++) {
        rating = 0.;
        for(struct movie* movies = movie; movies != NULL; movies = movies->next) {
            if (movie->year == first_year && movie->ratingValue > rating) {
                rating = movie->ratingValue;
                strcpy(title, movie->title);
            }
        }
        if (rating > 0) {
            printf("%d %.1f %s\n", first_year, rating, title);
        }
    }
    printf("\n");
}*/
char* large_file() {
    DIR* currDir = opendir(".");
    struct dirent* aDir;
    time_t lastModiftime;
    struct stat dirStat;
    char* entryName = calloc(257, sizeof(char)); //return array based off current set up
    while ((aDir = readdir(currDir)) != NULL) {
        if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
            stat(aDir->d_name, &dirStat);
            if (dirStat.st_mtime > large_file)
            {
                lastModiftime = dirStat.st_mtime;
                memset(entryName, '\0', sizeof(entryName));
                strcpy(entryName, aDir->d_name);
            }
        }
    }
    closedir(currDir);
    printf("Now processing the file chosen named %s.\n", PREFIX, entryName);
    return entryName;
}
char* small_file() {
    DIR* currDir = opendir(".");
    struct dirent* aDir;
    time_t lastModiftime;
    struct stat dirStat;
    char* entryName = calloc(257, sizeof(char)); //return array based off current set up
    while ((aDir = readdir(currDir)) != NULL) {
        if (strncmp(PREFIX, aDir->d_name, strlen(PREFIX)) == 0) {
            stat(aDir->d_name, &dirStat);
            if (dirStat.st_mtime < small_file)
            {
                lastModiftime = dirStat.st_mtime;
                memset(entryName, '\0', sizeof(entryName));
                strcpy(entryName, aDir->d_name);
            }
        }
    }
    closedir(currDir);
    //getenv(LOGNAME);
    printf("Now processing the file chosen named %s.\n", PREFIX, entryName);
    return entryName;
}

int main(int argc, const char* argv[]) {
    int file_descriptor;
    char* newFilePath = "./newFile.txt";
    file_descriptor = open(newFilePath, O_RDWR | O_CREAT | O_TRUNC, 0770);
    {
        printf("You must provide the name of the file to process\n");
        return EXIT_FAILURE;
    }
    if (!does_file_exists(argv[1])) {
        printf("Unable to find file %s.\n", argv[1]);
        return EXIT_FAILURE;
    }
    printf("==================================\n");
    printf("Processed file: %s\n", argv[1]);
    struct movie* list = processFile(argv[1]);
    printf("==========================================\n\n");
    menu_loop(list);
    printf("\n========================================\n");
    return EXIT_SUCCESS;
    return 0;
}
//main menu
void menu_loop(struct movie* movie) {
    int choose = 0;
    //display data to be shown
    printf("1. Select file to process?\n");
    printf("2. Exit program\n");
    printf("Enter a choice 1 or 2: \n");
    //user input
    while (choose == 0) {
        choose = user_input(choose);
    }
    if (choose >= 1 && choose <= 2) {
        data_output(choose, movie);
        output(movie);
    }
    return;
}
/*
struct movie* movie_create(char* current_line) {
    struct movie* current_movie = malloc(sizeof(struct movie));
    char* saveptr = NULL;

    //first token for Movie Title
    char* token = strtok_r(current_line, ",", &saveptr);
    current_movie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(current_movie->title, token);

    //second token for Movie release date
    token = strtok_r(NULL, ",", &saveptr);
    current_movie->year = atoi(token);

    //third token for Movie Languages and gets languages in string to remove the first '[' from it
    token = strtok_r(NULL, ",", &saveptr);
    current_movie->language = calloc(strlen(token), sizeof(char));
    token[strlen(token) - 1] = '\0';               // strips the ending ']'
    strcpy(current_movie->language, token + 1);  // strips the leading '['

    //last token for Movie Rating and removes ',' from beginning string then converts to float
    token = strtok_r(NULL, "\n", &saveptr);
    current_movie->ratingValue = strtod(token, NULL);

    //next node to NULL in newly creates movie entry
    current_movie->next = NULL;
    return current_movie;
}*/
/*
void movies_by_language(struct movie* movie) {
    char language[BUFSIZ];
    bool movie_found = false;
    char* token;
    char* rest;

    printf("Enter the language for which you want to see movies (Capatalize the first letter): ");
    fgets(language, BUFSIZ, stdin);
    for (token = language; *token != '\0'; token++)
        if (*token == '\n') *token = '\0';
    for(struct movie* movies = movie; movies != NULL; movies = movies->next)
    {
        rest = movie->language;
        while ((token = strtok_r(rest, ";", &rest)))
        {
            if (!strcmp(token, language))
            {
                movie_found = true;
                printf("%d %s\n", movie->year, movie->title);
                break;
            }
        }
    }

    if (!movie_found)
        printf("No movies released in %s\n", language);
    printf("\n");
}*/
//initialize next menu option
int process_menu(struct movie* movies) {
    char buff[BUFSIZ];
    int pick = 0;
    while(pick!='3')
        printf("Enter a choice from 1 to 3: \n");
    printf("Which file you want to process?\n");
    printf("Enter 1 to pick the largest file\n");
    printf("Enter 2 to pick the smallest file\n");
    printf("Enter 3 to specify the name of a file\n");
    fgets(buff, BUFSIZ, stdin);
    pick = atoi(buff);
    switch (pick) {
        case 1:
            printf("\n\nNow processing the chosen file named %s.csv\n", large_file);
            printf("\n\nCreated directory with name %s %lu %d", processFile);
            break;
            case 2:
                printf("\n\nNow processing the chosen file named %s.csv\n", small_file);
                printf("\n\nCreated directory with name %s %lu %d", processFile);
                break;
                case 3:
                    printf("\n\nEnter the complete file name: \n", large_file);
                    printf("Now processing the chosen file named %s %lu\n\n", processFile);
                    printf("\n\nCreated directory with name %s %lu %d", processFile);
                    break;
                    default:
                        printf("The file %s was not found, try again!\n\n", processFile);
    }
    (void)atoi(buff);
    return 0;
}

struct movie* processFile(const char* filePath) {
    FILE* movie_file = fopen(filePath, "r");
    char* current_line = NULL;
    size_t len = 0;
    ssize_t nread;
    int count = 0;

    //head and tail linked list
    struct movie* head = NULL;
    struct movie* tail = NULL;

    //skips first line in .csv file to then read the file line by line
    getline(&current_line, &len, movie_file);
    while ((nread = getline(&current_line, &len, movie_file)) != -1)
    {
        count++; //counts number of movies parsed
        struct movie* newNode = movie_create(current_line); //gets new movie Node in corresponding line
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

// printf("Parsed data for %d movies\n", count);
free(current_line);
fclose(movie_file);
//return head;
}
