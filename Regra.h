//
// Created by joaom on 02/11/2023.
//

#ifndef TP_REGRA_H
#define TP_REGRA_H

#include "utils.h"
#include "Sensores.h"

class Regra {
public:
    Regra(Sensores &sensor, float x,string nome);
    Regra(Sensores &sensor, string nome);
    int getId() const;
    string nome;

    bool verificar();

    float x;

    Sensores * getSensor();
    void resetSensor();

    string getTipo();


    virtual float getX();
    virtual float getY();

    void resetId();

private:
    int id;
    static int nextId;

protected:
    Sensores *sensor;
};

class RegraEntre : public Regra {
public:
    RegraEntre(Sensores &sensor, float x, float y);
    bool verificar();
    float getX() override;
    float getY() override;
private:
    float x;
    float y;
};

class RegraFora : public Regra {
public:
    RegraFora(Sensores &sensor, float x, float y);
    bool verificar();
    float getX() override;
    float getY() override;

private:
    float x;
    float y;
};



#endif //TP_REGRA_H
