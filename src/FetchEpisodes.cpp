#include "FetchEpisodes.h"
#include "FetchAndParse.h"
#include "Anime.h"
#include <iostream>
#include <map>
#include <algorithm>
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
    std::string playonvlc = "vlc " + link;
    const char * cplayonvlc = playonvlc.c_str();
    system(cplayonvlc);
}

void FetchEpisodes::DownloadAnime(std::string link)
{
    std::cout << "where to save? ";
    std::string save;
    getline(std::cin,save);
    save = Trim(save);
    std::string wgetcom = "wget --proxy=off -Q0 --user-agent=Mozilla/4.0  --passive-ftp ";
    if (!save.empty())
    {
        wgetcom += wgetcom + "-O "+ save + " " + link;
    }
    
    const char *cwgetcom = wgetcom.c_str();
    system(cwgetcom);
}
