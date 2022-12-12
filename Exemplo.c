#include <stdio.h>

typedef struct Treinador {
    int primaryKey;
    char name[50];
    int age;
} Ttrainer;

typedef struct Pokemon {
    int primaryKey;
    char name[50];
    char type[50];
} Tpoke;

typedef struct Relationship {
    int tPrimaryKey;
    int pokePrimaryKey;
    int level;
    char gender[50];
} Trel;

//Recebe um objeto do tipo trainer e um arquivo para escrever, e escreve o objeto no arquivo.
void saveTrainer(Ttrainer *trainer, FILE *out) {
    fwrite(&trainer->primaryKey, sizeof(int), 1, out);
    fwrite(trainer->name, sizeof(char), sizeof(trainer->name), out);
    fwrite(&trainer->age, sizeof(int), 1, out);
}

//Recebe um objeto do tipo pokémon e um arquivo para escrever, e escreve o objeto no arquivo.
void savePoke(Tpoke *poke, FILE *out) {
    fwrite(&poke->primaryKey, sizeof(int), 1, out);
    fwrite(poke->name, sizeof(char), sizeof(poke->name), out);
    fwrite(poke->type, sizeof(char), sizeof(poke->type), out);
}

//Lê o próximo treinador do arquivo.
Ttrainer *readTrainer(FILE *in) {
    Ttrainer *trainer = (Ttrainer *) malloc(sizeof(Ttrainer)); 
    //Caso a primary key não exista no arquivo returna NULL.
    if (fread(&trainer->primaryKey, sizeof(int), 1, in) <= 0) {
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
    if (fread(&poke->primaryKey, sizeof(int), 1, in) <= 0) {
        free(poke);
        return NULL;
    }

    fread(&poke->name, sizeof(char), sizeof(poke->name), in);
    fread(&poke->type, sizeof(char), sizeof(poke->type), in);

    return poke;
}
