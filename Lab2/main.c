#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 1201
#define CPF_LENGTH 11

long long int hashTable[TABLE_SIZE] = {0};

int hashFunction(long long int cpf) {
    if (cpf < 0) cpf = -cpf;
    return cpf % TABLE_SIZE;
}

void removeNonNumericChars(char *str) {
    int i, j = 0;
    for (i = 0; str[i]; i++) {
        if (isdigit((unsigned char)str[i])) {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

long long int convertToInteger(char *cpfStr) {
    char *endptr;
    long long int cpf = strtoll(cpfStr, &endptr, 10);
    if (*endptr != '\0') return -1;
    return cpf;
}

int insert(long long int cpf) {
    int index = hashFunction(cpf);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int pos = (index + i) % TABLE_SIZE;
        if (hashTable[pos] == 0) {
            hashTable[pos] = cpf;
            printf("CPF %lld inserido na posição %d\n", cpf, pos);
            return 0;
        } else if (hashTable[pos] == cpf) {
            printf("CPF %lld já está na tabela (posição %d)\n", cpf, pos);
            return 0;
        }
    }
    printf("Tabela cheia! Não foi possível inserir CPF %lld\n", cpf);
    return -1;
}

int main() {
    FILE *file = fopen("milcpfs.txt", "r");
    if (!file) {
        perror("Erro ao abrir o arquivo de CPFs");
        return 1;
    }

    char cpfStr[CPF_LENGTH + 10];
    long long int cpf;

    while (fscanf(file, "%20s", cpfStr) != EOF) {
        removeNonNumericChars(cpfStr);
        if (strlen(cpfStr) != CPF_LENGTH) {
            printf("CPF inválido: %s\n", cpfStr);
            continue;
        }

        cpf = convertToInteger(cpfStr);
        if (cpf == -1) {
            printf("Erro ao converter CPF: %s\n", cpfStr);
            continue;
        }

        printf("Lendo CPF: %lld\n", cpf);
        insert(cpf);
    }

    fclose(file);
    return 0;
}
