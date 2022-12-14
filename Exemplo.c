#include <stdio.h>
#include <stdlib.h>

typedef struct Treinador {
    int registration;
    char name[50];
    int age;
} Ttrainer;

typedef struct Pokemon {
    int pokeID;
    char name[50];
    char type[50];
} Tpoke;

typedef struct Relationship {
    int primaryKey;
    int registrationPK;
    int pokeIDPK;
    int level;
    char gender[50];
} Trel;

//Recebe um objeto do tipo trainer e um arquivo para escrever, e escreve o objeto no arquivo.
void saveTrainer(Ttrainer *trainer, FILE *out) {
    fwrite(&trainer->registration, sizeof(int), 1, out);
    fwrite(trainer->name, sizeof(char), sizeof(trainer->name), out);
    fwrite(&trainer->age, sizeof(int), 1, out);
}

//Recebe um objeto do tipo pokémon e um arquivo para escrever, e escreve o objeto no arquivo.
void savePoke(Tpoke *poke, FILE *out) {
    fwrite(&poke->pokeID, sizeof(int), 1, out);
    fwrite(poke->name, sizeof(char), sizeof(poke->name), out);
    fwrite(poke->type, sizeof(char), sizeof(poke->type), out);
}

// Recebe um objeto do tipo pokémon e um do tipo treinador, um arquivo

//Lê o próximo treinador do arquivo.
Ttrainer *readTrainer(FILE *in) {
    Ttrainer *trainer = (Ttrainer *) malloc(sizeof(Ttrainer)); 
    //Caso a primary key não exista no arquivo returna NULL.
    if (fread(&trainer->registration, sizeof(int), 1, in) <= 0) {
        free(trainer);
        return NULL;
    }

    fread(&trainer->name, sizeof(char), sizeof(trainer->name), in);
    fread(&trainer->age, sizeof(int), 1, in);

    return trainer;
}

//Lê o próximo treinador do arquivo.
Tpoke *readPoke(FILE *in) {
    Tpoke *poke = (Tpoke *) malloc(sizeof(Tpoke)); 
    //Caso a primary key não exista no arquivo returna NULL.
    if (fread(&poke->pokeID, sizeof(int), 1, in) <= 0) {
        free(poke);
        return NULL;
    }

    fread(&poke->name, sizeof(char), sizeof(poke->name), in);
    fread(&poke->type, sizeof(char), sizeof(poke->type), in);

    return poke;
}

Trel * createRel(Ttrainer * trainer, Tpoke * pokemon, int key, int lvl, char gend[]){
    Trel * new = (Trel *) malloc(sizeof(Trel));
    new -> registrationPK = trainer -> registration;
    new -> pokeIDPK = pokemon -> pokeID;
    new -> primaryKey = key;
    new -> level = lvl;

    *new -> gender = *gend;

    return new;
}

void saveRel(Trel * relation, FILE * out){
    fwrite(&relation-> primaryKey, sizeof(int), 1, out);
    fwrite(&relation -> registrationPK, sizeof(int), 1, out);
    fwrite(&relation -> pokeIDPK, sizeof(int), 1, out);
    fwrite(&relation -> level, sizeof(int), 1, out);
    fwrite(relation-> gender, sizeof(char), sizeof(relation->gender), out);
}

//Lê a próxima relação do arquivo
Trel *readRel(FILE * in){
    Trel * relation = (Trel *) malloc(sizeof(Trel));
    // Caso a primary key não exista no arquivo retorna NULL.
    if (fread(&relation -> primaryKey, sizeof(int), 1, in) <= 0){
        free(relation);
        return NULL;
    }

    fread(&relation -> registrationPK, sizeof(int), 1 ,in);
    fread(&relation -> pokeIDPK, sizeof(int), 1 ,in);
    fread(&relation -> level, sizeof(int), 1 ,in);
    fread(&relation -> gender, sizeof(char ), sizeof(relation ->gender),in);

    return relation;
}


// Busca um Pokémon no arquivo
Tpoke * searchPoke(int key, FILE *file){
    Tpoke *result = readPoke(file);

    while (result -> pokeID != key && result != NULL){
        result = readPoke(file);
    }
    return result;
}

// Busca um Treinador no arquivo
Ttrainer * searchTrainer(int key, FILE * file){
    Ttrainer *result = readTrainer(file);

    while(result -> registration != key && result != NULL){
        result = readTrainer(file);
    }
    return result;
}

Trel *searchRel(int trainerKey, int pokeKey, FILE * file){
    Trel *result = readRel(file);

    while (result -> registrationPK && result -> pokeIDPK && result != NULL){
        result = readRel(file);
    }

    // Se retorna nulo, os dois não tem relação registrada
    return result;
}


void search(int trainerKey, int pokeKey, FILE * file){
    Ttrainer * resultTrainer = searchTrainer(trainerKey, file);
    Tpoke  * resultPoke = searchPoke(pokeKey, file);
    Trel * result = searchRel(resultTrainer -> registration, resultPoke -> pokeID, file);

    if(result != NULL){
        printf("Treinador:\n");
        printf("%d\n", resultTrainer -> registration);
        printf("%s\n", resultTrainer -> name);
        printf("%d\n", resultTrainer -> age);
        printf("\n");

        printf("Pokémon: \n");
        printf("%d\n", resultPoke -> pokeID);
        printf("%s\n", resultPoke -> name);
        printf("%s\n", resultPoke -> type);
        printf("\n");

        printf("Relacionamento: \n");
        printf("%d\n", result -> primaryKey);
        printf("%d\n", result -> registrationPK);
        printf("%d\n", result -> pokeIDPK);
        printf("%d\n", result -> level);
        printf("%s\n", result -> gender);
        printf("\n");
    }
}