#include "stats.h"

#include <iostream>
#include <numeric>
#include <algorithm>


void 
print_stats (std::string action, std::vector<long>& data)
{
	long maximal = *std::max_element(data.begin(), data.end());
	long minimal = *std::min_element(data.begin(), data.end());
	double sum = std::accumulate(data.begin(), data.end(), 0.0);
	double average = sum / data.size();
	std::sort(data.begin(), data.end());
	double median = data[data.size()/2];

	std::cout << "Minimal " << action << " time: " << minimal << std::endl;
	std::cout << "Average " << action << " time: " << average << std::endl;
	std::cout << "Maximal " << action << " time: " << maximal << std::endl;
	std::cout << "Median " << action << " time: " << median << std::endl;
}

