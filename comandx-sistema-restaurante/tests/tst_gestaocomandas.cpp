#include <QtTest>
#include <IGestaoComandasService.h>
#include <GestaoComandasServiceFactory.h>
#include <IGestaoSalaoService.h>
#include <GestaoSalaoServiceFactory.h>
#include <Entidades.h>

class TestGestaoComandas : public QObject
{
    Q_OBJECT
private:
    IGestaoComandasService* servicoComandas;
    IGestaoSalaoService* servicoSalao;

private slots:
    void init() {
        // Setup executado antes de cada teste para garantir um estado limpo
        servicoComandas = GestaoComandasServiceFactory::create();
        servicoSalao = GestaoSalaoServiceFactory::create();
        // Resetar o estado das mesas para 'Livre'
        for(const auto& mesa : servicoSalao->getMesas()) {
            servicoSalao->alterarStatusMesa(mesa.id, Mesa::Livre);
        }
    }

    void cenario_criarComanda();
    void cenario_adicionarProduto();
    void cenario_fecharComanda();
};

void TestGestaoComandas::cenario_criarComanda()
{
    // DADO que a mesa 7 está livre
    const int idMesa = 7;
    QVERIFY(servicoSalao->getMesas().at(idMesa - 1).status == Mesa::Livre);

    // QUANDO Juliano seleciona a mesa 7 e cria uma nova comanda
    Comanda comanda = servicoComandas->criarComandaParaMesa(idMesa);

    // ENTÃO uma comanda deve ser criada para a mesa 7
    QVERIFY(comanda.ativa);
    QCOMPARE(comanda.idMesa, idMesa);

    // E a mesa 7 passa a estar com status "Ocupada"
    QCOMPARE(servicoSalao->getMesas().at(idMesa - 1).status, Mesa::Ocupada);
}

void TestGestaoComandas::cenario_adicionarProduto()
{
    // DADO que a comanda da mesa 7 está ativa
    Comanda comanda = servicoComandas->criarComandaParaMesa(7);
    const int idPizza = 1; // ID da Pizza Calabresa

    // QUANDO Juliano adiciona 2 unidades de "Pizza Calabresa" com observação
    bool resultado = servicoComandas->adicionarItem(comanda.id, idPizza, 2, "Sem cebola");
    QVERIFY(resultado);

    // ENTÃO a comanda 7 deve registar os itens corretamente
    Comanda comandaAtualizada = servicoComandas->getComandaPorId(comanda.id);
    QCOMPARE(comandaAtualizada.itens.count(), 1);
    QCOMPARE(comandaAtualizada.itens.first().idItemCardapio, idPizza);
    QCOMPARE(comandaAtualizada.itens.first().quantidade, 2);
    QCOMPARE(comandaAtualizada.itens.first().observacoes, QString("Sem cebola"));
}

void TestGestaoComandas::cenario_fecharComanda()
{
    // DADO que a comanda 7 possui itens registados
    Comanda comanda = servicoComandas->criarComandaParaMesa(7);
    servicoComandas->adicionarItem(comanda.id, 1, 2, ""); // 2x Pizza a 42.50 = 85.00

    // QUANDO Juliano solicita fechamento da comanda (aqui simulado pelo cálculo do total)
    double total = servicoComandas->calcularTotalComanda(comanda.id);

    // ENTÃO o sistema deve calcular o total
    QCOMPARE(total, 85.00);
}

QTEST_MAIN(TestGestaoComandas)
#include "tst_gestaocomandas.moc"



