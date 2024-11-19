/*
 * finds every file with the pattern mtconnect*.json
 * and send it through curl
 */
//#define LOOP
#define DEBUG

#include "errorcheck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
main (void)
{
#ifndef DEBUG
    while (1)
#endif
        {
            // Use find to list files starting with 'mtconnect' and ending with
            // '.json'
            FILE *fp = popen (
                "find . -maxdepth 1 -type f -name 'mtconnect*.json'", "r");
            if (fp == NULL)
                {
#ifdef DEBUG
                    perror ("Error opening pipe");
#endif
                    return 1;
                }

            char filename[256]; // Buffer to store each filename
            while (fgets (filename, sizeof (filename), fp) != NULL)
                {
#ifdef DEBUG
                    printf ("Sending file: %s ...", filename);
#endif
                    // Remove newline character from filename
                    filename[strcspn (filename, "\n")] = 0;

                    // Construct the curl command for each file
                    char syscommand[512];
                    snprintf (syscommand, sizeof (syscommand),
                              "curl --location "
                              "'https://api.dev.factoryflow.sinapsis.io/"
                              "production-tracker' "
                              "--header 'Authorization: "
                              "96a65a72-9de2-46a6-afb7-8ec9a5da2e8c' "
                              "--header 'Content-Type: application/json' "
                              "--data @%s > uploadErrorLog.txt",
                              filename);

                    // Execute the curl command
                    system (syscommand);

                    // upload error check
                    int error = errorcheck ();
                    printf ("upload error check= %d\r\n", error);
                    if (error == 0)
                        {
                            snprintf (syscommand, sizeof (syscommand),
                                      "mv %s ./sended/ ", filename);
                            system (syscommand);
                        }
#ifdef DEBUG
                    printf ("error file: ");
                    system ("cat uploadErrorLog.txt");
#endif
                    system ("rm uploadErrorLog.txt");
                }

            // Close the pipe
            fclose (fp);

            // Sleep before the next iteration
#ifdef LOOP
            usleep (250000);
#endif
        }
#ifdef DEBUG
    printf ("Finished\r\n");
#endif
    return 0;
}
