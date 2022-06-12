#include <string>
#include <curl/curl.h>



//Simple class that handles all online stuff, downloading files
class NetworkManager{
public:
    NetworkManager();
    virtual ~NetworkManager();
    int Init();

    void DownloadToFile(std::string URL, std::string pathToFile);
    void DownloadToString(std::string URL, std::string buffer);
    
    //returns true if v1 >= v2
    bool CompareVersions(string v1, string v2);
private:
    CURL* _curl;
}