#pragma once

#include "IGestaoComandasService.h"
#include <QMap>
#include <ICardapioDigitalService.h>
#include <IGestaoSalaoService.h>

class GestaoComandasServiceImpl : public IGestaoComandasService {
    Q_OBJECT

public:
    static GestaoComandasServiceImpl* getInstance();

    // Implementações da interface
    Comanda criarComandaParaMesa(int idMesa) override;
    bool adicionarItem(int idComanda, int idItemCardapio, int quantidade,
                       const QString& observacoes = QString()) override;
    Comanda getComandaPorId(int idComanda) const override;
    Comanda getComandaPorMesa(int idMesa) const override;
    double calcularTotalComanda(int idComanda) const override;
    bool removerItem(int idComanda, int idItem) override; // agora válido

private:
    GestaoComandasServiceImpl(QObject* parent = nullptr);
    ~GestaoComandasServiceImpl() override = default;
    GestaoComandasServiceImpl(const GestaoComandasServiceImpl&) = delete;
    GestaoComandasServiceImpl& operator=(const GestaoComandasServiceImpl&) = delete;

    QMap<int, Comanda> m_comandasAtivas;
    int m_proximoId = 1;

    // Dependências
    ICardapioDigitalService* m_servicoCardapio;
    IGestaoSalaoService* m_servicoSalao;
};
