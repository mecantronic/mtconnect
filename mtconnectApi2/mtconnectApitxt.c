#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_PATH "/mnt/windows_share/TIMESTAMP.txt"
#define MACHINE_ID "my-machine"

void generate_iso8601(char *buffer, int *time_parts) {
    struct tm tm_time = {0};
    tm_time.tm_year = time_parts[0] - 1900;
    tm_time.tm_mon = time_parts[1] - 1;
    tm_time.tm_mday = time_parts[2];
    tm_time.tm_hour = time_parts[3];
    tm_time.tm_min = time_parts[4];
    tm_time.tm_sec = time_parts[5];
    strftime(buffer, 30, "%Y-%m-%dT%H:%M:%S.000Z", &tm_time);
}

void parse_last_timestamp(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line1[100], line2[100];
    char last_type[50] = {0};
    char iso_time[30] = {0};
    int time_parts[6] = {0};

    // Read the file line by line to get the last two lines
    while (fgets(line1, sizeof(line1), file) != NULL) {
        if (fgets(line2, sizeof(line2), file) == NULL) {
            break;
        }
        strncpy(last_type, line1, sizeof(last_type) - 1);
        sscanf(line2, "%d,%d,%d,%d,%d,%d,", &time_parts[0], &time_parts[1],
               &time_parts[2], &time_parts[3], &time_parts[4], &time_parts[5]);
    }
    fclose(file);

    // Generate ISO 8601 format time
    generate_iso8601(iso_time, time_parts);

    // Determine status based on last_type
    char status[20];
    if (strstr(last_type, "START TIME")) {
        strcpy(status, "RUNNING");
    } else if (strstr(last_type, "END TIME")) {
        strcpy(status, "COMPLETED");
    } else {
        fprintf(stderr, "Invalid format in the file.\n");
        return;
    }

    // Generate the JSON structure
    printf("{\n");
    printf("    \"machineId\": \"%s\",\n", MACHINE_ID);
    printf("    \"startTime\": \"%s\",\n", iso_time);
    printf("    \"status\": \"%s\"\n", status);
    printf("}\n");
}

int main() {
    if (access(FILE_PATH, F_OK) != 0) {
        fprintf(stderr, "File %s not found!\n", FILE_PATH);
        return 1;
    }

    parse_last_timestamp(FILE_PATH);

    return 0;
}

