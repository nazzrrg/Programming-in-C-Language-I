#include <stdio.h>

int main(int argc, char** argv) {

    FILE *fin;

    fin = fopen(argv[1], "r");

    if (fin == NULL){
        printf("Unable to open file.\n");
        return 0;
    }

    int counter = 0;

    while (! feof(fin)) {
        counter++;
        char tmp[100];
        fgets(tmp, 100, fin);
        if (counter % 2 == 0) {
            printf("%s", tmp);
        }
    }

    fclose(fin);

    return 0;
}
