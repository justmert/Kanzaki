#include<iostream>
#include"FetchAndParse.h"
#include"Manage.h"

int main()
{
    system("clear");
    std::cout << "Fetching Anime Names"<< std::endl;
    FetchAndParse start;
    std::string html = start.DownloadHtml();
    std::cout << "\nAnimes" << std::endl;
    start.SplitLinkAndName(start.ParseHtml(html));

    Manage::ManageProgram();
    return 0;
}