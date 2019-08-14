#include <string>
#include <experimental/filesystem>
#include <unistd.h>
#include <iostream>
#include <limits.h>
class Anime;
class Manage
{
private:
public:
  static void ManageProgram();
  static std::string path;
  static std::string hname;
  static void PrintHelpFirst();
  static void PrintHelpSecond();
  static void ListFoundAnimes(std::string);
  static void ListAllAnimes();
  static void ListAllEpisodes(int number);
  static bool SelectAnime(Anime);
  static std::pair<std::string, std::string> ParseInput(std::string);
  Manage()
  {
    char hostname[HOST_NAME_MAX];
    getlogin_r(hostname,HOST_NAME_MAX);
    hname = hostname;
    
    path = "/home/" + std::string(hostname)+"/Animes";
    if (!std::experimental::filesystem::exists(path))
    {
      std::cout << "Creating Animes directory in your home" << std::endl;
      std::experimental::filesystem::create_directory(path);
    }
    
  }
};
