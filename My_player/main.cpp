#include "mainwindow.h"
#include <QApplication>
#include <QLocalSocket>
#include <QLocalServer>
#include <QFileInfo>
#include <QDataStream>

#define SOCKET_NAME "MyPlayerSingleInstance"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/icons/Main_icon.ico"));
    MainWindow w;

    // Попробовать подключиться к существующему экземпляру
    QLocalSocket socket;
    socket.connectToServer(SOCKET_NAME);

    if (socket.waitForConnected(100)) {
        if (argc > 1) {
            QByteArray block;
            QDataStream out(&block, QIODevice::WriteOnly);
            out << QString::fromLocal8Bit(argv[1]);
            socket.write(block);
            socket.flush();
            socket.waitForBytesWritten(100);
        }
        return 0;  // Завершить второй экземпляр
    }

    // Иначе — это первый экземпляр, создаём сервер
    QLocalServer server;
    if (QLocalServer::removeServer(SOCKET_NAME)) {
        server.listen(SOCKET_NAME);
    }

    // Обработка входящих подключений
    QObject::connect(&server, &QLocalServer::newConnection, &w, [&]() {
        QLocalSocket *client = server.nextPendingConnection();
        if (client->waitForReadyRead(100)) {
            QDataStream in(client);
            QString newFilePath;
            in >> newFilePath;
            w.loadFileFromPath(newFilePath);  // Загружаем новый файл
        }
        client->deleteLater();
    });

    // Загружаем файл, если был передан через аргумент
    if (argc > 1) {
        QString filePath = QString::fromLocal8Bit(argv[1]);
        QFileInfo checkFile(filePath);
        if (checkFile.exists() && checkFile.isFile()) {
            w.loadFileFromPath(filePath);
        }
    }

    w.show();
    return a.exec();
}
