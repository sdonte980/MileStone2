#ifndef MILESTONE2_SPLIT_H
#define MILESTONE2_SPLIT_H

#include <string>
#include <vector>


using namespace std;
class Split{
public:
    static vector<string> split(string line, string delimiter) {
        vector<string> data;
        size_t position = 0;
        while ((position = line.find(delimiter)) != string::npos) {
            if (!line.substr(0, position).empty()) {
                data.push_back(line.substr(0, position));
            }
            line.erase(0, position + delimiter.length());
        }
        data.push_back(line.substr(0, position));
        return data;

    }
};

#endif //MILESTONE2_SPLIT_H
