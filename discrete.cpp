
#include <algorithm>
#include <ctime>
#include "discrete.h"


/*
 * Initialize the random number generator
 */
boost::mt19937 DiscreteVariate::rng(time( NULL ));
/*
 * Initialize the uniform variate
 */
boost::uniform_01<> DiscreteVariate::N;

/*
 * Generate the cumulative distribution function for the given 
 * discrete probability mass function
 */
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

/*
 * Sample from the discrete distribution.
 */
std::size_t DiscreteVariate::operator()() 
{
	std::vector<double>::iterator lb = 
		std::lower_bound(cdf.begin(), cdf.end(), sampler() * sum);

	return lb - cdf.begin();
}
