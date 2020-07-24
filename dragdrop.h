#ifndef DRAGDROP_H
#define DRAGDROP_H

#include "auto.h"
#include <QWidget>
#include <QObject>
#include <QtWidgets>


/**
@class dragdrop
Класс, наследуемый от QTableWidget, который необходим для осуществления работы drag and drop.
Этот класс содержит конструктор, два метода и один член данных.
*/
class dragdrop : public QTableWidget
{
    Q_OBJECT

public:

    /// Конструктор
    explicit dragdrop(QWidget* parent = nullptr);

    dragdrop *next;
    dragdrop *prev;

    QLinkedList<Auto> *spisok;
    QLinkedList<DirectorySpisok> *dir_sp;

    /// Метод, отвечающий за создание объектов, присвоение им данных и создание связей в списке при открытии файла
    void open(QString);

    /// Метод, отвечающий за создание файла с записанным в нем списком объектов
    void save(QString);

    /// Метод, отвечающий за создание нового объекта и его связей в списке
    void addString(QString);

    /// Метод, отвечающий за удаление объекта и его связей в списке
    void removeString(int);

    /// Метод, возвращающий указатель на объект по ID
    QLinkedList<Auto>::iterator get(int);

    void openDir(QString, QString);

    void removeDir(int);

private:

    /// @fn mousePressEvent
    /// Метод, отслеживающий откуда началось перетаскивание
    /// @param event - параметр, отвечающий за событие (нажатие, удерживание кнопок мыши и т.п.)
    void mousePressEvent  (QMouseEvent *event);

    /// @fn mouseMoveEvent
    /// Метод, отвечающий за перетаскивание
    /// @param event - параметр, отвечающий за событие (нажатие, удерживание кнопок мыши и т.п.)
    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *);

    void dragMoveEvent(QDragMoveEvent *e);

    void dragLeaveEvent(QDragLeaveEvent *);

    void dropEvent(QDropEvent *);

    /// Переменная, в которой хранится координата начала перетаскивания
    QPoint startPoint;

};


class TableSpisok
{
    public:

        /// Переменная-член, хранящая информацию о количестве элементов списка
        int number;

        /// Переменная-член, указатель на первый элемент списка
        dragdrop *first;

        /// Переменная-член, указатель на последний элемент списка
        dragdrop *last;

        /// Конструктор, обнуляющий переменные-челны класса при создании объекта
        TableSpisok() {
            number = 0;
            first = last = nullptr;
        }

        /// Метод, отвечающий за создание нового объекта и его связей в списке
        void addTable(dragdrop *);

        /// Метод, отвечающий за удаление объекта и его связей в списке
        void removeTable(int);

        /// Метод, возвращающий указатель на объект по ID
        dragdrop *get(int);
};


#endif // DRAGDROP_H
