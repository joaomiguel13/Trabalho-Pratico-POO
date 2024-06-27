//
// Created by joaom on 02/11/2023.
//

#ifndef TP_PROPRIEDADESAMBIENTE_H
#define TP_PROPRIEDADESAMBIENTE_H

#include "utils.h"

class PropriedadesAmbiente {
private:
    string nome;
    string unidade;
protected:
    float min;
    float max;
    float atual;
public:
    PropriedadesAmbiente(string nome, string unidade, float min, float max, float atual);
    ~PropriedadesAmbiente();

    string getNome() const;
    string getUnidade() const;
    float getMin() const;
    float getMax() const;
    float getAtual() const;

    virtual void alteraValor(float valor);

    string toString();
};


class Humidade : public PropriedadesAmbiente {
public:
    Humidade(float min, float max, float atual);
    void alteraValor(float valor);
    ~Humidade();

};


class Fumo : public PropriedadesAmbiente {
public:
    Fumo(float min, float max, float atual);
    void alteraValor(float valor);
    ~Fumo();

};

#endif //TP_PROPRIEDADESAMBIENTE_H
