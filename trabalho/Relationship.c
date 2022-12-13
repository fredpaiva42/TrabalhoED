#include <stdio.h>
#include <stdlib.h>
#include <trainerStruct.h>
#include <pokemonStruct.h>
#include <relationshipStruct.h>

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

Trel *searchRel(int trainerKey, int pokeKey, FILE * file){
    Trel *result = readRel(file);

    while (result -> registrationPK && result -> pokeIDPK && result != NULL){
        result = readRel(file);
    }

    // Se retorna nulo, os dois não tem relação registrada
    return result;
}

void changeRel(int key, Trel *reg, FILE *fil) {
    Trel *rel = (Trel *) malloc(sizeof(Trel));

    while (1) {

        //Caso a primary key não exista no arquivo returna finaliza.
        if (fread(&rel->primaryKey, sizeof(int), 1, fil) <= 0) {
            free(rel);
            break;

        //Caso seja a chave procurada, ele altera o conteúdo seguindo o reg recebido como parâmetro e finaliza.
        } else if (rel->primaryKey == key) { 
            fwrite(reg->registrationPK, sizeof(int), 1, fil);
            fwrite(reg->pokeIDPK, sizeof(int), 1, fil);
            fwrite(reg->level, sizeof(int), 1, fil);
            fwrite(reg->gender, sizeof(char), sizeof(reg->gender), fil);
            break;
        }

        //Caso não, segue a função normalmente.
        fwrite(reg->registrationPK, sizeof(int), 1, fil);
        fwrite(reg->pokeIDPK, sizeof(int), 1, fil);
        fwrite(reg->level, sizeof(int), 1, fil);
        fwrite(reg->gender, sizeof(char), sizeof(reg->gender), fil);
    }
}