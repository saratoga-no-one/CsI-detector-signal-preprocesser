#ifndef NUCL_PHYS_UTILS_DATA_PROC_CONVOLUTION
#define NUCL_PHYS_UTILS_DATA_PROC_CONVOLUTION

#include <malloc.h>

namespace nucl_phys_utils{
	namespace data_proc{
		inline __attribute__((always_inline))  constexpr size_t convolution_1d_result_size(size_t data_size,size_t kernel_size,size_t stride=1)
		{
			return (data_size-kernel_size)/stride+1;
		}

		template<typename ConvData,typename ConvKernel>
		auto convolution_1d(ConvData* data,size_t data_size,ConvKernel* kernel,size_t kernel_size,size_t stride=1)->decltype(((*data)*(*kernel)))*
		{
			typedef decltype((*data)*(*kernel)) result_type;
			size_t len=convolution_1d_result_size(data_size,kernel_size,stride);
			result_type* conv_data=(result_type*)malloc(sizeof(result_type)*len);
			for(size_t pd=0;pd<len;++pd)
			{
				size_t d_offset=pd*stride;
				result_type result=0;
				for(size_t pk=0;pk<kernel_size;++pk)
					result+=*(kernel+pk)**(data+d_offset+kernel_size-pk-1);
				*(conv_data+pd)=result;
			}
			return conv_data;
		}

		template<typename ConvData,typename ConvKernel,typename ResultType>
		ResultType* convolution_1d(ConvData* data,size_t data_size,ConvKernel* kernel,size_t kernel_size,size_t stride=1)
		{
			size_t len=convolution_1d_result_size(data_size,kernel_size,stride);
			ResultType* conv_data=(ResultType*)malloc(sizeof(ResultType)*len);
			for(size_t pd=0;pd<len;++pd)
			{
				size_t d_offset=pd*stride;
				ResultType result=0;
				for(size_t pk=0;pk<kernel_size;++pk)
					result+=(ResultType)(*(kernel+pk)**(data+d_offset+kernel_size-pk-1));
				*(conv_data+pd)=result;
			}
			return conv_data;
		}

		double* convolution_kernel_1d_gaussian(size_t kernel_size,double standard_deviation=1,double expected_value=0,double range=3); //Distribution range: (¦Ì-range*¦Ò,¦Ì+range*¦Ò)
	}
}

#endif //NUCL_PHYS_UTILS_DATA_PROC_CONVOLUTION
