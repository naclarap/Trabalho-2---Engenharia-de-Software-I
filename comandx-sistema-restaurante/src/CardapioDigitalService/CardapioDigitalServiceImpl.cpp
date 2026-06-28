#include "CardapioDigitalServiceImpl.h"
#include "CardapioDigitalServiceFactory.h"

// Singleton da implementação
CardapioDigitalServiceImpl* CardapioDigitalServiceImpl::getInstance() {
    static CardapioDigitalServiceImpl instance;
    return &instance;
}

// Construtor com carga inicial de itens
CardapioDigitalServiceImpl::CardapioDigitalServiceImpl(QObject *parent)
    : ICardapioDigitalService(parent) {
    // Carga estática de itens para a Sprint 1
    m_itens << ItemCardapio{101, "Refrigerante Lata", 7.00};
    m_itens << ItemCardapio{102, "Pudim de Leite Condensado", 10.00};
    m_itens << ItemCardapio{201, "Pizza Calabresa", 42.50};
}

// Implementação da interface
QList<ItemCardapio> CardapioDigitalServiceImpl::getItens() const noexcept {
    return m_itens;
}


bool CardapioDigitalServiceImpl::getItemPorId(int id, ItemCardapio& item) const {
    for (const auto& i : m_itens) {
        if (i.id == id) {
            item = i;
            return true;
        }
    }
    return false;
}

ICardapioDigitalService* CardapioDigitalServiceFactory::create() {
    return CardapioDigitalServiceImpl::getInstance();
}

