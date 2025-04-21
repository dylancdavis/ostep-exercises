#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void print_reverse(FILE* fin, FILE* fout);

int main(int argc, char* argv[argc+1]) 
{
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        return 1;
    }

    if (argc == 1) {
        print_reverse(stdin, stdout);
    }

    // Input file but no output; write to STDOUT
    if (argc == 2) {
        FILE* fin = fopen(argv[1], "r");
        if (fin == NULL) {
            fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
            
            return 1;
        }

        print_reverse(fin, stdout);
        return 0;
    }

    // Input and output file
    if (argc == 3) {

        struct stat fin_stat;
        struct stat fout_stat;

        stat(argv[1], &fin_stat);
        stat(argv[2], &fout_stat);

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

        if (fin_stat.st_ino == fout_stat.st_ino) {
            fprintf(stderr, "reverse: input and output file must differ\n");
            return 1;
        }

        print_reverse(fin, fout);
    }
}

void print_reverse(FILE* fin, FILE* fout) {
    // read fin, count lines.
    int num_lines = -1;
    while (!feof(fin)) {
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, fin);
        num_lines++;
        free(line);
    }

    // reset fin
    rewind(fin);

    char** lines = malloc(num_lines * sizeof(char*));
    if (lines == NULL) {
        printf("malloc failed");
        exit(1);
    }

    for (int i=0; i<num_lines; i++) {
        char* line = NULL;
        size_t len = 0;
        ssize_t res = getline(&line, &len, fin);
        if (res == -1) {
            printf("malloc failed");
            exit(1);
        }
        lines[i] = line;
    }

    for (int i=num_lines-1; i>=0; i--) {
        fprintf(fout, "%s", lines[i]);
    }
}