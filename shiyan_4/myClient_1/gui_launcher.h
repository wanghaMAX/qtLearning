#ifndef GUI_LAUNCHER_H
#define GUI_LAUNCHER_H

#include <QObject>
#include <QWidget>
#include <QEvent>

class gui_launcher : public QObject
{
    Q_OBJECT
    QWidget *w;

public:
    explicit gui_launcher(QObject *parent = nullptr);
    virtual bool event(QEvent *ev){
        if(ev->type() == QEvent::User){
            w = new QWidget;
            w->show();
            return true;
        }
        return false;
    }

signals:

public slots:
};

#endif // GUI_LAUNCHER_H
