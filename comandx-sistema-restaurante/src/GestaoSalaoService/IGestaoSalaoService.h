#pragma once
#include <QObject>
#include <QList>
#include "gestaosalaoservice_global.h"
#include <Entidades.h>

/**
 * @brief Interface para o serviço de gestão do salão.
 * 
 * Esta interface define operações relacionadas ao gerenciamento
 * das mesas de um salão, incluindo consulta e alteração de status.
 * 
 * Implementações concretas devem fornecer a lógica de acesso e
 * atualização dos dados das mesas.
 */
class GESTAOSALAOSERVICE_EXPORT IGestaoSalaoService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construtor padrão da interface IGestaoSalaoService.
     * 
     * @param parent Ponteiro para o objeto pai (opcional).
     */
    explicit IGestaoSalaoService(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief Destrutor virtual.
     * 
     * Necessário para permitir destruição correta em heranças polimórficas.
     */
    virtual ~IGestaoSalaoService() = default;

    /**
     * @brief Recupera a lista de mesas do salão.
     * 
     * @return QList<Mesa> Lista com todas as mesas.
     */
    virtual QList<Mesa> getMesas() const = 0;

    /**
     * @brief Altera o status de uma mesa.
     * 
     * @param idMesa Identificador único da mesa.
     * @param novoStatus Novo status a ser atribuído (ex: Livre, Ocupada, Reservada).
     * @return true Se a alteração for bem-sucedida.
     * @return false Caso contrário.
     */
    virtual bool alterarStatusMesa(int idMesa, Mesa::Status novoStatus) = 0;

signals:
    /**
     * @brief Sinal emitido quando o status de uma mesa é alterado.
     * 
     * @param idMesa Identificador único da mesa.
     * @param novoStatus Novo status da mesa.
     */
    void statusMesaAlterado(int idMesa, Mesa::Status novoStatus);
};
