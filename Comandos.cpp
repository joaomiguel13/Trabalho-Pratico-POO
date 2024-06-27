//
// Created by joaom on 02/11/2023.
//
#include "Comandos.h"

Comandos::Comandos(){
}

void Comandos::startSimulator(){
    Terminal &t = Terminal::instance();
    string comando;
    int tamXTerminal = t.getNumCols();
    int tamYTerminal = t.getNumRows();
    int contador = 0;
    janelaOutput = new Window(70,0,50,25,true);
    *janelaOutput << "              ----> Output <----\n\n ";

    Window janelaComandos = Window(0, tamYTerminal - 3, tamXTerminal, 3);

    while (comando != "sair") {
        janelaComandos <<"Inserir comando: "; //escreve na janela
        janelaComandos >> comando; //le o comando
        if (contador==20){
            janelaOutput->clear();
            contador = 0;
            *janelaOutput << "            ----> Output <----\n\n ";
        }
        contador++;

        *janelaOutput <<"-> "<< VerificaComandos(comando)<<"\n"; //escreve na janela Output
        janelaComandos.clear(); //limpa a janela comandos
    }
}

void Comandos::clear(){
        janelaOutput->clear();
        *janelaOutput << "            ----> Output <----\n\n ";
}

void Comandos::criarWindows(){
    Terminal &t = Terminal::instance();
    int width = 15;
    int height = 6;
    /*for (int i = 1; i <= max; ++i) {
        zonas.emplace_back(); //cria as zonas
    }*/

    int x = 0, y = 0;
    int nColuna = 0;

    for (int i = 0; i < habitacao->getnLinhas()*habitacao->getnColunas(); i++) {
        windows.emplace_back(t.create_window(x, y, width, height, true)); // Adicione a janela ao vetor de janelas
        Window &janelaZonas = windows.back(); // Obter a janela mais recente
        //janelaZonas << zona.toString(); //mete as zonas no ecra
        ++nColuna;
        if (nColuna == habitacao->getnColunas()) {
            nColuna = 0;
            y += height;
            x = 0;
        } else {
            x += width;
        }
    }
}

void Comandos::refreshHabitacao(){
    vector<vector<Zona*>> zonas = habitacao->getZonas();
    for(int i = 0; i < habitacao->getnLinhas(); i++ ){
        for(int j = 0; j < habitacao->getnColunas(); j++){
            windows[i*habitacao->getnColunas()+j].clear();
            if(zonas[i][j] != nullptr){
                //windows[i*habitacao.getnColunas()+j].clear();
                windows[i*habitacao->getnColunas()+j] << zonas[i][j]->toString();
            }
        }
    }
}

string Comandos::VerificaComandos(const string& comando){

    istringstream iss(comando);
    string tipoComando;

    iss >> tipoComando;

    if(tipoComando == "prox"){
        return avancaInstante(comando);
    }
    else if(tipoComando == "avanca"){
        return avancaInstante(comando);
    }
    else if(tipoComando == "hnova"){
        return criaHabitacao(comando);
    }
    else if(tipoComando == "hrem"){
        return removeHabitacao(comando);
    }
    else if(tipoComando == "znova"){
        return criaNovaZona(comando);
    }
    else if(tipoComando == "zrem"){
        return removeZona(comando);
    }
    else if(tipoComando == "zlista"){
        return listaZonas(comando);
    }
    else if(tipoComando == "zcomp"){
        return listaComponentes(comando);
    }
    else if(tipoComando == "zprops"){
        return listaPropriedades(comando);
    }
    else if(tipoComando == "pmod"){
        return modificaPropriedade(comando);
    }
    else if(tipoComando == "cnovo"){
        return adicionaComponente(comando);
    }
    else if(tipoComando == "crem"){
        return removeComponente(comando);
    }
    else if(tipoComando == "rnova"){
        return novaRegra(comando);
    }
    else if(tipoComando == "pmuda"){
        return mudaComandoProcessador(comando);
    }
    else if(tipoComando == "rlista"){
        return listaRegras(comando);
    }
    else if(tipoComando == "rrem"){
        return removeRegra(comando);
    }
    else if(tipoComando == "asoc"){
        return associaProcessadorAparelho(comando);
    }
    else if(tipoComando == "ades"){
        return desassociaProcessadorAparelho(comando);
    }
    else if(tipoComando == "acom"){
        return enviaComandoAparelho(comando);
    }
    else if(tipoComando == "psalva"){
        return guardaEstadoProcessador(comando);
    }
    else if(tipoComando == "prepoe"){
        return carregaEstadoProcessador(comando);
    }
    else if(tipoComando == "prem"){
        return apagaProcessadorMemoria(comando);
    }
    else if(tipoComando =="plista"){
        return listaProcessadoresMemoria(comando);
    }
    else if(tipoComando == "exec"){
        return carregaFicheiroComandos(comando);
    }
    else if(tipoComando == "clear"){
        clear();
        return "Janela limpa!";
    }
    else{
        return "Comando invalido!";
    }
}

void Comandos::setExisteHabitacao(bool valor) {
    existeHabitacao = valor;
}

string Comandos::avancaInstante(const string& input) {
    istringstream iss(input);
    string comando;
    string invalido;
    int instante = 0;

    iss >> comando;

    if(iss){
        iss >> instante;
        if(iss && comando != "prox"){
            iss >> invalido;
            if(iss){
                return "Demasiados argumentos!";
            }
            if(instante > 0){
                for(int i = 0; i < instante; i++){
                    habitacao->avancaInstante();
                }
                return "Avancou  " + to_string(instante) + " instantes!";
            }
            else{
                return "Instante invalido!";
            }
        }
        else if(iss && comando == "prox"){
            return "Demasiados argumentos!";
        }
        else if(comando != "avanca"){
            return habitacao->avancaInstante();
        }
    }
    return "Comando invalido!";
}

string Comandos::criaHabitacao(const string &input) {
    if (existeHabitacao) {
        return "Ja existe uma habitacao!";
    } else{
        istringstream iss(input);
        string comando;
        int linha = 0, coluna = 0;
        string invalido;

        iss >> comando;
        if (iss) {
            iss >> linha >> coluna;
            if ((linha <= 4 && linha > 1) && (coluna > 1 && coluna <= 4)) {
                iss >> invalido;
                if (iss) {
                    return "Demasiados argumentos!";
                }
                setExisteHabitacao(true);
                map<string, Processador *> *processadores = new map<string, Processador *>;
                habitacao = new Habitacao(linha, coluna, *processadores);
                criarWindows();
                return "Habitacao criada com: " + to_string(linha) + " linhas e " + to_string(coluna) + " colunas";
            } else {
                return "Coordenadas invalidas! O maximo de linhas e colunas e 4";
            }
        }
        return "Comando invalido!";
    }
}

string Comandos::removeHabitacao(const string &input) {
    if (!existeHabitacao) {
        return "Nao existe uma habitacao para remover!";
    } else{
        istringstream iss(input);
        string comando,invalido;
        iss >> comando;
        if(iss){
            iss >> invalido;
            if(iss){
                return "Demasiados argumentos!";
            }
            setExisteHabitacao(false);
            windows.clear();
            habitacao->resetId();
            delete habitacao;
            habitacao = nullptr;
            return "Habitacao removida!";
        }
        return "Comando invalido!";
    }
}

string Comandos::criaNovaZona(const string &input){
    if(!existeHabitacao){
        return "Nao existe uma habitacao!";
    }
    istringstream iss(input);
    //string zona;
    string comando,invalido;
    int linha = -1, coluna = -1;

    iss >> comando;
    if(iss){
        iss >> linha >> coluna;
        if(linha < habitacao->getnLinhas() && linha >= 0 && coluna >= 0 && coluna < habitacao->getnColunas()){
            iss >> invalido;
            if(iss){
                return "Demasiados argumentos!";
            }
            if(habitacao->getZonas()[linha][coluna] != nullptr){
                return "Ja existe uma zona nessa posicao!";
            }
            habitacao->adicionaZona(linha, coluna);
            refreshHabitacao();
            return "Criou uma zona na linha " + to_string(linha) + " e coluna "+ to_string(coluna) + "[id: " +
                   to_string(Zona::getNextId()) + "]";
        }
        else{
            return "Coordenadas invalidas! Verifique o tamanho da habitacao!";
        }
    }
    return "Comando invalido!";
}

string Comandos::removeZona(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    string invalido;

    iss >> comando;
    if (iss) {
        iss >> idZona;
        if (iss) {
            if (idZona > 0) {
                iss >> invalido;
                if (iss) {
                    return "Demasiados argumentos!";
                }
                habitacao->removeZona(idZona);
                refreshHabitacao();
                return "Zona[id: " + to_string(idZona) + "] removida!";
            } else {
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!zrem<ID zona>";
}

string Comandos::listaZonas(const string &input) {
    istringstream iss(input);
    string comando;
    iss >> comando;
    string invalido;

    if(iss){
        iss >> invalido;
        if(iss){
            return "Demasiados argumentos!";
        }
        return habitacao->listarZonas();
    }
    return "Comando invalido!";
}

string Comandos::listaComponentes(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona;
        if(iss){
            if(idZona > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                string x = habitacao->listarComponentes(idZona);
                return x;
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::listaPropriedades(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona;
        if(iss){
            if(idZona > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->listarPropriedades(idZona);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::modificaPropriedade(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    string nome;
    float valor;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona >> nome >> valor;
        if(iss){
            if(idZona > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->modificaPropriedade(idZona, nome, valor);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::adicionaComponente(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    char tipo;
    string nome;
    string invalido;

    iss >> comando;
    if (iss) {
        iss >> idZona >> tipo >> nome;
        if (iss) {
            if (idZona > 0) {
                if (tipo == 's' || tipo == 'p' || tipo == 'a') {
                    iss >> invalido;
                    if (iss) {
                        return "Demasiados argumentos!";
                    }
                    string x = habitacao->adicionaComponente(idZona, tipo, nome);
                    refreshHabitacao();
                    return x;
                } else {
                    return "Tipo invalido! O tipo deve ser 's', 'p' ou 'a'.";
                }
            } else {
                return "Id invalido!";
            }
        }
    }
    return "Comando inválido!";
}

string Comandos::removeComponente(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    char tipo;
    int idComponente;
    string invalido;

    iss >> comando;
    if (iss) {
        iss >> idZona >> tipo >> idComponente;
        if (iss) {
            if (idZona > 0 && idComponente > 0) {
                if (tipo == 's' || tipo == 'p' || tipo == 'a') {
                    iss >> invalido;
                    if (iss) {
                        return "Demasiados argumentos!";
                    }
                    string x = habitacao->removeComponente(idZona, tipo, idComponente);
                    refreshHabitacao();
                    return x;
                } else {
                    return "Tipo invalido! O tipo deve ser 's', 'p' ou 'a'.";
                }
            } else {
                return "Id invalido!";
            }
        }
    }
    return "Comando inválido!";
}

string Comandos::novaRegra(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    string regra;
    int idProcRegra;
    float parametro;
    float parametro2;
    int idSensor;

    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra >> regra >> idSensor >> parametro;
        if(iss){
            if(idZona > 0 && idProcRegra > 0 && idSensor > 0){
                if(iss >> parametro2){
                    return habitacao->novaRegra(idZona, idProcRegra, regra, idSensor, parametro, parametro2);
                }
                else{
                    return habitacao->novaRegra(idZona, idProcRegra, regra, idSensor, parametro);
                }
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::mudaComandoProcessador(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    int idProcRegra;
    string novoComando;
    string invalido;


    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra >> novoComando;
        if(iss){
            iss >> invalido;
            if(iss){
                return "Demasiados argumentos!";
            }
            if(idZona > 0 && idProcRegra > 0){
                return habitacao->mudaComandoProcessador(idZona, idProcRegra, novoComando);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::listaRegras(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    int idProcRegra;
    string nomeRegra;
    int idSensorAssociado = 0;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra;
        if(iss){
            if(idZona > 0 && idProcRegra > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->listaRegras(idZona, idProcRegra);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::removeRegra(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    int idProcRegra;
    int idRegra;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra >> idRegra;
        if(iss){
            if(idZona > 0 && idProcRegra > 0 && idRegra > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->removeRegra(idZona, idProcRegra, idRegra);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::associaProcessadorAparelho(const string &input) {
    istringstream iss(input);
    string comando;
    int idProcRegra;
    int idZona;
    int idAparelho;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona  >> idProcRegra >> idAparelho;
        if(iss){
            if(idZona > 0 && idProcRegra > 0 && idAparelho > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->associaProcessadorAparelho(idZona, idProcRegra, idAparelho);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::desassociaProcessadorAparelho(const string &input) {
    istringstream iss(input);
    string comando;
    int idProcRegra;
    int idZona;
    int idAparelho;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra >> idAparelho;
        if(iss){
            if(idZona > 0 && idProcRegra > 0 && idAparelho > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->desassociaProcessadorAparelho(idZona, idProcRegra, idAparelho);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::enviaComandoAparelho(const string &input) {
    istringstream iss(input);
    string comando;
    int idZona;
    int idAparelho;
    string comandoAparelho;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> idZona >> idAparelho >> comandoAparelho;
        if(iss){
            if(idZona > 0 && idAparelho > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->enviaComandoAparelho(idZona, idAparelho, comandoAparelho);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::guardaEstadoProcessador(const string &input) {
    istringstream iss(input);
    string comando;
    string nome;
    string invalido;
    int idProcRegra;
    int idZona;

    iss >> comando;
    if(iss){
        iss >> idZona >> idProcRegra >> nome;
        if(iss){
            if(idZona > 0 && idProcRegra > 0){
                iss >> invalido;
                if(iss){
                    return "Demasiados argumentos!";
                }
                return habitacao->guardaEstadoProcessador(idZona, idProcRegra, nome);
            }
            else{
                return "Id invalido!";
            }
        }
    }
    return "Comando invalido!";
}

string Comandos::carregaEstadoProcessador(const string &input) {
    istringstream iss(input);
    string comando;
    string nome;
    string invalido;

    iss >> comando;
    if(iss) {
        iss >> nome;
        if (iss) {
            iss >> invalido;
            if (iss) {
                return "Demasiados argumentos!";
            }
            string x = habitacao->carregaEstadoProcessador(nome);
            refreshHabitacao();
            return x;
        }
    }
    return "Comando invalido!";
}

string Comandos::apagaProcessadorMemoria(const string &input) {
    istringstream iss(input);
    string comando;
    string nome;

    iss >> comando;
    if (iss) {
        iss >> nome;
        if (iss) {
            string invalido;
            iss >> invalido;
            if (iss) {
                return "Demasiados argumentos!";
            }
            return habitacao->apagaProcessadorMemoria(nome);
        }
    }
    return "Comando invalido!";
}

string Comandos::listaProcessadoresMemoria(const string &input) {
    istringstream iss(input);
    string comando;
    string nome;
    int idProcessador=0;
    int idZona=0;
    string invalido;

    iss >> comando;
    if(iss){
        iss >> invalido;
        if(iss){
            return "Demasiados argumentos!";
        }
        return habitacao->listaProcessadoresMemoria();
    }
    return "Comando invalido!";
}

string Comandos::carregaFicheiroComandos(const string &input) {
    istringstream iss(input);
    string comando;
    string nomeFicheiro;
    fstream ficheiro;
    string retorno;

    iss >> comando;
    if(iss){
        iss >> nomeFicheiro;
        if(iss){
            ficheiro.open(nomeFicheiro);
            if(ficheiro.is_open()){
                retorno = "Ficheiro " + nomeFicheiro + " carregado!\n";
                while(!ficheiro.eof()){
                    string linha;
                    getline(ficheiro, linha);
                    retorno += VerificaComandos(linha) + "\n";
                }
                return retorno;
            }
            else{
                return "Ficheiro nao encontrado!";
            }
        }
        return "Poucos arguemntos! Usar: exec <nomeFicheiro>";
    }
    return "Comando invalido!";
}