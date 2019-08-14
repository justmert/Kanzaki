#include<iostream>
#include"FetchAndParse.h"
#include"Manage.h"

int main()
{
    std::cout << "This program designed for linux\nIn order to use you must install vlc an wget. Thanks";
    std::string a;
    getline(std::cin,a);
    system("clear");
    std::cout << "Fetching Anime Names"<< std::endl;
    FetchAndParse start;
    std::string html = start.DownloadHtml();
    std::cout << "\nAnimes" << std::endl;
    start.SplitLinkAndName(start.ParseHtml(html));

    Manage program;
    program.ManageProgram();
    return 0;
}