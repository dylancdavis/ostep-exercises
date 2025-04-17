#include <stdio.h>

int main(int argc, char* argv[argc+1])
{
    if (argc == 1) {
        printf("wzip: file1 [file2 ...]\n");
        return 1;
    }

    int count = 0;
    char current = 0;

    for (int i=1; i<argc; i++) {
        char* fname = argv[i];
        FILE* f = fopen(fname, "r");

        if (f == NULL) {
            printf("wzip: cannot open file\n");
            return 1;
        }
        
        while(!feof(f)) {
            char c = fgetc(f);

            if (c == EOF) {
                break;
            }

            if (current == 0) {
                current = c;
            }

            if (c == current) {
                count += 1;
            } else {
                fwrite(&count, sizeof(int), 1, stdout);
                fwrite(&current, sizeof(char), 1, stdout);
                count = 1;
                current = c;
            }
        };

        fclose(f);
    }

    fwrite(&count, sizeof(int), 1, stdout);
    fwrite(&current, sizeof(char), 1, stdout);
}