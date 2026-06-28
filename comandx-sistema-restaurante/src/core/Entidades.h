#pragma once

#include <QString>
#include <QList>
#include <QDateTime>
#include "core_global.h"

/**
 * @brief Estrutura que representa um usuário do sistema.
 */
struct CORE_EXPORT Usuario {
    int id;          /**< Identificador único do usuário. */
    QString login;   /**< Login utilizado para autenticação. */
    QString nome;    /**< Nome completo do usuário. */
};

/**
 * @brief Estrutura que representa um item do cardápio.
 */
struct CORE_EXPORT ItemCardapio {
    int id;          /**< Identificador único do item. */
    QString nome;    /**< Nome do item. */
    double preco;    /**< Preço unitário do item. */
};

/**
 * @brief Estrutura que representa uma mesa no salão.
 */
struct CORE_EXPORT Mesa {
    /**
     * @brief Enumeração de status possíveis para uma mesa.
     */
    enum Status { 
        Livre,   /**< Mesa disponível para uso. */
        Ocupada  /**< Mesa atualmente ocupada. */
    };

    int id;         /**< Identificador único da mesa. */
    QString nome;   /**< Nome ou número da mesa. */
    Status status;  /**< Status atual da mesa. */
};

/**
 * @brief Estrutura que representa um item dentro de uma comanda.
 */
struct ItemComanda {
    int idItemCardapio;   /**< Identificador do item do cardápio. */
    QString nome;         /**< Nome do item. */
    int quantidade;       /**< Quantidade pedida. */
    double precoUnitario; /**< Valor unitário do item. */
    QString observacoes;  /**< Observações adicionais (ex: "sem sal"). */
};

/**
 * @brief Estrutura que representa uma comanda associada a uma mesa.
 */
struct CORE_EXPORT Comanda {
    int id;                    /**< Identificador único da comanda. */
    int idMesa;                /**< Identificador da mesa associada. */
    QDateTime abertura;        /**< Data e hora de abertura da comanda. */
    QList<ItemComanda> itens;  /**< Lista de itens adicionados à comanda. */
    bool ativa = false;        /**< Indica se a comanda está ativa (aberta). */
};
