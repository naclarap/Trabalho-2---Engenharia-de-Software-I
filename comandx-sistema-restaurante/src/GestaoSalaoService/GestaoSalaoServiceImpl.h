// libs/GestaoSalaoService/GestaoSalaoServiceImpl.h

#pragma once
#include "IGestaoSalaoService.h"
#include <QList>

class GestaoSalaoServiceImpl : public IGestaoSalaoService {
    Q_OBJECT
public:
    static GestaoSalaoServiceImpl* getInstance();
    QList<Mesa> getMesas() const override;
    bool alterarStatusMesa(int idMesa, Mesa::Status novoStatus) override;
private:
    GestaoSalaoServiceImpl(QObject *parent = nullptr);
    QList<Mesa> m_mesas;
};
