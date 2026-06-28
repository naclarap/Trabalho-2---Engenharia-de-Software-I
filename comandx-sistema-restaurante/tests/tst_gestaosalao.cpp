#include <QtTest>
#include <IGestaoSalaoService.h>
#include <GestaoSalaoServiceFactory.h>
#include <Entidades.h>

class TestGestaoSalao : public QObject
{
    Q_OBJECT
private slots:
    void cenario_visualizarMapaDeMesas();
};

void TestGestaoSalao::cenario_visualizarMapaDeMesas()
{
    // DADO que existem 10 mesas cadastradas no sistema
    IGestaoSalaoService* servico = GestaoSalaoServiceFactory::create();

    // QUANDO Juliano acede à tela do salão (aqui simulado pela chamada ao serviço)
    QList<Mesa> mesas = servico->getMesas();

    // ENTÃO ele deve visualizar todas as mesas numeradas de 1 a 10
    QCOMPARE(mesas.count(), 10);

    // E o status de cada mesa deve ser mostrado
    bool encontrouLivre = false;
    for(const Mesa& mesa : mesas) {
        QVERIFY(mesa.status == Mesa::Livre || mesa.status == Mesa::Ocupada);
        if(mesa.status == Mesa::Livre) encontrouLivre = true;
    }
    QVERIFY2(encontrouLivre, "Pelo menos uma mesa deveria estar livre no estado inicial.");
}
