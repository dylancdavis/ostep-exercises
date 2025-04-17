#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_and_return(FILE* fin, FILE* out);

int main(int argc, char* argv[argc+1]) 
{
    if (argc > 3) {
        printf("usage: reverse <input> <output>");
        fprintf(stderr, "usage: reverse <input> <output>");
        return 1;
    }

    if (argc == 1) {
        print_and_return(stdin, stdout);
    }

    // Input file but no output; write to STDOUT
    if (argc == 2) {
        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            printf("error: cannot open file '%s'", argv[1]);
            fprintf(stderr, "error: cannot open file '%s'", argv[1]);
            
            return 1;
        }

        print_and_return(fin, stdout);
        return 0;
    }

    // Input and output file
    if (argc == 3) {
        int v = strcmp(argv[1], argv[2]);
        if (v == 0) {
            printf("Input and output file must differ");
            fprintf(stderr, "Input and output file must differ");
            return 1;
        };

        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            printf("error: cannot open file '%s'", argv[1]);
            fprintf(stderr, "error: cannot open file '%s'", argv[1]);
            return 1;
        }

        FILE* fout = fopen(argv[2], "w");
        if (fout == NULL) {
            printf("error: cannot open file '%s'", argv[2]);
            fprintf(stderr, "error: cannot open file '%s'", argv[2]);
            return 1;
        }

        print_and_return(fin, fout);
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
    fprintf(fout, "%s", line);
    if (r == 0) {
        fputc('\n', fout);
    }
    free(line);
    return r+1;
}