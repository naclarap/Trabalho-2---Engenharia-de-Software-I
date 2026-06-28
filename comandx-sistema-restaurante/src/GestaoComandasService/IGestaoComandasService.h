#pragma once
#include <QObject>
#include "Gestaocomandasservice_global.h"
#include <Entidades.h>

/**
 * @brief Interface para o serviço de gestão de comandas.
 * 
 * Esta interface define operações para criar, manipular e consultar 
 * comandas associadas às mesas de um estabelecimento. 
 * Implementações concretas devem fornecer a lógica de persistência 
 * e atualização dos dados das comandas.
 */
class GESTAOCOMANDASSERVICE_EXPORT IGestaoComandasService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construtor padrão da interface IGestaoComandasService.
     * 
     * @param parent Ponteiro para o objeto pai (opcional).
     */
    explicit IGestaoComandasService(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief Destrutor virtual.
     * 
     * Necessário para permitir destruição correta em heranças polimórficas.
     */
    virtual ~IGestaoComandasService() = default;

    /**
     * @brief Cria uma nova comanda associada a uma mesa específica.
     * 
     * @param idMesa Identificador único da mesa.
     * @return Comanda Objeto da comanda recém-criada.
     */
    virtual Comanda criarComandaParaMesa(int idMesa) = 0;

    /**
     * @brief Adiciona um item a uma comanda existente.
     * 
     * @param idComanda Identificador da comanda.
     * @param idItemCardapio Identificador do item do cardápio.
     * @param quantidade Quantidade do item a ser adicionado.
     * @param observacoes Observações opcionais (ex: "sem cebola").
     * @return true Se o item foi adicionado com sucesso.
     * @return false Se houve falha na operação.
     */
    virtual bool adicionarItem(int idComanda, int idItemCardapio, int quantidade,
                               const QString& observacoes = QString()) = 0;

    /**
     * @brief Recupera uma comanda pelo seu identificador.
     * 
     * @param idComanda Identificador único da comanda.
     * @return Comanda Objeto da comanda correspondente.
     */
    virtual Comanda getComandaPorId(int idComanda) const = 0;

    /**
     * @brief Recupera uma comanda associada a uma mesa.
     * 
     * @param idMesa Identificador único da mesa.
     * @return Comanda Objeto da comanda correspondente à mesa.
     */
    virtual Comanda getComandaPorMesa(int idMesa) const = 0;

    /**
     * @brief Calcula o valor total de uma comanda.
     * 
     * @param idComanda Identificador único da comanda.
     * @return double Valor total da comanda.
     */
    virtual double calcularTotalComanda(int idComanda) const = 0;

    /**
     * @brief Remove um item de uma comanda.
     * 
     * @param idComanda Identificador único da comanda.
     * @param idItem Identificador do item a ser removido.
     * @return true Se o item foi removido com sucesso.
     * @return false Caso contrário.
     */
    virtual bool removerItem(int idComanda, int idItem) = 0;

signals:
    /**
     * @brief Sinal emitido quando uma comanda é atualizada.
     * 
     * @param comanda Objeto da comanda atualizada.
     */
    void comandaAtualizada(const Comanda& comanda);
};
