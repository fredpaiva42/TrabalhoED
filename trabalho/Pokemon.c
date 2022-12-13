#include <stdio.h>
#include <stdlib.h>
#include <pokemonStruct.h>

void savePoke(Tpoke *poke, FILE *out) {
    fwrite(&poke->pokeID, sizeof(int), 1, out);
    fwrite(poke->name, sizeof(char), sizeof(poke->name), out);
    fwrite(poke->type, sizeof(char), sizeof(poke->type), out);
}

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

Tpoke * searchPoke(int key, FILE *file){
    Tpoke *result = readPoke(file);

    while (result -> pokeID != key && result != NULL){
        result = readPoke(file);
    }
    return result;
}

void changePoke(int key, Tpoke *reg, FILE *fil) {
    Tpoke *poke = (Tpoke *) malloc(sizeof(Tpoke));
    while (1) {

        //Caso a primary key não exista no arquivo returna finaliza.
        if (fread(&poke->pokeID, sizeof(int), 1, fil) <= 0) {
            free(poke);
            break;

        //Caso seja a chave procurada, ele altera o conteúdo seguindo o reg recebido como parâmetro e finaliza.
        } else if (poke->pokeID == key){
            fwrite(reg->name, sizeof(char), sizeof(reg->name), fil);
            fwrite(reg->type, sizeof(char), sizeof(reg->type), fil);
            break;
        }

        //Caso não, segue a função normalmente.
        fread(&poke->name, sizeof(char), sizeof(poke->name), fil);
        fwrite(reg->type, sizeof(char), sizeof(reg->type), fil);
    } 
}