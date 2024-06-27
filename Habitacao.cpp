#include "Habitacao.h"

Habitacao::Habitacao(int linha, int coluna, map<string, Processador*> &saveProc) {
    this->saveProc = saveProc;
    nLinhas = linha;
    nColunas = coluna;
    contaInstantes = 0;

    for (int i = 0; i < linha; ++i) {
        vector<Zona*> linha;
        for (int j = 0; j < coluna; ++j) {
            linha.emplace_back(nullptr);
        }
        zonas.emplace_back(linha);
    }
}

Habitacao::~Habitacao(){
    for (auto& linha : zonas) {
        for (auto& ptrZona : linha) {
            delete ptrZona;
            ptrZona = nullptr;
        }
    }
    zonas.clear();
}

vector<vector<Zona*>> Habitacao::getZonas(){
    return zonas;
}

int Habitacao::getnLinhas() const{
    return nLinhas;
}

int Habitacao::getnColunas() const {
    return nColunas;
}

void Habitacao::adicionaZona(int linha, int coluna){
    zonas[linha][coluna] = new Zona();
}

void Habitacao::removeZona(int Id){
    for (auto& linha : zonas) {
        for (auto& ptrZona : linha) {
            if (ptrZona != nullptr && ptrZona->getId() == Id) {
                delete ptrZona;
                ptrZona = nullptr;
            }
        }
    }
}

string Habitacao::listarZonas() {
    stringstream ss;
    for (auto& linha : zonas) {
        for (auto& ptrZona : linha) {
            if (ptrZona != nullptr) {
                ss << ptrZona->listaZonas() << endl;
            }
        }
    }
    return ss.str();
}

string Habitacao::listarPropriedades(int i) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == i) {
                    return ptrZona->listaPropriedades();
                }
            }
        }
    }
    return "Zona sem propriedades";
}

string Habitacao::modificaPropriedade(int Id, string nomePropriedade, float novoValor) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == Id) {
                    return ptrZona->modificaPropriedade(nomePropriedade, novoValor);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::adicionaComponente(int id, char tipoComponente, string parametro) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == id) {
                    return ptrZona->adicionaComponente(tipoComponente, parametro);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::listarComponentes(int id) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == id) {
                    return ptrZona->listaComponentes();
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::removeComponente(int id, char tipoComponente, int idComponente) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == id) {
                    return ptrZona->removeComponente(tipoComponente, idComponente);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::novaRegra(int idZona, int idProcessador, string tipoRegra, int idSensor, float parametro) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == idZona) {
                    return ptrZona->novaRegra(idProcessador, tipoRegra, idSensor, parametro);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::novaRegra(int idZona, int idProcessador, string tipoRegra, int idSensor, float parametro,float parametro2) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == idZona) {
                    return ptrZona->novaRegra(idProcessador, tipoRegra, idSensor, parametro,parametro2);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::listaRegras(int idZona, int idProcRegra) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == idZona) {
                    return ptrZona->listaRegras(idProcRegra);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::removeRegra(int idZona, int idProcRegra, int idRegra) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if (ptrZona != nullptr) {
                if (ptrZona->getId() == idZona) {
                    return ptrZona->removeRegra(idProcRegra, idRegra);
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::mudaComandoProcessador(int idZona, int idProcRegra, const string& novoComando) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                if (ptrZona->getId() == idZona) {
                    return ptrZona->mudaComandoProcessador(idProcRegra, novoComando);
                }
            }

        }
    }
    return "Zona nao encontrada";
}

string Habitacao::avancaInstante() {
    stringstream ss;
    ++contaInstantes;
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                ss << ptrZona->avancaInstante(contaInstantes);
            }
        }
    }
    return ss.str();
}

string Habitacao::enviaComandoAparelho(int idZona, int idAparelho, string comando) {
for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                if (ptrZona->getId() == idZona) {
                    return ptrZona->enviaComandoAparelho(idAparelho, comando);
                }
            }

        }
    }
    return "Zona nao encontrada";
}

string Habitacao::associaProcessadorAparelho(int idZona, int idProcRegra, int idAparelho) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                if (ptrZona->getId() == idZona) {
                    return ptrZona->associaProcessadorAparelho(idProcRegra, idAparelho);
                }
            }

        }
    }
    return "Zona nao encontrada";
}

string Habitacao::desassociaProcessadorAparelho(int idZona, int idProcRegra, int idAparelho) {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                if (ptrZona->getId() == idZona) {
                    return ptrZona->desassociaProcessadorAparelho(idProcRegra, idAparelho);
                }
            }

        }
    }
    return "Zona nao encontrada";
}

string Habitacao::guardaEstadoProcessador(int idZona, int idProcRegra, string nome) {
    if(saveProc.find(nome) != saveProc.end())
        return "Nome ja existente";
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                if (ptrZona->getId() == idZona) {
                    saveProc[nome] = ptrZona->guardaEstadoProcessador(idProcRegra);
                    if(saveProc[nome] == nullptr)
                        return "Processador nao encontrado";
                    return "Processador guardado com sucesso";
                }
            }
        }
    }
    return "Zona nao encontrada";
}

string Habitacao::listaProcessadoresMemoria() {
    stringstream ss;
    for (auto &it: saveProc) {
        ss << it.first << "\n";
        ss << "ID do processador: " <<it.second->getId() << "\n";
        ss <<"ID da zona : " << it.second->getIdZona() << "\n";
        ss << it.second->getNumRegras() << "\n";
    }
    return ss.str();
}

string Habitacao::carregaEstadoProcessador(string nome) {
    for (auto &it: saveProc) {
        if (it.first == nome) {
            for (auto &linha: zonas) {
                for (auto &ptrZona: linha) {
                    if(ptrZona != nullptr){
                        if (ptrZona->getId() == it.second->getIdZona()) {
                            ptrZona->carregaEstadoProcessador(it.second);
                            return "Processador carregado com sucesso";
                        }
                    }
                }
            }
            return "Zona nao encontrada";
        }
    }
    return "Processador em memoria nao encontrado";
}

string Habitacao::apagaProcessadorMemoria(string nome) {
    for (auto &it: saveProc) {
        if (it.first == nome) {
            saveProc.erase(nome);
            return "Processador apagado com sucesso";
        }
    }
    return "Processador nao encontrado";
}

void Habitacao::resetId() {
    for (auto &linha: zonas) {
        for (auto &ptrZona: linha) {
            if(ptrZona != nullptr){
                ptrZona->resetId();
            }
        }
    }
}

