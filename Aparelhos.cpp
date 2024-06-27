//
// Created by joaom on 02/11/2023.
//

#include "Aparelhos.h"


int Aparelhos::nextId = 1;

int Aparelhos::getNextId() {
    return nextId;
}

Aparelhos::Aparelhos(string tipoAparelho, char letra, string estado) {
    this->nome = tipoAparelho;
    this->letra = letra;
    this->estado = estado;
    id = nextId++;

    lastCommand = false;
}

char Aparelhos::getLetra() const {
    return letra;
}

string Aparelhos::getNome() const {
    return nome;
}

string Aparelhos::getEstado() const {
    return estado;
}

void Aparelhos::setEstado(string estado) {
    this->estado = estado;
    lastCommand = true;
}

int Aparelhos::getId() const {
    return id;
}

string Aparelhos::getLastCommand() const {
    if(lastCommand){
        if(estado == "ligado")
            return "liga";
        else if(estado == "desligado")
            return "desliga";
    }else{
        return "none";
    }
    return "";
}

Aquecedor::Aquecedor(map<string,float> *valorPropriedade) : Aparelhos("Aquecedor", 'a', "desligado") {
    fezRuido = false;
    this->valorPropriedade = valorPropriedade;
}

Aquecedor::~Aquecedor() {
}

Aspersor::Aspersor(map <string,float> *valorPropriedade) : Aparelhos("Aspersor", 's', "desligado") {
    this->valorPropriedade = valorPropriedade;
    guardaInstante = 0;
    contaDesligado = 0;
}

Aspersor::~Aspersor() {
}

Refrigerador::Refrigerador(map<string,float> *valorPropriedade) : Aparelhos("Refrigerador", 'r', "desligado") {
    this->valorPropriedade = valorPropriedade;
    addRuido = false;
}

Refrigerador::~Refrigerador() {
}

Lampada::Lampada(map<string,float> *valorPropriedade) : Aparelhos("Lampada", 'l', "desligado") {
    this->valorPropriedade = valorPropriedade;
    ligado = false;
}

Lampada::~Lampada() {
}


Aparelhos::~Aparelhos() {
}

void Aparelhos::avancaInstante(int contaInstantes) {

}

void Aparelhos::resetId() {
    nextId = 1;
}

void Aquecedor::avancaInstante(int contaInstantes) {
    if (getEstado() == "ligado") {
        if (!fezRuido) {
            valorPropriedade->at("som") += 5;
            fezRuido = true;
        }
        if (contaInstantes % 3 == 0) {
            if (valorPropriedade->at("temperatura") + 1 <= 50)
                valorPropriedade->at("temperatura") += 1;
            else
                valorPropriedade->at("temperatura") = 50;
        }
    } else if (getEstado() == "desligado") {
        if (fezRuido) {
            fezRuido = false;
            valorPropriedade->at("som") -= 5;
        }
    }
}

void Aspersor::avancaInstante(int contaInstantes){
    if (getEstado() == "ligado") {
        contaDesligado = 0;
        ++guardaInstante;
        if(guardaInstante == 1){
            if(valorPropriedade->at("humidade") + 50 <= 75)
                valorPropriedade->at("humidade") += 50;
            else
                valorPropriedade->at("humidade") = 75;
            valorPropriedade->at("vibracao") += 100;
        }
        else if(guardaInstante == 2){
            valorPropriedade->at("fumo") = 0;
        }
    }
    else if(getEstado() == "desligado"){
        guardaInstante = 0;
        ++contaDesligado;
        if(contaDesligado == 5){
            valorPropriedade->at("vibracao") -= 100;
        }
    }
}

void Refrigerador::avancaInstante(int contaInstantes) {
    if (getEstado() == "ligado") {
        if (contaInstantes % 3 == 0)
            valorPropriedade->at("temperatura") -= 1;
        if(!addRuido){
            valorPropriedade->at("som") += 20;
            addRuido = true;
        }
    }
    else if(getEstado() == "desligado"){
        if(addRuido){
            valorPropriedade->at("som") -= 20;
            addRuido = false;
        }
    }
}

void Lampada::avancaInstante(int contaInstantes) {
    if (getEstado() == "ligado") {
        if(!ligado){
            valorPropriedade->at("luz") += 900;
            ligado = true;
        }
    }
    else if(getEstado() == "desligado"){
        if(ligado){
            valorPropriedade->at("luz") -= 900;
            ligado = false;
        }
    }
}
