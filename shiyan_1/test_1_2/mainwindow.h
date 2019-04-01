#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

private:
    void drawText();
//    QPainter *painter1;

protected:
    void paintEvent(QPaintEvent *event);

};

#endif // MAINWINDOW_H
