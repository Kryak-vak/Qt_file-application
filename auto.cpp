#include "auto.h"

#include "QFile"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextDecoder>
#include <QTextStream>

/**
  @fn Processor
  Конструктор, инициализирует необходимые переменные-члены
*/
Auto::Auto(QString receivedProducer,
           QString receivedModel,
           QString receivedSocket,
           int receivedFreq,
           int receivedCores,
           int receivedPrice):
           autoNumber(receivedProducer),
           autoOwner(receivedModel),
           autoDate(receivedSocket),
           autoTime(receivedFreq),
           autoType(receivedCores),
           autoPrice(receivedPrice),
           next(nullptr),
           prev(nullptr)
{

}


/// @name Методы установки параметров
/// @{

/// Устанавливает производителя
void Auto::setNumber(QString received)
{
    autoNumber = received;
}

/// Устанавливает модель
void Auto::setOwner(QString received)
{
    autoOwner = received;
}

/// Устанавливает разъем
void Auto::setDate(QString received)
{
    autoDate = received;
}

/// Устанавливает частоту
void Auto::setTime(int received)
{
    autoTime = received;
}

/// Устанавливает количество ядер
void Auto::setType(int received)
{
    autoType = received;
}

/// Устанавливает цену
void Auto::setPrice(int received)
{
    autoPrice = received;
}
/// @}


Directory::Directory(int receivedId,
                     QString receivedProperty):
                     dirId(receivedId),
                     dirProperty(receivedProperty)
{

}

void Directory::setId(int received)
{
    dirId = received;
}

void Directory::setProperty(QString received)
{
    dirProperty = received;
}


DirectorySpisok::DirectorySpisok():
    spisok(new QLinkedList<Directory>)
{

}

void DirectorySpisok::openDir(QString fileName)
{
    QFile file(fileName); /// Объект с файлом, название которого переданного в функцию
    QString text; /// Переменная, в которую будут поочереди записываться строчки из файла

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        while(!file.atEnd()) /// Цикл будет работать, пока не будет записан весь файл
        {
            text = file.readLine(); /// Записываем в переменную строчку из файла
            addDirString(text);
        }

        file.close();
    }
}

void DirectorySpisok::saveDir(QString fileName)
{
    QTextCodec::setCodecForLocale( QTextCodec::codecForName("UTF-8"));

    QFile file(fileName); /// Объект с файлом, название которого переданного в функцию
    QTextStream writeStream(&file);
    QLinkedList<Directory>::iterator iter;

    int i = 1;
    if(file.open(QIODevice::WriteOnly))
    {
        for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        {
            writeStream << i << ';';
            writeStream << iter->getProperty() << ';';

            if(iter!=--spisok->end())
                writeStream << "\n";
        }

        file.close();
    }
}

void DirectorySpisok::addDirString(QString data)
{
    QStringList list = data.split(";"); /// Массив, в который записываются участки строчки с разделением по точке с запятой

    Directory *newDir = new Directory(list.at(0).toInt(), /// Создаем объект, передавая в конструктор данные из массива
                                      list.at(1));
    this->spisok->push_back(*newDir);
    free(newDir);
}

void DirectorySpisok::removeDirString(int num)
{
    QLinkedList<Directory>::iterator iter;

    int i = 1; /// Переменная-счетчик

    for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        if(i == num){
            spisok->erase(iter);
            break;
        }
}

void DirectorySpisok::openValues(int rowCount)
{
    values = new QStringList;
    for(int i=0; i < rowCount*2; i++){
        values->append("");
    }
}

QString DirectorySpisok::get(int id)
{
    QLinkedList<Directory>::iterator iter;
    id--;
    int i = 0; /// Переменная-счетчик

    for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        if (i == id)
            return iter->getProperty(); /// Если запрашиваемое id совпадает с номер объекта по списку, возвращаем его

    return nullptr; /// Если совпадения не произошло, возвращаем пустой указатель
}

int DirectorySpisok::getPos(QString rProperty)
{
    QLinkedList<Directory>::iterator iter;

    int i = 1;

    for(iter=spisok->begin();iter!=spisok->end();iter++,i++)
        if(iter->getProperty() == rProperty)
            return i;

    return -1;
}

int DirectorySpisok::getValue(int num)
{
    QStringList::iterator iter;

    int i = 1;

    for(iter=values->begin(); iter!=values->end();iter++,i++)
        if(num == i)
            return iter->toInt();
    return 0;
}

void DirectorySpisok::setValue(int row, int rValue)
{
    QStringList::iterator iter;

    int i = 0;

    for(iter=values->begin(); iter!=values->end();iter++,i++)
        if(row == i)
            values->replace(i, QString::number(rValue));
}
