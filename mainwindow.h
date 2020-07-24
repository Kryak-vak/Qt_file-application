#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "auto.h"
#include "dragdrop.h"
#include "qcustomplot.h"

#include <QMainWindow>
#include <QTranslator>
#include <QActionGroup>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
@class MainWindow
Класс, который отвечает за функционирование главного окна программы.
Этот класс содержит конструктор, деструктор, девять методов-слотов, четыре метода и пять членов данных.
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /// @fn MainWindow
    /// Конструктор
    MainWindow(QWidget *parent = nullptr);

    /// @fn ~MainWindow
    /// Деструктор
    ~MainWindow();

    QString dict1;
    QString dict2;

private slots:

    /// Слот, отвечающий за работу пункта открытия файла в меню программы
    void on_action_1_openFile_triggered();

    /// Слот, отвечающий за работу пункта сохранения файла в меню программы
    void on_action_2_saveFile_triggered();

    /// Слот, отвечающий за работу пункта выхода в меню программы
    void on_action_3_exit_triggered();

    /// Слот, отвечающий за работу пункта об авторе в меню программы
    void on_action_4_aboutAuthor_triggered();

    /// Слот, отвечающий за работу пунктов языков в меню программы
    /// @param action - параметр, соответствующий конкретному пункту меню смены языка, который выбрал пользователь
    void switchLanguage(QAction *action);

    /// Слот, отслеживающий изменения текста объекта меню searchLineEdit
    void on_searchLineEdit_textChanged();

    /// Слот, изменющий соответствующий параметр объекта при изменении содержимого ячейки виджета tableWidget
    /// @param row - параметр, хранящий номер строки измененной ячейки
    /// @param column - параметр, хранящий номер столбца измененной ячейки
    void tableWidget_cellChanged(int row, int column);

    /// Слот, отвечающий за работу пункта информации в меню программы
    void on_action_5_Info_triggered();

    /// Слот, отвечающий за работу контекстного меню
    /// @param pos - параметр, хранящий координату курсора в момент вызова контекстного меню
    void ShowContextMenu(const QPoint& pos);

    void tab_close_triggered(int id);

    void on_pushButton_Search_clicked();

    void on_pushButton_Window_clicked();

    void on_pushButton_Diagramm_clicked();

    void on_actionOpen_dictionaries_triggered();

    void on_actionAdd_new_dictionary_triggered();

    void on_actionCreate_new_triggered();

    void on_actionShow_dictionaries_triggered();

    void on_actionAdd_new_record_triggered();

    void on_actionRemove_record_triggered();

    void on_actionClose_and_save_dictionaries_triggered();

private:

    /// Объект, необходимый для создания главного окна
    Ui::MainWindow *ui;

    /// Объект, необходимый для хранения и структуризации считываемых данных
    TableSpisok *table_sp;

    /// Переменная-член, хранящая информацию о текущем языке программы
    QString currentLanguage;

    /// Объект, необходимый для обеспечения перевода текста в программе
    QTranslator appTranslator;

    /// Переменная-член, хранящая в себе список всех пунктов меню доступных языков программы
    QActionGroup *languageActionGroup;

    /// @fn createLanguageMenu
    /// Метод, отвечающий за создание пункта меню со всеми доступными языками
    /// Доступные языки определяются по количеству файлов .qm в папке translations
    void createLanguageMenu();

    dragdrop * createTable(int);

    void addDiagramm();

    void addTab(QString);

    void addDir(QString);

    /// @fn readSettings
    /// Метод, устанавливающий сохраненные настройки главного окна, при открытии программы
    void readSettings();

    /// @fn writeSettings
    /// Метод, сохраняющий установленные настройки главного окна, при закрытии программы
    void writeSettings();

    /// @fn showTable
    /// Метод, загружающий данные в виджет tableWidget
    void showTable();
};
#endif // MAINWINDOW_H
