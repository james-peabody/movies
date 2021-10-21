#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>    // bool type
#include <string.h>     // strtok_r
#include <sys/types.h>
#include <sys/stat.h>   // stat
#include <pwd.h>
#include <dirent.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include "movies.h"


struct movie* processFile(const char* filePath)
{
    return;
}
int main(int argc, const char* argv[]) {
    int filename;
    srand(time(0));
    //filename = open(newFilePath, O_RDWR | O_CREAT | O_TRUNC, 0770);
    {
        printf("You must provide the name of the file to process\n", filename);
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

int large_file(char* filename, char* extension) {
    DIR* currDir = opendir(".");  // create FD that opens the current directory
    struct dirent* aDir;          // create structure for a directory entry
    struct stat dirStat;          // create STAT structure
    unsigned long len_ext = strlen(extension);
    unsigned long long file_size = 0;
    unsigned long int len_name = 0;
    bool file_found = false;

    while ((aDir = readdir(currDir)) != NULL) {
        len_name = strlen(aDir->d_name);
        if (len_name > len_ext) {
            const char* ext = &aDir->d_name[len_name - len_ext];
            if (strcmp(ext, extension) == 0) {
                stat(aDir->d_name, &dirStat);
                if (dirStat.st_size > file_size) {
                    strcpy(filename, aDir->d_name);
                    file_size = dirStat.st_size;
                    file_found = true;
                }
            }
        }
    }
    closedir(currDir);   //close current Dir
    if (file_found)      //file found or not found
        return 0;
    return 1;
}

int small_file(char* filename, char* extension) {
    DIR* currDir = opendir(".");  // create FD that opens the current directory
    struct dirent* aDir;          // create structure for a directory entry
    struct stat dirStat;          // create STAT structure
    unsigned long len_ext = strlen(extension);
    unsigned long long file_size = ULLONG_MAX;
    unsigned long int len_name = 0;
    bool file_found = false;

    while ((aDir = readdir(currDir)) != NULL) {  //go through all enteries
        len_name = strlen(aDir->d_name);
        if (len_name > len_ext) {
            const char* ext = &aDir->d_name[len_name - len_ext];
            if (strcmp(ext, extension) == 0) {
                stat(aDir->d_name, &dirStat);     //get data for current entry
                if (dirStat.st_size > file_size) {
                    strcpy(filename, aDir->d_name);
                    file_size = dirStat.st_size;
                    file_found = true;
                }
            }
        }
    }
    closedir(currDir);
    if (file_found)
        return 0;
    return 1;
}

int create_directory(char* filename, char* usr_id) {
    struct stat dirStat;
    int i = rand() % 99999;  //rand() function to generate a value between 1-99999
    char buff[BUFSIZ];

    sprintf(buff, "%d", i);   //String print to output on char buff
    strcpy(filename, usr_id);
    strcat(filename, ".movies.");
    strcat(filename, buff);

    if (stat(filename, &dirStat) == -1) {      // getting stat on filename 
        mkdir(filename, 0640);            //creating directories setting file promissions
        return 0;
    }
    return 1;
}

//main menu
void menu_loop(struct movie* movie) {
    int choose = 0;
    do {
        //display data to be shown
        printf("1. Select file to process?\n");
        scanf("%d", &choose);            //recieves user input
        printf("2. Exit program\n");
        scanf("%d", &choose);         //recieves user input
        printf("Enter a choice 1 or 2: \n");
        //user input
    } while (choose != 2) {
        choose = user_input(choose);
    }
   // if (choose >= 1 && choose <= 2) {
     //   data_output(choose, movie);
      //  output(movie);
   // }
    //return 0;
//}

//initialize next menu option
int process_menu(struct movie* movies) {
    char buff[BUFSIZ], filename[NAME_MAX], dir_name[NAME_MAX], usr_id[BUFSIZ];
    int pick = 0;
        do {        //define pick instead of choice for menu switch case 1, 2, 3
            printf("Which file you want to process?\n");
            printf("Enter 1 to pick the largest file\n");
            scanf("%d", &pick);        //pick 1 for largest file, recieves user input
            printf("Enter 2 to pick the smallest file\n");
            scanf("%d", &pick);         //pick 2 for smallest file, recieves user input
            printf("Enter 3 to specify the name of a file\n\n");  
            scanf("%d", &pick);//pick 3 for specific file, recieves user input
            printf("Enter a choice from 1 to 3: ");
            fgets(buff, BUFSIZ, stdin);
            pick = atoi(buff);
        }
        switch (pick) {
        case 1:
            if (large_file(filename, ".csv") == 0) {
                printf("\n\nNow processing the chosen file named %s\n", filename);      //gives largest file 
                if (getlogin_r(usr_id, BUFSIZ) == 0) {
                    create_directory(dir_name, usr_id);
                    printf("\n\nCreated directory with name %s\n\n", dir_name);
                }
                else {
                    printf("That directory already exists. Try again.\n\n");
                }
            }
            break;
        case 2:
            if (small_file(filename, ".csv") == 0) {
                printf("\n\nNow processing the chosen file named %s\n", filename);           //gives smallest file
                if (getlogin_r(usr_id, BUFSIZ) == 0) {
                    create_directory(dir_name, usr_id);
                    printf("\n\nCreated directory with name %s\n\n", dir_name);
                }
                else {
                    printf("That directory already exists. Try again.\n\n");        //if wrong file recieved then error
                }
                break;
        case 3:
            printf("\n\nEnter the complete file name: \n");
            printf("Now processing the chosen file named %s\n", filename);
            if (getlogin_r(usr_id, BUFSIZ) == 0) {
                create_directory(dir_name, usr_id);                  //
                printf("\n\nCreated directory with name %s \n \n", dir_name);
                break;
        default:
            printf("The file %s was not found, try again!\n\n", dir_name);
            }
            (void)atoi(buff);
            } while (pick != '3');
            return 0;
            }
        }
    }

        /*
        struct movie* processFile(const char* filename); {
        FILE* movie_file = fopen(filename, "r");
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
                tail = newNode;s
            }
        }
        printf("Parsed data for %d movies\n", year);
        free(processFile);
        fclose(processFile);
        //return head;
    }
    */
