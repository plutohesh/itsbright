#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 256

int main() {
    char path[MAX_PATH];
    int brightness, max_brightness, new_brightness;
    FILE *fp;

    // Loop through all directories in /sys/class/backlight/
    for (int i = 0; i < 10; i++) {
        sprintf(path, "/sys/class/backlight/%d/brightness", i);

        // Read brightness and max_brightness values from each directory
        fp = fopen(path, "r");
        if (fp == NULL) {
            printf("Error opening file %s\n", path);
            exit(1);
        }
        fscanf(fp, "%d", &brightness);
        fclose(fp);

        sprintf(path, "/sys/class/backlight/%d/max_brightness", i);
        fp = fopen(path, "r");
        if (fp == NULL) {
            printf("Error opening file %s\n", path);
            exit(1);
        }
        fscanf(fp, "%d", &max_brightness);
        fclose(fp);

        // Calculate new brightness value
        new_brightness = brightness + (max_brightness * 5 / 100);

        // Write new brightness value back to the corresponding directory
        fp = fopen(path, "w");
        if (fp == NULL) {
            printf("Error opening file %s\n", path);
            exit(1);
        }
        fprintf(fp, "%d", new_brightness);
        fclose(fp);
    }

    return 0;
}
