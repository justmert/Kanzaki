#include<string>
#include<vector>
#include<map>
class Anime;
class FetchAndParse
{
    private:
    public:
    static void SplitLinkAndName(const std::vector<std::string> &,
                    std::vector<Anime> & vector = FetchAndParse::vector);
    static std::vector<std::string> ParseHtml(std::string &html);
    static std::vector<Anime> vector;
    static std::string DownloadHtml(std::string url = "https://storage.kanzaki.ru/ANIME___/");
};