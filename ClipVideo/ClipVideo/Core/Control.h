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
		// ͨ�������õĲ���
		int64_t executorStartTimestamp = 0;// ִ��������ʱ���뼶ʱ�����13λ��
		float   checkFps = 0;// �㷨����֡�ʣ�ÿ����Ĵ�����
		int     videoWidth = 0;  // ������Ƶ�������ؿ�
		int     videoHeight = 0; // ������Ƶ�������ظ�
		int     videoChannel = 0;
		int     videoIndex = -1;
		int     videoFps = 0;
		int     audioIndex = -1;
		int     audioFps = 0;
	};
}
#endif //BXC_CONTROL_H
