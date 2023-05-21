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
		bool happen = false;// �Ƿ����¼�
		float happenScore = 0;// �����¼��ķ���


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
		bool connect();     // ������ý�����
		bool reConnect();   // ������ý�����
		void closeConnect();// �ر���ý����������
		int mConnectCount = 0;

		AVFormatContext* mFmtCtx = nullptr;

		int writePkt(AVPacket* pkt);

		//��Ƶ֡
		AVCodecContext* mVideoCodecCtx = NULL;
		AVStream* mVideoStream = NULL;
		int mVideoIndex = -1;
		void pushVideoFrame(unsigned char* data, int size);

		//��Ƶ֡
		AVCodecContext* mAudioCodecCtx = NULL;
		AVStream* mAudioStream = NULL;
		int mAudioIndex = -1;
		void pushAudioFrame(unsigned char* data, int size);

	public:
		static void encodeVideoAndWriteStreamThread(void* arg); // ������Ƶ֡������
		static void encodeAudioAndWriteStreamThread(void* arg); // ������Ƶ֡������

	private:

		Control* mControl;

		//��Ƶ֡

		std::queue <VideoFrame*> mVideoFrameQ;
		std::mutex               mVideoFrameQ_mtx;
		bool getVideoFrame(VideoFrame*& frame, int& frameQSize);
		void clearVideoFrameQueue();

		//��Ƶ֡
		std::queue <AudioFrame*> mAudioFrameQ;
		std::mutex               mAudioFrameQ_mtx;
		bool getAudioFrame(AudioFrame*& frame, int& frameQSize);// ��ȡ��frame����ҪpushReusedAudioFrame
		void clearAudioFrameQueue();


		// ������
		std::mutex             mWritePkt_mtx;

		// bgr24תyuv420p
		unsigned char clipValue(unsigned char x, unsigned char min_val, unsigned char  max_val);
		bool bgr24ToYuv420p(unsigned char* bgrBuf, int w, int h, unsigned char* yuvBuf);
	};

}
#endif //BXC_AVPUSHSTREAM_H
