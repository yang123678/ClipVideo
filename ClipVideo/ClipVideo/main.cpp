#include "Core/Control.h"
#include "Core/ControlExecutor.h"

using namespace BXC;
int main(int argc, char* argv[]) {

    Control control;

    control.streamUrl = "../data/≤‚ ‘2.mp4";
    control.pushStreamUrl = "../data/≤‚ ‘2_4.mp4";


    control.supportHardwareVideoDecode = false;
    control.algorithmApiHost = "http://127.0.0.1:9003";

    ControlExecutor controlExecutor(&control);
    controlExecutor.start();

    return 0;
}