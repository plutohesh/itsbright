#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH_LEN 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [up|down]\n", argv[0]);
        return 1;
    }

    char path[MAX_PATH_LEN];
    snprintf(path, MAX_PATH_LEN, "/sys/class/backlight/*/brightness");

    FILE *fp = fopen(path, "r+");
    if (fp == NULL) {
        printf("Failed to open brightness file\n");
        return 1;
    }

    int current_brightness;
    fscanf(fp, "%d", &current_brightness);

    int new_brightness;
    if (strcmp(argv[1], "up") == 0) {
        new_brightness = current_brightness * 1.05;
    } else if (strcmp(argv[1], "down") == 0) {
        new_brightness = current_brightness * 0.95;
    } else {
        printf("Invalid argument: %s\n", argv[1]);
        return 1;
    }

    fseek(fp, 0, SEEK_SET);
    fprintf(fp, "%d", new_brightness);
    fclose(fp);

    return 0;
}
