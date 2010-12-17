/*
 *	Author: Josh Bryan <josh.bryan@gmail.com>
 *	This file is copyright 2010 by Josh Bryan.
 *
 *  This file is part of Reinforcement Learning Demo.
 *
 *  Foobar is free software: you can redistribute it and/or modify it under the
 *  terms of the GNU General Public License as published by the Free Software
 *  Foundation, either version 3 of the License, or (at your option) any later
 *  version.
 *
 *  Foobar is distributed in the hope that it will be useful, but WITHOUT ANY
 *  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 *  FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 *  details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */


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
