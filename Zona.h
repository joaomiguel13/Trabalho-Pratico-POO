#ifndef TP_ZONA_H
#define TP_ZONA_H

#include "utils.h"
#include "Aparelhos.h"
#include "Sensores.h"
#include "Processador.h"
#include "PropriedadesAmbiente.h"

class Zona {
public:
    Zona();
    ~Zona();

    string toString() const;

    int getId() const;
    static int getNextId();

    string addSensor(string tipoPropriedade);
    string addAparelho(string tipoAparelho);

    string listaZonas();

    string listaComponentes();
    string adicionaComponente(char tipoComponente, const string& parametro);
    string removeComponente(char tipoComponente, int idComponente);

    string listaPropriedades();
    string modificaPropriedade(string nome, float valor);

    string novaRegra(int idProcessador, string tipoRegra, int idSensor, float parametro1);
    string novaRegra(int idProcessador, string tipoRegra, int idSensor, float parametro1, float parametro2);
    string listaRegras(int idProcRegra);
    string removeRegra(int idProcRegra, int idRegra);
    string mudaComandoProcessador(int idProcRegra, const string& novoComando);

    string avancaInstante(int contaInstantes);
    void updateValorInstante();

    string enviaComandoAparelho(int idAparelho, string comando);
    string associaProcessadorAparelho(int idProcRegra, int idAparelho);
    string desassociaProcessadorAparelho(int idProcRegra, int idAparelho);

    Processador *guardaEstadoProcessador(int idProcRegra);
    string carregaEstadoProcessador(Processador *pProcessador);

    void resetId();

private:
    int id;
    static int nextId;

    vector<PropriedadesAmbiente*> propriedades;
    vector<Sensores*> sensores;
    vector<Aparelhos*> aparelhos;
    vector<Processador*> processadores;

    vector<Sensores*> sensoresAssociadosAregra;

    map<string, float> chaveValor;
};


#endif //TP_ZONA_H
