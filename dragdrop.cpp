#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dragdrop.h"

#include <QMimeData>
#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QMouseEvent>
#include <QString>


/**
  @fn dragdrop
  Конструктор
*/
dragdrop::dragdrop(QWidget *parent):
    QTableWidget(parent),
    spisok(new QLinkedList<Auto>),
    dir_sp(new QLinkedList<DirectorySpisok>)
{
    next = prev = nullptr;
}

void dragdrop::open(QString fileName)
{
    QFile file(fileName); /// Объект с файлом, название которого переданного в функцию
    QString text; /// Переменная, в которую будут поочереди записываться строчки из файла

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd()) /// Цикл будет работать, пока не будет записан весь файл
        {
            text = file.readLine(); /// Записываем в переменную строчку из файла
            addString(text);
        }

        file.close();
    }
}

void dragdrop::save(QString fileName)
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8"));

    QFile file(fileName); /// Объект с файлом, название которого переданного в функцию
    QTextStream writeStream(&file);
    QLinkedList<Auto>::iterator iter;
    QLinkedList<DirectorySpisok>::iterator dirIter;

    int i = 1;
    if(file.open(QIODevice::WriteOnly))
    {
        for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        {
            writeStream << i << ';';
            writeStream << iter->getNumber() << ';';
            writeStream << iter->getOwner() << ';';
            writeStream << iter->getDate() << ';';
            writeStream << iter->getTime() << ';';
            writeStream << iter->getType() << ';';
            writeStream << iter->getPrice() << ';';

            for(int j=7; j < this->horizontalHeader()->count(); j++)
                for(dirIter=this->dir_sp->begin(); dirIter!=this->dir_sp->end(); dirIter++)
                    if(this->horizontalHeaderItem(j)->text() == dirIter->name){
                        if(!this->item(i - 1, j)->text().isEmpty())
                            writeStream << QString::number(dirIter->getPos(this->item(i - 1, j)->text())) << ';';
                        else
                            writeStream << "0;";
                    }

            if(iter!=--spisok->end())
                writeStream << "\n";
        }

        file.close();
    }
}

void dragdrop::addString(QString data)
{
    QStringList list = data.split(";"); /// Массив, в который записываются участки строчки с разделением по точке с запятой

    Auto *newAuto = new Auto(list.at(1), /// Создаем объект, передавая в конструктор данные из массива
                             list.at(2),
                             list.at(3),
                             list.at(4).toInt(),
                             list.at(5).toInt(),
                             list.at(6).toInt());

    this->spisok->push_back(*newAuto);
    free(newAuto);
}

void dragdrop::removeString(int num)
{
    QLinkedList<Auto>::iterator iter;

    int i = 1; /// Переменная-счетчик

    for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        if(i == num){
            spisok->erase(iter);
            break;
        }
}

QLinkedList<Auto>::iterator dragdrop::get(int id)
{
    QLinkedList<Auto>::iterator iter;

    int i = 0; /// Переменная-счетчик

    for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        if (i == id)
            return iter; /// Если запрашиваемое id совпадает с номер объекта по списку, возвращаем его

    return nullptr; /// Если совпадения не произошло, возвращаем пустой указатель
}

void dragdrop::openDir(QString fileName, QString dirName)
{
    DirectorySpisok *newDirectorySpisok = new DirectorySpisok();
    newDirectorySpisok->openDir(fileName);
    newDirectorySpisok->name = dirName;

    dir_sp->push_back(*newDirectorySpisok);

    free(newDirectorySpisok);
}

void dragdrop::removeDir(int num)
{
    QLinkedList<DirectorySpisok>::iterator iter;
    int i = 1;

    for(iter=dir_sp->begin();iter!=dir_sp->end();iter++,i++)
        if(i == num){
            dir_sp->erase(iter);
            break;
        }
}

/**
  @fn mousePressEvent
  Метод, отслеживающий откуда началось перетаскивание
  @param event - параметр, отвечающий за событие (нажатие, удерживание кнопок мыши и т.п.)
*/
void dragdrop::mousePressEvent(QMouseEvent *event)
{
    QTableWidget::mousePressEvent(event);
    startPoint = event->pos();
}


/**
  @fn mouseMoveEvent
  Метод, отвечающий за перетаскивание
  @param event - параметр, отвечающий за событие (нажатие, удерживание кнопок мыши и т.п.)
  Данные процессора записываются в переменную str
  А потом в объект типа MimeData
*/
void dragdrop::mouseMoveEvent(QMouseEvent *event)
{
    QString str;

    if (( event->buttons() & Qt::LeftButton ) && QApplication::startDragDistance() <= ( event->pos() - startPoint ).manhattanLength())
    {

    QModelIndex id = indexAt(event->pos());

    if(id.isValid())
    {
        setDragDropMode(QAbstractItemView::DragDrop);
        QLinkedList<DirectorySpisok>::iterator iter;
        bool flag = true;

        for (int i = 0; i < this->horizontalHeader()->count(); i++){
            for(iter=this->dir_sp->begin(); iter!=this->dir_sp->end(); iter++)
                if(this->horizontalHeaderItem(i)->text() == iter->name){
                    str += QString::number(iter->getPos(item(currentItem()->row(), i)->text())) + ";";
                    flag = false;
                }
            if(flag)
                str += item(currentItem()->row(), i)->text() + ";";
            flag = true;
        }

          QDrag *drag = new QDrag(this);
          QMimeData * mimeData = new QMimeData();
          mimeData->setText(str);
          drag->setMimeData(mimeData);
          drag->exec();
          this->setAcceptDrops(true);
        }
    else
    {
        setDragDropMode(QAbstractItemView::NoDragDrop);
    }
  }
}

void dragdrop::dragEnterEvent(QDragEnterEvent *event)
{
    event->setAccepted(true);
}

void dragdrop::dragMoveEvent(QDragMoveEvent *event)
{
    event->setAccepted(true);
}

void dragdrop::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->setAccepted(true);
}

void dragdrop::dropEvent(QDropEvent *event)
{
    QPoint dropPoint = event->pos();
    QModelIndex id = indexAt(dropPoint);

    if(id.isValid())
        if (event->mimeData()->text() != ""){
            QStringList str = event->mimeData()->text().split(';');

            for(int i = 1; i < this->horizontalHeader()->count(); i++){
                item(itemAt(dropPoint)->row(), i)->setText(str.at(i));
            }
        }
}

dragdrop *TableSpisok::get(int id)
{
    id++;
    dragdrop *current = nullptr; /// Указатель на текущий объект
    dragdrop *nextTable = first; /// Указатель на следующий объект

    int i = 0; /// Переменная-счетчик

    while(nextTable) /// Цикл проходится по всем объектам списка
    {
        i++;
        current = nextTable;
        nextTable = nextTable->next;

        if (i == id) return current; /// Если запрашиваемое id совпадает с номер объекта по списку, возвращаем его
    }
    return nullptr; /// Если совпадения не произошло, возвращаем пустой указатель
}


void TableSpisok::removeTable(int num)
{
    dragdrop *prev = nullptr, *next = nullptr, *current = first; /// Указатели на предыдущий, текущий и следующий объекты

    int i = 1; /// Переменная-счетчик
    num += 1;

    if (number == 1){
        first = nullptr; /// Обнуляем указатель на первый элемент
        last = nullptr; /// Обнуляем указатель на последний элемент
        delete current; /// Очищаем память
        number = 0; /// Обнуляем переменную, отвечающую за количество объектов в списке
    }
    else{
        while (i != num){ /// Цикл будет работать до тех пор, пока current не станет указывать на элемент под номером num
            i++;
            current = current->next;}

        prev = current->prev;
        next = current->next;

        if (prev && next){
            prev->next = next;
            next->prev = prev;//error1
        }
        else{
            if (prev){
                prev->next = nullptr;
                last = prev;
            }
            else{
                next->prev = nullptr;
                first = next;
            }
        }
        delete current; /// Очищаем память
        number--; /// Отнимаем единицу от переменной, отвечающей за количество объектов в списке
    }
}

void TableSpisok::addTable(dragdrop *rTable)
{
    if (!last){
        first = rTable;
    }
    else{
        rTable->prev = last;
        last->next = rTable;
    }

    last = rTable;
    number++;
}
