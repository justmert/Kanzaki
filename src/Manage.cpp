#include "Manage.h"
#include <iostream>
#include <algorithm>
#include "FetchAndParse.h"
#include "Anime.h"
#include "FetchEpisodes.h"
#define v FetchAndParse::vector
#define ep FetchEpisodes::VectorEpisode



std::string MakeInput()
{
    std::string input;
    std::getline(std::cin, input);
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    return Trim(input);
}

int returnNum(const std::string s)
{
    int num;
    try
    {
        num = std::stoi(s);
    }
    catch (const std::exception &error)
    {
        std::cout << "Given argument is not a number" << std::endl;
    }
    return num;
}

std::pair<std::string, std::string> Manage::ParseInput(std::string input)
{
    auto it = std::find(input.begin(), input.end(), ' ');
    //first space encountered
    auto it2 = std::find_if(it, input.end(), [](char p) { return p != ' '; });
    // first non space encountered after first space

    std::string argument = std::string(it2, input.end());
    std::string command = std::string(input.begin(), it);
    return {command, argument};
}

void Manage::ListFoundAnimes(std::string argument)
{
    std::vector<Anime> found;
    for (auto &&item : FetchAndParse::vector)
    {
        std::string name = item.name;
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        auto it = name.find(argument);
        if (it != std::string::npos)
        {
            found.push_back(item);
        }
    }

    if (found.empty())
    {
        std::cout << "No anime found" << std::endl;
    }
    else
    {
        system("clear");
        std::cout << "Found animes" << std::endl;
        for (auto &&item : found)
        {
            std::cout << " " << item.number << "・" << item.name << std::endl;
        }
    }
}

void Manage::ManageProgram()
{
    while (true)
    {
        std::cout << "\n❖ › ";
        std::string input = MakeInput();
        if (input == "exit")
        {
            return;
        }

        if (input == "-h" || input == "help")
        {
            PrintHelpFirst();
        }

        else if (input == "-l" || input == "list")
        {
            ListAllAnimes();
        }
        else
        {
            std::pair<std::string, std::string> mypair = ParseInput(input);
            if (mypair.first == "-s" || mypair.first == "select")
            {
                int num;
                try
                {
                    num = std::stoi(mypair.second);
                }
                catch (const std::exception &error)
                {
                    std::cout << "Given argument is not a number" << std::endl;
                    continue;
                }
                auto it = std::find_if(v.begin(), v.end(), [&](Anime p) { return p.number == num; });
                if (it != v.end())
                {
                    bool do_exit = SelectAnime(v[num-1]);
                    if (do_exit)
                        return;
                    else
                        ListAllAnimes();
                }
                else
                {
                    std::cout << "There is no anime with that number" << std::endl;
                }
            }
            else if (mypair.first == "-f" || mypair.first == "find")
            {
                ListFoundAnimes(mypair.second);
            }
            else
            {
                std::cout << "There is no such a command" << std::endl;
            }
        }
    }
}

void Manage::ListAllAnimes()
{
    system("clear");
    std::cout << "Animes" << std::endl;
    for (auto &&item : FetchAndParse::vector)
    {
        std::cout << " " << item.number << "・" << item.name << std::endl;
    }
}

bool Manage::SelectAnime(Anime item)
{
    std::cout << "Fetching " << item.name << " episodes\n";
    std::string episodelink = FetchEpisodes::FetchAnimeEp(item.number-1);

    while (true)
    {
        std::cout << "\n❖ " << item.name << " › ";
        std::string input = MakeInput();
        if (input == "back" || input == "-b" || input == "exit")
        {
            if (input == "exit")
                return true;
            else
                return false;
        }
        else if (input == "-e" || input == "episodes")
        {
            ListAllEpisodes(item.number-1);
        }
        else if (input == "-h" || input == "help")
        {
            PrintHelpSecond();
        }
        else
        {
            std::pair<std::string, std::string> mypair = ParseInput(input);
            std::string mf = mypair.first;
            if (mf == "-p" || mf == "play" || mf == "-d" || input == "download")
            {
                int num;
                try
                {
                    num = std::stoi(mypair.second);
                }
                catch (const std::exception &e)
                {
                    std::cout << "Given argument is not a number" << std::endl;
                    continue;
                }
                auto it = std::find_if(ep.begin(), ep.end(), [&](Anime p) { return p.number == num; });
                if (it != ep.end())
                {
                    std::string videoLink ="https://storage.kanzaki.ru/ANIME___/"+ item.link + ep[num-1].link;
                    if (mypair.first == "-p" || mypair.first == "play")
                    {
                        FetchEpisodes::PlayAnime(videoLink);
                    }
                    else if (mypair.first == "-d" || mypair.first == "download")
                    {
                        FetchEpisodes::DownloadAnime(videoLink);
                    }
                }
                else
                {
                    std::cout << "There is no episode with that number" << std::endl;
                }
            }
            else
            {
                std::cout << "There is no such a command" << std::endl;
            }
        }
    }
}
void Manage::ListAllEpisodes(int number)
{
    system("clear");
    std::cout << "\nEpisodes" << std::endl;
    for (auto &&item : ep)
    {
        std::cout << " " << item.number << "・" << item.name << std::endl;
    }
}

void Manage::PrintHelpFirst()
{
    std::cout << " Commands" << std::endl;
    std::cout << "   -h || help                >      show help" << std::endl;
    std::cout << "   -f || find [argument]     >      list matching animes" << std::endl;
    std::cout << "   -s || select [number]     >      select anime for play or download" << std::endl;
    std::cout << "   -l || list                >      list all animes" << std::endl;
    std::cout << "   exit                      >      exit program" << std::endl;
}

void Manage::PrintHelpSecond()
{
    std::cout << " Commands" << std::endl;
    std::cout << "   -h || help                >      show help" << std::endl;
    std::cout << "   -e || episodes            >      list episodes" << std::endl;
    std::cout << "   -b || back                >      back from selected anime to all list" << std::endl;
    std::cout << "   -p || play [episode]      >      play that episode" << std::endl;
    std::cout << "   -d || download [episode]  >      download that episode" << std::endl;
    std::cout << "   exit                      >      exit program" << std::endl;
}