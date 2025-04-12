#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "data.txt"
#define MAX_LENGTH 256

typedef struct {
	char poem[200];
	char rabbit_name[25];
	int eggs;
} PoemData;

void storeData() {
	FILE *file = fopen(FILENAME, "a");
	if (file == NULL) {
		perror("\nError when opening file");
		return;
	}

	PoemData inputData;
	printf("\nPoem: ");
	scanf(" %199[^\n]", inputData.poem);
	printf("\nRabbit name: ");
	scanf(" %24[^\n]", inputData.rabbit_name);
	inputData.eggs = 0;
	
	fprintf(file, "%s,%s,%d\n", inputData.poem, inputData.rabbit_name, inputData.eggs);
	fclose(file);
	printf("\nData stored successfully!\n");
}

void retData() {
	FILE *file = fopen(FILENAME, "r");
	if (file == NULL) {
	perror("\nError when opening file");
		return;
	}

	printf("------------------------------------------------------------------------------------------------------------------\n");
	char line[MAX_LENGTH];
	while (fgets(line, sizeof(line), file)) {
		PoemData outputData;
		sscanf(line, " %199[^,],%24[^,],%d", outputData.poem, outputData.rabbit_name, &outputData.eggs);
		printf("%s\t%s\t%d\n", outputData.poem, outputData.rabbit_name, outputData.eggs);
	}
	
	fclose(file);
}

void remData() {
	FILE *file = fopen(FILENAME, "r");
	if (file == NULL) {
		perror("\nError when opening file");
		return;
	}
	
	FILE *tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		perror("\nError when creating temp file");
		fclose(file);
		return;
	}
	
	char rabbit_name[25];
	printf("\nRabbit entry remove: ");
	scanf(" %24[^\n]", rabbit_name);
	
	char line[MAX_LENGTH];
	int removed = 0;
	while (fgets(line, sizeof(line), file)) {
		PoemData outputData;
		sscanf(line, " %199[^,],%24[^,],%d", outputData.poem, outputData.rabbit_name, &outputData.eggs);
		
		if (strcmp(outputData.rabbit_name, rabbit_name) != 0) {
			fprintf(tempFile, "%s", line);
		} else {
			removed = 1;
		}
	}
	
	fclose(file);
	fclose(tempFile);
	
	remove(FILENAME);
	rename("temp.txt", FILENAME);
	
	if (removed) {
	printf("\nPoem data removed.\n");
	} else {
	printf("\nPoem data not found.\n");
	}
}

void modData() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("\nError when opening file");
        return;
    }
    
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        perror("\nError when creating temp file");
        fclose(file);
        return;
    }
    
    char rabbit_name[25];
    printf("\nRabbit entry modify: ");
    scanf(" %24[^\n]", rabbit_name);
    
    char line[MAX_LENGTH];
    int modified = 0;
    while (fgets(line, sizeof(line), file)) {
        PoemData outputData;
        sscanf(line, "%199[^,],%24[^,],%d", outputData.poem, outputData.rabbit_name, &outputData.eggs);
        
        if (strcmp(outputData.rabbit_name, rabbit_name) != 0) {
            fprintf(tempFile, "%s", line);
        } else {
            PoemData newData = outputData;
            int option;
            do {
                printf("\nModify:\n");
                printf("1. Poem\n");
                printf("2. Name\n");
                printf("3. Eggs count\n");
                printf("4. Exit\n");
                printf("Option: ");
                scanf("%d", &option);
                
                switch (option) {
                    case 1:
                        printf("\nNew poem: ");
                        scanf(" %199[^\n]", newData.poem);
                        break;
                    case 2:
                        printf("\nNew name: ");
                        scanf(" %24[^\n]", newData.rabbit_name);
                        break;
                    case 3:
                        printf("\nNew eggs count: ");
                        scanf("%d", &newData.eggs);
                        break;
                    case 4:
                        printf("\nExiting...\n");
                        break;
                    default:
                        printf("\nInvalid option.\n");
                }
            } while (option != 4);
            
            fprintf(tempFile, "%s,%s,%d\n", newData.poem, newData.rabbit_name, newData.eggs);
            modified = 1;
        }
    }
    
    fclose(file);
    fclose(tempFile);
    
    remove(FILENAME);
    rename("temp.txt", FILENAME);
    
    if (modified) {
        printf("\nPoem data modified.\n");
    } else {
        printf("\nPoem data not found.\n");
    }
}

void mainMenu() {
	int option;
	do {
		printf("\nPoem database\n");
		printf("1. Add new\n");
		printf("2. Retrieve data\n");
		printf("3. Remove data\n");
		printf("4. Modify data\n");
		printf("5. Exit\n");
		printf("Option: ");
		scanf("%d", &option);
		
		switch (option) {
			case 1:
				storeData();
			break;
			case 2:
				retData();
				break;
			case 3:
				remData();
				break;
			case 4:
				modData();
				break;
			case 5:
				printf("\nExiting...\n");
				break;
			default:
				printf("\nInvalid option.\n");
		}
	} while (option != 5);
}

int main() {
	mainMenu();
	return 0;
}