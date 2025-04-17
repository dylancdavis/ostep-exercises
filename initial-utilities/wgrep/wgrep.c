#include <stdio.h>
#include <string.h>

void grep_file(FILE* f, char* search_term);

int main(int argc, char* argv[argc+1])
{
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        return 1;
    }

    char* search_term = argv[1];

    if (argc == 2) {
        grep_file(stdin, search_term);
    }

    for (int i=2; i<argc; i++) {
        char* fname = argv[i];
        FILE* f = fopen(fname, "r");
        
        if (f == NULL) {
            printf("wgrep: cannot open file\n");
            return 1;
        }

        grep_file(f, search_term);
    }
}

void grep_file(FILE* f, char* search_term) {
    while(!feof(f)) {
        char* line = NULL;
        size_t len = 0;
        getline(&line, &len, f);

        char* res = strstr(line, search_term);
        if (res != NULL) {
            printf("%s", line);
        }
    }
}