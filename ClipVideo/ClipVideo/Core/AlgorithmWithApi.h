#ifndef BXC_ALGORITHMWITHAPI_H
#define BXC_ALGORITHMWITHAPI_H

#include "Algorithm.h"
#include <vector>

namespace BXC {

    struct AlgorithmDetectObject;

    class AlgorithmWithApi : public Algorithm
    {
    public:
        AlgorithmWithApi(std::string& host);
        virtual ~AlgorithmWithApi();
    public:
        bool test();
        virtual bool objectDetect(int height, int width, unsigned char* bgr, std::vector<AlgorithmDetectObject>& detects);
    private:
        std::string mHost;
    };
}
#endif //BXC_ALGORITHMWITHAPI_H