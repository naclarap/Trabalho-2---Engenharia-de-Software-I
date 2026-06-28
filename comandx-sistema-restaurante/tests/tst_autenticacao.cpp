#include <QtTest>
#include <IControleAcessoService.h>
#include <ControleAcessoServiceFactory.h>
#include <Entidades.h>

class TestAutenticacao : public QObject
{
    Q_OBJECT
private slots:
    void cenario_loginValido();
    void cenario_loginInvalido();
};

void TestAutenticacao::cenario_loginValido()
{
    // DADO que o garçom Juliano está cadastrado no sistema
    IControleAcessoService* servico = ControleAcessoServiceFactory::create();

    // QUANDO Juliano insere seu login e senha corretamente
    bool resultado = servico->autenticar("Juliano", "7647484");

    // ENTÃO ele deve ser autenticado
    QVERIFY2(resultado, "A autenticação deveria ter sido bem-sucedida.");

    // E (verificação de estado) o seu nome deve ser "Juliano"
    QCOMPARE(servico->usuarioLogado().nome, QString("Juliano"));

    servico->logout(); // Limpa o estado para o próximo teste
}

void TestAutenticacao::cenario_loginInvalido()
{
    // DADO que o garçom Juliano está cadastrado
    IControleAcessoService* servico = ControleAcessoServiceFactory::create();

    // QUANDO Juliano insere a senha errada
    bool resultado = servico->autenticar("Juliano", "123456");

    // ENTÃO o sistema deve exibir a mensagem "Senha incorreta" (verificação da lógica)
    QVERIFY2(!resultado, "A autenticação com senha errada deveria falhar.");

    // E não permitir acesso à tela inicial (verificação de estado)
    QVERIFY2(!servico->isLogado(), "O estado do serviço deveria ser 'não logado'.");
}


