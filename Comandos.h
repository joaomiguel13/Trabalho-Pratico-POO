//
// Created by joaom on 02/11/2023.
//
#ifndef TP_COMANDOS_H
#define TP_COMANDOS_H

#include "utils.h"
#include "Zona.h"
#include "Habitacao.h"

class Comandos {
public:
    Comandos();
    void startSimulator();
private:
    string VerificaComandos(const string& comando);
    bool existeHabitacao = false;
    void setExisteHabitacao(bool valor);
    string avancaInstante(const string& input);
    string criaHabitacao(const string& input);
    string removeHabitacao(const string& input);
    string criaNovaZona(const string& input);
    string removeZona(const string& input);
    string listaZonas(const string& input);
    string listaComponentes(const string& input);
    string listaPropriedades(const string& input);
    string modificaPropriedade(const string& input);
    string adicionaComponente(const string& input);
    string removeComponente(const string& input);
    string novaRegra(const string& input);
    string mudaComandoProcessador(const string& input);
    string listaRegras(const string& input);
    string removeRegra(const string& input);
    string associaProcessadorAparelho(const string& input);
    string desassociaProcessadorAparelho(const string& input);
    string enviaComandoAparelho(const string& input);
    string guardaEstadoProcessador(const string& input);
    string carregaEstadoProcessador(const string& input);
    string apagaProcessadorMemoria(const string& input);
    string listaProcessadoresMemoria(const string& input);
    string carregaFicheiroComandos(const string& input);
    Habitacao *habitacao = nullptr;

    Window *janelaOutput = nullptr;

    vector<Window> windows;
    void criarWindows();
    void refreshHabitacao();
    void clear();
};


#endif //TP_COMANDOS_H
