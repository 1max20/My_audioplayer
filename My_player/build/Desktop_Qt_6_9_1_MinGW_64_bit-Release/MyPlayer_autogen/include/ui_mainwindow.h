/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <clickslider.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen_file;
    QAction *actionOpen_playlist;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnPrev;
    QPushButton *btnPlayPause;
    QPushButton *btnNext;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_Replay;
    QHBoxLayout *horizontalLayout_5;
    QLabel *File_Name;
    QHBoxLayout *horizontalLayout_2;
    QTableView *tableView;
    QVBoxLayout *verticalLayout;
    ClickSlider *positionSlider;
    QHBoxLayout *horizontalLayout_4;
    QLabel *currentTimeLabel;
    QSpacerItem *horizontalSpacer_4;
    QLabel *timeLabel;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btn_mute;
    ClickSlider *volumeSlider;
    QLabel *albumCoverLabel;
    QMenuBar *menubar;
    QMenu *btnChooseFolder;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(830, 653);
        MainWindow->setMinimumSize(QSize(800, 600));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Main_icon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow\n"
"{\n"
"background: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 rgba(255, 40, 40, 255),     \n"
"        stop:0.5 rgba(30, 0, 50, 255),        \n"
"        stop:1 rgba(0, 10, 50, 255)           \n"
"    );\n"
"}\n"
"\n"
"QMenuBar {\n"
"    background: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 rgba(255, 40, 40, 255),    /* \320\272\321\200\320\260\321\201\320\275\321\213\320\271 \321\201\320\273\320\265\320\262\320\260 */\n"
"        stop:1 rgba(0, 10, 50, 255)       /* \320\272\320\276\321\201\320\274\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \321\201\320\270\320\275\320\270\320\271 \321\201\320\277\321\200\320\260\320\262\320\260 */\n"
"    );\n"
"    color: white;\n"
"    border: none;\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    background: transparent;\n"
"    padding: 4px 12px;\n"
"}\n"
"\n"
"QMenuBar::item:selected {\n"
"    background-color: rgba(255, 255, 255, 30);  /* \321\201"
                        "\320\273\320\265\320\263\320\272\320\260 \320\277\320\276\320\264\321\201\320\262\320\265\321\202\320\272\320\260 \320\277\321\200\320\270 \320\275\320\260\320\262\320\265\320\264\320\265\320\275\320\270\320\270 */\n"
"}\n"
"\n"
"QMenu {\n"
"    background: qlineargradient(\n"
"        spread:pad,\n"
"        x1:0, y1:0, x2:1, y2:1,\n"
"        stop:0 rgba(30, 0, 50, 255),\n"
"        stop:1 rgba(0, 10, 50, 255)\n"
"    );\n"
"    color: white;\n"
"}\n"
"\n"
"QMenu::item:selected {\n"
"    background-color: rgba(255, 255, 255, 30);\n"
"}\n"
""));
        MainWindow->setIconSize(QSize(32, 32));
        actionOpen_file = new QAction(MainWindow);
        actionOpen_file->setObjectName("actionOpen_file");
        actionOpen_playlist = new QAction(MainWindow);
        actionOpen_playlist->setObjectName("actionOpen_playlist");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        centralwidget->setStyleSheet(QString::fromUtf8(""));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnPrev = new QPushButton(centralwidget);
        btnPrev->setObjectName("btnPrev");
        btnPrev->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnPrev->sizePolicy().hasHeightForWidth());
        btnPrev->setSizePolicy(sizePolicy);
        btnPrev->setMouseTracking(false);
        btnPrev->setTabletTracking(false);
        btnPrev->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        btnPrev->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"Border:none;\n"
"Border-radius: 22px;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("previous.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnPrev->setIcon(icon1);
        btnPrev->setIconSize(QSize(32, 32));
        btnPrev->setCheckable(false);
        btnPrev->setAutoDefault(true);

        horizontalLayout->addWidget(btnPrev);

        btnPlayPause = new QPushButton(centralwidget);
        btnPlayPause->setObjectName("btnPlayPause");
        sizePolicy.setHeightForWidth(btnPlayPause->sizePolicy().hasHeightForWidth());
        btnPlayPause->setSizePolicy(sizePolicy);
        btnPlayPause->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"Border:none;\n"
"Border-radius: 22px;\n"
"background-color: rgb(255, 255, 255);\n"
"color: rgb(51, 15, 255);\n"
"min-width:45px;\n"
"max-width:45px;\n"
"min-height:45px;\n"
"max-height:45px;\n"
"padding:0px;\n"
"}\n"
""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("play.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnPlayPause->setIcon(icon2);
        btnPlayPause->setIconSize(QSize(30, 30));
        btnPlayPause->setCheckable(true);
        btnPlayPause->setChecked(false);
        btnPlayPause->setAutoRepeatDelay(300);
        btnPlayPause->setFlat(false);

        horizontalLayout->addWidget(btnPlayPause, 0, Qt::AlignmentFlag::AlignHCenter);

        btnNext = new QPushButton(centralwidget);
        btnNext->setObjectName("btnNext");
        btnNext->setEnabled(true);
        sizePolicy.setHeightForWidth(btnNext->sizePolicy().hasHeightForWidth());
        btnNext->setSizePolicy(sizePolicy);
        btnNext->setMouseTracking(false);
        btnNext->setTabletTracking(false);
        btnNext->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        btnNext->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"Border:none;\n"
"Border-radius: 22px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("next.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btnNext->setIcon(icon3);
        btnNext->setIconSize(QSize(32, 32));
        btnNext->setCheckable(false);
        btnNext->setAutoDefault(true);

        horizontalLayout->addWidget(btnNext);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_Replay = new QPushButton(centralwidget);
        btn_Replay->setObjectName("btn_Replay");
        btn_Replay->setEnabled(true);
        sizePolicy.setHeightForWidth(btn_Replay->sizePolicy().hasHeightForWidth());
        btn_Replay->setSizePolicy(sizePolicy);
        btn_Replay->setMouseTracking(false);
        btn_Replay->setTabletTracking(false);
        btn_Replay->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        btn_Replay->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"Border:none;\n"
"Border-radius: 22px;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("repeat.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_Replay->setIcon(icon4);
        btn_Replay->setIconSize(QSize(32, 32));
        btn_Replay->setCheckable(false);
        btn_Replay->setAutoDefault(true);

        horizontalLayout->addWidget(btn_Replay);


        gridLayout->addLayout(horizontalLayout, 4, 1, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        File_Name = new QLabel(centralwidget);
        File_Name->setObjectName("File_Name");
        sizePolicy.setHeightForWidth(File_Name->sizePolicy().hasHeightForWidth());
        File_Name->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        font.setPointSize(12);
        font.setStyleStrategy(QFont::PreferDefault);
        File_Name->setFont(font);
        File_Name->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: rgb(192, 192, 192);\n"
"}"));
        File_Name->setFrameShape(QFrame::Shape::NoFrame);
        File_Name->setFrameShadow(QFrame::Shadow::Raised);
        File_Name->setTextFormat(Qt::TextFormat::RichText);

        horizontalLayout_5->addWidget(File_Name);


        gridLayout->addLayout(horizontalLayout_5, 1, 1, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setSizeConstraint(QLayout::SizeConstraint::SetFixedSize);
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy1);
        tableView->setStyleSheet(QString::fromUtf8("QTableView\n"
"{\n"
"background-color: rgba(0, 0, 5, 0.5);\n"
"    color: white;                      \n"
"    border: none;\n"
"    gridline-color: rgba(192, 192, 192, 30);\n"
"}\n"
"QHeaderView::section {\n"
"    background: qlineargradient(\n"
"        x1:0, y1:0, x2:1, y2:0,\n"
"        stop:0 rgba(255, 40, 40, 255),\n"
"        stop:1 rgba(0, 10, 50, 255)\n"
"    );\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 4px;\n"
"}\n"
"\n"
"QTableCornerButton::section {\n"
"    background-color: rgba(60, 0, 40, 255);  /* \321\202\321\221\320\274\320\275\321\213\320\271 \320\272\321\200\320\260\321\201\320\275\320\276-\321\204\320\270\320\276\320\273\320\265\321\202\320\276\320\262\321\213\320\271 */\n"
"    border: none;\n"
"}\n"
"\n"
"QTableView::item:selected {\n"
"    background-color: rgba(192, 192, 192, 50); /* \320\262\321\213\320\264\320\265\320\273\320\265\320\275\320\270\320\265 */\n"
"    color: white;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"    border: none;\n"
"    background: transparen"
                        "t;\n"
"    width: 10px;\n"
"    margin: 0px 0px 0px 0px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: rgba(255, 40, 40, 100); /* \320\277\320\276\320\273\321\203\320\277\321\200\320\276\320\267\321\200\320\260\321\207\320\275\321\213\320\271 \320\272\321\200\320\260\321\201\320\275\321\213\320\271 */\n"
"    min-height: 20px;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QScrollBar::add-line:vertical,\n"
"QScrollBar::sub-line:vertical {\n"
"    height: 0px;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical,\n"
"QScrollBar::sub-page:vertical {\n"
"    background: none;\n"
"}\n"
"\n"
""));

        horizontalLayout_2->addWidget(tableView);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 5, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        positionSlider = new ClickSlider(centralwidget);
        positionSlider->setObjectName("positionSlider");
        positionSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"height:10px;\n"
"background:none;\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"background:rgb(173, 0, 0);\n"
"height:40px;\n"
"width:20px;\n"
"margin:-7px -7px;\n"
"border-radius:5px;\n"
"}"));
        positionSlider->setMaximum(100);
        positionSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout->addWidget(positionSlider);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        currentTimeLabel = new QLabel(centralwidget);
        currentTimeLabel->setObjectName("currentTimeLabel");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(currentTimeLabel->sizePolicy().hasHeightForWidth());
        currentTimeLabel->setSizePolicy(sizePolicy2);
        currentTimeLabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: rgb(192, 192, 192);\n"
"}"));

        horizontalLayout_4->addWidget(currentTimeLabel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName("timeLabel");
        sizePolicy2.setHeightForWidth(timeLabel->sizePolicy().hasHeightForWidth());
        timeLabel->setSizePolicy(sizePolicy2);
        timeLabel->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: rgb(192, 192, 192);\n"
"}"));
        timeLabel->setFrameShape(QFrame::Shape::NoFrame);

        horizontalLayout_4->addWidget(timeLabel);


        gridLayout->addLayout(horizontalLayout_4, 3, 1, 1, 2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        btn_mute = new QPushButton(centralwidget);
        btn_mute->setObjectName("btn_mute");
        btn_mute->setEnabled(true);
        btn_mute->setMouseTracking(false);
        btn_mute->setTabletTracking(false);
        btn_mute->setFocusPolicy(Qt::FocusPolicy::StrongFocus);
        btn_mute->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"Border:none;\n"
"Border-radius: 22px;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("volume-mute2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        btn_mute->setIcon(icon5);
        btn_mute->setIconSize(QSize(32, 32));
        btn_mute->setCheckable(false);
        btn_mute->setAutoDefault(true);

        horizontalLayout_3->addWidget(btn_mute);

        volumeSlider = new ClickSlider(centralwidget);
        volumeSlider->setObjectName("volumeSlider");
        sizePolicy.setHeightForWidth(volumeSlider->sizePolicy().hasHeightForWidth());
        volumeSlider->setSizePolicy(sizePolicy);
        volumeSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal\n"
"{\n"
"height:10px;\n"
"background:(243, 248, 251);\n"
"}\n"
"QSlider::handle:horizontal\n"
"{\n"
"background:rgb(173, 0, 0);\n"
"height:40px;\n"
"width:20px;\n"
"margin:-7px -7px;\n"
"border-radius:5px;\n"
"}"));
        volumeSlider->setMaximum(100);
        volumeSlider->setOrientation(Qt::Orientation::Horizontal);

        horizontalLayout_3->addWidget(volumeSlider);


        gridLayout->addLayout(horizontalLayout_3, 4, 2, 1, 1);

        albumCoverLabel = new QLabel(centralwidget);
        albumCoverLabel->setObjectName("albumCoverLabel");
        albumCoverLabel->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(albumCoverLabel->sizePolicy().hasHeightForWidth());
        albumCoverLabel->setSizePolicy(sizePolicy3);
        albumCoverLabel->setMinimumSize(QSize(200, 200));
        albumCoverLabel->setFrameShape(QFrame::Shape::NoFrame);
        albumCoverLabel->setPixmap(QPixmap(QString::fromUtf8(":/icons/Main_icon2.png")));
        albumCoverLabel->setScaledContents(true);

        gridLayout->addWidget(albumCoverLabel, 0, 1, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 830, 25));
        btnChooseFolder = new QMenu(menubar);
        btnChooseFolder->setObjectName("btnChooseFolder");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(btnChooseFolder->menuAction());
        btnChooseFolder->addSeparator();
        btnChooseFolder->addAction(actionOpen_file);
        btnChooseFolder->addAction(actionOpen_playlist);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "My_player", nullptr));
        actionOpen_file->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\260\321\203\320\264\320\270\320\276\321\204\320\260\320\271\320\273", nullptr));
        actionOpen_playlist->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\260\320\277\320\272\321\203 \321\201 \320\260\321\203\320\264\320\270\320\276\321\204\320\260\320\271\320\273\320\260\320\274\320\270", nullptr));
        btnPrev->setText(QString());
        btnPlayPause->setText(QString());
        btnNext->setText(QString());
        btn_Replay->setText(QString());
        File_Name->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt; font-style:italic; color:#c0c0c0;\">Name:</span></p></body></html>", nullptr));
        currentTimeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#c0c0c0;\">00:00</span></p></body></html>", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" color:#c0c0c0;\">00:00</span></p></body></html>", nullptr));
        btn_mute->setText(QString());
        btnChooseFolder->setTitle(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\262\320\276\320\264\320\275\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
