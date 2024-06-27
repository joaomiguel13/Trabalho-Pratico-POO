//
// Created by joaom on 02/11/2023.
//

#include "Regra.h"

int Regra::nextId = 1;

Regra::Regra(Sensores &sensor,float x, string nome) {
    this->sensor = &sensor;
    this->x = x;
    this->nome = nome;
    id = nextId++;
}

Regra::Regra(Sensores &sensor, string nome) {
    this->sensor = &sensor;
    this->nome = nome;
    id = nextId++;
}

float Regra::getX() {
    return x;
}

float Regra::getY() {
    return 0;
}

string Regra::getTipo() {
    return nome;
}

bool Regra::verificar() {
    if(nome == "igual_a"){
        return sensor->getValorAtual() == x;
    }else if(nome == "menor_que"){
        return sensor->getValorAtual() < x;
    }else if(nome == "maior_que"){
        return sensor->getValorAtual() > x;
    }
    return false;
}

RegraEntre::RegraEntre(Sensores &sensor, float x, float y) : Regra(sensor, "entre") {
    this->x = x;
    this->y = y;
}

float RegraEntre::getX()  {
    return x;
}

float RegraEntre::getY()  {
    return y;
}

bool RegraEntre::verificar() {
    return sensor->getValorAtual() > x && sensor->getValorAtual() < y;
}

RegraFora::RegraFora(Sensores &sensor, float x, float y) : Regra(sensor, "fora" ) {
    this->x = x;
    this->y = y;
}

float RegraFora::getX() {
    return x;
}

float RegraFora::getY(){
    return y;
}

bool RegraFora::verificar() {
    return sensor->getValorAtual() < x || sensor->getValorAtual() > y;
}


int Regra::getId() const {
    return id;
}

Sensores* Regra::getSensor() {
    return sensor;
}

void Regra::resetSensor() {
    sensor = nullptr;
}

void Regra::resetId() {
    nextId = 1;
}

