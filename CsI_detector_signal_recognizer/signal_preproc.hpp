#ifndef NUCL_PHYS_UTILS_CSI_DETECTOR_SIGNAL_RECOGNIZER_SIGNAL_PREPROC
#define NUCL_PHYS_UTILS_CSI_DETECTOR_SIGNAL_RECOGNIZER_SIGNAL_PREPROC

#include <cstddef>
#include "../data_proc/convolution.hpp"
#include "../data_proc/signal_proc.hpp"

#define SINGLE_EVENT_POINT_NUM 20000
#define PREPROC_KERNEL_SIZE 96
#define PREPROC_KERNEL_SIZE_2 6
#define PREPROC_KERNEL_STRIDE ((PREPROC_KERNEL_SIZE)/3)
#define PREPROC_KERNEL_STRIDE_2 ((PREPROC_KERNEL_SIZE_2)/3)

namespace nucl_phys_utils{
	namespace csi_detector_signal_recognizer{
		extern double* preproc_kernel;
		extern double* preproc_kernel_2;
		template<typename T>//Use default kernel 1.
		auto down_sampling(T* data,size_t single_event_point_num=SINGLE_EVENT_POINT_NUM)->decltype(nucl_phys_utils::data_proc::convolution_1d(data,single_event_point_num,preproc_kernel,PREPROC_KERNEL_SIZE,PREPROC_KERNEL_STRIDE))
		{
			return nucl_phys_utils::data_proc::convolution_1d(data,single_event_point_num,preproc_kernel,PREPROC_KERNEL_SIZE,PREPROC_KERNEL_STRIDE);
		}
		constexpr size_t down_sampled_size(size_t data_size=SINGLE_EVENT_POINT_NUM,size_t kernel_size=PREPROC_KERNEL_SIZE,size_t stride=PREPROC_KERNEL_STRIDE)
		{
			return nucl_phys_utils::data_proc::convolution_1d_result_size(data_size,kernel_size,stride);
		}
		template<typename T>//Use default kernels.
		auto preprocess_original_signal(T* data,size_t single_event_point_num=SINGLE_EVENT_POINT_NUM)->decltype(nucl_phys_utils::data_proc::convolution_1d(data,single_event_point_num,preproc_kernel,PREPROC_KERNEL_SIZE,PREPROC_KERNEL_STRIDE))
		{
			auto gauss_1=down_sampling(data,single_event_point_num);
			auto diff=nucl_phys_utils::data_proc::difference(gauss_1,down_sampled_size(single_event_point_num));
			auto gauss_2=nucl_phys_utils::data_proc::convolution_1d(diff,down_sampled_size(single_event_point_num)-1,preproc_kernel_2,PREPROC_KERNEL_SIZE_2,PREPROC_KERNEL_STRIDE_2);
			free(diff);
			free(gauss_1);
			return gauss_2;
		}
		constexpr size_t preprocessed_size(size_t data_size=SINGLE_EVENT_POINT_NUM,size_t kernel_size=PREPROC_KERNEL_SIZE,size_t stride=PREPROC_KERNEL_STRIDE)
		{
			return down_sampled_size(down_sampled_size(data_size)-1,PREPROC_KERNEL_SIZE_2,PREPROC_KERNEL_STRIDE_2);
		}

		void CsI_detector_signal_extract_classify_preprocess_all_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num=SINGLE_EVENT_POINT_NUM);
		void CsI_detector_signal_extract_classify_preprocess_all_text_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num=SINGLE_EVENT_POINT_NUM,char coord_separate_ch=9,char point_end_ch=10);
		void CsI_detector_signal_extract_preprocess_all_from_bin(const char* bin_path,const char* dest_folder_path,size_t single_event_point_num=SINGLE_EVENT_POINT_NUM);

	}
}

#endif//NUCL_PHYS_UTILS_CSI_DETECTOR_SIGNAL_RECOGNIZER_SIGNAL_PREPROC
