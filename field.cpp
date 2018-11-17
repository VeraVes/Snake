#include "field.h"


void Field::checkMove()
{
    head = body[body.size()-1];
    if (whereMove==righ)
    {
        body.push_back(QPoint(head.x()+1,head.y()));
    }
    if (whereMove==lef)
    {
        body.push_back(QPoint(head.x()-1,head.y()));
    }
    if (whereMove==up)
    {
        body.push_back(QPoint(head.x(),head.y()-1));
    }
    if (whereMove==down)
    {
        body.push_back(QPoint(head.x(),head.y()+1));
    }
}

void Field::makeNewFood()
{
    auto itw=walls.end();
    auto its=body.end();
    do
    {
        newFood = QPoint(rand()%m_columns,rand()%m_rows);
        itw=std::find(walls.begin(), walls.end(), newFood);
        its=std::find(body.begin(), body.end(), newFood);
    }
    while ((itw!=walls.end())||(its!=body.end()));
}

Field::Field(QWidget *parent) : QWidget(parent)
{
    body.push_back(QPoint(1,1));
    body.push_back(QPoint(2,1));
    body.push_back(QPoint(3,1));
    whereMove = righ;
    tryMove = whereMove;
    counter=0;
    m_rows=30;
    m_columns=50;
    width=5;
    timerInterval=100;
    idTimer=0;
    killTime=true;
    for (int i=0;i<m_columns; i++)
    {
        walls.push_back(QPoint(i, 0));
        walls.push_back(QPoint(i,m_rows-1));
    }
    for (int i=1;i<m_rows-1; i++)
    {
        walls.push_back(QPoint(0, i));
        walls.push_back(QPoint(m_columns-1,i));
    }
    food = QPoint(m_columns,m_rows);
    newFood = QPoint(m_columns,m_rows);
    head = body[body.size()-1];
}

void Field::clearField()
{
    repaint();
}

void Field::slotNewGame()
{
    if(killTime==false)
    {
        killTimer(idTimer);
        killTime==true;
    }
    counter = 0;
    emit setCount(counter);
    food = QPoint(m_columns,m_rows);
    makeNewFood();
    whereMove = righ;
    tryMove=whereMove;
    idTimer=startTimer(timerInterval);
    killTime=false;
    while(!body.empty())
    {
        body.pop_front();
    };
    body.push_back(QPoint(1,1));
    body.push_back(QPoint(2,1));
    body.push_back(QPoint(3,1));
    setFocus();
    repaint();
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    for (int i = 0; i<m_columns; i++) //рисуем поле
    {
        for (int j = 0; j<m_rows; j++)
        {
            painter.fillRect(QRect(i*width,j*width,width-1,width-1),Qt::lightGray);
        }
    }
    int i=0;
    while(i<body.size()) //рисуем змейку
    {
        painter.fillRect(QRect(body[i].x()*width,body[i].y()*width,width-1,width-1),Qt::blue);
        ++i;
    }
    i=0;
    while(i<walls.size()) //рисуем стены
    {
        painter.fillRect(QRect(walls[i].x()*width,walls[i].y()*width,width-1,width-1),Qt::darkGray);
        ++i;
    }
    painter.fillRect(QRect(newFood.x()*width,newFood.y()*width,width-1,width-1),Qt::red);
    painter.fillRect(QRect(food.x()*width,food.y()*width,width-1,width-1),Qt::green);
}

void Field::timerEvent(QTimerEvent *event)
{
    whereMove = tryMove;
    checkMove(); //продвинуть голову на ход
    if (food!=body[0]) //если старая еда не дошла до хвоста змеи
    {
        body.pop_front();//удалить попу
    }
    else
    {
        food=QPoint(m_columns,m_rows); //иначе удалить еду с поля
    }
    head = body[body.size()-1];
    auto itw=std::find(walls.begin(), walls.end(), head); //ищем совпадение головы со стенами
    auto its=std::find(body.begin(), body.end()-2, head);//ищем совпадение головы с телом
    if ((itw!=walls.end())||(its!=body.end()-2)) //если врезались, заканчиваем игру
    {
        killTimer(idTimer);
        killTime=true;
        QMap<int, QString> recordsList;
        QSettings *settings = new QSettings("C:\\Users\\adm\\Documents\\My_proj\\Zmeyka\\leaders.ini",QSettings::IniFormat);
        for(int i=1 ;i < 4;i++) //считали в списки
        {
            recordsList[settings->value("player"+QString::number(i)+"score").toInt()]=settings->value("player"+QString::number(i)+"name").toString();
        }
        auto recordsitv=recordsList.begin();
        auto recordsitk=recordsList.keyBegin();
        for(int i=1 ;i <= recordsList.size();i++)
        {
            qDebug()<<*recordsitv<<*recordsitk;
            ++recordsitv;
            ++recordsitk;
        }
        qDebug()<<endl;
        if (counter>*(recordsList.keyBegin()))
        {
        Records* records = new Records;
        if (records->exec() == QDialog::Accepted)
            {
                recordsList.remove(*(recordsList.keyBegin()));
                recordsList[counter]="kaka";
            }
        delete records;
        }
        recordsitv=recordsList.begin();
        recordsitk=recordsList.keyBegin();
        for(int i=1 ;i <= recordsList.size();i++)
        {
            qDebug()<<*recordsitv<<*recordsitk;
            ++recordsitv;
            ++recordsitk;
        }
        recordsitv=recordsList.begin();
        recordsitk=recordsList.keyBegin();
        for(int i=1;i<= recordsList.size();i++)
        {
            settings->setValue("player"+QString::number(i)+"name", *recordsitv);
            ++recordsitv;
            settings->setValue("player"+QString::number(i)+"score",*recordsitk);
            ++recordsitk;
        }
        settings->sync();//записали
        EndGameDialog* endGameDialog = new EndGameDialog;
        if (endGameDialog->exec() == QDialog::Accepted)
        {
            emit signalNewGame();
        }
        delete endGameDialog;
    }
    if (newFood==head) //если скушали еду
    {
        food = newFood;
        ++counter;
        emit setCount(counter);
        makeNewFood(); //сделать новую пищу
    }
    repaint();
}

void Field::keyPressEvent(QKeyEvent *event) //установить куда будем двигаться в следующий ход
{
    if (((whereMove==righ)||(whereMove==lef))&&(event->key()==Qt::Key_Up))
    {
        tryMove=up;
        return;
    }
    if (((whereMove==righ)||(whereMove==lef))&&(event->key()==Qt::Key_Down))
    {
        tryMove=down;
        return;
    }
    if (((whereMove==up)||(whereMove==down))&&(event->key()==Qt::Key_Right))
    {
        tryMove=righ;
        return;
    }
    if (((whereMove==up)||(whereMove==down))&&(event->key()==Qt::Key_Left))
    {
        tryMove=lef;
    }
}

//for(int i=0;i<vec.size();i++)
//{
//    qDebug()<<vec[i];
//}
//for(int i=0;i<body.size();i++)
//{
//    qDebug()<<body[i];
//}
