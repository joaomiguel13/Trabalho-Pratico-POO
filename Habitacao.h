//
// Created by joaom on 06/11/2023.
//

#ifndef TP_CRIARSIMULADOR_H
#define TP_CRIARSIMULADOR_H

#include "utils.h"
#include "Zona.h"

class Habitacao{
private:
    vector<vector<Zona*>> zonas;
    int nLinhas;
    int nColunas;
    int contaInstantes;

    map<string, Processador *> saveProc;

 public:
    Habitacao(int linha, int coluna, map<string, Processador*> &saveProc);

    int getnLinhas() const;
    int getnColunas() const;

    void adicionaZona(int linha, int coluna);
    void removeZona(int Id);
    string listarZonas();

    string modificaPropriedade(int Id, string nomePropriedade, float novoValor);
    string listarPropriedades(int i);

    vector<vector<Zona*>> getZonas();

    string adicionaComponente(int id, char tipoComponente, string parametro);
    string listarComponentes(int id);
    string removeComponente(int id, char tipoComponente, int idComponente);

    string novaRegra(int idZona, int idProcessador, string tipoRegra, int idSensor, float parametro);
    string novaRegra(int idZona, int idProcessador, string tipoRegra, int idSensor, float parametro,float parametro2);
    string listaRegras(int idZona, int idProcRegra);
    string removeRegra(int idZona, int idProcRegra, int idRegra);

    string mudaComandoProcessador(int idZona, int idProcRegra, const string& novoComando);

    string avancaInstante();

    string enviaComandoAparelho(int idZona, int idAparelho, string comando);
    string associaProcessadorAparelho(int idZona, int idProcRegra, int idAparelho);
    string desassociaProcessadorAparelho(int idZona, int idProcRegra, int idAparelho);

    ~Habitacao();

    string guardaEstadoProcessador(int idZona, int idProcRegra, string nome);
    string listaProcessadoresMemoria();
    string carregaEstadoProcessador(string nome);
    string apagaProcessadorMemoria(string nome);

    void resetId();
};


#endif //TP_CRIARSIMULADOR_H
