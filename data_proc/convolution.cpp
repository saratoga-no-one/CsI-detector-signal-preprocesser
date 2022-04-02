#include <malloc.h>
#include <math.h>
#include "convolution.hpp"
#include <bphysik/experiment_utils/DataProcess.hpp>

using namespace bphysik::experiment_utils;

double* nucl_phys_utils::data_proc::convolution_kernel_1d_gaussian(size_t kernel_size,double standard_deviation,double expected_value,double range)
{
	double* kernel=(double*)malloc(sizeof(double)*kernel_size);
	if(kernel_size==1)
	{
		*kernel=1;
		return kernel;
	}else if(kernel_size==2)
	{
		*kernel=0.5;
		*(kernel+1)=0.5;
		return kernel;
	}
	double distrib_x=expected_value-range*standard_deviation;
	double stride=2*range*standard_deviation/(kernel_size-1);
	double C1=-2*standard_deviation*standard_deviation;
	double C2=sqrt(2*M_PI)*standard_deviation;
	for(size_t i=0;i<kernel_size;++i,distrib_x+=stride)
		*(kernel+i)=exp((distrib_x-expected_value)*(distrib_x-expected_value)/C1)/C2;
	double weight_sum=calc_sum(kernel,kernel_size);
	for(size_t i=0;i<kernel_size;++i)
		*(kernel+i)/=weight_sum;
	return kernel;
}
