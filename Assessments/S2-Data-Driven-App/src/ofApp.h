#pragma once

#include "Country.h"
#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;

	// Asynchronous API network methods
	void fetchCountryData();
	void urlResponse(ofHttpResponse & response);

	// GUI Controls (ofxGui)
	ofxPanel gui;
	ofxInputField<std::string> countryInput;
	ofxButton searchBtn;

	// Typography / Font assets
	ofTrueTypeFont titleFont;
	ofTrueTypeFont bodyFont;

	// Domain Model: Encapsulated Country entity (OOP)
	Country currentCountry;

	std::string statusMessage = "Enter a country name to search.";
	bool isLoading = false;
	bool hasError = false;
};