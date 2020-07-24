/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_1_openFile;
    QAction *action_2_saveFile;
    QAction *action_3_exit;
    QAction *action_4_aboutAuthor;
    QAction *actionRussian_2;
    QAction *actionEnglish_2;
    QAction *actionGerman;
    QAction *action_5_Info;
    QAction *actionOpen_dictionaries;
    QAction *actionAdd_new_dictionary;
    QAction *actionCreate_new;
    QAction *actionShow_dictionaries;
    QAction *actionAdd_new_record;
    QAction *actionRemove_record;
    QAction *actionClose_and_save_dictionaries;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QFrame *line;
    QTabWidget *tabWidget;
    QFrame *line_2;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_Search;
    QLineEdit *searchLineEdit;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_Diagramm;
    QPushButton *pushButton_Window;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menuSwitch_language;
    QMenu *menuDictioanary;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(734, 445);
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/Thesquid.ink-Free-Flat-Sample-Owl.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(231, 220, 255);\n"
"selection-color: rgb(0, 0, 0);\n"
"font: 10pt \"MS Shell Dlg 2\";\n"
"selection-background-color: rgb(255, 255, 255);"));
        MainWindow->setToolButtonStyle(Qt::ToolButtonIconOnly);
        action_1_openFile = new QAction(MainWindow);
        action_1_openFile->setObjectName(QString::fromUtf8("action_1_openFile"));
        action_2_saveFile = new QAction(MainWindow);
        action_2_saveFile->setObjectName(QString::fromUtf8("action_2_saveFile"));
        action_3_exit = new QAction(MainWindow);
        action_3_exit->setObjectName(QString::fromUtf8("action_3_exit"));
        action_4_aboutAuthor = new QAction(MainWindow);
        action_4_aboutAuthor->setObjectName(QString::fromUtf8("action_4_aboutAuthor"));
        actionRussian_2 = new QAction(MainWindow);
        actionRussian_2->setObjectName(QString::fromUtf8("actionRussian_2"));
        actionRussian_2->setCheckable(true);
        actionRussian_2->setChecked(true);
        actionEnglish_2 = new QAction(MainWindow);
        actionEnglish_2->setObjectName(QString::fromUtf8("actionEnglish_2"));
        actionEnglish_2->setCheckable(true);
        actionGerman = new QAction(MainWindow);
        actionGerman->setObjectName(QString::fromUtf8("actionGerman"));
        actionGerman->setCheckable(true);
        action_5_Info = new QAction(MainWindow);
        action_5_Info->setObjectName(QString::fromUtf8("action_5_Info"));
        actionOpen_dictionaries = new QAction(MainWindow);
        actionOpen_dictionaries->setObjectName(QString::fromUtf8("actionOpen_dictionaries"));
        actionAdd_new_dictionary = new QAction(MainWindow);
        actionAdd_new_dictionary->setObjectName(QString::fromUtf8("actionAdd_new_dictionary"));
        actionCreate_new = new QAction(MainWindow);
        actionCreate_new->setObjectName(QString::fromUtf8("actionCreate_new"));
        actionShow_dictionaries = new QAction(MainWindow);
        actionShow_dictionaries->setObjectName(QString::fromUtf8("actionShow_dictionaries"));
        actionAdd_new_record = new QAction(MainWindow);
        actionAdd_new_record->setObjectName(QString::fromUtf8("actionAdd_new_record"));
        actionRemove_record = new QAction(MainWindow);
        actionRemove_record->setObjectName(QString::fromUtf8("actionRemove_record"));
        actionClose_and_save_dictionaries = new QAction(MainWindow);
        actionClose_and_save_dictionaries->setObjectName(QString::fromUtf8("actionClose_and_save_dictionaries"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetMinAndMaxSize);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setWindowModality(Qt::ApplicationModal);
        line->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(100);
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(400, 20));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(145, 146, 159);"));
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(60);
        line->setMidLineWidth(0);
        line->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMouseTracking(true);
        tabWidget->setAcceptDrops(true);
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(171, 171, 255);"));
        tabWidget->setTabsClosable(true);

        verticalLayout_2->addWidget(tabWidget);

        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setWindowModality(Qt::ApplicationModal);
        sizePolicy.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy);
        line_2->setMinimumSize(QSize(400, 20));
        line_2->setStyleSheet(QString::fromUtf8("background-color: rgb(145, 146, 159);\n"
"selection-background-color: rgb(255, 255, 184);"));
        line_2->setFrameShadow(QFrame::Raised);
        line_2->setLineWidth(60);
        line_2->setFrameShape(QFrame::HLine);

        verticalLayout_2->addWidget(line_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_Search = new QPushButton(centralwidget);
        pushButton_Search->setObjectName(QString::fromUtf8("pushButton_Search"));
        pushButton_Search->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 190, 190);"));
        pushButton_Search->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));

        horizontalLayout_3->addWidget(pushButton_Search);

        searchLineEdit = new QLineEdit(centralwidget);
        searchLineEdit->setObjectName(QString::fromUtf8("searchLineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(searchLineEdit->sizePolicy().hasHeightForWidth());
        searchLineEdit->setSizePolicy(sizePolicy1);
        searchLineEdit->setMinimumSize(QSize(200, 0));
        searchLineEdit->setBaseSize(QSize(0, 0));
        searchLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(201, 190, 255);"));

        horizontalLayout_3->addWidget(searchLineEdit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        pushButton_Diagramm = new QPushButton(centralwidget);
        pushButton_Diagramm->setObjectName(QString::fromUtf8("pushButton_Diagramm"));
        pushButton_Diagramm->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 190, 190);"));

        horizontalLayout_3->addWidget(pushButton_Diagramm);

        pushButton_Window = new QPushButton(centralwidget);
        pushButton_Window->setObjectName(QString::fromUtf8("pushButton_Window"));
        pushButton_Window->setStyleSheet(QString::fromUtf8("background-color: rgb(190, 190, 190);"));

        horizontalLayout_3->addWidget(pushButton_Window);


        verticalLayout_3->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setEnabled(true);
        MainWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 734, 22));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(menubar->sizePolicy().hasHeightForWidth());
        menubar->setSizePolicy(sizePolicy2);
        menubar->setCursor(QCursor(Qt::ArrowCursor));
        menubar->setNativeMenuBar(true);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuSwitch_language = new QMenu(menu_2);
        menuSwitch_language->setObjectName(QString::fromUtf8("menuSwitch_language"));
        menuDictioanary = new QMenu(menubar);
        menuDictioanary->setObjectName(QString::fromUtf8("menuDictioanary"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menuDictioanary->menuAction());
        menubar->addAction(menu->menuAction());
        menuFile->addAction(action_1_openFile);
        menuFile->addAction(actionCreate_new);
        menuFile->addAction(action_2_saveFile);
        menuFile->addAction(action_3_exit);
        menu->addAction(action_4_aboutAuthor);
        menu->addAction(action_5_Info);
        menu_2->addAction(menuSwitch_language->menuAction());
        menuDictioanary->addAction(actionOpen_dictionaries);
        menuDictioanary->addAction(actionAdd_new_record);
        menuDictioanary->addAction(actionRemove_record);
        menuDictioanary->addAction(actionAdd_new_dictionary);
        menuDictioanary->addAction(actionShow_dictionaries);
        menuDictioanary->addAction(actionClose_and_save_dictionaries);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        action_1_openFile->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        action_1_openFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        action_2_saveFile->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
#if QT_CONFIG(shortcut)
        action_2_saveFile->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        action_3_exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        action_4_aboutAuthor->setText(QCoreApplication::translate("MainWindow", "About author", nullptr));
        actionRussian_2->setText(QCoreApplication::translate("MainWindow", "Russian", nullptr));
        actionEnglish_2->setText(QCoreApplication::translate("MainWindow", "English", nullptr));
        actionGerman->setText(QCoreApplication::translate("MainWindow", "German", nullptr));
        action_5_Info->setText(QCoreApplication::translate("MainWindow", "Info", nullptr));
#if QT_CONFIG(shortcut)
        action_5_Info->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+H", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen_dictionaries->setText(QCoreApplication::translate("MainWindow", "Open dictionaries", nullptr));
        actionAdd_new_dictionary->setText(QCoreApplication::translate("MainWindow", "Add new dictionary", nullptr));
        actionCreate_new->setText(QCoreApplication::translate("MainWindow", "Create new", nullptr));
        actionShow_dictionaries->setText(QCoreApplication::translate("MainWindow", "Show dictionaries", nullptr));
        actionAdd_new_record->setText(QCoreApplication::translate("MainWindow", "Add new record", nullptr));
        actionRemove_record->setText(QCoreApplication::translate("MainWindow", "Remove record", nullptr));
        actionClose_and_save_dictionaries->setText(QCoreApplication::translate("MainWindow", "Close and save dictionaries", nullptr));
        pushButton_Search->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        pushButton_Diagramm->setText(QCoreApplication::translate("MainWindow", "Diagramm", nullptr));
        pushButton_Window->setText(QCoreApplication::translate("MainWindow", "Window", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuSwitch_language->setTitle(QCoreApplication::translate("MainWindow", "Switch language", nullptr));
        menuDictioanary->setTitle(QCoreApplication::translate("MainWindow", "Dictionary", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
