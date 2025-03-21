#pragma once
#include <QObject>
#include <QSettings>
#include <QTextCodec>
#include <vector>
#include <memory>
#include <map>

using ParamsItem = std::pair<QString, QString>;
using ParamsList = std::vector<ParamsItem>;
using TranslateMap = std::map<QString, QString>;
class SettingControl : protected QSettings
{
    Q_OBJECT
public:
    SettingControl(QString filename, const ParamsList& settingsList)
        : QSettings(filename, QSettings::IniFormat)
    {
        codec_ = QTextCodec::codecForName("utf-8");
        this->setIniCodec(codec_);
        for (const auto& obj : settingsList)
        {
            if (!contains(obj.first))
            {
                setValue(obj.first, obj.second);
            }
        }
        sync();
    };
    template <typename t>
    inline t GetSetting(QString SettingName)
    {
        return this->value(SettingName).value<t>();
    }
    void SetValue(const QString& param, const QVariant& value)
    {
        setValue(param, value);
    }
    void SetSettingTranslation(const ParamsList& settingsList) {}
    ~SettingControl(){};

private:
    TranslateMap translateMap;
    QTextCodec* codec_;
};
using PSettingControl = std::shared_ptr<SettingControl>;