// Header for application
#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	void setup() override;
	void update() override;
	void draw() override;

	// API Handling
	void fetchWeatherData();
	void urlResponse(ofHttpResponse & response);

	// GUI Elements
	ofxPanel gui;
	ofxInputField<std::string> locationInput;
	ofxButton searchBtn;

	// Custom Fonts for Big Text Display
	ofTrueTypeFont titleFont;
	ofTrueTypeFont bodyFont;

	// API Config & Weather Data Variables
	std::string apiKey = "4f7ec3c7b26545ee9ca113406261007";
	std::string cityName = "N/A";
	std::string country = "N/A";
	std::string conditionText = "N/A";

	float tempC = 0.0f;
	float feelsLikeC = 0.0f;
	int humidity = 0;
	std::string statusMessage = "Enter a city to search.";
	bool isLoading = false;
	bool hasError = false;
};
