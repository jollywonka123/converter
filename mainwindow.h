#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "appcontext.h"

extern "C" {
#include "entrypoint.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AppContext context;
    void initializeContext();
    void initAppParams();
    void updateLabels();
    void showResult();
    void clearOutput();

private slots:
    void onConvertClicked();
    void inputTextChanged();
    void inputNumSystemSelected();
    void outputNumSystemSelected();

};
#endif // MAINWINDOW_H
