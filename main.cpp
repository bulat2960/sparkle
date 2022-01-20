#include <QApplication>

#include <QHotkey>
#include <QFile>
#include <QSettings>

#include "mainwindow.h"
#include "popupwidget.h"

void initStyleSheet(QApplication *app)
{
    QFile styleFile(":/styles/styles.css");

    if (styleFile.open(QIODevice::ReadOnly))
    {
        QTextStream textStream(&styleFile);
        QString styleSheet = textStream.readAll();
        styleFile.close();

        app->setStyleSheet(styleSheet);
    }
    else
    {
        qDebug() << "Can't open stylesheet file";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    QHotkey activatePopupsHotkey(QKeySequence("Ctrl+Alt+W"), true, &a);

    QObject::connect(&showHotkey, &QHotkey::activated, &mainWindow, &MainWindow::showFullScreen);
    QObject::connect(&hideHotkey, &QHotkey::activated, &mainWindow, &MainWindow::hide);
    QObject::connect(&activatePopupsHotkey, &QHotkey::activated, &mainWindow, &MainWindow::updatePopupsActiveStatus);

    initStyleSheet(&a);

    trayIcon.show();

    return a.exec();
}
