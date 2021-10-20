//  movies_by_year.h
//  movie
#ifndef movies_h
#define movies_h

struct movie {
    char* title;
    int year;
    char* language; //maximum number movie released and maximum length of language string characters
    float ratingValue;
    struct movie* next;
};

/*menu loop
const char* main_menu =
"==============================================\n\n"
"---------------Data Selection----------------\n"
"1. Select file to process?\n"
"2. Exit program\n";
*/
//process menu
/*const char* sub_menu =
"========================================\n\n"
"Which file you want to process?\n"
"Enter 1 to pick the largest file\n"
"Enter 2 to pick the smallest file\n"
"Enter 3 to specify the name of a file\n";
*/



bool does_file_exists(const char* filename);
int main(int argc, const char* argv[]);
//void movie_by_year(struct movie* movie);
//void high_rated_movies_by_year(struct movie* movie);
//void movies_by_language(struct movie* movie);
int process_menu(struct movie* movie);          //main_menu
void menu_loop(struct movie* movie);            //sub menu
//struct movie* movie_create(char* current_line);
struct movie* processFile(const char* filePath);

#endif /*movies_by_year_h */
