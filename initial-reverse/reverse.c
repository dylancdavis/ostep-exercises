#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int print_and_return(FILE* fin, FILE* out);

int main(int argc, char* argv[argc+1]) 
{
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    if (argc == 1) {
        print_and_return(stdin, stdout);
    }

    // Input file but no output; write to STDOUT
    if (argc == 2) {
        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            
            return 1;
        }

        print_and_return(fin, stdout);
        return 0;
    }

    // Input and output file
    if (argc == 3) {

        struct stat fin_stat;
        struct stat fout_stat;

        stat(argv[1], &fin_stat);
        stat(argv[2], &fout_stat);

        if (fin_stat.st_ino == fout_stat.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            return 1;
        }

        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            return 1;
        }

        FILE* fout = fopen(argv[2], "w");
        if (fout == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
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