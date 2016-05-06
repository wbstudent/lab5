#include "Dataset.h"
static unsigned int size = 0;

void Dataset::push_back(Sample sample)
{
	
	if( size == 0 )//po pierwszym wywołaniu już nigdy nie pwoinno wynosić 0
	{
		size = sample.features().size();
	}
	if(sample.features().size() == size)//doda tylko jeśli rozmiar kolejnych dodawanych próbek jest taki sam, jak pierwszej dodanej
		_samples.push_back(sample);
}