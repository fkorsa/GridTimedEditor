#include "mainwindow.h"
#include "mainwidget.h"

#include "ui_mainwindow.h"
#include "ui_newfiledialog.h"

#include <functional>  

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(onNewFileClicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(onSaveClicked()));
    connect(ui->actionSave_as, SIGNAL(triggered(bool)), this, SLOT(onSaveAsClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNewFileClicked()
{
    Ui::NewFileDialog* uiNewFileDialog = new Ui::NewFileDialog;
    QDialog* newFileDialog = new QDialog(this);
    uiNewFileDialog->setupUi(newFileDialog);
    QDialog::DialogCode result = (QDialog::DialogCode)newFileDialog->exec();
    if (result == QDialog::Accepted)
    {
        MainWidget* mainWidget = new MainWidget(QSize(uiNewFileDialog->gridSizeX->value(), uiNewFileDialog->gridSizeY->value()), uiNewFileDialog->frameCount->value());
        auto tabIndex = ui->tabWidget->addTab(mainWidget, "Untitled");
        QObject::connect(mainWidget, &MainWidget::nameChanged, this, std::bind(&MainWindow::onTabNameChange, this, tabIndex, std::placeholders::_1));
        mainWidgets.push_back(mainWidget);
    }
    delete uiNewFileDialog;
}

void MainWindow::onSaveAsClicked()
{
    if (ui->tabWidget->currentIndex() == -1)
    {
        return;
    }
    mainWidgets[ui->tabWidget->currentIndex()]->saveAs();
}

void MainWindow::onSaveClicked()
{
    if (ui->tabWidget->currentIndex() == -1)
    {
        return;
    }
    mainWidgets[ui->tabWidget->currentIndex()]->save();
}

void MainWindow::onTabNameChange(int tabIndex, QString newName)
{
    ui->tabWidget->setTabText(tabIndex, newName);
}
