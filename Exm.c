#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


void decryptFile(const char* filename, int key) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    

    char* encryptedData = (char*)malloc(fileSize);
    fread(encryptedData, 1, fileSize, file);
    fclose(file);

    char* decryptedData = (char*)malloc(fileSize);
    int i;
    for (i = 0; i < fileSize; i++) {
        decryptedData[i] = encryptedData[i] ^ key;
    }


    printf("Decrypted data:\n%s\n", decryptedData);

    free(encryptedData);
    free(decryptedData);
}

int main() {
    const char* filename = "Encrypted3.txt";
    int final_key = -1; 

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open the file.\n");
        return 1;
    }

    int key;
    for (key = 0; key < 256; key++) {
        fseek(file, 0, SEEK_SET);  

        int meaningful_content = 1;
        int character;
        while ((character = fgetc(file)) != EOF) {
            int decrypted = character ^ key;
			          
            if (!isprint(decrypted) && !isspace(decrypted)) {
                meaningful_content = 0;
                break;
            }
        }

        if (meaningful_content) {
            final_key = key;
            break;  
        }
    }

    if (final_key != -1) {
        printf("Correct key found: %d\n", final_key);
        decryptFile(filename, final_key);
    } else {
        printf("Unable to find the correct key.\n");
    }

    fclose(file);
    return 0;
}
