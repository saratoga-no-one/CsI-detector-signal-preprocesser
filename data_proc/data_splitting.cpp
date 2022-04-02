#include <malloc.h>
#include <direct.h>
#include <AMEIZ-3-1706/anm2dr/util/CStringUtils.hpp>
#include <AMEIZ-3-1706/anm2dr/util/Utils.hpp>
#include <AMEIZ-3-1706/engine/io/ValueUtils.hpp>
#include <AMEIZ-3-1706/engine/io/IOUtils.hpp>
#include "data_splitting.hpp"

using namespace anm2dr::util;
using namespace engine::io;

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_text_from_bin(const char* bin_path,const char* text_path,size_t extract_idx,size_t single_event_sampling_point_num,char coord_separate_ch,char point_end_ch)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_sampling_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(len*extract_idx,std::ios::beg);
	bin_file.read(bin,len);
	bin_file.close();
	unsigned short* data=(unsigned short*)bin;
	write_bin_to_text_file(text_path,data,single_event_sampling_point_num,coord_separate_ch,point_end_ch);
	free(bin);
}

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_all_text_from_bin(const char* bin_path,const char* text_folder_path,size_t single_event_sampling_point_num,char coord_separate_ch,char point_end_ch)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_sampling_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(0,std::ios::end);
	size_t event_num=bin_file.tellg();
	bin_file.seekg(0,std::ios::beg);
	event_num/=len;
	const char* bin_name=getFileName(bin_path);
	const char* output_path=str_join(text_folder_path,'/',bin_name);
	if(!isExist(output_path))
		mkdir(output_path);
	for(size_t e=0;e<event_num;++e)
	{
		bin_file.seekg(len*e,std::ios::beg);
		bin_file.read(bin,len);
		unsigned short* data=(unsigned short*)bin;
		const char* text_path=str_join(output_path,'/',"event_",e,".dat");
		write_bin_to_text_file(text_path,data,single_event_sampling_point_num,coord_separate_ch,point_end_ch);
		free((void*)text_path);
	}
	bin_file.close();
	free((void*)output_path);
	free((void*)bin_name);
	free(bin);
}

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_from_bin(const char* bin_path,const char* dest_path,size_t extract_idx,size_t single_event_sampling_point_num)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_sampling_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(len*extract_idx,std::ios::beg);
	bin_file.read(bin,len);
	bin_file.close();
	writeBytesToFile(dest_path,bin,len);
	free(bin);
}

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_all_from_bin(const char* bin_path,const char* dest_folder_path,size_t single_event_sampling_point_num)
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
		writeBytesToFile(dest_path,bin,len);
		free((void*)dest_path);
	}
	bin_file.close();
	free((void*)output_path);
	free((void*)bin_name);
	free(bin);
}

unsigned short* nucl_phys_utils::data_proc::CsI_detector_signal_extract_from_bin(const char* bin_path,size_t extract_idx,size_t single_event_sampling_point_num)
{
	std::ifstream bin_file(bin_path,std::ios::in|std::ios::binary);
	register size_t len=2*single_event_sampling_point_num;
	char* bin=(char*)malloc(len);
	bin_file.seekg(len*extract_idx,std::ios::beg);
	bin_file.read(bin,len);
	bin_file.close();
	return (unsigned short*)bin;
}

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_classify_all_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num)
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
		writeBytesToFile(dest_path,bin,len);
		free((void*)dest_path);
	}
	delete &infos;
	bin_file.close();
	free((void*)bin_name);
	free(bin);
}

void nucl_phys_utils::data_proc::CsI_detector_signal_extract_classify_all_text_from_bin(const char* bin_path,const char* info_file,const char* dest_folder_path,size_t single_event_point_num,char coord_separate_ch,char point_end_ch)
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
		const char* dest_path=str_join(output_path,"/event_",e,".dat");
		free((void*)output_path);
		unsigned short* data=(unsigned short*)bin;
		write_bin_to_text_file(dest_path,data,single_event_point_num,coord_separate_ch,point_end_ch);
		free((void*)dest_path);
	}
	delete &infos;
	bin_file.close();
	free((void*)bin_name);
	free(bin);
}

anm2dr::util::ArrayList<const char*>& nucl_phys_utils::data_proc::load_event_info(const char* info_file)
{
	size_t str_len;
	char* info_text=(char*)readBytesFromFile(info_file,&str_len);
	ArrayList<KeyValuePairStr> &key_value_pairs=parseKeyValuePairStr(info_text,str_len,'#',' ');
	register int num=key_value_pairs.getLastIndex()+1;
	anm2dr::util::ArrayList<const char*>* infos=new anm2dr::util::ArrayList<const char*>(num);
	for(int i=0;i<num;++i)
	{
		KeyValuePairStr pair=key_value_pairs.get(i);
		if(str_eq("alpha",pair.value))
			infos->at(parseInt(pair.key))="alpha";
		else if(str_eq("gamma",pair.value))
			infos->at(parseInt(pair.key))="gamma";
		else
			infos->at(parseInt(pair.key))="else";
	}
	free(info_text);
	delete &key_value_pairs;
	return *infos;
}
