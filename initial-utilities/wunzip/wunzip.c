#include <stdio.h>

int main(int argc, char* argv[argc+1])
{
    if (argc == 1) {
        printf("wunzip: file1 [file2 ...]\n");
        return 1;
    }

    int count = 0;
    char c = 0;

    for (int i=1; i<argc; i++) {
        char* fname = argv[i];
        FILE* f = fopen(fname, "r");

        if (f == NULL) {
            printf("wunzip: cannot open file\n");
            return 1;
        }
        
        while(!feof(f)) {

            fread(&count, sizeof(int), 1, f);
            c = fgetc(f);

            if (c == EOF) {
                break;
            }

            // jank looping for repeating put character
            for (int i=0; i<count;i++) {
                fputc(c, stdout);
            }
        };

        fclose(f);
    }
}