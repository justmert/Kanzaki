#include "FetchAndParse.h"
#include <iostream>
#include <string>
#include <vector>
#include "Anime.h"
#include <algorithm>
#include <curl/curl.h>
std::vector<Anime> FetchAndParse::vector;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string FetchAndParse::DownloadHtml(std::string url)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    // std::cout << url << std::endl;

    curl = curl_easy_init();
    if (curl)
    {
        const char* cstr = url.c_str();
        curl_easy_setopt(curl, CURLOPT_URL, cstr);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return readBuffer;
    }
}

std::vector<std::string> FetchAndParse::ParseHtml(std::string &html)
{
    bool first = true;
    std::vector<std::string> vec;
    size_t found = 0;
    while (true)
    {
        int i = 0;
        std::string substr;
        found = html.find("<a href=\"",found+1);
        if (found==std::string::npos)
            break;
        while (html[found+i+9]!='<')
        {
            substr += html[found+i+9];
            i++;
        }
        if (!first)
        { //don't take first item
            vec.push_back(substr);
        }
        first = false;
    }
    return vec;
}

void FetchAndParse::SplitLinkAndName(const std::vector<std::string> & tempvec, std::vector<Anime> & vector)
{
    int i = 1 ;
    for (auto &&item : tempvec)
    {
        auto it = std::find(item.begin(),item.end(),'>');
        std::string link = std::string(item.begin(),it-1);
        std::string name = std::string(it+1,item.end()-1);

        auto iter = std::find(name.begin(),name.end(),'_');
        while (iter!=name.end())
        {
            name[iter-name.begin()] = ' ';
            iter = std::find(name.begin(),name.end(),'_');
        }
        std::cout <<" " << i << "・"<< name << std::endl;
        Anime piece;
        piece.link = link;
        piece.name = name;
        piece.number = i;
        vector.push_back(piece);
        i++;
    }
}