#include <stdio.h>

int main(int argc, char* argv[argc+1])
{
    for (int i=1; i<argc; i++) {
        char* fname = argv[i];
        FILE* f = fopen(fname, "r");

        
        if (f == NULL) {
            printf("wcat: cannot open file\n");
            return 1;
        }
        
        while(!feof(f)) {
            char c = fgetc(f);
            if (c != EOF) {
                printf("%c", c);
            }
        }
    }
}