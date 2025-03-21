#include "radio_track.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>
#include <QtCore/QTranslator>

std::shared_ptr<SettingControl> InitializeApplicationSettings()
{
    QFileInfo fileInfo(qApp->applicationFilePath());
    QString sFilename =
        fileInfo.absolutePath() + '/' + fileInfo.baseName() + ".ini";
    ParamsList settingsList{
        {"Position/Latitude", "44.234"}, {"Position/Longitude", "34.234"},
        {"Draw/MaxLines", "30"},         {"Draw/MaxRect", "3000"},
        {"Draw/TempNetStepSec", "300"},
    };
    return std::make_shared<SettingControl>(sFilename, settingsList);
}

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QTranslator myTrans;
    if (myTrans.load(":/translate/radio_track_ru.qm"))
    {
        a.installTranslator(&myTrans);
    }
    a.installTranslator(&myTrans);
    const auto appSettings = InitializeApplicationSettings();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    track::radio_track w(appSettings);
    w.show();
    return a.exec();
}
