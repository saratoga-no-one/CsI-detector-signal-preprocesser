#ifndef NUCL_PHYS_UTILS_DATA_PROC_DATA_SPLITTING
#define NUCL_PHYS_UTILS_DATA_PROC_DATA_SPLITTING

#include <cstddef>
#include <fstream>
#include <AMEIZ-3-1706/engine/io/KeyValueParser.hpp>

#define CSI_DETECTOR_SINGLE_EVENT_POINT_NUM 20000

namespace nucl_phys_utils{
	namespace data_proc{
		//bin means a very large file that collects all the events of CsI detector.extract_idx is 0-max.
		void CsI_detector_signal_extract_text_from_bin(const char* bin_path,const char* text_path,size_t extract_idx,size_t single_event_sampling_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM,char coord_separate_ch=9,char point_end_ch=10);
		void CsI_detector_signal_extract_all_text_from_bin(const char* bin_path,const char* text_folder_path,size_t single_event_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM,char coord_separate_ch=9,char point_end_ch=10);
		void CsI_detector_signal_extract_from_bin(const char* bin_path,const char* dest_path,size_t extract_idx,size_t single_event_sampling_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM);
		void CsI_detector_signal_extract_all_from_bin(const char* bin_path,const char* dest_folder_path,size_t single_event_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM);
		unsigned short* CsI_detector_signal_extract_from_bin(const char* bin_path,size_t extract_idx,size_t single_event_sampling_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM);
		void CsI_detector_signal_extract_classify_all_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM);
		void CsI_detector_signal_extract_classify_all_text_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num=CSI_DETECTOR_SINGLE_EVENT_POINT_NUM,char coord_separate_ch=9,char point_end_ch=10);
		anm2dr::util::ArrayList<const char*>& load_event_info(const char* info_file);

		template<typename T>
		void write_bin_to_text_file(const char* text_path,T* bin,size_t size,char coord_separate_ch=9,char point_end_ch=10)
		{
			std::ofstream file(text_path,std::ios::out|std::ios::binary);
			for(size_t i=0;i<size;++i,++bin)
				file<<i<<coord_separate_ch<<(*bin)<<point_end_ch;
			file.close();
		}
	}
}

#endif//NUCL_PHYS_UTILS_DATA_PROC_DATA_SPLITTING
