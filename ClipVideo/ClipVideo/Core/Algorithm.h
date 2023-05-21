#ifndef BXC_ALGORITHM_H
#define BXC_ALGORITHM_H

#include <string>
#include <vector>

namespace BXC {

    struct AlgorithmDetectObject
    {
        int x1;
        int y1;
        int x2;
        int y2;
        float score;
        std::string class_name;
    };


    class Algorithm
    {
    public:
        Algorithm();
        virtual ~Algorithm();
    public:
        virtual bool objectDetect(int height, int width, unsigned char* bgr, std::vector<AlgorithmDetectObject>& detects) = 0;
    protected:
        bool parseObjectDetect(std::string& response, std::vector<AlgorithmDetectObject>& detects);

    };

}

#endif //BXC_ALGORITHM_H