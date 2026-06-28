// libs/GestaoSalaoService/GestaoSalaoServiceImpl.cpp

#include "GestaoSalaoServiceImpl.h"

// A implementação deve estar aqui!
GestaoSalaoServiceImpl* GestaoSalaoServiceImpl::getInstance() {
    static GestaoSalaoServiceImpl instance;
    return &instance;
}

// O construtor deve ser implementado aqui!
GestaoSalaoServiceImpl::GestaoSalaoServiceImpl(QObject *parent) : IGestaoSalaoService(parent) {
    m_mesas << Mesa{1, "Mesa 01", Mesa::Livre};
    m_mesas << Mesa{2, "Mesa 02", Mesa::Livre};
    m_mesas << Mesa{3, "Mesa 03", Mesa::Livre};
    m_mesas << Mesa{4, "Mesa 04", Mesa::Livre};
    m_mesas << Mesa{5, "Mesa 05", Mesa::Livre};
    m_mesas << Mesa{6, "Mesa 06", Mesa::Livre};
    m_mesas << Mesa{7, "Mesa 07", Mesa::Livre};
    m_mesas << Mesa{8, "Mesa 08", Mesa::Livre};
    m_mesas << Mesa{9, "Mesa 09", Mesa::Livre};
    m_mesas << Mesa{10, "Mesa 10", Mesa::Livre};

}

QList<Mesa> GestaoSalaoServiceImpl::getMesas() const {
    return m_mesas;
}

bool GestaoSalaoServiceImpl::alterarStatusMesa(int idMesa, Mesa::Status novoStatus) {
    for (auto& mesa : m_mesas) {
        if (mesa.id == idMesa) {
            if (mesa.status != novoStatus) {
                mesa.status = novoStatus;
                emit statusMesaAlterado(idMesa, novoStatus);
            }
            return true;
        }
    }
    return false;
}
