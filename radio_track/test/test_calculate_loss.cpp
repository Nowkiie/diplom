#include <gtest/gtest.h>
#include <calculate/calculationLosses.h>
#include <fstream>

//todo(PtakhovaA): добавить класс, в котором реализовать методы парсинга строки и сохранение высот

TEST(calc_loss, test_example_from_library)
{
    using namespace track::calculation::losses;

    std::shared_ptr<calcLosses> calc_losses = std::make_shared<calcLosses>();

    std::vector<double> profile{
        142,  25.6, 1692, 1692, 1693, 1693, 1693, 1693, 1693, 1693, 1694, 1694,
        1694, 1694, 1694, 1694, 1694, 1694, 1694, 1695, 1695, 1695, 1695, 1695,
        1695, 1695, 1695, 1696, 1696, 1696, 1696, 1696, 1696, 1697, 1697, 1697,
        1697, 1697, 1697, 1697, 1697, 1697, 1697, 1698, 1698, 1698, 1698, 1698,
        1698, 1698, 1698, 1698, 1698, 1699, 1699, 1699, 1699, 1699, 1699, 1700,
        1700, 1700, 1700, 1700, 1700, 1700, 1701, 1701, 1701, 1701, 1701, 1701,
        1702, 1702, 1702, 1702, 1702, 1702, 1702, 1702, 1703, 1703, 1703, 1703,
        1703, 1703, 1703, 1703, 1703, 1704, 1704, 1704, 1704, 1704, 1704, 1704,
        1704, 1705, 1705, 1705, 1705, 1705, 1705, 1705, 1705, 1705, 1705, 1706,
        1706, 1706, 1706, 1706, 1706, 1706, 1706, 1706, 1707, 1707, 1707, 1707,
        1707, 1707, 1707, 1708, 1708, 1708, 1708, 1708, 1708, 1708, 1708, 1709,
        1709, 1709, 1709, 1709, 1710, 1710, 1710, 1710, 1710, 1710, 1710, 1710,
        1709};

    double A_db =
        calc_losses->calculateLossesInItmModel(15, 3, profile, 5, 3500, 1);
    double diff = abs(141 - A_db);

    ASSERT_LE(diff, 10);
}

TEST(calc_loss, test_radiomobile_radiotrack_ukraina)
{
    std::fstream inf{"profile_ukraina.txt"};

    std::string str{};
    int num = 0;
    std::vector<double> heights;
    auto parse_str = [&heights](std::string& str, std::string delimeter)
    {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimeter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimeter.length());
        }
        // tokens.push_back(str);
        heights.push_back(stod(tokens[1]));
    };

    while (std::getline(inf, str))
    {
        num++;
        if (num >= 21)
        {
            //todo
            parse_str(str, "\t");
        }
    }

    using namespace track::calculation::losses;
    std::shared_ptr<calcLosses> calc_losses = std::make_shared<calcLosses>();

    double A_db =
        calc_losses->calculateLossesInItmModel(2, 2, heights, 5, 23, 1);

    double diff = abs(A_db - 110.9);
    ASSERT_LE(diff, 10);
}

TEST(calc_loss, test_radiomobile_radiotrack_kirov)
{
    std::ifstream inf{"profile_kirov.txt"};

    std::string str{};
    int num = 0;
    std::vector<double> heights;
    auto parse_str = [&heights](std::string& str, std::string delimeter)
    {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimeter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimeter.length());
        }
        // tokens.push_back(str);
        heights.push_back(stod(tokens[1]));
    };

    while (std::getline(inf, str))
    {
        num++;
        if (num >= 21)
        {
            //todo
            parse_str(str, "\t");
        }
    }

    using namespace track::calculation::losses;
    std::shared_ptr<calcLosses> calc_losses = std::make_shared<calcLosses>();

    double A_db =
        calc_losses->calculateLossesInItmModel(15, 15, heights, 5, 144, 0);

    double diff = abs(A_db - 128.9);
    ASSERT_LE(diff, 10);
}

TEST(calc_margin, test_radiotrack_radiomobile)
{
    std::ifstream inf{"profile6.txt"};

    std::string str{};
    int num = 0;
    std::vector<double> heights;
    auto parse_str = [&heights](std::string& str, std::string delimeter)
    {
        std::vector<std::string> tokens;
        size_t pos = 0;
        std::string token;
        while ((pos = str.find(delimeter)) != std::string::npos)
        {
            token = str.substr(0, pos);
            tokens.push_back(token);
            str.erase(0, pos + delimeter.length());
        }
        // tokens.push_back(str);
        heights.push_back(stod(tokens[1]));
    };

    while (std::getline(inf, str))
    {
        num++;
        if (num >= 21)
        {
            //todo
            parse_str(str, "\t");
        }
    }

    using namespace track::calculation::losses;
    std::shared_ptr<calcLosses> calc_losses = std::make_shared<calcLosses>();

    double A_db =
        calc_losses->calculateLossesInItmModel(2, 2, heights, 5, 23, 1);

    double margin = 40 + 2 + 2 - A_db + 107;


}