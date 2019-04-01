#ifndef CLIENTUI_H
#define CLIENTUI_H

#include <QWidget>
#include <QPushButton>
#include <QTcpSocket>
#include <QThread>

namespace Ui {
class clientUI;
}

class clientUI : public QWidget
{
    Q_OBJECT

public:
    explicit clientUI(QWidget *parent = nullptr);
    ~clientUI();
    QTcpSocket *socket;
    int8_t id;
    void send();

private slots:
    void on_pushButton_clicked();

private:
    Ui::clientUI *ui;

signals:
    void sig(QString);
};

#endif // CLIENTUI_H
