#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_and_return(FILE* fin, FILE* out);

int main(int argc, char* argv[argc+1]) 
{
    FILE* fin;
    FILE* fout;

    fin = NULL;
    fout = NULL;

    if (argc == 1) {
        printf("reading from stdin not supported\n");
        return 1;
    }

    // Input file but no output; write to STDOUT
    if (argc == 2) {
        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            printf("error opening file");
            return 1;
        }

        print_and_return(fin, stdout);
        return 0;
    }

    // Input and output file
    if (argc == 3) {
        printf("hgere?");
        int v = strcmp(argv[1], argv[2]);
    }
}

int print_and_return(FILE* fin, FILE* fout) {
    if (feof(fin)) {
        fclose(fin);
        return 0;
    }

    char* line = NULL;
    size_t len = 0;
    getline(&line, &len, fin);

    int r = print_and_return(fin, fout);
    printf("%s", line);
    if (r == 0) {
        fputc('\n', fin);
    }
    free(line);
    return r+1;
}