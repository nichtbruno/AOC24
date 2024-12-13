#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("input.txt", "r");
    if(file == NULL) {
        printf("Couldn't open file!");
        return 1;
    }

    char line[256];
    while(fgets(line, sizeof(line), file) != 0) {
        printf("%s", line);
    }

    fclose(file);

    return 0;
}
