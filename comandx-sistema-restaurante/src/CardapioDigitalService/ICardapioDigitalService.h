#pragma once

#include <QObject>
#include <QList>
#include "CardapioDigitalService_global.h"  
#include "Entidades.h"

/**
 * @brief Interface para o serviço de cardápio digital.
 * 
 * Esta classe define a interface para manipulação e consulta de itens de um cardápio digital.
 * Implementações concretas devem herdar desta classe e fornecer a lógica para recuperação
 * dos itens e busca por ID.
 */
class CARDAPIODIGITALSERVICE_EXPORT ICardapioDigitalService : public QObject {
    Q_OBJECT
public:
    /**
     * @brief Construtor da interface ICardapioDigitalService.
     * 
     * @param parent Ponteiro para o objeto pai (opcional).
     */
    explicit ICardapioDigitalService(QObject *parent = nullptr) : QObject(parent) {}

    /**
     * @brief Destrutor virtual.
     * 
     * Permite destruição adequada em heranças polimórficas.
     */
    virtual ~ICardapioDigitalService() = default;

    /**
     * @brief Recupera a lista de todos os itens do cardápio.
     * 
     * @return QList<ItemCardapio> Lista contendo todos os itens disponíveis.
     */
    virtual QList<ItemCardapio> getItens() const noexcept = 0;

    /**
     * @brief Busca um item do cardápio a partir do seu ID.
     * 
     * @param id Identificador único do item.
     * @param item Referência onde o item encontrado será armazenado.
     * @return true Se o item foi encontrado.
     * @return false Se nenhum item correspondente foi encontrado.
     */
    virtual bool getItemPorId(int id, ItemCardapio& item) const = 0;
};
