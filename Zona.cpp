//
// Created by joaom on 02/11/2023.
//

#include "Zona.h"

int Zona::nextId = 0;

Zona::Zona() {
    id = ++nextId;
    propriedades.emplace_back(new PropriedadesAmbiente("temperatura", "graus celsius", -273, 9999, 0));
    propriedades.emplace_back(new PropriedadesAmbiente("luz", "lumens",0, 9999,0));
    propriedades.emplace_back(new Humidade(0, 100,0));
    propriedades.emplace_back(new PropriedadesAmbiente("radiacao", "becquerel",0, 9999,0));
    propriedades.emplace_back(new PropriedadesAmbiente("vibracao", "hertz",0, 9999,0));
    propriedades.emplace_back(new PropriedadesAmbiente("som", "decibeis",0, 9999,0));
    propriedades.emplace_back(new Fumo(0, 100,0));

    for(PropriedadesAmbiente *p : propriedades){
        chaveValor.emplace(p->getNome(), p->getAtual());
    }
}

int Zona::getNextId(){
    return nextId;
}

string Zona::toString() const {
    stringstream ss;
    ss << "Zona " << to_string(id) + "\n";
    for(Sensores *s : sensores){
        ss << s->getLetra() + to_string(s->getId());
    }
    ss << "\n";
    for(Aparelhos *a : aparelhos){
        ss << a->getLetra() + to_string(a->getId());
    }
    ss << "\n";
    for(Processador *p : processadores){
        ss << "p" + to_string(p->getId());
    }
    return ss.str();
}

string Zona::listaZonas() {
    return "Zona " + to_string(id) + "\n" + "Sensores: " + to_string(sensores.size()) +"\n" + "Aparelhos: " + to_string(aparelhos.size()) +"\n"+ "Processadores: " + to_string(processadores.size()) + "\n";
}

int Zona::getId() const {
    return id;
}

string Zona::adicionaComponente(char tipoComponente, const string& parametro) {
    if(tipoComponente == 's'){
        return addSensor(parametro);
    }
    else if(tipoComponente == 'a'){
        return addAparelho(parametro);
    }
    else if(tipoComponente == 'p'){
        processadores.push_back(new Processador(parametro, id));
        return "Processador adicionado com sucesso";
    }
    else{
        return "Tipo de componenente invalido";
    }
}

string Zona::addAparelho(string tipoAparelho){
    if(tipoAparelho == "aquecedor"){
        aparelhos.push_back(new Aquecedor(&chaveValor));
        return "Aquecedor adicionado com sucesso";
    }
    else if(tipoAparelho == "aspersor"){
        aparelhos.push_back(new Aspersor(&chaveValor));
        return "Aspersor adicionado com sucesso";
    }
    else if(tipoAparelho == "refrigerador"){
        aparelhos.push_back(new Refrigerador(&chaveValor));
        return "Refrigerador adicionado com sucesso";
    }
    else if(tipoAparelho == "lampada"){
        aparelhos.push_back(new Lampada(&chaveValor));
        return "Lampada adicionada com sucesso";
    }
    else{
        return "Tipo de aparelho invalido";
    }
}

string Zona::addSensor(string tipoPropriedade){
    if(tipoPropriedade == "temperatura"){
        sensores.push_back(new Sensores('t',tipoPropriedade, &chaveValor));
        return "Sensor de temperatura adicionado com sucesso";
    }
    else if(tipoPropriedade == "luz"){
        sensores.push_back(new Sensores('m',tipoPropriedade,&chaveValor));
        return "Sensor de luz adicionado com sucesso";
    }
    else if(tipoPropriedade == "humidade"){
        sensores.push_back(new Sensores('h',tipoPropriedade,&chaveValor));
        return "Sensor de humidade adicionado com sucesso";
    }
    else if(tipoPropriedade == "radiacao"){
        sensores.push_back(new Sensores('d',tipoPropriedade,&chaveValor));
        return "Sensor de radiacao adicionado com sucesso";
    }
    else if(tipoPropriedade == "vibracao"){
        sensores.push_back(new Sensores('v',tipoPropriedade,&chaveValor));
        return "Sensor de vibracao adicionado com sucesso";
    }
    else if(tipoPropriedade == "som"){
        sensores.push_back(new Sensores('o',tipoPropriedade,&chaveValor));
        return "Sensor de som adicionado com sucesso";
    }
    else if(tipoPropriedade == "fumo"){
        sensores.push_back(new Sensores('f',tipoPropriedade,&chaveValor));
        return "Sensor de fumo adicionado com sucesso";
    }
    else{
        return "Tipo de sensor invalido";
    }
}

string Zona::listaPropriedades() {
    stringstream ss;
    for(PropriedadesAmbiente *p : propriedades){
        ss << p->toString();
    }
    return ss.str();
}

string Zona::modificaPropriedade(string nome, float valor) {
    stringstream ss;
    for(PropriedadesAmbiente *p : propriedades){
        ss.str("");
        if(p->getNome() == nome && valor >= p->getMin() && valor <= p->getMax()){
            p->alteraValor(valor);
            chaveValor.find(nome)->second = valor;
            ss << p->toString();
            break;
        }
        else{
            ss << "Propriedade nao encontrada ou valor fora dos limites\n";
        }
    }
    return ss.str();
}

string Zona::listaComponentes() {
    stringstream ss;
    ss << "Sensores:\n";
    for(Sensores *s : sensores){
        ss << s->getLetra() << ";" << s->getId() << ";" << to_string(s->getValorAtual()) + "\n";
    }
    ss << "\nAparelhos:\n";
    for(Aparelhos *a : aparelhos){
        ss << a->getLetra() << ";" << a->getId() << ";" << a->getNome() << ";" << a->getLastCommand() << "\n";
    }
    ss << "\nProcessadores:\n";
    for(Processador *p : processadores){
        ss << "p" << ";" << p->getId() << ";" << "processador" << ";" << p->getNumRegras() << "regras" << "\n";
    }
    return ss.str();
}

Zona::~Zona() {
}

string Zona::removeComponente(char tipoComponente, int idComponente) {
    stringstream ss;
    if(tipoComponente == 's'){
        auto it = sensores.begin();
        while(it != sensores.end()){
            if((*it)->getId() == idComponente){
                for(Sensores *s : sensoresAssociadosAregra){
                   if((*it)->getId() == s->getId()){
                       return "Sensor nao pode ser removido porque tem regras associadas";
                   }
                }
                delete *it;
                sensores.erase(it);
                return "Sensor removido com sucesso";
            }
            it++;
        }
    }else if(tipoComponente == 'a'){
        auto it = aparelhos.begin();
        while(it != aparelhos.end()){
            if((*it)->getId() == idComponente){
                delete *it;
                aparelhos.erase(it);
                return "Aparelho removido com sucesso";
            }
            it++;
        }
    }else if(tipoComponente == 'p'){
        auto it = processadores.begin();
        while(it != processadores.end()){
            if((*it)->getId() == idComponente){
                if((*it)->getNumRegras() == 0){
                    delete *it;
                    processadores.erase(it);
                    return "Processador removido com sucesso";
                }
                else{
                    return "Processador nao pode ser removido porque tem regras associadas";
                }
            }
            it++;
        }
    }
    return "Componente nao encontrado";
}

string Zona::novaRegra(int idProcessador, string tipoRegra, int idSensor, float parametro1) {
    stringstream ss;
    Sensores *s = nullptr;
    for(Sensores *sensor : sensores){
        if(sensor->getId() == idSensor){
            s = sensor;
            break;
        }
    }
    for(Processador *p : processadores){
        if(p->getId() == idProcessador){
            if(tipoRegra == "igual_a"){
                p->addRegra(new Regra(*s,parametro1,"igual_a"));
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "maior_que"){
                p->addRegra(new Regra(*s,parametro1,"maior_que"));
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "menor_que"){
                p->addRegra(new Regra(*s,parametro1,"menor_que"));
                return "Regra adicionada com sucesso";
            }
            else{
                return "Tipo de regra invalido";
            }
        }
    }
    return "Processador nao encontrado";
}

string Zona::novaRegra(int idProcessador, string tipoRegra, int idSensor, float parametro1,float parametro2) {
    stringstream ss;
    Sensores *s = nullptr;
    for(Sensores *sensor : sensores){
        if(sensor->getId() == idSensor){
            s = sensor;
            break;
        }
    }
    if(s == nullptr){
        return "Sensor nao encontrado";
    }
    for(Processador *p : processadores){
        if(p->getId() == idProcessador){
            if(tipoRegra == "entre"){
                p->addRegra(new RegraEntre(*s,parametro1,parametro2));
                sensoresAssociadosAregra.push_back(s);
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "fora"){
                p->addRegra(new RegraFora(*s,parametro1,parametro2));
                sensoresAssociadosAregra.push_back(s);
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "maior_que"){
                p->addRegra(new Regra(*s,parametro1,"maior_que"));
                sensoresAssociadosAregra.push_back(s);
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "menor_que"){
                p->addRegra(new Regra(*s,parametro1,"menor_que"));
                sensoresAssociadosAregra.push_back(s);
                return "Regra adicionada com sucesso";
            }
            else if(tipoRegra == "igual_a"){
                p->addRegra(new Regra(*s,parametro1,"igual_a"));
                sensoresAssociadosAregra.push_back(s);
                return "Regra adicionada com sucesso";
            }
            else{
                return "Tipo de regra invalido";
            }
        }
    }
    return "Processador nao encontrado";

}

string Zona::listaRegras(int idProcRegra) {
    stringstream ss;
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            ss << p->listarRegras();
            return ss.str();
        }
    }
    return "Processador nao encontrado";
}

string Zona::removeRegra(int idProcRegra, int idRegra) {
    stringstream ss;
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            if(p->removeRegra(idRegra)){
                return "Regra removida com sucesso";
            }
            else{
                return "Regra nao encontrada";
            }
        }
    }
    return "Processador nao encontrado";
}

string Zona::mudaComandoProcessador(int idProcRegra, const string& novoComando) {
    stringstream ss;
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            p->setComando(novoComando);
            return "Comando alterado com sucesso";
        }
    }
    return "Processador nao encontrado";
}

string Zona::avancaInstante(int contaInstantes) {
    stringstream ss;
    for(Processador *p : processadores){
        p->avaliaRegras();
    }
    for(Aparelhos *a : aparelhos){
        a->avancaInstante(contaInstantes);
    }
    updateValorInstante();
    return "Instante avancado com sucesso";
}

void Zona::updateValorInstante(){
    for(auto & it : chaveValor) {
        if(it.first == "temperatura"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "temperatura"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if(it.first == "som"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "som"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if(it.first == "luz"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "luz"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if(it.first == "humidade"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "humidade"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if(it.first == "vibracao"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "vibracao"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if(it.first == "fumo"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "fumo"){
                    p->alteraValor(it.second);
                }
            }
        }
        else if (it.first == "radiacao"){
            for(PropriedadesAmbiente *p : propriedades){
                if(p->getNome() == "radiacao"){
                    p->alteraValor(it.second);
                }
            }
        }
    }
}

string Zona::enviaComandoAparelho(int idAparelho, string comando) {
    stringstream ss;
    for(Aparelhos *a : aparelhos){
        if(a->getId() == idAparelho){
            if(a->getEstado() == "ligado"){
                if(comando == "desliga"){
                    a->setEstado("desligado");
                    return "Aparelho desligado com sucesso";
                }
                else if (comando == "liga"){
                    return "Aparelho ja se encontra ligado";
                }
                else{
                    return "Comando invalido";
                }
            }
            else{
                if(comando == "liga"){
                    a->setEstado("ligado");
                    return "Aparelho ligado com sucesso";
                }
                else if(comando == "desliga"){
                    return "Aparelho ja se encontra desligado";
                }
                else{
                    return "Comando invalido";
                }
            }
        }
    }
    return "Aparelho nao encontrado";
}

string Zona::associaProcessadorAparelho(int idProcRegra, int idAparelho) {
    stringstream ss;
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            for(Aparelhos *a : aparelhos){
                if(a->getId() == idAparelho){
                   return p->associaAparelho(a);
                }
            }
            return "Aparelho nao encontrado";
        }
    }
    return "Processador nao encontrado";
}

string Zona::desassociaProcessadorAparelho(int idProcRegra, int idAparelho) {
stringstream ss;
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            for(Aparelhos *a : aparelhos){
                if(a->getId() == idAparelho){
                    return p->desassociaAparelho(a);
                }
            }
            return "Aparelho nao encontrado";
        }
    }
    return "Processador nao encontrado";
}

Processador *Zona::guardaEstadoProcessador(int idProcRegra) {
    for(Processador *p : processadores){
        if(p->getId() == idProcRegra){
            Processador *clone = p->clone();
            clone->resetSensor();
            return clone;
        }
    }
    return nullptr;
}

string Zona::carregaEstadoProcessador(Processador *pProcessador) {
    for(Processador *p : processadores){
        if(p->getId() == pProcessador->getId()){
            p = pProcessador;
            return "Processador carregado com sucesso";
        }
    }
    processadores.push_back(pProcessador);
    return "Processador não existia! Criado com sucesso";
}

void Zona::resetId() {
    nextId = 0;
    for(Processador *p : processadores){
        p->resetId();
    }
    for(Aparelhos *a : aparelhos){
        a->resetId();
    }
    for (Sensores *s : sensores){
        s->resetId();
    }
}
