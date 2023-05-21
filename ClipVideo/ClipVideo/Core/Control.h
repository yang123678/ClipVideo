#ifndef BXC_CONTROL_H
#define BXC_CONTROL_H

#include <string>

namespace BXC {
	struct Control
	{
	public:
		std::string streamUrl;
		std::string pushStreamUrl;
		bool supportHardwareVideoDecode;
		std::string algorithmApiHost;

	public:
		// 通过计算获得的参数
		int64_t executorStartTimestamp = 0;// 执行器启动时毫秒级时间戳（13位）
		float   checkFps = 0;// 算法检测的帧率（每秒检测的次数）
		int     videoWidth = 0;  // 布控视频流的像素宽
		int     videoHeight = 0; // 布控视频流的像素高
		int     videoChannel = 0;
		int     videoIndex = -1;
		int     videoFps = 0;
		int     audioIndex = -1;
		int     audioFps = 0;
	};
}
#endif //BXC_CONTROL_H
