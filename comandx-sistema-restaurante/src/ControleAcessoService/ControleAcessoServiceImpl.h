#pragma once
#include "IControleAcessoService.h"

class ControleAcessoServiceImpl : public IControleAcessoService {
    Q_OBJECT
public:
    static ControleAcessoServiceImpl* getInstance();

    bool autenticar(const QString& login, const QString& senha) override;
    void logout() override;
    bool isLogado() const override;
    Usuario usuarioLogado() const override;

private:
    ControleAcessoServiceImpl(QObject *parent = nullptr);
    ~ControleAcessoServiceImpl() override = default;
    ControleAcessoServiceImpl(const ControleAcessoServiceImpl&) = delete;
    ControleAcessoServiceImpl& operator=(const ControleAcessoServiceImpl&) = delete;

    bool m_isLogado = false;
    Usuario m_usuarioLogado;
};
