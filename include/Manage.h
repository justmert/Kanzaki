// #include<pair>
#include<string>
class Anime;
class Manage
{
  private:
  public:
    static void ManageProgram();
    static void PrintHelpFirst();
    static void PrintHelpSecond();
    static void ListFoundAnimes(std::string);
    static void ListAllAnimes();
    static void ListAllEpisodes(int number);
    static bool SelectAnime(Anime);
    static std::pair<std::string,std::string> ParseInput(std::string);
};

