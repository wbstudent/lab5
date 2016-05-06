#pragma once
#include <vector>
#include "Sample.h"

/*
- Stwórz klasę `Prediction`, dziedziczącą po klasie `Sample`, dodającą do niej zmienną `prediction`,
- Rozszerz ją o metodę statyczną `accuracy()`, przyjmującą wektor obiektów klasy `Prediction`, informującą o tym, w jakim odsetku ich zmienne `label` i `prediction` mają tę samą wartość.
*/

class Prediction : Sample
{
	int _prediction;
public:
	Prediction(int label, int prediction, std::vector<float> features);
	static float accuracy(std::vector<Prediction> predictions);
	
};