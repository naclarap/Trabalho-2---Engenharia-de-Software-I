#pragma once

#include "ICardapioDigitalService.h"
#include <QList>

class CardapioDigitalServiceImpl : public ICardapioDigitalService {
    Q_OBJECT

public:
    static CardapioDigitalServiceImpl* getInstance();

    // Métodos da interface
    QList<ItemCardapio> getItens() const noexcept override;

    bool getItemPorId(int id, ItemCardapio& item) const override;

private:
    CardapioDigitalServiceImpl(QObject *parent = nullptr);
    ~CardapioDigitalServiceImpl() override = default;
    CardapioDigitalServiceImpl(const CardapioDigitalServiceImpl&) = delete;
    CardapioDigitalServiceImpl& operator=(const CardapioDigitalServiceImpl&) = delete;

    QList<ItemCardapio> m_itens;
};
