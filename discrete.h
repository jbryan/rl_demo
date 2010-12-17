
#ifndef _DISCRETE_H
#define _DISCRETE_H

#include <vector>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>

/*
 * This class represents a discrete random variate with an
 * aribtrary probability distribution.
 */
class DiscreteVariate 
{
	public:
		DiscreteVariate(std::vector<double> const &);
		std::size_t operator()();

	private:
		boost::variate_generator<boost::mt19937&, boost::uniform_01<> >
			sampler;

		//the cumulative distribution
		std::vector<double> cdf;
		//normalizing sum of the cdf
		double sum;

		static boost::mt19937 rng;
		static boost::uniform_01<> N;

};

#endif
