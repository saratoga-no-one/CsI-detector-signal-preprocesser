#include "signal_preproc.hpp"
#include "../data_proc/convolution.hpp"
#include "../data_proc/data_splitting.hpp"
#include <AMEIZ-3-1706/anm2dr/util/CStringUtils.hpp>
#include <AMEIZ-3-1706/anm2dr/util/Utils.hpp>
#include <AMEIZ-3-1706/engine/io/ValueUtils.hpp>
#include <AMEIZ-3-1706/engine/io/IOUtils.hpp>

using namespace anm2dr::util;
using namespace engine::io;

using namespace nucl_phys_utils::data_proc;

namespace nucl_phys_utils{
	namespace csi_detector_signal_recognizer{
		double* preproc_kernel=convolution_kernel_1d_gaussian(PREPROC_KERNEL_SIZE);//stride=kernel_size/3
		double* preproc_kernel_2=convolution_kernel_1d_gaussian(PREPROC_KERNEL_SIZE_2);
	}
}

void nucl_phys_utils::csi_detector_signal_recognizer::CsI_detector_signal_extract_classify_preprocess_all_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(0,std::ios::end);
	size_t event_num=bin_file.tellg();
	bin_file.seekg(0,std::ios::beg);
	event_num/=len;
	const char* bin_name=getFileName(bin_path);
	anm2dr::util::ArrayList<const char*>& infos=load_event_info(info_file);
	for(size_t e=0;e<event_num;++e)
	{
		bin_file.seekg(len*e,std::ios::beg);
		bin_file.read(bin,len);
		unsigned short* data=(unsigned short*)bin;
		auto preproc_data=preprocess_original_signal(data,single_event_point_num);
		const char* output_path=str_join(dest_folder_path,'/',bin_name,'/',infos.at(e));
		if(!isExist(output_path))
			mkdir(output_path);
		const char* dest_path=str_join(output_path,"/event_",e,".bin");
		free((void*)output_path);
		writeBytesToFile(dest_path,preproc_data,sizeof(decltype(*preproc_data))*preprocessed_size(single_event_point_num));
		free(preproc_data);
		free((void*)dest_path);
	}
	delete &infos;
	bin_file.close();
	free((void*)bin_name);
	free(bin);
}

void nucl_phys_utils::csi_detector_signal_recognizer::CsI_detector_signal_extract_classify_preprocess_all_text_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num,char coord_separate_ch,char point_end_ch)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(0,std::ios::end);
	size_t event_num=bin_file.tellg();
	bin_file.seekg(0,std::ios::beg);
	event_num/=len;
	const char* bin_name=getFileName(bin_path);
	anm2dr::util::ArrayList<const char*>& infos=load_event_info(info_file);
	for(size_t e=0;e<event_num;++e)
	{
		bin_file.seekg(len*e,std::ios::beg);
		bin_file.read(bin,len);
		const char* output_path=str_join(dest_folder_path,'/',bin_name,'/',infos.at(e));
		if(!isExist(output_path))
			mkdir(output_path);
		const char* dest_path=str_join(output_path,"/event_",e,".bin");
		free((void*)output_path);
		unsigned short* data=(unsigned short*)bin;
		auto preproc_data=preprocess_original_signal(data,single_event_point_num);
		write_bin_to_text_file(dest_path,preproc_data,preprocessed_size(single_event_point_num),coord_separate_ch,point_end_ch);
		free(preproc_data);
		free((void*)dest_path);
	}
	delete &infos;
	bin_file.close();
	free((void*)bin_name);
	free(bin);
}

void nucl_phys_utils::csi_detector_signal_recognizer::CsI_detector_signal_extract_preprocess_all_from_bin(const char* bin_path,const char* dest_folder_path,size_t single_event_sampling_point_num)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_sampling_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(0,std::ios::end);
	size_t event_num=bin_file.tellg();
	bin_file.seekg(0,std::ios::beg);
	event_num/=len;
	const char* bin_name=getFileName(bin_path);
	const char* output_path=str_join(dest_folder_path,'/',bin_name);
	if(!isExist(output_path))
		mkdir(output_path);
	for(size_t e=0;e<event_num;++e)
	{
		bin_file.seekg(len*e,std::ios::beg);
		bin_file.read(bin,len);
		const char* dest_path=str_join(output_path,'/',"event_",e,".bin");
		unsigned short* data=(unsigned short*)bin;
		auto preproc_data=preprocess_original_signal(data,single_event_sampling_point_num);
		writeBytesToFile(dest_path,preproc_data,sizeof(decltype(*preproc_data))*preprocessed_size(single_event_sampling_point_num));
		free(preproc_data);
		free((void*)dest_path);
	}
	bin_file.close();
	free((void*)output_path);
	free((void*)bin_name);
	free(bin);
}
