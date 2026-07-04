#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// =============================================
// HASH TABLE with linear probing
// =============================================

typedef struct {
    char *key;
    char *value;
} HashNode;

static HashNode DELETED_NODE = {NULL, NULL};
#define DELETED (&DELETED_NODE)

unsigned int hash_function(const char *key, int table_size) {
    unsigned long hash = 5381;
    int c;
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + (unsigned char)c; // hash * 33 + c
    }
    return hash % table_size;
}

void free_hash_table(HashNode **table, int size) {
    if (table == NULL) return;
    for (int i = 0; i < size; ++i) {
        if (table[i] && table[i] != DELETED) {
            free(table[i]->key);
            free(table[i]->value);
            free(table[i]);
        }
    }
    free(table);
}

HashNode** create_hash_table(int size) {
    if (size <= 0) return NULL;
    return calloc(size, sizeof(HashNode*));
}

// Helper function to safely delete one entry
void delete_entry(HashNode **table, int pos) {
    if (table[pos] && table[pos] != DELETED) {
        free(table[pos]->key);
        free(table[pos]->value);
        free(table[pos]);
        table[pos] = DELETED;
    }
}

int main() {
    HashNode **hash_table = NULL;
    int table_size = 0;
    char command[64];

    printf("=== Hash Table ===\n\n");
    printf("Commands:\n");
    printf("  create     - create a new table\n");
    printf("  add        - add or update a key-value pair\n");
    printf("  search     - find value by key\n");
    printf("  delete     - delete entry (multiple options)\n");
    printf("  print      - display the entire table\n");
    printf("  save       - save to database.txt\n");
    printf("  load       - load from database.txt\n");
    printf("  exit       - exit the program\n\n");

    while (1) {
        printf("> ");
        if (scanf("%63s", command) != 1) break;

        // ====================== CREATE ======================
        if (strcmp(command, "create") == 0) {
            free_hash_table(hash_table, table_size);
            
            printf("Enter table size: ");
            if (scanf("%d", &table_size) != 1 || table_size <= 0) {
                printf("Error: size must be > 0\n");
                table_size = 0;
                hash_table = NULL;
            } else {
                hash_table = create_hash_table(table_size);
                if (hash_table) {
                    printf("Table created successfully (size: %d)\n", table_size);
                }
            }
        }

        // ====================== PRINT ======================
        else if (strcmp(command, "print") == 0) {
            if (!hash_table) {
                printf("Create a table first!\n");
                continue;
            }
            printf("\n=== Hash Table Content ===\n");
            for (int i = 0; i < table_size; ++i) {
                if (hash_table[i] == DELETED) {
                    printf("[%2d] <DELETED>\n", i);
                } else if (hash_table[i]) {
                    printf("[%2d] %s -> %s\n", i, hash_table[i]->key, hash_table[i]->value);
                } else {
                    printf("[%2d] <empty>\n", i);
                }
            }
        }

        // ====================== ADD ======================
        else if (strcmp(command, "add") == 0) {
            if (!hash_table) {
                printf("Create a table first!\n");
                continue;
            }

            char key[256], value[256];
            printf("Key: ");
            scanf(" %255s", key);
            printf("Value: ");
            scanf(" %255s", value);

            unsigned int hash = hash_function(key, table_size);
            int first_deleted = -1;
            int target = -1;
            bool found = false;

            for (int i = 0; i < table_size && !found; ++i) {
                int pos = (hash + i) % table_size;

                if (hash_table[pos] == DELETED) {
                    if (first_deleted == -1) first_deleted = pos;
                }
                else if (hash_table[pos] && strcmp(hash_table[pos]->key, key) == 0) {
                    free(hash_table[pos]->value);
                    hash_table[pos]->value = strdup(value);
                    printf("Value updated for key '%s'\n", key);
                    found = true;
                }
                else if (hash_table[pos] == NULL) {
                    target = pos;
                    break;
                }
            }

            if(!found){
                if (target == -1 && first_deleted != -1) target = first_deleted;

            if (target != -1) {
                hash_table[target] = malloc(sizeof(HashNode));
                if (hash_table[target]) {
                    hash_table[target]так->key = strdup(key);
                    hash_table[target]->value = strdup(value);
                    printf("Added: '%s' -> '%s' (index %d)\n", key, value, target);
                }
            }else 
                printf("Error: table is full!\n");
        }
    

        // ====================== SEARCH ======================
        else if (strcmp(command, "search") == 0) {
            if (!hash_table) {
                printf("Table not created yet!\n");
                continue;
            }

            char option;
            printf("A - search by key\n");
            printf("B - search by index\n");
            scanf(" %c", &option);

            if (option == 'A' || option == 'a') {
                char key[256];
                printf("Enter key: ");
                scanf(" %255s", key);

                unsigned int hash = hash_function(key, table_size);
                int found = 0;

                for (int i = 0; i < table_size; ++i) {
                    int pos = (hash + i) % table_size;
                    if (hash_table[pos] == NULL) break;
                    if (hash_table[pos] != DELETED && strcmp(hash_table[pos]->key, key) == 0) {
                        printf("Found! Index %d: %s\n", pos, hash_table[pos]->value);
                        found = 1;
                        break;
                }
            }
                if (!found) printf("Key '%s' not found\n", key);
        }
            else if (option == 'B' || option == 'b') {
                int index;
                printf("Enter index: ");
                scanf(" %d", &index);
                if (index < 0 || index >= table_size) 
                    printf("Error: index out of bounds\n");
                else {
                    if (hash_table[index] == NULL || hash_table[index] == DELETED)
                        printf("The index is not initialized");
                    else 
                        printf("Key(%s) and Value(%s)", hash_table[index]->key, hash_table[index]->value);
                }
            }
            else
                printf("Invalid option\n");
            
    }


        // ====================== DELETE ======================
        else if (strcmp(command, "delete") == 0) {
            if (!hash_table) {
                printf("Table not created yet!\n");
                continue;
            }

            char option;
            printf("A - delete by key\n");
            printf("B - delete by index\n");
            printf("C - delete all entries\n");
            printf("D - delete entire table\n");
            printf("Choose option: ");
            scanf(" %c", &option);

            if (option == 'A' || option == 'a') {
                char key[256];
                printf("Enter key: ");
                scanf(" %255s", key);

                unsigned int hash = hash_function(key, table_size);
                int deleted = 0;

                for (int i = 0; i < table_size; ++i) {
                    int pos = (hash + i) % table_size;
                    if (hash_table[pos] == NULL) break;
                    if (hash_table[pos] != DELETED && strcmp(hash_table[pos]->key, key) == 0) {
                        delete_entry(hash_table, pos);
                        printf("Key '%s' deleted\n", key);
                        deleted = 1;
                        break;
                    }
                }
                if (!deleted) printf("Key '%s' not found\n", key);
            }
            else if (option == 'B' || option == 'b') {
                int index;
                printf("Enter index: ");
                scanf("%d", &index);

                if (index < 0 || index >= table_size) {
                    printf("Error: index out of bounds\n");
                } else {
                    delete_entry(hash_table, index);
                    printf("Entry at index %d deleted\n", index);
                }
            }
            else if (option == 'C' || option == 'c') {
                for (int i = 0; i < table_size; ++i) {
                    delete_entry(hash_table, i);
                }
                printf("All entries deleted\n");
            }
            else if (option == 'D' || option == 'd') {
                free_hash_table(hash_table, table_size);
                hash_table = NULL;
                table_size = 0;
                printf("Entire hash table deleted\n");
            }
            else {
                printf("Invalid option\n");
            }
        }

        // ====================== SAVE ======================
        else if (strcmp(command, "save") == 0) {
            if (!hash_table) {
                printf("Nothing to save\n");
                continue;
            }
            FILE *f = fopen("database.txt", "w");
            if (!f) {
                printf("Failed to open file\n");
                continue;
            }
            fprintf(f, "%d\n", table_size);
            for (int i = 0; i < table_size; ++i) {
                if (hash_table[i] && hash_table[i] != DELETED) {
                    fprintf(f, "%d %s %s\n", i, hash_table[i]->key, hash_table[i]->value);
                }
            }
            fclose(f);
            printf("Table saved to database.txt\n");
        }

        // ====================== LOAD ======================
        else if (strcmp(command, "load") == 0) {
            FILE *f = fopen("database.txt", "r");
            if (!f) {
                printf("database.txt not found\n");
                continue;
            }

            free_hash_table(hash_table, table_size);
            if (fscanf(f, "%d", &table_size) != 1 || table_size <= 0) {
                printf("Error reading file\n");
                fclose(f);
                continue;
            }

            hash_table = create_hash_table(table_size);
            if (!hash_table) {
                fclose(f);
                continue;
            }

            int idx;
            char key[256], value[256];
            while (fscanf(f, "%d %255s %255s", &idx, key, value) == 3) {
                if (idx >= 0 && idx < table_size) {
                    if (hash_table[idx]) {
                        free(hash_table[idx]->key);
                        free(hash_table[idx]->value);
                        free(hash_table[idx]);
                    }
                    hash_table[idx] = malloc(sizeof(HashNode));
                    if (hash_table[idx]) {
                        hash_table[idx]->key = strdup(key);
                        hash_table[idx]->value = strdup(value);
                    }
                }
            }
            fclose(f);
            printf("Data loaded successfully\n");
        }

        // ====================== EXIT ======================
        else if (strcmp(command, "exit") == 0) {
            free_hash_table(hash_table, table_size);
            printf("Goodbye!\n");
            break;
        }

        else {
            printf("Unknown command. Type 'print' for help.\n");
        }
    }

    return 0;
}
}
