/* in this file:
 *	 - download the remote file
 *   - read the local file
 *   - create variables
 *   - create json structure
 *   - name json file with date
 *   - send file -> commented. transmition.c make the job
 */

#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define the structure to store the data
typedef struct
{
    char machineId[50];
    char startTime[50];
    char status[50];
} OkumaData;

int
main ()
{
    FILE *file;
    char line[256];
    OkumaData okumadata;

    system ("curl '192.168.0.200:5000/current' -o mtfile.xml");

    // Open the input file in read mode
    file = fopen ("mtfile.xml", "r");
    if (file == NULL)
        {
#define DEBUG
            perror ("Error opening input file");
#endif
            return 1;
        }

    // Read each line of the file
    while (fgets (line, sizeof (line), file))
        {
            // Look for 'status="' and extract the value
            char *statusPtr = strstr (line, "Execution dataItemId");
            if (statusPtr != NULL)
                {
#ifdef DEBUG
                    printf ("found excecution dataitemId\r\n");
#endif
                    char *start = strstr (line, "timestamp=")
                                  + 11; // Find the start of the tag value
                                        // (after 'timestamp=\"')
#ifdef DEBUG
                    if (start != NULL)
                        printf ("timestamp\r\n");
#endif
                    char *end = strstr (start,
                                        "\""); // Find the end of the tag value
                                               // (before '</Execution>')
#ifdef DEBUG
                    if (end != NULL)
                        printf ("\"\r\n");
#endif
                    int value_length = end - start;
#ifdef DEBUG
                    printf ("%d\r\n", value_length);
#endif
                    strncpy (okumadata.startTime, start, value_length);
                    okumadata.startTime[23] = 'Z';
                    okumadata.startTime[24] = '\0';
#ifdef DEBUG
                    printf ("%s\r\n", okumadata.startTime);
#endif
                    start = strstr (line, ">")
                            + 1; // Find the start of the tag value (after '>')
                    end = strstr (
                        line, "</Execution>"); // Find the end of the tag value
                                               // (before '</Execution>')
                    value_length = end - start;
                    strncpy (okumadata.status, start, value_length);
                    okumadata.status[value_length + 1] = '\0';
                    // statusPtr += strlen("status=\"");
                    // sscanf(statusPtr, "%[^\"]", okumadata.status);
                }

            // Look for 'machineId="' and extract the value
            // char *machineIdPtr = strstr(line, "machineId=\"");
            // if (machineIdPtr != NULL) {
            //    machineIdPtr += strlen("machineId=\"");
            //    sscanf(machineIdPtr, "%[^\"]", okumadata.machineId);
            //}
            strcpy (okumadata.machineId, "d49234f3a599");
        }

    // Close the input file
    fclose (file);

    // Get current date and time for filename
    time_t now = time (NULL);
    struct tm *t = localtime (&now);
    char filename[100];

    // two ways to name .json file example with the same date
    // first: mtconnect-2024-11-10-22-12-34.json -> with machine time
    // second: 2024-11-10-22-12-34.257Z.json -> with downloaded file time
    // strftime(filename, sizeof(filename), "mtconnect-%Y-%m-%d-%H-%M-%S.json",
    // t);
    strcpy (filename, "mtconnect-");
    strcat (filename, okumadata.startTime);

    // Replace ':' with '-' in the filename
    for (char *p = filename; *p; p++)
        {
            if (*p == ':')
                {
                    *p = '-';
                }
        }

    // this is only if we use the file time
    strcat (filename, ".json");

    // Open the output file in write mode
    FILE *outputFile = fopen (filename, "w");
    if (outputFile == NULL)
        {
#define DEBUG
            perror ("Error opening output file");
#endif
            return 1;
        }

    // Write the structure data in JSON format to the output file
    fprintf (outputFile, "{\n");
    fprintf (outputFile, "    \"machineId\": \"%s\",\n", okumadata.machineId);
    fprintf (outputFile, "    \"startTime\": \"%s\",\n", okumadata.startTime);
    fprintf (outputFile, "    \"status\": \"%s\"\n", okumadata.status);
    fprintf (outputFile, "}\n");

    // Close the output file
    fclose (outputFile);
#ifdef DEBUG
    printf ("Data saved to %s successfully.\n", filename);
#endif
    /* -> This moves to the transmition program <-
        // Define the curl command with the new filename
        char curlCommand[512];
        snprintf(curlCommand, sizeof(curlCommand),
            "curl --location
       'https://api.dev.factoryflow.sinapsis.io/production-tracker' "
            "--header 'Authorization: 96a65a72-9de2-46a6-afb7-8ec9a5da2e8c' "
            "--header 'Content-Type: application/json' "
            "--data @%s", filename);

        // Execute the curl command
        int result = system(curlCommand);
        if (result == -1) {
            perror("Error executing curl command");
            return 1;
        }

        printf("Data sent successfully.\n");
    */
    return 0;
}
