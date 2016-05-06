#pragma once
#include <vector>
/*
- Stwórz klasę `Sample`, zawierającą:
    - zmienną całkowitą `label`,
    - wektor liczb zmiennoprzecinkowych `features`,
- w konstruktorze klasy `Sample` przyjmuj oba te parametry,
- stwórz też dla nich *gettery*.
*/

class Sample {
protected:
	int _label;
	std::vector<float> _features;
public:
	Sample(int label, std::vector<float> features);
	int label() {return _label;}
	std::vector<float> features() {return _features;}
};