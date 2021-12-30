#include <QApplication>
#include <QSettings>

#include <QAction>
#include <QMenu>
#include <QHotkey>

#include "mainwindow.h"
#include "popupwidget.h"

#include "charts/piechart.h"
#include "charts/linechart.h"

#include <QChartView>
#include <QRandomGenerator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMap<int, double> values;

    a.setApplicationName(QStringLiteral("Sparkle"));

    QString applicationPath = QCoreApplication::applicationFilePath().replace('/', '\\');
    QSettings autostartSettings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    autostartSettings.setValue("Sparkle", applicationPath);

    MainWindow mainWindow;
    QObject::connect(&a, &QApplication::aboutToQuit, &mainWindow, &MainWindow::save);

    QSystemTrayIcon trayIcon(QIcon(":/icons/sparkle.png"));
    QObject::connect(&a, &QApplication::aboutToQuit, &trayIcon, &QSystemTrayIcon::hide);

    auto quitAction = new QAction("Quit", &trayIcon);
    QObject::connect(quitAction, &QAction::triggered, &mainWindow, &MainWindow::close);

    auto trayIconMenu = new QMenu;

    trayIconMenu->addAction(quitAction);
    trayIcon.setContextMenu(trayIconMenu);


    QHotkey showHotkey(QKeySequence("Ctrl+Alt+S"), true, &a);
    QHotkey hideHotkey(QKeySequence("Ctrl+Alt+D"), true, &a);

    QObject::connect(&showHotkey, &QHotkey::activated, &mainWindow, &MainWindow::show);
    QObject::connect(&hideHotkey, &QHotkey::activated, &mainWindow, &MainWindow::hide);


    trayIcon.show();
    mainWindow.showFullScreen();

    return a.exec();
}
