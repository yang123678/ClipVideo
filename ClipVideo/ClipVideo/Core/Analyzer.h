#ifndef BXC_ANALYZER_H
#define BXC_ANALYZER_H

#include <string>
#include <vector>
namespace BXC {

	struct Control;
	struct AlgorithmDetectObject;
	class Algorithm;

	class Analyzer
	{
	public:
		explicit Analyzer(Control* control);
		~Analyzer();
	public:
		bool checkVideoFrame(bool check, int64_t frameCount, unsigned char* data, float& happenScore);
		bool checkAudioFrame(bool check, int64_t frameCount, unsigned char* data, int size);


	private:
		Control* mControl;
		Algorithm* mAlgorithm;

		std::vector<AlgorithmDetectObject> mDetects;


	};
}
#endif //BXC_ANALYZER_H

