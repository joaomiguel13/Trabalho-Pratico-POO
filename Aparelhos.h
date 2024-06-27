//
// Created by joaom on 02/11/2023.
//

#ifndef TP_APARELHOS_H
#define TP_APARELHOS_H

#include "utils.h"

class Aparelhos {
private:
    string nome;
    char letra;
    string estado;
    int id;
    static int nextId;

    bool lastCommand;

public:
    Aparelhos(string tipoAparelho, char letra, string estado);
    ~Aparelhos();

    static int getNextId();

    string getNome() const;
    char getLetra() const;

    string getEstado() const;
    void setEstado(string estado);

    int getId() const;

    string getLastCommand() const;

    virtual void avancaInstante(int contaInstantes);

    void resetId();
};

class Aquecedor : public Aparelhos {
public:
    Aquecedor(map <string,float> *valorPropriedade);
    ~Aquecedor();

    void avancaInstante(int contaInstantes) override;
private:
    bool fezRuido;
    map <string,float> *valorPropriedade;
};

class Aspersor : public Aparelhos {
public:
    Aspersor(map <string,float> *valorPropriedade);
    ~Aspersor();

    void avancaInstante(int contaInstantes) override;

private:
    map <string,float> *valorPropriedade;
    int guardaInstante;
    int contaDesligado;
};

class Refrigerador : public Aparelhos {
public:
    Refrigerador(map <string,float> *valorPropriedade);
    ~Refrigerador();

    void avancaInstante(int contaInstantes) override;

private:
    map <string,float> *valorPropriedade;
    bool addRuido;
};

class Lampada : public Aparelhos {
public:
    Lampada(map <string,float> *valorPropriedade);
    ~Lampada();

    void avancaInstante(int contaInstantes) override;

private:
    map <string,float> *valorPropriedade;

    bool ligado;
};




#endif //TP_APARELHOS_H
