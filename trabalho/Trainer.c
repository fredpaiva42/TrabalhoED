#include <stdio.h>
#include <stdlib.h>
#include <trainerStruct.h>

void saveTrainer(Ttrainer *trainer, FILE *out) {
    fwrite(&trainer->registration, sizeof(int), 1, out);
    fwrite(trainer->name, sizeof(char), sizeof(trainer->name), out);
    fwrite(&trainer->age, sizeof(int), 1, out);
}

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

Ttrainer * searchTrainer(int key, FILE * file){
    Ttrainer *result = readTrainer(file);

    while(result -> registration != key && result != NULL){
        result = readTrainer(file);
    }
    return result;
}

void changeTrainer(int key, Ttrainer *reg, FILE *fil) {
    Ttrainer *trainer = (Ttrainer *) malloc(sizeof(Ttrainer));
    while (1) {

        //Caso a primary key não exista no arquivo returna finaliza.
        if (fread(&trainer->registration, sizeof(int), 1, fil) <= 0) {
            free(trainer);
            break;

        //Caso seja a chave procurada, ele altera o conteúdo seguindo o reg recebido como parâmetro e finaliza.
        } else if (trainer->registration == key){
            fwrite(reg->name, sizeof(char), sizeof(reg->name), fil);
            fwrite(&reg->registration, sizeof(int), 1, fil);
            break;
        }

        //Caso não, segue a função normalmente.
        fread(&trainer->name, sizeof(char), sizeof(trainer->name), fil);
        fread(&trainer->age, sizeof(int), 1, fil);
    } 
}