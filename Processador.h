//
// Created by joaom on 02/11/2023.
//

#ifndef TP_PROCESSADOR_H
#define TP_PROCESSADOR_H

#include "utils.h"
#include "Regra.h"
#include "Aparelhos.h"

class Processador {
public:
    Processador(string comand,int idZona);
    ~Processador();


    static int getNextId();
    int getId() const;
    int getIdZona() const;


    void addRegra(Regra *regra);
    string listarRegras();
    int getNumRegras();
    bool removeRegra(int idRegra);

    void setComando(string novoComando);
    string getComando();

    string associaAparelho(Aparelhos *pAparelhos);
    string desassociaAparelho(Aparelhos *pAparelhos);
    int getNumAparelhosAssociados();

    Processador* clone();

    void avaliaRegras();

    void resetSensor();

    void resetId();

private:
    int id;
    int idZona;
    static int nextId;
    vector<Regra*> regras;
    string comando;

    vector<Aparelhos*> aparelhosAssociados;
};


#endif //TP_PROCESSADOR_H
