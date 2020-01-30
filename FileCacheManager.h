#ifndef MILESTONE2_FILECACHEMANAGER_H
#define MILESTONE2_FILECACHEMANAGER_H


#include "CacheManager.h"
#include <vector>

class FileCacheManager : public CacheManager {
public:
    FileCacheManager();
    int hasSolution(string problem) override;
    void updateData(string problem, string solution) override;
    void saveToDisk(string problem, string solution) override;
    void loadDataMap();
    string getSolution(string problem) override;

};


#endif //MILESTONE2_FILECACHEMANAGER_H