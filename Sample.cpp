#include "Sample.h"
Sample::Sample(int label, std::vector<float> features)
	{
		_label = label;
		_features = features; //czy lepiej przez referencję?
	}