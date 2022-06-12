#include "NetworkManager.h"

#include <string>
#include <iostream>

size_t download_to_string(char* ptr, size_t size, size_t nmemb, void* userdata)
{
    size_t realsize = size * nmemb;
    std::string* str = (std::string*)userdata;
    (*str).append(ptr, realsize);
    return realsize;
}

size_t download_to_file(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}


NetworkManager::NetworkManager(){

}
NetworkManager::~NetworkManager(){
    curl_easy_cleanup(_curl);
    curl_global_cleanup();
}
int NetworkManager::Init(){
    curl_global_init(CURL_GLOBAL_DEFAULT);

    _curl = curl_easy_init();
    if(!_curl){
        std::cout << "Something went wrong with CURL initialization"<<std::endl;
        return 1;
    }

    curl_easy_setopt(_curl, CURLOPT_CAINFO, ".\\cacert.pem");
    curl_easy_setopt(_curl, CURLOPT_CAPATH, ".\\cacert.pem");
    return 0;
}

void NetworkManager::DownloadToFile(std::string URL, std::string pathToFile){
    CURLcode res;

    FILE* fp = fopen(pathToFile.c_str(), "wb");
    curl_easy_setopt(_curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, download_to_file);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, fp);
    res = curl_easy_perform(_curl);
    fclose(fp);
    if (res != CURLE_OK)
        throw new std::exception(curl_easy_strerror(res));
}
std::string NetworkManager::DownloadToString(std::string URL){
    std::string buffer;
    CURLcode res;
    
    curl_easy_setopt(_curl, CURLOPT_URL, URL.c_str());

    curl_easy_setopt(_curl, CURLOPT_SSL_VERIFYSTATUS, 1);
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, download_to_string);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(_curl);

    if(res!=CURLE_OK)
    {
        std::cout << "error en curl" <<std::endl;
        std::cout << curl_easy_strerror(res) <<std::endl;
        throw new std::exception();
    }
    return buffer;
}

