#ifndef MILESTONE2_CACHEMANAGER_H
#define MILESTONE2_CACHEMANAGER_H

#include <string>
#include <map>

using namespace std;


class CacheManager {
protected:
    map <string,string> data;
    mutable pthread_mutex_t mutex;

public:
    virtual int hasSolution(string problem) = 0;
    virtual void updateData(string problem, string solution) = 0;
    virtual void saveToDisk(string problem, string solution)= 0;
    virtual string getSolution(string problem) = 0;
    virtual ~CacheManager() = default;
};
#endif //MILESTONE2_CACHEMANAGER_H