#include "GestaoComandasServiceImpl.h"
// Adicionamos o include da Fábrica aqui
#include "GestaoComandasServiceFactory.h"
#include <CardapioDigitalServiceFactory.h>
#include <GestaoSalaoServiceFactory.h>
#include <QDateTime>

GestaoComandasServiceImpl* GestaoComandasServiceImpl::getInstance() {
    static GestaoComandasServiceImpl instance;
    return &instance;
}

GestaoComandasServiceImpl::GestaoComandasServiceImpl(QObject* parent)
    : IGestaoComandasService(parent) {
    // Injeção de dependência via Singleton/Factory no construtor
    m_servicoCardapio = CardapioDigitalServiceFactory::create();
    m_servicoSalao = GestaoSalaoServiceFactory::create();
}

Comanda GestaoComandasServiceImpl::criarComandaParaMesa(int idMesa) {
    // Verifica se já existe comanda ativa para a mesa
    for(const auto& cmd : m_comandasAtivas) {
        if (cmd.idMesa == idMesa && cmd.ativa) {
            return cmd;
        }
    }

    Comanda novaComanda;
    novaComanda.id = m_proximoId++;
    novaComanda.idMesa = idMesa;
    novaComanda.abertura = QDateTime::currentDateTime();
    novaComanda.ativa = true;
    m_comandasAtivas[novaComanda.id] = novaComanda;

    m_servicoSalao->alterarStatusMesa(idMesa, Mesa::Ocupada);
    emit comandaAtualizada(novaComanda);
    return novaComanda;
}

bool GestaoComandasServiceImpl::adicionarItem(int idComanda, int idItemCardapio, int quantidade, const QString& observacoes) {
    if (!m_comandasAtivas.contains(idComanda)) {
        return false;
    }

    ItemCardapio item;
    if (!m_servicoCardapio->getItemPorId(idItemCardapio, item)) {
        return false;
    }

    Comanda& comanda = m_comandasAtivas[idComanda];

    // Agora inicializando observações
    comanda.itens.append({item.id, item.nome, quantidade, item.preco, observacoes});

    emit comandaAtualizada(comanda);
    return true;
}


Comanda GestaoComandasServiceImpl::getComandaPorId(int idComanda) const {
    return m_comandasAtivas.value(idComanda);
}

Comanda GestaoComandasServiceImpl::getComandaPorMesa(int idMesa) const {
    for(const auto& cmd : m_comandasAtivas) {
        if (cmd.idMesa == idMesa && cmd.ativa) {
            return cmd;
        }
    }
    return Comanda(); // Retorna comanda inválida/inativa
}


IGestaoComandasService* GestaoComandasServiceFactory::create() {
    return GestaoComandasServiceImpl::getInstance();
}

double GestaoComandasServiceImpl::calcularTotalComanda(int idComanda) const {
    if (!m_comandasAtivas.contains(idComanda)) return 0.0;
    const Comanda& comanda = m_comandasAtivas[idComanda];
    double total = 0.0;
    for (const auto& item : comanda.itens) {
        total += item.quantidade * item.precoUnitario;
    }
    return total;
}

bool GestaoComandasServiceImpl::removerItem(int idComanda, int idItem) {
    if (!m_comandasAtivas.contains(idComanda)) return false;
    Comanda &comanda = m_comandasAtivas[idComanda];
    for (int i = 0; i < comanda.itens.size(); ++i) {
        if (comanda.itens[i].idItemCardapio == idItem) {  // corrigido
            comanda.itens.removeAt(i);
            emit comandaAtualizada(comanda);
            return true;
        }
    }
    return false;
}
