#include "FetchEpisodes.h"
#include "Manage.h"
#include "FetchAndParse.h"
#include <iostream>
#include <map>
#include <experimental/filesystem>
#include "Anime.h"
#include <algorithm>
#define fs std::experimental::filesystem
std::vector<Anime> FetchEpisodes::VectorEpisode;

std::string FetchEpisodes::FetchAnimeEp(int animeNum)
{

    std::string link = FetchAndParse::vector[animeNum].link;
    std::string episodeLink = "https://storage.kanzaki.ru/ANIME___/" + link;

    std::string animehtml = FetchAndParse::DownloadHtml(episodeLink);
    system("clear");
    std::cout << "Episodes" << std::endl;
    FetchAndParse::SplitLinkAndName(FetchAndParse::ParseHtml(animehtml), VectorEpisode);

    return episodeLink;
}

void FetchEpisodes::PlayAnime(std::string link)
{
    std::string playonvlc = "vlc " + link + "  --network-caching=5000";
    std::cout << playonvlc << std::endl;
    const char *cplayonvlc = playonvlc.c_str();
    system(cplayonvlc);
}

std::string FetchEpisodes::replaceSpaces(std::string str)
{
    for (int i = 0; i < str.size(); i++)
    {
        if (ispunct(str[i])||isspace(str[i]))
        {
            str[i] = '.';
        }
    }
    str.erase(std::unique(str.begin(),str.end(),[](char p, char k){return p == k && p == '.';}),str.end());
    if (str[0] == '.')
    {
        str = std::string(str.begin()+1,str.end());
    }
    return str;
}

void FetchEpisodes::DownloadAnime(std::string link, std::string &animeName, std::string &epname)
{
    bool dosave = false;
    std::string where;
    animeName = replaceSpaces(animeName);
    epname = replaceSpaces(epname);
    if (!fs::exists(Manage::path + "/" + animeName))
    {
        fs::create_directory(Manage::path + "/" + animeName);
    }
    std::string defaultpath = Manage::path + "/" + animeName + "/" + epname + ".mp4";

    std::cout << "where do you want to save episode: ";
    getline(std::cin, where);

    std::string wgetcom = "wget --proxy=off -Q0 --user-agent=Mozilla/4.0  --passive-ftp ";
    wgetcom += link;

    if (!where.empty())
    {
        wgetcom += " -O " + where;
    }
    else
    {
        std::cout << "saving to " + defaultpath;
        wgetcom += " -O " + defaultpath;
    }
    

    const char *cwgetcom = wgetcom.c_str();
    system(cwgetcom);
}