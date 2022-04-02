#include "data_proc/data_splitting.hpp"
#include "CsI_detector_signal_recognizer/signal_preproc.hpp"
#include "data_proc/convolution.hpp"
#include "data_proc/signal_proc.hpp"
#include <iostream>

using namespace nucl_phys_utils::data_proc;
using namespace nucl_phys_utils::csi_detector_signal_recognizer;

int main(int argc,char** argv)
{
	if(argc==4)
		CsI_detector_signal_extract_classify_preprocess_all_from_bin(*(argv+1),*(argv+3),*(argv+2));
	else if(argc==3)
		CsI_detector_signal_extract_preprocess_all_from_bin(*(argv+1),*(argv+2));
	std::cout<<"Process complete."<<std::endl;
}

