#pragma once

#include "ofMain.h"

class Country {
private:
	std::string commonName;
	std::string officialName;
	std::string capital;
	std::string region;
	std::string subregion;
	int population;

public:
	Country();

	// Verileri JSON nesnesinden ayrıştırıp atayan kurucu/metot
	void parseFromJson(const ofJson & item);

	// Ekrana kendi bilgilerini çizen metot (Encapsulation)
	void draw(float x, float y, ofTrueTypeFont & font);

	// Getter metotları
	std::string getCommonName() const;
	std::string getOfficialName() const;
	std::string getCapital() const;
	std::string getRegion() const;
	std::string getSubregion() const;
	int getPopulation() const;
};
