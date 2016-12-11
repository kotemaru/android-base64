// APL/2.0

#include <stdio.h>
#include <string.h>
#include "base64.h"

static const char *USAGE = "usage";

static int encode(const char *fileName) {
    char inBuff[101];
    char outBuff[101];
    FILE *inFile = fopen(fileName, "r");
    if (inFile == NULL) throw "Can not open file.";
    int n = 0;
    while ((n = fread(inBuff, 1, 57, inFile)) > 0) {
        base64_encode(outBuff, 100, (const uint8_t *) inBuff, n);
        printf("%s\n", outBuff);
    }
    if (ferror(inFile) != 0) throw "Fail read.";
    fclose(inFile);
    return 0;
}

static int decode(const char *fileName) {
    char inBuff[101];
    char outBuff[101];
    FILE *outFile = fopen(fileName, "w");
    if (outFile == NULL) throw "Can not open file.";
    int total = 0;
    while (gets(inBuff) != NULL) {
        if (strlen(inBuff) == 0) break;
        if (inBuff[0] == '=') break;

        int n = base64_decode((uint8_t *) outBuff, inBuff, 100);
        total += n;
        fwrite(outBuff, 1, n, outFile);
        fflush(outFile);
        if (ferror(outFile) != 0) throw "Fail write.";
    }
    fclose(outFile);
    printf("\nSuccess: decode %s %dBytes\n", fileName, total);
    return 0;
}

int main(int argc, char *argv[]) {
    try {
        if (argc == 2) {
            return encode(argv[1]);
        } else if (argc == 3 && strcmp(argv[1], "-d") == 0) {
            return decode(argv[2]);
        } else {
            throw USAGE;
        }
    } catch (const char *err) {
        if (err == USAGE) {
            printf("Usage: base64 [-d] <file>\n    -d : decode.");
        } else {
            printf("Error: %s\n", err);
        }
        return 1;
    }
}
