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
