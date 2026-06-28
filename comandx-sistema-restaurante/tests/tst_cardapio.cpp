#include <QtTest>
#include <ICardapioDigitalService.h>
#include <CardapioDigitalServiceFactory.h>
#include <Entidades.h>

class TestCardapio : public QObject
{
    Q_OBJECT
private slots:
    void cenario_visualizarCardapio();
};

void TestCardapio::cenario_visualizarCardapio()
{
    // DADO que existem produtos cadastrados
    ICardapioDigitalService* servico = CardapioDigitalServiceFactory::create();

    // QUANDO Juliano acessa o cardápio
    QList<ItemCardapio> cardapio = servico->getItens();

    // ENTÃO ele deve visualizar os produtos listados
    QVERIFY(cardapio.count() >= 3);

    bool encontrouPizza = false;
    bool encontrouRefri = false;
    bool encontrouPudim = false;

    for(const auto& item : cardapio) {
        if(item.nome == "Pizza Calabresa") {
            encontrouPizza = true;
            QCOMPARE(item.preco, 42.50);
        }
        if(item.nome == "Refrigerante Lata") {
            encontrouRefri = true;
            QCOMPARE(item.preco, 7.00);
        }
        if(item.nome == "Pudim de Leite Condensado") {
            encontrouPudim = true;
            QCOMPARE(item.preco, 10.00);
        }
    }
    QVERIFY(encontrouPizza && encontrouRefri && encontrouPudim);
}
