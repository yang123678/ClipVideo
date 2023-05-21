#include "Analyzer.h"
#include <opencv2/opencv.hpp>
#include "Utils/Log.h"
#include "Utils/Common.h"
#include "Control.h"
#include "AlgorithmWithApi.h"

namespace BXC {
    Analyzer::Analyzer(Control* control) :
        mControl(control)
    {
        mAlgorithm = new AlgorithmWithApi(control->algorithmApiHost);
    }

    Analyzer::~Analyzer()
    {
        mDetects.clear();
        if (mAlgorithm) {
            delete mAlgorithm;
            mAlgorithm = nullptr;
        }

    }

    bool Analyzer::checkVideoFrame(bool check, int64_t frameCount, unsigned char* data, float& happenScore) {
        bool happen = false;

        cv::Mat image(mControl->videoHeight, mControl->videoWidth, CV_8UC3, data);
        //cv::Mat image = cv::imread("D:\\file\\data\\images\\1.jpg");
        //cv::imshow("image", image);
        //cv::waitKey(0);
        //cv::destroyAllWindows();

        //int target_width = 300;
        //int target_height = 200;
        //int target_left = (mWidth - target_width) / 2;
        //int target_top = (mHeight - target_height) / 2;

        //cv::rectangle(image,cv::Rect(target_left,target_top,target_width,target_height),
        //              cv::Scalar(0,255,0),3
        //        ,cv::LINE_8,0);

        if (check) {
            mDetects.clear();
            mAlgorithm->objectDetect(mControl->videoHeight, mControl->videoWidth, data, mDetects);

        }
        int x1, y1, x2, y2;
        for (int i = 0; i < mDetects.size(); i++)
        {
            x1 = mDetects[i].x1;
            y1 = mDetects[i].y1;
            x2 = mDetects[i].x2;
            y2 = mDetects[i].y2;
            if (x1 >= 0 and y1 >= 0 and x2 <= mControl->videoWidth and y2 <= mControl->videoHeight) {
                cv::rectangle(image, cv::Rect(x1, y1, (x2 - x1), (y2 - y1)), cv::Scalar(0, 255, 0), 2, cv::LINE_8, 0);

                std::string class_name = mDetects[i].class_name + "-" + std::to_string(mDetects[i].score);
                cv::putText(image, class_name, cv::Point(x1, y1 + 15), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);

                // ÈËÁ³Ìî³äÑÕÉ« start
                cv::Mat roi((y2 - y1), (x2 - x1), CV_8UC3, cv::Scalar(0, 255, 0));
                cv::Mat imageROI = image(cv::Range(y1, y2), cv::Range(x1, x2));
                roi.copyTo(imageROI);
                // ÈËÁ³Ìî³äÑÕÉ« end
            }

        }


        std::string info = "checkFps:" + std::to_string(mControl->checkFps);
        cv::putText(image, info, cv::Point(20, 40), cv::FONT_HERSHEY_COMPLEX, mControl->videoWidth / 1000, cv::Scalar(0, 0, 255), 1, cv::LINE_AA);


        return happen;

    }
    bool Analyzer::checkAudioFrame(bool check, int64_t frameCount, unsigned char* data, int size) {

        return false;
    }

}