#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onNewFileClicked();
    void onSaveClicked();
    
private:
    Ui::MainWindow *ui;
    std::vector<MainWidget*> mainWidgets;
};

#endif // MAINWINDOW_H
