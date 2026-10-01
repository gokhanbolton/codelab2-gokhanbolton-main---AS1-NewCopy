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

	// Deserialises and binds data attributes from a JSON object
	void parseFromJson(const ofJson & item);

	// Renders encapsulated demographic data to the canvas
	void draw(float x, float y, ofTrueTypeFont & font);

	// Public accessor methods (Getters)
	std::string getCommonName() const;
	std::string getOfficialName() const;
	std::string getCapital() const;
	std::string getRegion() const;
	std::string getSubregion() const;
	std::string getCurrency() const;
	int getPopulation() const;
};