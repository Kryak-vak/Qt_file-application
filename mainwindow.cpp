#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QDir>


/**
  @fn MainWindow
  Конструктор, инициализирует необходимые объекты, а так же вызывает необходимые функции
  Например readSettings()
*/
MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    table_sp(new TableSpisok)
{
    ui->setupUi(this);

    readSettings(); /// Считываем настройки которые были при предыдущем закрытии программы

    qApp->installTranslator(&appTranslator); /// Подключаем переменную где будут хранится переводы
    createLanguageMenu(); /// Создаем список всех языков в меню

    connect(ui->tabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(tab_close_triggered(int)));

    dict1 = nullptr;
    dict2 = nullptr;
}

/// Деструктор, который очищает память, а также сохраняет настройки главного меню
MainWindow::~MainWindow()
{
    writeSettings(); /// Функция сохраняет настройки программы когда срабатывает деструктор
    delete ui;
}


/**
  @fn on_action_1_openFile_triggered
  Метод, отвечающий за работу пункта открытия файла в меню программы
  Создает объект типа QFileDialog, для предоставления пользователю возможности выбрать файл
  Обнуляет список
  Если пользователь выбрал файл, то вызывает функцию open()
  После заполнения списка заполняет tableWidget
*/
void MainWindow::on_action_1_openFile_triggered()
{
    if(dict1 != nullptr && dict2 != nullptr){
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open document"),
                                                        QDir::currentPath(),
                                                        tr("Document (*.txt)"));

        if (!fileName.isEmpty()){ /// Вызываем функцию считывания данных, только если пользователь выбрал какой-либо файл
            addTab(tr("Tab "));

            dragdrop *currentTable = table_sp->last;//ui->tabWidget->currentIndex()
            currentTable->open(fileName);
            currentTable->openDir(dict1, tr("Time"));
            currentTable->openDir(dict2, tr("Type"));//НЕДОРАБОТАНО!

            showTable(); /// После считывания данных, заполняем ими таблицу
        }
    }
    else
        QMessageBox::warning(this, tr("Dictionaries closed"), tr("You need to open dictionaries first!"));
}


/**
  @fn on_action_2_saveFile_triggered
  Метод, отвечающий за работу пункта сохранения файла в меню программы
  Создает объект типа QFileDialog, для предоставления пользователю выбора параметров сохранения
  Если пользователь выбрал файл, то вызывает функцию save()
*/
void MainWindow::on_action_2_saveFile_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        tr("Save"),
                                                        QDir::homePath(),
                                                        tr("Document (*.txt)"));

        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());

        if (!fileName.isEmpty())
            currentTable->save(fileName);
    }
}

/**
  @fn showTable
  Метод, загружающий данные в виджет tableWidget.
  Сначала приводит таблицу к исходному виду.
  Потом в цикле поочередно перебирает объекты списка, информацию которых записывает в ячейки таблицы,
  попутно применяя к ним необходимые параметры.
  А так же считывает текст из объекта searchLineEdit, и окрашивает ячейки с совпадающим текстом
*/
void MainWindow::showTable()
{
    dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
    currentTable->disconnect(currentTable, SIGNAL(cellChanged(int, int)), this, SLOT(tableWidget_cellChanged(int, int)));

    QBrush brush = QBrush(QColor(66, 49, 255)); /// Объект-кисть, в цвет которой будут окрашиваться искомые пользователем данные
    QString search = ui->searchLineEdit->text(); /// В переменной содержится текст, из объекта searchLineEdit

    if(currentTable->columnCount() != 5 + currentTable->dir_sp->count()){
        currentTable->setColumnCount(5 + currentTable->dir_sp->count());
        currentTable->setHorizontalHeaderItem(4 + currentTable->dir_sp->count(), new QTableWidgetItem(currentTable->dir_sp->last().name));

        for(int i = 0; i < currentTable->rowCount(); i++){
            currentTable->dir_sp->last().openValues(currentTable->rowCount());

            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            currentTable->setItem(i, 4 + currentTable->dir_sp->count(), item);
        }
    }
    currentTable->setSortingEnabled(0);

    if(currentTable->rowCount() < currentTable->spisok->count()){
        currentTable->setRowCount(currentTable->spisok->count());
        for(int i=0; i<currentTable->columnCount(); i++)
            currentTable->setItem(currentTable->rowCount()-1, i, new QTableWidgetItem());
    }
    else
        currentTable->setRowCount(currentTable->spisok->count());

    int i = 1; /// Переменная-счетчик, необходимая для заполнения столбца ID
    QLinkedList<Auto>::iterator iter; /// Указатель на первый объект списка

    for(iter=currentTable->spisok->begin();iter!=currentTable->spisok->end();iter++) /// Цикл закончится, когда закончится список
    {
        int count = i - 1;
        QLinkedList<DirectorySpisok>::iterator dirIter;

        QTableWidgetItem *item = new QTableWidgetItem; /// Объект, для заполнения таблицы, содержит в себе данные и различные настройки
        item->setTextAlignment(Qt::AlignCenter); /// Настраиваем выравнивание текста по центру
        item->setData(Qt::EditRole, i); /// В качестве данных передаем ID записи
        currentTable->setItem(count , 0, item); /// Заполняем первый столбец таблицы


        item = new QTableWidgetItem(iter->getNumber());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(1)->text() == dirIter->name)
                item = new QTableWidgetItem(dirIter->get(iter->getNumber().toInt()));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 1, item);


        item = new QTableWidgetItem(iter->getOwner());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(2)->text() == dirIter->name)
                item = new QTableWidgetItem(dirIter->get(iter->getOwner().toInt()));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 2, item);


        item = new QTableWidgetItem(iter->getDate());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(3)->text() == dirIter->name)
                item = new QTableWidgetItem(dirIter->get(iter->getDate().toInt()));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 3, item);


        item = new QTableWidgetItem;
        item->setData(Qt::EditRole, iter->getTime());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(4)->text() == dirIter->name)
                item = new QTableWidgetItem(dirIter->get(iter->getTime()));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 4, item);


        item = new QTableWidgetItem();
        item->setData(Qt::EditRole, iter->getType());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(5)->text() == dirIter->name)
                item = new QTableWidgetItem(QString(dirIter->get(iter->getType())));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 5, item);


        item = new QTableWidgetItem;
        item->setData(Qt::EditRole, iter->getPrice());
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++)
            if(currentTable->horizontalHeaderItem(6)->text() == dirIter->name)
                item = new QTableWidgetItem(dirIter->get(iter->getPrice()));

        item->setTextAlignment(Qt::AlignCenter);
        currentTable->setItem(count , 6, item);

        int j = 7;
        for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++){
            bool flag = true;

            for(int k = 0;k < 7;k++)
                if(currentTable->horizontalHeaderItem(k)->text() == dirIter->name){
                    flag = false;
                    break;
                }

            if(flag){
                if(!currentTable->item(count, j)->text().isEmpty()){
                    item = new QTableWidgetItem(dirIter->get(dirIter->getValue(count+1)));
                    item->setTextAlignment(Qt::AlignCenter);
                    currentTable->setItem(count , j, item);
                }
                j++;
            }
        }

        if(!search.isEmpty()){
            for(int j=1;j < currentTable->columnCount(); j++)
                if(currentTable->item(count, j)->text() == search)
                    currentTable->item(count, j)->setBackground(brush);
        }
        i++;
    }
    currentTable->setSortingEnabled(1); /// Включаем возможность сортировки
    currentTable->connect(currentTable, SIGNAL(cellChanged(int, int)), this, SLOT(tableWidget_cellChanged(int, int)));
}


/**
  @fn on_searchLineEdit_textChanged
  Обновляет таблицу каждый раз когда изменяется текст в объекте searchLineEdit
*/
void MainWindow::on_searchLineEdit_textChanged()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm"))
        showTable();
}


/**
  @fn createLanguageMenu
  Метод, который создает список пунктов меню с доступными языками
  Список создается динамически, на основе файлов .qm, которые находятся в папке translations
  В конце вызывает фунцию switchLanguage(), в качестве аргумента передавая тот язык,
  который был сохранен при закрытии программы
*/
void MainWindow::createLanguageMenu()
{
    languageActionGroup = new QActionGroup(this); /// Объект где будут хранится все пункты меню с языками

    connect(languageActionGroup, SIGNAL(triggered(QAction*)), /// Привязываем нажатие на пукт со слотом
            this, SLOT(switchLanguage(QAction*)));

    QDir dir("://translations/"); /// Переменная, в которой находится путь к папке с .qm файлами

    QStringList fileNames =
            dir.entryList(QStringList("multilang_*.qm")); /// Переменная со списком названий всех файлов

    for (int i = 0; i < fileNames.size(); i++) { /// Цикл сработает столько раз, сколько файлов содержится в папке
        QString locale = fileNames[i]; /// В переменную записывается название i-того файла
        locale.remove(0, locale.indexOf('_') + 1); /// Удаляем из названия файла все что идет до "_"
        locale.truncate(locale.lastIndexOf('.')); /// Удаляем ".qm". В итоге получаем строку типа Russian_RU, English_EN и т.п.

        QAction *action = new QAction(this); /// Создаем новый пункт меню

        action->setCheckable(true); /// Добавляем возможность поставить/убрать галочку
        action->setData(locale); /// Записываем название файла, который будет привязан к данному пункту
        ui->menuSwitch_language->addAction(action); /// Добавляем пункт в список языков меню
        languageActionGroup->addAction(action); /// Добавляем пункт в список со всеми пунктами языков
    }

    for (int i=0; i < languageActionGroup->actions().count(); i++){ /// Цикл проходит по всем загруженным в программу языкам
        if (languageActionGroup->actions()[i]->data() == currentLanguage){ /// Ищем пункт меню, язык которого совпадает с языком по умолчанию
            switchLanguage(languageActionGroup->actions()[i]); /// После того как нужный язык отыскался вызываем функцию, которая меняет язык интерфейса
            languageActionGroup->actions()[i]->setChecked(true); /// Ставим галочку у выбранного языка
        }
    }
}

dragdrop * MainWindow::createTable(int columns)
{
    dragdrop *newtableWidget = new dragdrop();

    newtableWidget->setColumnCount(columns);
    for(int i=0; i < columns; i++){
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        newtableWidget->setHorizontalHeaderItem(i, __qtablewidgetitem);
    }

    newtableWidget->horizontalHeaderItem(0)->setText(tr("ID"));

    if(columns == 7){
        newtableWidget->horizontalHeaderItem(1)->setText(tr("Number"));
        newtableWidget->horizontalHeaderItem(2)->setText(tr("Owner"));
        newtableWidget->horizontalHeaderItem(3)->setText(tr("Date"));
        newtableWidget->horizontalHeaderItem(4)->setText(tr("Time"));
        newtableWidget->horizontalHeaderItem(5)->setText(tr("Type"));
        newtableWidget->horizontalHeaderItem(6)->setText(tr("Price"));
    }
    else{
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
        newtableWidget->horizontalHeaderItem(1)->setText(tr(currentTable->dir_sp->last().name.toStdString().c_str()));
    }

    newtableWidget->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
    newtableWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(172, 207, 156);\n"
                                                    "gridline-color: rgb(200, 200, 200);\n"
                                                    "background-color: rgb(171, 171, 255);\n"
                                                    "alternate-background-color: rgb(230, 230, 230);\n"
                                                    ""));
    newtableWidget->setAutoScroll(true);
    newtableWidget->setAlternatingRowColors(true);
    newtableWidget->horizontalHeader()->setVisible(true);
    newtableWidget->verticalHeader()->setVisible(false);
    newtableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    newtableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    newtableWidget->setAcceptDrops(true);
    newtableWidget->setDragEnabled(true);
    newtableWidget->setDefaultDropAction(Qt::DropAction::CopyAction);

    connect(newtableWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(ShowContextMenu(const QPoint&)));
    connect(newtableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(tableWidget_cellChanged(int, int)));

    return newtableWidget;
}

static bool compare(const QPointF& first, const QPointF& second)
{
    if (first.x() < second.x())
    {
        return true;
    }
    else if (first.x() > second.x())
    {
        return false;
    }
    else
    {
        if (first.y() < second.y())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

double maxTime(dragdrop *table){
    QLinkedList<DirectorySpisok>::iterator dirIter = table->dir_sp->begin();
    QLinkedList<Auto>::iterator iter;
    double max = 0;

    for(iter=table->spisok->begin(); iter!=table->spisok->end(); iter++)
    {//item = new QTableWidgetItem(dirIter->get(dirIter->getValue(count+1)));
        if(max < dirIter->get(iter->getTime()).toInt())
            max = dirIter->get(iter->getTime()).toInt();
    }
    return max;
}

double maxPrice(dragdrop *table){
    QLinkedList<Auto>::iterator iter;
    double max = 0;

    for(iter=table->spisok->begin(); iter!=table->spisok->end(); iter++)
    {
        if(max < iter->getPrice())
            max = iter->getPrice();
    }
    return max;
}

void MainWindow::addDiagramm()
{
    dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());

    QCustomPlot *newdiagramm = new QCustomPlot();

    QWidget *newTab = new QWidget();
    QString title = tr("Diagramm");
    ui->tabWidget->addTab(newTab, title);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(newTab);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    horizontalLayout->addWidget(newdiagramm);

    ui->tabWidget->setCurrentIndex(ui->tabWidget->count()-1);

    QList<QPointF> pointsList;
    QLinkedList<Auto>::iterator iter;
    QLinkedList<DirectorySpisok>::iterator dirIter = currentTable->dir_sp->begin();

    for(iter=currentTable->spisok->begin(); iter!=currentTable->spisok->end(); iter++)
    {
        pointsList << QPointF(dirIter->get(iter->getTime()).toInt(), iter->getPrice());
        qDebug()<< QPointF(dirIter->get(iter->getTime()).toInt(), iter->getPrice());
    }

    std::sort(pointsList.begin(), pointsList.end(), compare);

    double a = maxTime(currentTable), b = maxPrice(currentTable) + 100;
    int N = static_cast<int>(round(b * 10));

    QVector<double> x(N), y(N);

    for (int i = 0; i < currentTable->spisok->count(); i++)
    {
        x[i] = pointsList.at(i).x();
        y[i] = pointsList.at(i).y();
    }

    newdiagramm->clearGraphs();
    newdiagramm->addGraph();
    newdiagramm->graph(0)->setPen(QPen(Qt::yellow, 1));
    newdiagramm->graph(0)->setData(x, y);
    newdiagramm->xAxis->setLabel(tr("Time"));
    newdiagramm->yAxis->setLabel(tr("Price"));
    newdiagramm->xAxis->setLabelColor(Qt::white);
    newdiagramm->yAxis->setLabelColor(Qt::white);
    newdiagramm->yAxis->setBasePen(QPen(Qt::white, 1));
    newdiagramm->yAxis->setTickPen(QPen(Qt::white, 1));
    newdiagramm->xAxis->setRange(0, a);
    newdiagramm->xAxis->setBasePen(QPen(Qt::white, 1));
    newdiagramm->xAxis->setTickPen(QPen(Qt::white, 1));
    newdiagramm->xAxis->setTickLabelColor(Qt::white);
    newdiagramm->yAxis->setTickLabelColor(Qt::white);
    newdiagramm->yAxis->setRange(0, b);
    newdiagramm->setBackground(QBrush(QColor(100, 100, 120)));
    newdiagramm->replot();
}


void MainWindow::addTab(QString title)
{
    QWidget *newTab = new QWidget();
    title.append(QString::number(table_sp->number + 1));

    ui->tabWidget->addTab(newTab, title);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(newTab);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    dragdrop *newtableWidget = createTable(7);

    horizontalLayout->addWidget(newtableWidget);
    table_sp->addTable(newtableWidget);

    ui->tabWidget->tabBar()->moveTab(ui->tabWidget->count() - 1, table_sp->number - 1);
}

void MainWindow::addDir(QString title)
{
    QWidget *newTab = new QWidget();

    ui->tabWidget->addTab(newTab, title);

    QHBoxLayout *horizontalLayout = new QHBoxLayout(newTab);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setSpacing(0);

    dragdrop *newDirWidget = createTable(2);

    horizontalLayout->addWidget(newDirWidget);
}


/**
  @fn switchLanguage
  Метод, который переводит язык приложения на выбранный пользователем язык
  При помощи данных, записанных в каждый пункт меню языка, узнается на какой именно язык нужно переключить
  Далее загружается необходимый файл и меняется переменная currentLanguage
  Интерфейс программы обновляется с помощью функции retranslateUi()
  Далее вызывается цикл, который переводит пункты меню языков при помощи функции .translate
  Этот цикл необходим так как список языков создается динамически
  @param action - параметр, отвечающий за выбранный пользователем пункт меню
*/
void MainWindow::switchLanguage(QAction *action)
{
    QString locale = action->data().toString(); /// Определяем локаль которую выбрал пользователь (например ru_RU)
    appTranslator.load("://translations/multilang_" + locale); /// Загружаем тот перевод который выбрал пользователь
    currentLanguage = locale; /// Меняем язык по умолчаню на выбранный пользователем

    ui->retranslateUi(this); /// Обновляем интерфейс приложения

    QTranslator translator; /// Объект, необходимый для перевода динамически созданных названий языков в пункте меню
    translator.load("://translations/multilang_" + locale); /// Загружаем тот перевод, который был выбран пользователем
    QString actionName; /// Все пункты меню смены языка должны быть переведены на тот язык, который выбрал пользователь. Они будут поочереди записыватся в эту переменную

    for (int i=0; i < languageActionGroup->actions().count(); i++){ /// Цикл проходит по всем загруженным в программу языкам
        actionName = languageActionGroup->actions()[i]->data().toString(); /// В data() содержится имя файла прикрепленного к соответсвующему пункту меню ("Russian_RU")
        actionName.truncate(actionName.lastIndexOf('_')); /// Удаляем все начиная с "_", в итоге получаем записть вида "Russian"
        const char* language = actionName.toStdString().c_str(); /// Функция translate() работает только с const char* поэтому конвертируем название из QString в этот тип

        actionName = translator.translate("MainWindow", language); /// Записываем в переменную название языка переведенное на выбранный пользователем язык

        languageActionGroup->actions()[i]->setText(actionName); /// Устанавливаем переведенный варинт в строку меню
    }
}


/**
  @fn on_action_3_exit_triggered
  Метод, отвечающий за работу пункта выхода в меню программы
  Создается диалоговое окно, которое удостоверяется хочет ли пользователь выйти
  В случае утвердительного ответа, приложение закрывается
*/
void MainWindow::on_action_3_exit_triggered()
{
    QMessageBox exitMsg(QMessageBox::Question,
                        tr("Exit"),
                        tr("Are you sure you want to quit?"),
                        nullptr,
                        this);

    exitMsg.addButton(tr("Yes"), QMessageBox::AcceptRole); /// Кнопки к диалоговому окну добавляем отдельно
    exitMsg.addButton(tr("No"), QMessageBox::RejectRole); /// Чтобы иметь возможность их перевести

    if (exitMsg.exec() == QMessageBox::AcceptRole) /// Если была нажата кнопка "Yes", закрываем приложение
        this->close();
}


/**
  @fn on_action_4_aboutAuthor_triggered
  Метод, отвечающий за работу пункта об авторе в меню программы
  Вызывается диалоговое окно с запрошенной информацией
*/
void MainWindow::on_action_4_aboutAuthor_triggered()
{
    QMessageBox authBox(QMessageBox::Information,
                        tr("Project author"),
                        tr("Vakashev Shamil Timurovich\n"
                           "                 IEUIS 2-1"),
                        nullptr,
                        this);
    authBox.exec();
}


/**
  @fn on_action_5_Info_triggered
  Метод, отвечающий за работу пункта информации в меню программы
  Вызывается диалоговое окно с запрошенной информацией
*/
void MainWindow::on_action_5_Info_triggered()
{
    QMessageBox authBox(QMessageBox::Information,
                        tr("Help info"),
                        tr("To open/close files u can use the menu or quick access buttons\n\n"
                           "After you opened a file you can search for a certain info by typing\n"
                           "it into the search line at the right bottom\n\n"
                           "To edit the record double-tap on the attribute\n\n"
                           "Press the right button to access the context menu"),
                        nullptr,
                        this);
    authBox.exec();
}


/**
  @fn readSettings
  Метод, устанавливающий сохраненные настройки главного окна, при открытии программы
*/
void MainWindow::readSettings()
{
    QSettings settings("MainWindow");

    restoreGeometry(settings.value("geometry", saveGeometry()).toByteArray()); /// Восстанавливает геометрию (размер и координаты) окна
    currentLanguage = settings.value("language").toString(); /// Восстанавливает язык окна
}


/**
  @fn writeSettings
  Метод, сохраняющий установленные настройки главного окна, при закрытии программы
*/
void MainWindow::writeSettings()
{
    QSettings settings("MainWindow");

    settings.setValue("geometry", saveGeometry()); /// Сохраняет геометрию (размер и координаты) окна
    settings.setValue("language", currentLanguage); /// Сохраняет язык окна
}


/**
  @fn on_tableWidget_cellChanged
  Метод, изменющий соответствующий параметр объекта при изменении содержимого ячейки виджета tableWidget
  По ID при помощи функции get() из списка находится необходимый объект, и необходимое своиство перезаписывается
  @param row - параметр, хранящий номер строки измененной ячейки
  @param column - параметр, хранящий номер столбца измененной ячейки
*/
void MainWindow::tableWidget_cellChanged(int row, int column)
{
    dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());

    QString data = currentTable->item(row, column)->text(); /// Переменная, в которой содержится измененный текст ячейки
    int id = (currentTable->item(row, 0)->text()).toInt(); /// Переменная, в которую записывается ID объекта, чтобы можно было его отыскать в списке
    QLinkedList<Auto>::iterator iter = currentTable->get(id - 1); /// Указатель на необходимый объект
    QLinkedList<DirectorySpisok>::Iterator dirIter = currentTable->dir_sp->begin();

    switch (column) { /// Узнаем какое своиство объекта необходимо поменять по столбцу измененной ячейки
        case 1: iter->setNumber(data); break;
        case 2: iter->setOwner(data); break;
        case 3: iter->setDate(data); break;
        case 4: iter->setTime(data.toInt()); break;
        case 5: iter->setType(data.toInt()); break;
        case 6: iter->setPrice(data.toInt()); break;
    }

    int j = 7;
    for(dirIter=currentTable->dir_sp->begin();dirIter!=currentTable->dir_sp->end();dirIter++){
        bool flag = true;

        for(int k = 0;k < 7;k++)
            if(currentTable->horizontalHeaderItem(k)->text() == dirIter->name){
                flag = false;
                break;
            }

        if(flag){
            if(dirIter->name == currentTable->horizontalHeaderItem(column)->text()){
                dirIter->setValue(row, data.toInt());
            }
            j++;
        }
    }

    showTable();
}

/**
  @fn ShowContextMenu
  Метод, отвечающий за работу контекстного меню
  Полученная координата преобразуется в глобальную
  Создается объект QMenu, в который добавляются необходимые пункты
  Далее прописываются действия для каждого выбора
  При добавлении строки создается пустая строка
  А при удалении из списка удалется необходимый объект
  @param pos - параметр, хранящий координату курсора в момент вызова контекстного меню
*/
void MainWindow::ShowContextMenu(const QPoint& pos)
{
    dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());

    QPoint globalPos = currentTable->mapToGlobal(pos); /// Записываем координату, переведенную в глобальные координаты экрана
    QMenu contextMenu; /// Создаем новое меню

    contextMenu.addAction(tr("Add new line")); /// Добавляем пункт добавления строчки
    contextMenu.addAction(tr("Delete line")); /// Добавляем пункт удаления строчки

    int row = currentTable->selectionModel()->currentIndex().row(); /// Записываем в переменную индекс элемента модели для текущего элемента или недопустимый индекс, если текущий элемент отсутствует

    if (row >= 0)
    {
        QString id = currentTable->item(row, 0)->text(); /// Переменная, хранящая в себе номер выбранного объекта
        QAction* selectedItem = contextMenu.exec(globalPos); /// Объект, в который записывается выбранный пользователем пункт контекстного меню

        if (selectedItem){
            if (selectedItem->iconText()==tr("Add new line")){
                currentTable->addString(";;;;;;"); /// Добавляем пустую строчку

                //for(int i=0; i < currentTable->horizontalHeader()->count() - 1; i++)
                  //  currentTable->setItem(currentTable->rowCount()-1, i, new QTableWidgetItem());

                /*QLinkedList<DirectorySpisok>::iterator iter;

                for(iter = currentTable->dir_sp->begin(); iter != currentTable->dir_sp->end(); iter++){
                    QMessageBox::about(this, "a",QString::number(iter->spisok->last().getId() + 1));
                    iter->addDirString(QString(";") + QString::number(iter->spisok->last().getId() + 1));
                }*/

                showTable(); /// Обновляем таблицу
            }

            if (selectedItem->iconText() == tr("Delete line")){
                currentTable->removeString(id.toInt()); /// Удаляем объект с необходимым ID

                /*QLinkedList<DirectorySpisok>::iterator iter;

                for(iter = currentTable->dir_sp->begin(); iter != currentTable->dir_sp->end(); iter++){
                    iter->removeDirString(id.toInt());
                }*/

                showTable(); /// Обновляем таблицу
            }
        }
    }
}

void MainWindow::tab_close_triggered(int id)
{
    QMessageBox exitMsg(QMessageBox::Question,
                        tr("Closing"),
                        tr("Are you sure you want to close the tab?"),
                        nullptr,
                        this);

    exitMsg.addButton(tr("Yes"), QMessageBox::AcceptRole); /// Кнопки к диалоговому окну добавляем отдельно
    exitMsg.addButton(tr("No"), QMessageBox::RejectRole); /// Чтобы иметь возможность их перевести

    if (exitMsg.exec() == QMessageBox::AcceptRole){ /// Если была нажата кнопка "Yes", закрываем приложение
        if (ui->tabWidget->tabBar()->tabText(id) != tr("Diagramm"))
            table_sp->removeTable(id);
        ui->tabWidget->removeTab(id);
    }
}

void MainWindow::on_pushButton_Search_clicked()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm"))
        showTable();
}

void MainWindow::on_pushButton_Window_clicked()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){

        dragdrop *newtableWidget = createTable(7);
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());

        newtableWidget->disconnect(newtableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(tableWidget_cellChanged(int, int)));
        QLinkedList<DirectorySpisok>::iterator dirIter;
        for(dirIter=currentTable->dir_sp->begin(); dirIter!=currentTable->dir_sp->end(); dirIter++)
            newtableWidget->dir_sp->push_back(*dirIter);

        newtableWidget->setRowCount(currentTable->rowCount());
        newtableWidget->setColumnCount(currentTable->columnCount());
        for(int row = 0; row < currentTable->rowCount(); row++)
            for(int column = 0; column < currentTable->columnCount(); column++){
                QTableWidgetItem *item = currentTable->item(row, column)->clone();
                newtableWidget->setItem(row, column, item);
            }

        newtableWidget->setGeometry(this->geometry().x() + 50,
                                    this->geometry().y() + 50,
                                    800, 350);
        newtableWidget->setWindowTitle(ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()));
        newtableWidget->show();
    }
}

void MainWindow::on_pushButton_Diagramm_clicked()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm"))
        addDiagramm();
}

void MainWindow::on_actionOpen_dictionaries_triggered()
{
    dict1 = QFileDialog::getOpenFileName(this,
                                         tr("Open first dictionary"),
                                         QDir::currentPath(),
                                         tr("Document (*.txt)"));

    dict2 = QFileDialog::getOpenFileName(this,
                                         tr("Open second dictionary"),
                                         QDir::currentPath(),
                                         tr("Document (*.txt)"));
    if(dict1.isEmpty() || dict2.isEmpty()){
        QMessageBox::warning(this, tr("Warning"), tr("Directories weren't open!"));
    }
}

void MainWindow::on_actionAdd_new_dictionary_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){

        QString fileName =
                QFileDialog::getOpenFileName(this,
                                             tr("Open another dictionary"),
                                             QDir::currentPath(),
                                             tr("Document (*.txt)"));

        bool flag = false;
        QString dirName = QInputDialog::getText(this,
                                                tr("Add directory"),
                                                tr("Column name:"),
                                                QLineEdit::Normal,
                                                "",
                                                &flag);

        if(flag && !dirName.isEmpty()){
            dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
            currentTable->openDir(fileName, dirName);
            showTable();
        }
    }
}

void MainWindow::on_actionCreate_new_triggered()
{
    if(dict1 != nullptr && dict2 != nullptr){
        addTab(tr("Tab "));

        dragdrop *currentTable = table_sp->last;

        for(int i=0; i < 5; i++)
            currentTable->addString(";;;;;;");

        currentTable->openDir(dict1, tr("Time"));
        currentTable->openDir(dict2, tr("Type"));

        showTable(); /// После считывания данных, заполняем ими таблицу
    }
    else
        QMessageBox::warning(this, tr("Dictionaries closed"), tr("You need to open dictionaries first!"));
}

void MainWindow::on_actionShow_dictionaries_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
        QLinkedList<DirectorySpisok>::iterator dirIter;
        QLinkedList<Directory>::iterator iter;
        QTableWidgetItem *item = new QTableWidgetItem();
        int i = 0;

        for(dirIter=currentTable->dir_sp->begin(); dirIter!=currentTable->dir_sp->end(); dirIter++){
            dragdrop *newDirWidget = createTable(2);

            newDirWidget->disconnect(newDirWidget, SIGNAL(cellChanged(int, int)),
                                     this, SLOT(tableWidget_cellChanged(int, int)));

            iter=dirIter->spisok->begin();
            newDirWidget->setRowCount(dirIter->spisok->count());
            for(int row = 0; row < newDirWidget->rowCount(); row++, iter++){
                item = new QTableWidgetItem();
                item->setText(QString::number(row + 1));
                item->setTextAlignment(Qt::AlignCenter);
                newDirWidget->setItem(row, 0, item);

                item = new QTableWidgetItem();
                item->setText(iter->getProperty());
                item->setTextAlignment(Qt::AlignCenter);
                newDirWidget->setItem(row, 1, item);
                }

            newDirWidget->setGeometry(this->geometry().x() + 50 + 300 * i,
                                      this->geometry().y() + 50,
                                      300, 400);
            newDirWidget->horizontalHeaderItem(1)->setText(dirIter->name);
            newDirWidget->setWindowTitle(tr("Dictionary"));
            newDirWidget->show();

            i++;
        }
    }
}

void MainWindow::on_actionAdd_new_record_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
        QLinkedList<DirectorySpisok>::iterator dirIter;
        QLinkedList<Directory>::iterator iter;

        bool flag = false;
        QString dirName = QInputDialog::getText(this,
                                                tr("Choose directory"),
                                                tr("Column name:"),
                                                QLineEdit::Normal,
                                                "",
                                                &flag);

        QString newRecord = QInputDialog::getText(this,
                                                  tr("Add record"),
                                                  tr("New record:"),
                                                  QLineEdit::Normal,
                                                  "",
                                                  &flag);

        if(flag && !dirName.isEmpty() && !newRecord.isEmpty())
            for(dirIter=currentTable->dir_sp->begin(); dirIter!=currentTable->dir_sp->end(); dirIter++)
                if(dirIter->name == dirName)
                    dirIter->addDirString(QString::number(dirIter->spisok->count()+1) + ';' + newRecord);
    }
}

void MainWindow::on_actionRemove_record_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
        QLinkedList<DirectorySpisok>::iterator dirIter;
        QLinkedList<Directory>::iterator iter;

        bool flag = false;
        QString dirName = QInputDialog::getText(this,
                                                tr("Choose directory"),
                                                tr("Column name:"),
                                                QLineEdit::Normal,
                                                "",
                                                &flag);

        QString delRecord = QInputDialog::getText(this,
                                                  tr("Delete record"),
                                                  tr("Record ID:"),
                                                  QLineEdit::Normal,
                                                  "",
                                                  &flag);

        if(flag && !dirName.isEmpty() && !delRecord.isEmpty())
            for(dirIter=currentTable->dir_sp->begin(); dirIter!=currentTable->dir_sp->end(); dirIter++)
                if(dirIter->name == dirName)
                    dirIter->removeDirString(delRecord.toInt());

        showTable();
    }
}

void MainWindow::on_actionClose_and_save_dictionaries_triggered()
{
    if(table_sp->number && ui->tabWidget->tabBar()->tabText(ui->tabWidget->currentIndex()) != tr("Diagramm")){
        dragdrop *currentTable = table_sp->get(ui->tabWidget->currentIndex());
        QLinkedList<DirectorySpisok>::iterator dirIter = currentTable->dir_sp->begin();

        dirIter->saveDir(dict1); dirIter++;
        dirIter->saveDir(dict2); dirIter++;

        while(dirIter != currentTable->dir_sp->end()){
            QString fileName = QFileDialog::getSaveFileName(this,
                                                            tr("Save"),
                                                            QDir::homePath(),
                                                            tr("Document (*.txt)"));

            if (!fileName.isEmpty())
                dirIter->saveDir(fileName);

            dirIter++;
        }

        int num = this->table_sp->number;
        for(int i = 0; i < num; i++){
            this->table_sp->removeTable(0);
            ui->tabWidget->removeTab(0);
        }
    }
}
