#pragma once
#include <vector>
#include "Sample.h"
/*
- Stwórz klasę `Dataset`, zawierającą:
    - wektor obiektów klasy `Sample`,
    - metodę `push_back()`, dodającą nową próbkę do wektora:
        - metoda ta powinna sprawdzać, czy wektor `features` dla każdej z wprowadzanych próbek jest tej samej długości.
*/

class Dataset {
	std::vector<Sample> _samples;
public:
	void push_back(Sample sample);
	std::vector<Sample> samples() { return _samples;}
};