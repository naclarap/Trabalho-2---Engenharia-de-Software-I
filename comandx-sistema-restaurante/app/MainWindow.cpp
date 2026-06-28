#include "MainWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

// Inclusão das Fábricas
#include <ControleAcessoServiceFactory.h>
#include <GestaoSalaoServiceFactory.h>
#include <CardapioDigitalServiceFactory.h>
#include <GestaoComandasServiceFactory.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupServices();
    setupUI();
    setupConnections();

    setWindowTitle("ComandX - Sprint 1");
    setMinimumSize(800, 600);

    // Estado inicial
    handleStatusLogin(m_servicoAcesso->isLogado());
}

MainWindow::~MainWindow() {}

void MainWindow::setupServices() {
    m_servicoAcesso = ControleAcessoServiceFactory::create();
    m_servicoSalao = GestaoSalaoServiceFactory::create();
    m_servicoCardapio = CardapioDigitalServiceFactory::create();
    m_servicoComandas = GestaoComandasServiceFactory::create();
}

void MainWindow::setupUI() {
    // ---- Página de Login ----
    m_loginPage = new QWidget;
    QFormLayout *loginLayout = new QFormLayout(m_loginPage);
    m_loginLineEdit = new QLineEdit;
    m_senhaLineEdit = new QLineEdit;
    m_senhaLineEdit->setEchoMode(QLineEdit::Password);
    QPushButton *loginButton = new QPushButton("Entrar");
    loginLayout->addRow("Usuário:", m_loginLineEdit);
    loginLayout->addRow("Senha:", m_senhaLineEdit);
    loginLayout->addRow(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    // ---- Página do Salão ----
    m_salaoPage = new QWidget;
    QVBoxLayout *salaoVLayout = new QVBoxLayout(m_salaoPage);
    QPushButton* logoutButton = new QPushButton("Logout");
    m_layoutMesas = new QGridLayout;
    salaoVLayout->addWidget(logoutButton, 0, Qt::AlignRight);
    salaoVLayout->addLayout(m_layoutMesas);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);

    // ---- Página da Comanda ----
    m_comandaPage = new QWidget;
    QGridLayout* comandaLayout = new QGridLayout(m_comandaPage);
    m_labelTituloComanda = new QLabel("Comanda");
    m_cardapioListWidget = new QListWidget;
    m_comandaListWidget = new QListWidget;
    QPushButton* btnAdicionar = new QPushButton("Adicionar Item >>");
    QPushButton* btnVoltar = new QPushButton("<< Voltar para o Salão");
    comandaLayout->addWidget(m_labelTituloComanda, 0, 0, 1, 2);
    comandaLayout->addWidget(new QLabel("Cardápio"), 1, 0);
    comandaLayout->addWidget(new QLabel("Itens na Comanda"), 1, 1);
    comandaLayout->addWidget(m_cardapioListWidget, 2, 0);
    comandaLayout->addWidget(m_comandaListWidget, 2, 1);
    comandaLayout->addWidget(btnAdicionar, 3, 0);
    comandaLayout->addWidget(btnVoltar, 3, 1);
    connect(btnAdicionar, &QPushButton::clicked, this, &MainWindow::onAdicionarItemClicked);
    connect(btnVoltar, &QPushButton::clicked, this, &MainWindow::onVoltarParaSalaoClicked);


    // ---- Widget principal ----
    m_stackedWidget = new QStackedWidget;
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_salaoPage);
    m_stackedWidget->addWidget(m_comandaPage);
    setCentralWidget(m_stackedWidget);
}

void MainWindow::setupConnections() {
    connect(m_servicoAcesso, &IControleAcessoService::statusLoginAlterado, this, &MainWindow::handleStatusLogin);
    connect(m_servicoSalao, &IGestaoSalaoService::statusMesaAlterado, this, &MainWindow::handleStatusMesa);
    connect(m_servicoComandas, &IGestaoComandasService::comandaAtualizada, this, &MainWindow::handleComandaAtualizada);
}

void MainWindow::onLoginClicked() {
    if (!m_servicoAcesso->autenticar(m_loginLineEdit->text(), m_senhaLineEdit->text())) {
        QMessageBox::warning(this, "Erro", "Usuário ou senha inválidos.");
    }
}

void MainWindow::onLogoutClicked() {
    m_servicoAcesso->logout();
}

void MainWindow::handleStatusLogin(bool logado) {
    if (logado) {
        showSalaoPage();
    } else {
        m_loginLineEdit->clear();
        m_senhaLineEdit->clear();
        showLoginPage();
    }
}

void MainWindow::showLoginPage() {
    m_stackedWidget->setCurrentWidget(m_loginPage);
}

void MainWindow::showSalaoPage() {
    popularMesas();
    m_stackedWidget->setCurrentWidget(m_salaoPage);
}

void MainWindow::popularMesas() {
    // Limpa layout
    qDeleteAll(m_botoesMesa);
    m_botoesMesa.clear();

    QList<Mesa> mesas = m_servicoSalao->getMesas();
    int row = 0, col = 0;
    for (const Mesa& mesa : mesas) {
        QPushButton* btn = new QPushButton(mesa.nome);
        btn->setMinimumSize(100, 80);
        m_botoesMesa[mesa.id] = btn;
        handleStatusMesa(mesa.id, mesa.status); // Define cor inicial

        connect(btn, &QPushButton::clicked, this, [this, id = mesa.id](){
            onMesaClicked(id);
        });

        m_layoutMesas->addWidget(btn, row, col);
        col++;
        if (col >= 4) { col = 0; row++; }
    }
}

void MainWindow::handleStatusMesa(int idMesa, Mesa::Status novoStatus) {
    if (m_botoesMesa.contains(idMesa)) {
        QString style = "color: white; font-weight: bold;";
        if (novoStatus == Mesa::Livre) {
            style += "background-color: green;";
        } else {
            style += "background-color: red;";
        }
        m_botoesMesa[idMesa]->setStyleSheet(style);
    }
}

void MainWindow::onMesaClicked(int idMesa) {
    showComandaPage(idMesa);
}

void MainWindow::showComandaPage(int idMesa) {
    m_labelTituloComanda->setText(QString("Gerenciando Comanda da Mesa %1").arg(idMesa));

    // Verifica se já existe uma comanda ou cria uma nova
    Comanda comanda = m_servicoComandas->getComandaPorMesa(idMesa);
    if (!comanda.ativa) {
        comanda = m_servicoComandas->criarComandaParaMesa(idMesa);
    }
    m_comandaAtualId = comanda.id;

    popularCardapio();
    atualizarDisplayComanda(comanda);
    m_stackedWidget->setCurrentWidget(m_comandaPage);
}

void MainWindow::popularCardapio() {
    m_cardapioListWidget->clear();
    QList<ItemCardapio> itens = m_servicoCardapio->getItens();
    for (const auto& item : itens) {
        QString texto = QString("%1 - R$ %2").arg(item.nome).arg(item.preco, 0, 'f', 2);
        QListWidgetItem* listItem = new QListWidgetItem(texto);
        listItem->setData(Qt::UserRole, item.id); // Guarda o ID do item
        m_cardapioListWidget->addItem(listItem);
    }
}

void MainWindow::onAdicionarItemClicked() {
    QListWidgetItem* selected = m_cardapioListWidget->currentItem();
    if (!selected || m_comandaAtualId == -1) return;

    int idItem = selected->data(Qt::UserRole).toInt();
    m_servicoComandas->adicionarItem(m_comandaAtualId, idItem, 1); // Quantidade 1 para simplicidade
}

void MainWindow::handleComandaAtualizada(const Comanda& comanda) {
    if (comanda.id == m_comandaAtualId) {
        atualizarDisplayComanda(comanda);
    }
}

void MainWindow::atualizarDisplayComanda(const Comanda& comanda) {
    m_comandaListWidget->clear();
    double total = 0.0;
    for (const auto& item : comanda.itens) {
        QString texto = QString("%1x %2 (R$ %3)")
        .arg(item.quantidade)
            .arg(item.nome)
            .arg(item.precoUnitario * item.quantidade, 0, 'f', 2);
        m_comandaListWidget->addItem(texto);
        total += item.precoUnitario * item.quantidade;
    }
    m_comandaListWidget->addItem("");
    m_comandaListWidget->addItem(QString("TOTAL: R$ %1").arg(total, 0, 'f', 2));
}

void MainWindow::onVoltarParaSalaoClicked() {
    m_comandaAtualId = -1;
    showSalaoPage();
}
