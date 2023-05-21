#ifndef BXC_AVPUSHSTREAM_H
#define BXC_AVPUSHSTREAM_H
#include <queue>
#include <mutex>
extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
}
namespace BXC {
	struct Control;
	struct VideoFrame
	{
	public:
		enum VideoFrameType
		{
			BGR = 0,
			YUV420P,

		};
		VideoFrame(VideoFrameType type, int size, int width, int height) {
			this->type = type;
			this->size = size;
			this->width = width;
			this->height = height;
			this->data = new uint8_t[this->size];

		}
		~VideoFrame() {
			delete[] this->data;
			this->data = nullptr;
		}

		VideoFrameType type;
		int size;
		int width;
		int height;
		uint8_t* data;
		bool happen = false;// 是否发生事件
		float happenScore = 0;// 发生事件的分数


	};

	struct AudioFrame
	{
	public:
		AudioFrame(int size) {
			this->size = size;
			this->data = new uint8_t[this->size];
		}
		~AudioFrame() {
			delete[] this->data;
			this->data = NULL;
		}

		int size;
		uint8_t* data;
	};


	class AvPushStream
	{
	public:
		AvPushStream(Control* control);
		~AvPushStream();
	public:
		bool connect();     // 连接流媒体服务
		bool reConnect();   // 重连流媒体服务
		void closeConnect();// 关闭流媒体服务的连接
		int mConnectCount = 0;

		AVFormatContext* mFmtCtx = nullptr;

		int writePkt(AVPacket* pkt);

		//视频帧
		AVCodecContext* mVideoCodecCtx = NULL;
		AVStream* mVideoStream = NULL;
		int mVideoIndex = -1;
		void pushVideoFrame(unsigned char* data, int size);

		//音频帧
		AVCodecContext* mAudioCodecCtx = NULL;
		AVStream* mAudioStream = NULL;
		int mAudioIndex = -1;
		void pushAudioFrame(unsigned char* data, int size);

	public:
		static void encodeVideoAndWriteStreamThread(void* arg); // 编码视频帧并推流
		static void encodeAudioAndWriteStreamThread(void* arg); // 编码音频帧并推流

	private:

		Control* mControl;

		//视频帧

		std::queue <VideoFrame*> mVideoFrameQ;
		std::mutex               mVideoFrameQ_mtx;
		bool getVideoFrame(VideoFrame*& frame, int& frameQSize);
		void clearVideoFrameQueue();

		//音频帧
		std::queue <AudioFrame*> mAudioFrameQ;
		std::mutex               mAudioFrameQ_mtx;
		bool getAudioFrame(AudioFrame*& frame, int& frameQSize);// 获取的frame，需要pushReusedAudioFrame
		void clearAudioFrameQueue();


		// 推流锁
		std::mutex             mWritePkt_mtx;

		// bgr24转yuv420p
		unsigned char clipValue(unsigned char x, unsigned char min_val, unsigned char  max_val);
		bool bgr24ToYuv420p(unsigned char* bgrBuf, int w, int h, unsigned char* yuvBuf);
	};

}
#endif //BXC_AVPUSHSTREAM_H
