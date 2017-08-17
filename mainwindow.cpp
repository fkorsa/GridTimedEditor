#include "mainwindow.h"
#include "mainwidget.h"

#include "ui_mainwindow.h"
#include "ui_newfiledialog.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    connect(ui->actionNew, SIGNAL(triggered(bool)), this, SLOT(onNewFileClicked()));
    connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(onSaveClicked()));
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
        ui->tabWidget->addTab(mainWidget, "Untitled");
        mainWidgets.push_back(mainWidget);
    }
    delete uiNewFileDialog;
}

void MainWindow::onSaveClicked()
{
    if (ui->tabWidget->currentIndex() == -1)
    {
        return;
    }
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               QString(),
                               tr("TimedGrid (*.tmg)"));
    if (fileName.isEmpty())
    {
        return;
    }
    mainWidgets[ui->tabWidget->currentIndex()]->saveTo(fileName);
}
