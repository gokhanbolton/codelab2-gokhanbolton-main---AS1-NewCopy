#pragma once

#include "Country.h"
#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;

	// API Metotlari
	void fetchCountryData();
	void urlResponse(ofHttpResponse & response);

	// GUI Elemanlari
	ofxPanel gui;
	ofxInputField<std::string> countryInput;
	ofxButton searchBtn;

	// Fontlar
	ofTrueTypeFont titleFont;
	ofTrueTypeFont bodyFont;

	// OOP Modeli: Country Nesnesi
	Country currentCountry;

	std::string statusMessage = "Enter a country name to search.";
	bool isLoading = false;
	bool hasError = false;
};
