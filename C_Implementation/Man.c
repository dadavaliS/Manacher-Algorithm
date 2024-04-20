#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* preprocessString(const char *s) {
    int length = strlen(s);
    char *processed = malloc((2 * length + 4) * sizeof(char)); // Allocate memory for processed string
    if(processed == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    
    int j = 0;
    processed[j++] = '^';
    for (int i = 0; i < length; ++i) {
        processed[j++] = '#';
        processed[j++] = s[i];
    }
    processed[j++] = '#';
    processed[j++] = '$';
    processed[j] = '\0'; // Null-terminate the string
    return processed;
}

char* manacher(const char *s) {
    char* processed = preprocessString(s);
    int n = strlen(processed);
    int* P = malloc(n * sizeof(int)); // Allocate memory for the P array
    if(P == NULL) {
        printf("Memory allocation failed\n");
        free(processed); // Free allocated memory before exiting
        exit(1);
    }

    int center = 0, right = 0;

    for (int i = 1; i < n - 1; ++i) {
        int mirror = 2 * center - i;

        P[i] = (i < right) ? (right - i < P[mirror] ? right - i : P[mirror]) : 0;

        while (processed[i + (1 + P[i])] == processed[i - (1 + P[i])])
            P[i]++;

        if (i + P[i] > right) {
            center = i;
            right = i + P[i];
        }
    }

    int maxLen = 0, centerIndex = 0;
    for (int i = 1; i < n - 1; ++i) {
        if (P[i] > maxLen) {
            maxLen = P[i];
            centerIndex = i;
        }
    }
    
    free(P); // Free allocated memory for P array

    char* result = malloc((maxLen + 1) * sizeof(char)); // Allocate memory for result string
    if(result == NULL) {
        printf("Memory allocation failed\n");
        free(processed); // Free allocated memory before exiting
        exit(1);
    }
    
    memcpy(result, &s[(centerIndex - 1 - maxLen) / 2], maxLen); // Copy the substring into result
    result[maxLen] = '\0'; // Null-terminate the string
    
    free(processed); // Free allocated memory for processed string
    return result;
}

int main() {
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening the input file");
        return 1;
    }

    char inputString[100];
    while (fgets(inputString, sizeof(inputString), inputFile) != NULL) {
        // Remove trailing newline character
        if(inputString[strlen(inputString) - 1] == '\n')
            inputString[strlen(inputString) - 1] = '\0';

        char* result = manacher(inputString);
        printf("Longest palindromic substring for \"%s\": %s\n", inputString, result);
        free(result); // Free allocated memory for result string
    }

    fclose(inputFile);
    return 0;
}
