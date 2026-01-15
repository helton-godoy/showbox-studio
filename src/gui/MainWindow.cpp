#include "MainWindow.h"
#include "Canvas.h"
#include "ObjectInspector.h"
#include "PropertyEditor.h"
#include "core/StudioWidgetFactory.h"
#include "core/StudioController.h"
#include <QStatusBar>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QDockWidget>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Showbox Studio");
    resize(1200, 800);
    
    m_factory = new StudioWidgetFactory();
    m_controller = new StudioController(this);
    
    setupUI();
    createSampleWidgets();
    
    // Sincronizar seleção: Canvas -> Inspector & Property Editor
    connect(m_controller, &StudioController::widgetSelected, m_inspector, &ObjectInspector::selectItemForWidget);
    connect(m_controller, &StudioController::widgetSelected, m_propEditor, &PropertyEditor::setTargetWidget);
    
    // Atualizar hierarquia inicial
    m_inspector->updateHierarchy(m_canvas);
}

MainWindow::~MainWindow()
{
    delete m_factory;
}

void MainWindow::setupUI()
{
    statusBar()->showMessage("Pronto");

    // Central Widget: CANVAS
    m_canvas = new Canvas(this);
    setCentralWidget(m_canvas);

    // Left Dock: TOOLBOX & INSPECTOR (em abas)
    setTabPosition(Qt::LeftDockWidgetArea, QTabWidget::North);

    QDockWidget *dockInspector = new QDockWidget("Hierarquia", this);
    m_inspector = new ObjectInspector(dockInspector);
    dockInspector->setWidget(m_inspector);
    addDockWidget(Qt::LeftDockWidgetArea, dockInspector);

    QDockWidget *dockToolbox = new QDockWidget("Toolbox", this);
    QListWidget *listToolbox = new QListWidget(dockToolbox);
    listToolbox->addItem("PushButton");
    listToolbox->addItem("Label");
    listToolbox->addItem("Chart");
    dockToolbox->setWidget(listToolbox);
    addDockWidget(Qt::LeftDockWidgetArea, dockToolbox);
    
    tabifyDockWidget(dockInspector, dockToolbox);

    // Right Dock: PROPERTIES
    QDockWidget *dockProps = new QDockWidget("Propriedades", this);
    m_propEditor = new PropertyEditor(dockProps);
    dockProps->setWidget(m_propEditor);
    addDockWidget(Qt::RightDockWidgetArea, dockProps);
}

void MainWindow::createSampleWidgets()
{
    // Teste de criação via Factory
    QWidget *w1 = m_factory->createLabel("<h1>Bem-vindo ao Showbox Studio</h1>", "lbl_welcome");
    QWidget *w2 = m_factory->createPushButton("Clique-me", "btn_test");
    QWidget *w3 = m_factory->createChart("Gráfico de Vendas", "chart_vendas");

    m_canvas->addWidget(w1);
    m_canvas->addWidget(w2);
    m_canvas->addWidget(w3);

    // Registrar no controller para seleção
    m_controller->manageWidget(w1);
    m_controller->manageWidget(w2);
    m_controller->manageWidget(w3);
}


