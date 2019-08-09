#include<string>
#include<vector>
#include<algorithm>
class Anime;
class FetchEpisodes
{
    private:
    public:
    static std::vector<Anime> VectorEpisode;
    static std::string FetchAnimeEp(int);
    static void DownloadAnime(std::string);
    static void PlayAnime(std::string);
};

static std::string Trim(std::string str)
{
    str.erase(str.begin(), find_if(str.begin(), str.end(), [](char p) { return !isspace(p); }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int p) { return !std::isspace(p); }).base(), str.end());
    return str;
}