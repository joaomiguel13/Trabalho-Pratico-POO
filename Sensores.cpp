//
// Created by joaom on 02/11/2023.
//

#include "Sensores.h"

int Sensores::nextId = 1;

Sensores::Sensores(char letra,string propriedade, map<string,float> *chaveValor) {
    this->letra = letra;
    this->propriedade = propriedade;
    this->chaveValor = chaveValor;
    id = nextId++;
}


char Sensores::getLetra() const {
    return letra;
}

string Sensores::getNome() const {
    return nome;
}

int Sensores::getId() const {
    return id;
}

float Sensores::getValorAtual(){
    return chaveValor->find(propriedade)->second;
}


Sensores::~Sensores() {
}

void Sensores::resetId() {
    nextId = 1;
}

