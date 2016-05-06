#include "Prediction.h"

float Prediction::accuracy(std::vector<Prediction> predictions)
{
	float pred = 0;
	int predLength = predictions.size();
	for(int i = 0; i < predLength; i++)
		if(predictions[i]._label == predictions[i]._prediction)
			pred++;
	return pred / predLength;
}

Prediction::Prediction(int label, int prediction, std::vector<float> features):Sample(label, features)
{
	_features = features;
	_prediction = prediction;
}