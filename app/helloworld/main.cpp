#include "cmake-git-version-tracking/git.h"
#include "g3log/log.hpp"

#include <QDate>
#include <QLocale>
#include <QDir>
#include <QStandardPaths>
#include <QCoreApplication>

#include <QTimer>
#include <QDebug>

int main(int argc, char *argv[])
{
    try
    {
        QCoreApplication app(argc, argv);
        QString buildTimestamp = QString("%1 %2").arg(QLocale("en_US").toDate(QString(__DATE__).simplified(), "MMM d yyyy").toString("dd.MM.yy"), __TIME__);
        QString version = QString::fromStdString(GitMetadata::Describe());
        QCoreApplication::setApplicationVersion(version);

        QString logPath = QDir::toNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::TempLocation)) + QDir::separator();
        g3::initializeLoggingFramework(app.applicationName().toStdString(), logPath.toStdString(), true);
        qInfo().noquote() << QString("%1 version %2 (%3) [Qt version %4, logPath=%5]").arg(app.applicationName(), version, buildTimestamp, qVersion(), logPath);

        QTimer::singleShot(3000, /*this*/ nullptr, []()
        {
            qDebug() << "Hello world";
        } );

        return app.exec();
    }
    catch(std::exception& e)
    {
         qCritical() << "C++ exception occurred:" << e.what();
    }
    catch(...)
    {
        qCritical() << "C++ exception occurred: unknown exception class";
    }
    return -1;
}
