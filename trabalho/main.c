#include <stdio.h>
#include <stdlib.h>
#include <trainerStruct.h>
#include <pokemonStruct.h>
#include <relationshipStruct.h>

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