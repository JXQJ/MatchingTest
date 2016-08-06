#ifndef WEIGHTED_AVERAGE_FILTER_H
#define WEIGHTED_AVERAGE_FILTER_H

#include "Filter.h"

class WeightedAverageFilter : public Filter
{
private:
	const static float FILTER_WEIGHT;
	bool isFirstData;
	float prevData;
public:
	WeightedAverageFilter();
	~WeightedAverageFilter();
	float update(const float measurement);
	void clear();
};

#endif // WEIGHTED_AVERAGE_FILTER_H