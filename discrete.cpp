
#include <algorithm>
#include <ctime>
#include "discrete.h"


boost::mt19937 DiscreteVariate::rng(time( NULL ));
boost::uniform_01<> DiscreteVariate::N;

DiscreteVariate::DiscreteVariate(std::vector<double> const &pmf) : 
	sampler(rng,N) 
{ 
	std::vector<double>::const_iterator it;
	sum = 0.0;
	for (it = pmf.begin(); it != pmf.end(); it++) 
	{
		sum += *it;
		cdf.push_back(sum);
	}
}

std::size_t DiscreteVariate::operator()() 
{
	std::vector<double>::iterator lb = 
		std::lower_bound(cdf.begin(), cdf.end(), sampler() * sum);

	return lb - cdf.begin();
}
