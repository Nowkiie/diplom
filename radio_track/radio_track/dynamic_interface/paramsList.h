#pragma once
#include <QStringList>

namespace track::climateParams
{
enum climateList
{
    equatorial,
    continental_sub_tropic,
    martitime_sub_tropic,
    desert,
    continental_temperate,
    martitime_temperate_over_land,
    martitime_temperate_over_sea,
};

static QStringList getClimateList();
};  // namespace track::climateParams

inline QStringList climateParams::getClimateList()
{
    QStringList result;

    for (int it = climateList::equatorial;
         it <= climateList::martitime_temperate_over_sea; it++)
    {
        const auto climate = static_cast<climateParams::climateList>(it);

        switch (climate)
        {
            case equatorial:
            {
                result.push_back(QObject::tr("equatorial"));
                break;
            }
            case continental_sub_tropic:
            {
                result.push_back(QObject::tr("continental_sub_tropic"));
                break;
            }
            case martitime_sub_tropic:
            {
                result.push_back(QObject::tr("martitime_sub_tropic"));
                break;
            }
            case desert:
            {
                result.push_back(QObject::tr("desert"));
                break;
            }
            case continental_temperate:
            {
                result.push_back(QObject::tr("continental_temperate"));
                break;
            }
            case martitime_temperate_over_land:
            {
                result.push_back(QObject::tr("martitime_temperate_over_land"));
                break;
            }
            case martitime_temperate_over_sea:
            {
                result.push_back(QObject::tr("martitime_temperate_over_sea"));
                break;
            }
            default:
            {
                //todo(PtakhovaA): add logger
                break;
            };
        }
    }
    return result;
}
