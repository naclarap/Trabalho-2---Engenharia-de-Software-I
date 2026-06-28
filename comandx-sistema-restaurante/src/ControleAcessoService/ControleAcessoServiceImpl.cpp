#include "ControleAcessoServiceImpl.h"

ControleAcessoServiceImpl* ControleAcessoServiceImpl::getInstance() {
    static ControleAcessoServiceImpl instance;
    return &instance;
}

ControleAcessoServiceImpl::ControleAcessoServiceImpl(QObject *parent)
    : IControleAcessoService(parent) {}

bool ControleAcessoServiceImpl::autenticar(const QString& login, const QString& senha) {
    if (login.toLower() == "Juliano" && senha == "7647484") {
        if (!m_isLogado) {
            m_isLogado = true;
            m_usuarioLogado = {1, "garcom", "Garçom Padrão"};
            emit statusLoginAlterado(true);
        }
        return true;
    }
    return false;
}

void ControleAcessoServiceImpl::logout() {
    if (m_isLogado) {
        m_isLogado = false;
        m_usuarioLogado = {};
        emit statusLoginAlterado(false);
    }
}

bool ControleAcessoServiceImpl::isLogado() const { return m_isLogado; }
Usuario ControleAcessoServiceImpl::usuarioLogado() const { return m_usuarioLogado; }
