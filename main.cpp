#include "Sample.h"
#include "Dataset.h"
#include "Prediction.h"

#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <time.h>
#include <math.h>
#include <map>
#include <algorithm>
#include <iomanip>
/*
- Jako argumenty wiersza poleceń programu, przekaż nazwę pliku oraz liczbę całkowitą `k`,
- dla celów testowych, w repozytorium znajduje się plik `wine.csv`,
- wczytaj plik `wine.csv` do wektora obiektów typu `Sample` tak, aby pierwsza jego kolumna określała `label`, a pozostałe znalazły się w wektorze `features`,
- stwórz dwa obiekty klasy `Dataset`. Pierwszy nazwij `train`, drugi `test`,
- do `train` wprowadź losowe 20% wczytanych z pliku obiektów, a do `test`, resztę,
- zaimplementuj funkcję `knn()`, zwracającą wektor obiektów klasy `Prediction` przyjmującą jako argumenty dwa obiekty typu `Dataset` (`train` i `test`) i zmienną całkowitą `k`:
    - utwórz w niej wektor `predictions`:
    - do utworzonego wektora wprowadź kopie wszystkich obiektów (mają typ `Sample`) znajdujących się w `test`, uzupełniając dla nich wartość `prediction`, według następującego schematu:

>   Dla każdego obiektu ze zbioru testowego znajdź `k` obiektów ze zbioru uczącego, którego cechy (`features`) znajdują się w najmniejszej od niego [odległości](https://pl.wikipedia.org/wiki/Odległość). Za `prediction` uznaj `label`, który powtarza się najczęściej wśród znalezionych.
>   

- Wyświetl użytkownikowi informacje o zbiorze (nazwa pliku, liczba próbek, liczba cech) oraz jakość klasyfikacji (`accuracy()`).
*/
const int NUM_OF_LABELS = 3;
const float TRAIN_PERCENTAGE = 0.2;
using namespace std;

//vector <Prediction> knn(Dataset *train, Dataset *test, int k);
bool takeOneLineAndPutItIntoSample(ifstream& csvFile, std::vector<Sample>& samp);
int mode(vector<int> v);
vector<Prediction> knn(Dataset& train, Dataset& test, int k);

int main(int argc, char const *argv[])
{
	int k = atoi(argv[2]);
	string filename = argv[1];
	vector<Sample> wineSamples;

	ifstream file ( filename );
	bool isLine = true;
	while(isLine)//dopóki takeOneLineAndPutItIntoSample odczytuje linie pliku .csv
	{
		isLine = takeOneLineAndPutItIntoSample( file, wineSamples );
	}
	
	file.close();

	Dataset train;
	Dataset test;

	srand(time(NULL));

	int vecLength = wineSamples.size();
	int trainLength = vecLength*TRAIN_PERCENTAGE;

	for(int i = 0; i < trainLength; i++)
	{
		int toPut = rand()%vecLength;
		train.push_back(wineSamples[toPut]);
		wineSamples.erase(wineSamples.begin() + toPut);//usuwam, zeby sie nie powtórzyły, zamiast tego można zapisać, które trafiły do train
		vecLength--;
	}
	
	for(int i = 0; i < vecLength; i++){
		test.push_back(wineSamples[i]);//tych nie muszę usuwać
	}
	cout << "Wczytano " << train.samples().size() + test.samples().size() << " próbek z pliku " << filename << '.' << endl;
	cout << "Każda z wczytanych próbek posiada " << test.samples()[0].features().size() << " cech." << endl;
	cout << train.samples().size() <<" ("<<TRAIN_PERCENTAGE*100 <<"%) próbek użyto w zbiorze uczącym." << endl;
	float accuracy = Prediction::accuracy(knn(train, test, k)); 
	cout << "Poprawność przewidywań wyniosła " << setprecision(2) << accuracy*100<< "%." << endl;
	
}

bool takeOneLineAndPutItIntoSample(ifstream& csvFile, vector<Sample>& samp)
{
	string line, cell;
	int label = -1;
	getline(csvFile, line);
	std::istringstream s(line);
    vector<float> vectorOfFeatures;

   	if(!getline(s, cell, ','))//wczytuje linię aż do przecinka-czyli pierwszą kolumnę, jeśli nie wczyta, to koniec tekstu
   		return false;
   	label = stoi(cell);
  
	while (getline(s, cell,','))//wczytuje kolejne kolumny do wektora features
	{
		vectorOfFeatures.push_back(stof(cell));
	}

    samp.push_back(*(new Sample(label, vectorOfFeatures)));
    return true;
}

vector<Prediction> knn(Dataset& train, Dataset& test, int k)
{
	std::vector<Prediction> predictions;
	int testSize = test.samples().size();
	int trainSize = train.samples().size();
	int featureSize = test.samples()[0].features().size();

	map<float, int> minimalDistances;
	for(int i = 0; i < testSize; i++)//dla każdej próbki ze zbioru testowego
	{
		minimalDistances.clear();
		float distance = 0;
		for(int j = 0; j < trainSize; j++)//policz dystans od każdej z próbek ze zbioru uczącego
		{	
			for(int m = 0; m < featureSize; m++)//poprzez dodanie, dla każdej z cech
			{
				distance += pow((test.samples()[i].features()[m]-train.samples()[j].features()[m]), 2);	//kwadratu różnicy cechy próbki ze zbioru uczącego i cechy próbki ze zbioru testowego 
			}

			distance = sqrt(distance);//i wzięcie pierwiastka kwadratowego z wyniku
			minimalDistances[distance] = (train.samples()[j].label());//połącz odległość z etykietą
		}
		map <float, int>::iterator minimalDistancesIterator = minimalDistances.begin();

		vector<int> labels;
		for(int j = 0; j < k; ++minimalDistancesIterator)//z k najmniejszych(będących "na początku" słownika)
		{
			labels.push_back(minimalDistancesIterator->second);//weź etykietę i dodaj do wektora etykiet
			j++;
		}
		
		int pred = mode(labels);//znajduje najczęstszą etykietę
		predictions.push_back(*(new Prediction(test.samples()[i].label(), pred, test.samples()[i].features())));
	}	
	return predictions;
}

int mode(vector<int> v)//zwraca najczęściej powtarzającą się liczbę w wektorze, pewnie można sprytniej
{
	int vSize = v.size();
	sort (v.begin(), v.end());

	int reps = 0;
	int repsMax = 0;
	int nowLab = *v.begin();
	int maxLab;
	for(int i = 0; i < vSize; i++)
	{
		if (v[i] == nowLab)
		{
			reps++;
			if(reps > repsMax)
			{
				maxLab = nowLab;
				repsMax = reps;
			}
		}
		else
		{
			nowLab = v[i];
			reps = 1;
		}
	}
	return maxLab;
}