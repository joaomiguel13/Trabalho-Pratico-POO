//
// Created by joaom on 02/11/2023.
//

#include "Processador.h"

int Processador::nextId = 1;


int Processador::getNextId() {
    return nextId;
}

Processador::Processador(string comand, int idZona)  {
    this->idZona = idZona;
    id = nextId++;
    this->comando = comand;
}

int Processador::getId() const {
    return id;
}

int Processador::getIdZona() const {
    return idZona;
}

void Processador::addRegra(Regra *regra) {
    regras.push_back(regra);
}

int Processador::getNumRegras(){
    return regras.size();
}

string Processador::listarRegras() {
    stringstream ss;

    for (const auto &regra: regras) {
        ss << "Regra " << regra->getId() << ": ";
        if(regra->getSensor() != nullptr){
            ss<< "Sensor: "<< regra->getSensor()->getId() << " ";
        }

        if (regra->getTipo() == "igual_a") {
            ss << "igual_a " << regra->getX();
        } else if (regra->getTipo() == "menor_que") {
            ss << "menor_que " << regra->getX();
        } else if (regra->getTipo() == "maior_que") {
            ss << "maior_que " << regra->getX();
        } else if (regra->getTipo() == "entre") {
            ss << "entre " << regra->getX() << " e " << regra->getY();
        } else if (regra->getTipo() == "fora") {
            ss << "fora " << regra->getX() << " e " << regra->getY();
        }

        ss << "\n";
    }
    return ss.str();
}


Processador::~Processador() {
}

bool Processador::removeRegra(int idRegra) {
    for (int i = 0; i < regras.size(); ++i) {
        if (regras[i] != nullptr) {
            if (regras[i]->getId() == idRegra) {
                delete regras[i];
                regras.erase(regras.begin() + i);
                return true;
            }
        }
    }
    return false;
}

void Processador::setComando(string novoComando) {
    comando = novoComando;
}

int Processador::getNumAparelhosAssociados() {
    return aparelhosAssociados.size();
}

string Processador::getComando() {
    return comando;
}

string Processador::associaAparelho(Aparelhos *pAparelhos) {
    for (auto & aparelhosAssociado : aparelhosAssociados) {
        if (aparelhosAssociado->getId() == pAparelhos->getId()) {
            return "Aparelho ja associado";
        }
    }
    aparelhosAssociados.push_back(pAparelhos);
    return "Aparelho associado";
}

string Processador::desassociaAparelho(Aparelhos *pAparelhos) {
    for (int i = 0; i < aparelhosAssociados.size(); ++i) {
        if (aparelhosAssociados[i]->getId() == pAparelhos->getId()) {
            aparelhosAssociados.erase(aparelhosAssociados.begin() + i);
            return "Aparelho desassociado";
        }
    }
    return "Aparelho nao esta associado";
}

Processador *Processador::clone() {
    return new Processador(*this);
}

void Processador::avaliaRegras() {
    for(auto &regra : regras){
        if(regra->getSensor() != nullptr){
            if(!regra->verificar()){
                return;
            }
        }

    }
    for(auto &aparelho : aparelhosAssociados){
        if(comando == "liga"){
            aparelho->setEstado("ligado");
        }
        else if(comando == "desliga"){
            aparelho->setEstado("desligado");
        }
    }
}

void Processador::resetSensor() {
    for(auto &regra : regras){
        regra->resetSensor();
    }
}

void Processador::resetId() {
    nextId = 1;

    for(auto &regra : regras){
        regra->resetId();
    }
}



