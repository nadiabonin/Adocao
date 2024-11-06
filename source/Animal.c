#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "/workspaces/Adocao/include/animal.h"
#include "/workspaces/Adocao/include/config.h"

void gravarAnimal(FILE *file, struct Animal animal);
int incluirNovoAnimal(FILE* file, struct Animal animal, int ultimoID);
int lerUltimoID(FILE* file);
void lerAnimal(FILE* file, struct Animal * ptrAnimal);
int desativarAnimal(struct Animal animal, int id);
void VaiParaIncluirAnimal(FILE *arquivo_animal);
struct Animal LerDadosAnimalX(); 
int incluirNovoAnimalX(FILE* file, struct Animal animal);
int lerUltimoIDX(FILE* file);

//gravar um animal no struct
void gravarAnimal(FILE *file, struct Animal animal) {

    printf("Cadastrar um animal novo!\n");

    //especie do animal, usando enum
    char variavel1;
    do {
        printf("Digite a especie do animal, so pode G para gato, C para cachorro: ");
        scanf(" %c", &variavel1);
        if (variavel1 == 'G' || variavel1 == 'g') {
            animal.especie = gato;
        } else if (variavel1 == 'C' || variavel1 == 'c') {
            animal.especie = cachorro;
        } else {
            printf("Entrada inválida. APENAS G ou C.\n");
        }
    } while (variavel1 != 'G' && variavel1 != 'g' && variavel1 != 'C' && variavel1 != 'c');
    getchar();

    printf("Digite o nome do animal: ");
    fgets(animal.nome, sizeof(animal.nome), stdin);
    animal.nome[strcspn(animal.nome, "\n")] = '\0';

    printf("Digite a raça do animal: ");
    fgets(animal.raca, sizeof(animal.raca), stdin);
    animal.raca[strcspn(animal.raca, "\n")] = '\0';

    printf("Digite a descrição do animal: ");
    fgets(animal.descricao, sizeof(animal.descricao), stdin);
    animal.descricao[strcspn(animal.descricao, "\n")] = '\0';
    //animal automaticamente disponivel pra adoção
    animal.status = Disponivel;

    fprintf(file, "%d|%c|%c|%s|%s|%s\n", animal.ID, animal.especie, animal.status, animal.nome, animal.raca, animal.descricao);
}

// incluir um novo animal no arquivo e atualizar o último id
int incluirNovoAnimal(FILE* file, struct Animal animal, int ultimoID) {
    fseek(file, 0, SEEK_END);
    animal.ID = ultimoID + 1;
    gravarAnimal(file, animal);
    return animal.ID;
}

// ler o último id salvo no arquivo
int lerUltimoID(FILE* file) {
    char str[300];
    int ultimoID = 0;

    fseek(file, 0, SEEK_SET);
    while (fgets(str, sizeof(str), file) != NULL) {
        char *token = strtok(str, "|");
        if (token != NULL) {
            ultimoID = atoi(token);
        }
    }
    return ultimoID;
}

// le as informaçoes no arquivo, separa por | e os coloca em ponteiros para variaveis q vao ter as informaçoes dos animais
void lerAnimal(FILE* file, struct Animal * ptrAnimal) {
    char str[300];

    if (fgets(str, sizeof(str), file) == NULL) {
        return;
    }

    char *token = strtok(str, "|");
    if (token != NULL) {
        ptrAnimal->ID = atoi(token);
    }

    token = strtok(NULL, "|");
    if (token != NULL) {
        strncpy(ptrAnimal->nome, token, sizeof(ptrAnimal->nome) - 1);
        ptrAnimal->nome[sizeof(ptrAnimal->nome) - 1] = '\0';
    }

    token = strtok(NULL, "|");
    if (token != NULL) {
        strncpy(ptrAnimal->raca, token, sizeof(ptrAnimal->raca) - 1);
        ptrAnimal->raca[sizeof(ptrAnimal->raca) - 1] = '\0';
    }

    token = strtok(NULL, "|");
    if (token != NULL) {
        strncpy(ptrAnimal->descricao, token, sizeof(ptrAnimal->descricao) - 1);
        ptrAnimal->descricao[sizeof(ptrAnimal->descricao) - 1] = '\0';
    }



}

int desativarAnimal(struct Animal animal, int id) {
    //buscar pelo id e desativar o animal = animal adotado
    animal.status = Adotado;
    return 0;
}

void MenuAnimal() {

    FILE *arquivo_animal = fopen(ArqAnimal, "a+");
    if (arquivo_animal == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return -1;
    }

    while(1)
    {
        char opcao = ' ';

        printf("1. Incluir Animal");
        printf("2. Excluir Animal");
        printf("3. Listar Animais");
        printf("4. Retornar");

        printf("Digite uma opção: ");
        scanf("%c", &opcao);

        switch (opcao)
        {
            case '1':
                VaiParaIncluirAnimal(arquivo_animal);
                break;
            
            case '2':
                break;
            
            case '3':
                break;
            
            case '4':
                fclose(arquivo_animal);
                return 1;

            default:
                printf("... Tente novamente");
                break;
        }
    }

    return 1;
}

void VaiParaIncluirAnimal(FILE *arquivo_animal)
{
    struct Animal animal = LerDadosAnimalX();
    incluirNovoAnimalX(arquivo_animal, animal);
}


struct Animal LerDadosAnimalX() 
{
    struct Animal animal;

    printf("Cadastrar um animal novo!\n");

    //especie do animal, usando enum
    char variavel1;
    do {
        printf("Digite a especie do animal, so pode G para gato, C para cachorro: ");
        scanf(" %c", &variavel1);
        if (variavel1 == 'G' || variavel1 == 'g') {
            animal.especie = gato;
        } else if (variavel1 == 'C' || variavel1 == 'c') {
            animal.especie = cachorro;
        } else {
            printf("Entrada inválida. APENAS G ou C.\n");
        }
    } while (variavel1 != 'G' && variavel1 != 'g' && variavel1 != 'C' && variavel1 != 'c');
    getchar();

    printf("Digite o nome do animal: ");
    fgets(animal.nome, sizeof(animal.nome), stdin);
    animal.nome[strcspn(animal.nome, "\n")] = '\0';

    printf("Digite a raça do animal: ");
    fgets(animal.raca, sizeof(animal.raca), stdin);
    animal.raca[strcspn(animal.raca, "\n")] = '\0';

    printf("Digite a descrição do animal: ");
    fgets(animal.descricao, sizeof(animal.descricao), stdin);
    animal.descricao[strcspn(animal.descricao, "\n")] = '\0';
    //animal automaticamente disponivel pra adoção
    animal.status = Disponivel;

    return animal;
}

int incluirNovoAnimalX(FILE* file, struct Animal animal) {
    int ultimoId = lerUltimoIDX(file);
    fseek(file, 0, SEEK_END);
    animal.ID = ultimoId + 1;

    fprintf(file, "%d|%c|%c|%s|%s|%s\n", animal.ID, animal.especie, animal.status, animal.nome, animal.raca, animal.descricao);

    return animal.ID;
}

int lerUltimoIDX(FILE* file) {
    char str[300];
    int ultimoId = 0;

    fseek(file, 0, SEEK_SET);
    while (fgets(str, sizeof(str), file) != NULL) {
        char *token = strtok(str, "|");
        if (token != NULL) {
            ultimoId = atoi(token);
        }
    }
    return ultimoId;
}

