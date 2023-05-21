#ifndef BXC_CONTROLEXECUTOR_H
#define BXC_CONTROLEXECUTOR_H
#include <thread>
#include <queue>
#include <mutex>
namespace BXC {

	class AvPullStream;
	class AvPushStream;
	class Analyzer;
	struct Control;

	class ControlExecutor
	{
	public:
		explicit ControlExecutor(Control* control);
		~ControlExecutor();
	public:
		static void decodeAndAnalyzeVideoThread(void* arg);// 解码视频帧和实时分析视频帧
		static void decodeAndAnalyzeAudioThread(void* arg);// 解码音频帧和实时分析音频帧

	public:
		bool start();

		bool getState();
		void setState_remove();
	public:
		Control* mControl;
		AvPullStream* mPullStream;
		AvPushStream* mPushStream;
		Analyzer* mAnalyzer;

	private:
		bool mState = false;
		std::vector<std::thread*> mThreads;

	};
}
#endif //BXC_CONTROLEXECUTOR_H