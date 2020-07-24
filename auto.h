#ifndef AUTO_H
#define AUTO_H

#include <QString>
#include <QLinkedList>

/**
@class Auto
Класс, необходимый для создания объектов, содержащих в себе информацию о процессорах.
Этот класс содержит конструктор, семь методов и девять членов данных.
*/
class Auto {

    private:

        QString autoNumber;

        QString autoOwner;

        QString autoDate;

        int autoTime;

        int autoType;

        int autoPrice;

    public:
        Auto(QString, QString, QString, int, int, int);

        Auto *next;

        Auto *prev;

        void setNumber(QString);

        void setOwner(QString);

        void setDate(QString);

        void setTime(int);

        void setType(int);

        void setPrice(int);


        QString getNumber() {return autoNumber;}

        QString getOwner() {return autoOwner;}

        QString getDate() {return autoDate;}

        int getTime() {return autoTime;}

        int getType() {return autoType;}

        int getPrice() {return autoPrice;}
};


class Directory {

    private:
        int dirId;

        QString dirProperty;

    public:
        Directory(int, QString);

        void setId(int);

        void setProperty(QString);

        int getId() {return dirId;}

        QString getProperty() {return dirProperty;}
};

class DirectorySpisok {

    public:
        QLinkedList<Directory> *spisok;

        QStringList *values;

        QString name;

        DirectorySpisok();

        void openDir(QString);

        void saveDir(QString);

        void addDirString(QString);

        void removeDirString(int);

        void openValues(int);

        /// Метод, возвращающий указатель на объект по ID
        QString get(int);

        int getPos(QString);

        int getValue(int);

        void setValue(int, int);


};


#endif // AUTO_H
