#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LSH_RL_BUFSIZE  1024        // Buffer to read line
#define LSH_TOK_BUFSIZE 64          // Buffer to tokenize
#define LSH_TOK_DELIM   " \t\r\n\a" // Tokenizer delimiter chars

void lsh_loop(void);
char *lsh_read_line(void);
char **lsh_split_line(char *line);

int main(int argc, char **argv) 
{
    // Load config files, if any.

    // Run command loop.
    // lsh_loop();

    // Testing reading a line
    char *line;
    line = lsh_read_line();
    printf("Printing the read line:\n");
    for (int i = 0; line[i] != '\0'; i++) 
    {
        printf("%c", line[i]);
    } 
    printf("\n");

    // Testing parsing a line
    char **args;
    args = lsh_split_line(line);
    printf("Printing the tokenized strings:\n");
    for (int i = 0; args[i] != NULL; i++) 
    {
        printf("%s ", args[i]);
    } 
    printf("\n");

    // Freeing tests
    free(line);
    free(args);

    // Perform any shutdown/cleanup.

    return EXIT_SUCCESS;
}

/*
void lsh_loop(void) 
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = lsh_read_line();
        args = lsh_split_line(line);
        status = lsh_execute(args);

        free(line);
        free(args);
    } while (status);
}
*/

char *lsh_read_line(void) 
{
    int bufsize = LSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);
    int c;

    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Read a character
        c = getchar();

        // If we hit EOF, replace it with a null character and return.
        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        } else {
            buffer[position] = c;
        }
        position++;

        // If we have exceeded the buffer, reallocate.
        if (position >= bufsize) {
            bufsize += LSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}

char **lsh_split_line(char *line) 
{
    int bufsize = LSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;
    
    if (!tokens) {
        fprintf(stderr, "lsh: allocation erro\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, LSH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += LSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
