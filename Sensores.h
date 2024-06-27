//
// Created by joaom on 02/11/2023.
//

#ifndef TP_SENSORES_H
#define TP_SENSORES_H

#include "utils.h"

class Sensores {
private:
    char letra;
    string nome;
    string propriedade;
    int id;
    static int nextId;
    map<string,float> *chaveValor;

public:
    Sensores(char letra,string propriedade, map<string,float> *chaveValor);
    ~Sensores();

    static int getNextId();
    int getId() const;

    string getNome() const;
    char getLetra() const;

    float getValorAtual();

    void resetId();
};


#endif //TP_SENSORES_H
