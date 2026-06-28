#pragma once
#include <QObject>
#include <QString>
#include "Controleacessoservice_global.h"
#include <Entidades.h>

/**
 * @brief Interface para o serviço de controle de acesso.
 * 
 * Esta interface define operações relacionadas à autenticação de usuários
 * em um sistema. Implementações concretas devem fornecer a lógica para 
 * login, logout e verificação do estado de autenticação.
 */
class CONTROLEACESSOSERVICE_EXPORT IControleAcessoService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construtor padrão da interface IControleAcessoService.
     * 
     * @param parent Ponteiro para o objeto pai (opcional).
     */
    explicit IControleAcessoService(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief Destrutor virtual.
     * 
     * Necessário para permitir a destruição adequada em heranças polimórficas.
     */
    virtual ~IControleAcessoService() = default;

    /**
     * @brief Autentica um usuário no sistema.
     * 
     * @param login Nome de login do usuário.
     * @param senha Senha correspondente ao login.
     * @return true Se a autenticação for bem-sucedida.
     * @return false Se a autenticação falhar.
     */
    virtual bool autenticar(const QString& login, const QString& senha) = 0;

    /**
     * @brief Encerra a sessão do usuário autenticado.
     */
    virtual void logout() = 0;

    /**
     * @brief Verifica se existe um usuário logado no sistema.
     * 
     * @return true Se houver um usuário autenticado.
     * @return false Caso contrário.
     */
    virtual bool isLogado() const = 0;

    /**
     * @brief Recupera as informações do usuário atualmente logado.
     * 
     * @return Usuario Objeto representando o usuário autenticado.
     */
    virtual Usuario usuarioLogado() const = 0;

signals:
    /**
     * @brief Sinal emitido quando o status de login do usuário é alterado.
     * 
     * @param logado Valor booleano indicando o novo estado de autenticação.
     * - true: Usuário autenticado.
     * - false: Usuário desconectado.
     */
    void statusLoginAlterado(bool logado);
};
