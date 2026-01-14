//imports
#include <stdlib.h>
#include <stdio.h>

//defintions
#define LSH_RL_BUFSIZE 1024

//MARK: READ A LINE
//this function takes a line that the user types in once prompted (using stdin)
//function needs to allocate a block of space for this line and allocate more 
//if exceeded
char *lsh_read_line(void) {
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    //check if buffer has been allocated space to with malloc
    //if not print allocation error
    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        //read a char
        c = getchar();

        //CHANGE THIS TO ADAPT TO GETLINE -- TODO
        //if we hit EOF, replace with a null char and return 
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        //if buffer exceeded, reallocate
        if (position > bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            //check again for allocation error
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

//MARK: PARSING THE LINE
char **lsh_split_line(char *line) {

}

//MARK: Shell loop
//Read, Parse, Execute
void lsh_loop(void) {
    char *line;
    char **args;
    int status;

    do {
        printf("> "); //prompts for the shell 
       line = lsh_read_line(); //gets line
       args = lsh_split_line(line); //separates the line into arguments
       status = lsh_execute(args); //defines when to exit using arguments

       //frees all heap allocated pointers
       free(line); 
       free(args);

    } while (status);
}

//MARK: Main 
// initialze, interpret, terminate
int main (int argc, char **argv) {
    //load files if any

    //run command loop
    lsh_loop();

    //terminate / perform shutdown/cleanup

    return 0;
}