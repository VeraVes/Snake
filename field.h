#ifndef FIELD_H
#define FIELD_H

#include "endgamedialog.h"
#include "records.h"
#include <QObject>
#include <QWidget>
#include <QQueue>
#include <QPoint>
#include <QPaintEvent>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QList>
#include <QSettings>
#include <QMap>

enum Move {righ, lef, up, down};

class Field : public QWidget
{
    Q_OBJECT
    QList<QPoint> body; //координаты каждого звена тела змеи
    Move whereMove; //переменная запоминает, куда было совершено последнее движение
    Move tryMove;
    int counter; //подсчет очков
    int m_rows; //длина поля
    int m_columns; //ширина поля
    int width; // толщина клетки
    int timerInterval; //частота таймера
    int idTimer;
    QPoint food;
    QPoint newFood;
    QVector<QPoint> walls;
    QPoint head;
    void checkMove();
    void makeNewFood();
    bool killTime;
friend class Food;
public:
    explicit Field(QWidget *parent = nullptr);
    void clearField();
signals:
    void signalNewGame();
    void setCount(int);
public slots:
    void slotNewGame();
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void timerEvent(QTimerEvent *event);
    virtual void keyPressEvent(QKeyEvent *event);
};



#endif // FIELD_H
