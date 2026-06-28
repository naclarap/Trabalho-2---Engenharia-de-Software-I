#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QListWidget>
#include <QLabel>
#include <QMap>

#include <IControleAcessoService.h>
#include <IGestaoSalaoService.h>
#include <ICardapioDigitalService.h>
#include <IGestaoComandasService.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginClicked();
    void onLogoutClicked();
    void onMesaClicked(int idMesa);
    void onAdicionarItemClicked();
    void onVoltarParaSalaoClicked();

    // Slots para reagir aos sinais dos serviços
    void handleStatusLogin(bool logado);
    void handleStatusMesa(int idMesa, Mesa::Status novoStatus);
    void handleComandaAtualizada(const Comanda& comanda);

private:
    void setupUI();
    void setupServices();
    void setupConnections();

    void showLoginPage();
    void showSalaoPage();
    void showComandaPage(int idMesa);

    void popularMesas();
    void popularCardapio();
    void atualizarDisplayComanda(const Comanda& comanda);

    // Serviços
    IControleAcessoService* m_servicoAcesso;
    IGestaoSalaoService* m_servicoSalao;
    ICardapioDigitalService* m_servicoCardapio;
    IGestaoComandasService* m_servicoComandas;

    // UI Widgets
    QStackedWidget *m_stackedWidget;
    QWidget *m_loginPage;
    QWidget *m_salaoPage;
    QWidget *m_comandaPage;

    // Login page
    QLineEdit *m_loginLineEdit;
    QLineEdit *m_senhaLineEdit;

    // Salão Page
    QGridLayout *m_layoutMesas;
    QMap<int, QPushButton*> m_botoesMesa;

    // Comanda Page
    QLabel* m_labelTituloComanda;
    QListWidget* m_cardapioListWidget;
    QListWidget* m_comandaListWidget;
    int m_comandaAtualId = -1;
};
