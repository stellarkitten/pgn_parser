#include <fstream>
#include <algorithm>

int main()
{
    std::string Event;
    std::string Site;
    std::string White;
    std::string Black;
    std::string Result;
    std::string UTCDate;
    std::string UTCTime;
    std::string WhiteElo;
    std::string BlackElo;
    std::string WhiteRatingDiff;
    std::string BlackRatingDiff;
    std::string ECO;
    std::string Opening;
    std::string TimeControl;
    std::string Termination;

    std::ofstream output_file("example/data.csv");
    output_file << "Event,Site,White,Black,Result,UTCDate,UTCTime,WhiteElo,BlackElo,WhiteRatingDiff,BlackRatingDiff,ECO,Opening,TimeControl,Termination" << std::endl;

    std::fstream input_file("example/lichess_db_standard_rated_2013-01.pgn");  // Source: https://database.lichess.org/

    std::string line;
    while (std::getline(input_file, line))
    {
        if (line.rfind('[', 0) == 0)
        {
            line.pop_back();  // Deletes last ]
            line.pop_back();  // Deletes last "

            int middle = line.find(' ');  // First space separates variable and value

            std::string variable = line.substr(1, middle-1);  // Variable starts after [ and ends before first space
            std::string value = line.substr(middle+2);  // Value starts after first "

            value.erase(std::remove(value.begin(), value.end(), ','), value.end());  // Removes commas that contaminate csv

            if (variable == "Event") Event = value;
            else if (variable == "Site") Site = value;
            else if (variable == "White") White = value;
            else if (variable == "Black") Black = value;
            else if (variable == "Result") Result = value;
            else if (variable == "UTCDate") UTCDate = value;
            else if (variable == "UTCTime") UTCTime = value;
            else if (variable == "WhiteElo") WhiteElo = value;
            else if (variable == "BlackElo") BlackElo = value;
            else if (variable == "WhiteRatingDiff") WhiteRatingDiff = value;
            else if (variable == "BlackRatingDiff") BlackRatingDiff = value;
            else if (variable == "ECO") ECO = value;
            else if (variable == "Opening") Opening = value;
            else if (variable == "TimeControl") TimeControl = value;
            else if (variable == "Termination") Termination = value;
        }

        if (line.rfind('1', 0) == 0 | line == "[Event")
        {
            output_file << Event << "," << Site << "," << White << "," << Black << "," << Result << "," << UTCDate << "," << UTCTime << "," << WhiteElo << "," << BlackElo << "," << WhiteRatingDiff << "," << BlackRatingDiff << "," << ECO << "," << Opening << "," << TimeControl << "," << Termination << std::endl;
        }
    }

    input_file.close();
    output_file.close();
    return 0;
}
