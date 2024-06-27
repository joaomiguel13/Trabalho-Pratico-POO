//
// Created by joaom on 02/11/2023.
//

#include "PropriedadesAmbiente.h"

PropriedadesAmbiente::PropriedadesAmbiente(string nome, string unidade, float min, float max, float atual) {
    this->nome = nome;
    this->unidade = unidade;
    this->min = min;
    this->max = max;
    this->atual = atual;
}

PropriedadesAmbiente::~PropriedadesAmbiente() {

}

string PropriedadesAmbiente::getNome() const {
    return nome;
}

string PropriedadesAmbiente::getUnidade() const {
    return unidade;
}

float PropriedadesAmbiente::getMin() const {
    return min;
}

float PropriedadesAmbiente::getMax() const {
    return max;
}

float PropriedadesAmbiente::getAtual() const {
    return atual;
}

string PropriedadesAmbiente::toString() {
    stringstream ss;
    ss << "Nome: " << nome + "\n";
    ss << "Valor atual: " << to_string(atual)+ ";" + to_string(min) + ";" + to_string(max) + "\n";
    ss << "Unidade: " << unidade + "\n";
    return ss.str();
}

void PropriedadesAmbiente::alteraValor(float valor) {
    if(valor >= min){
        atual = valor;
    }
}


Humidade::Humidade(float min, float max, float atual) : PropriedadesAmbiente("humidade", "%", min, max, atual) {

}

void Humidade::alteraValor(float valor) {
    if(valor >= min && valor <= max){
        atual = valor;
    }
}

Humidade::~Humidade() {

}

Fumo::Fumo(float min, float max, float atual) : PropriedadesAmbiente("fumo", "Obscuracao(%)", min, max, atual) {

}

void Fumo::alteraValor(float valor) {
    if(valor >= min && valor <= max){
        atual = valor;
    }
}

Fumo::~Fumo() {

}