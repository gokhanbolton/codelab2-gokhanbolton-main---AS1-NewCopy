#pragma once

#include "ofMain.h"

class Country {
private:
	std::string commonName;
	std::string officialName;
	std::string capital;
	std::string region;
	std::string subregion;
	std::string currency;
	int population;

public:
	Country();

	// Verileri JSON nesnesinden ayristirip atayan metot
	void parseFromJson(const ofJson & item);

	// Ekrana bilgileri cizen metot (Encapsulation)
	void draw(float x, float y, ofTrueTypeFont & font);

	// Getter metotlari
	std::string getCommonName() const;
	std::string getOfficialName() const;
	std::string getCapital() const;
	std::string getRegion() const;
	std::string getSubregion() const;
	std::string getCurrency() const;
	int getPopulation() const;
};
