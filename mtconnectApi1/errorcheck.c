#include "errorcheck.h"
#include <stdio.h>
#include <string.h>

int
errorcheck (void)
{
    FILE *file = fopen ("uploadErrorLog.txt", "r");
    if (file == NULL)
        {
            // perror("Error opening file");
            return -1;
        }

    char line[256];
    int found = 0;

    // Read each line in the file
    while (fgets (line, sizeof (line), file))
        {
            // Check if "error" is in the line (case-sensitive)
            if (strstr (line, "error") != NULL)
                {
                    fclose (file);
                    return 1;
                    break;
                }
        }

    fclose (file);
    return 0;
}
