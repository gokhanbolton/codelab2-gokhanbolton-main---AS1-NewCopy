#include "ofApp.h"

void ofApp::setup() {
    ofSetBackgroundColor(25, 30, 40);
    ofRegisterURLNotification(this);

    // Load built-in system font at large sizes (24pt for body, 36pt for headers)
    bodyFont.load(OF_TTF_SANS, 24);
titleFont.load(OF_TTF_SANS, 36);

// Drastically scale up GUI panel width and control height
    ofxGuiSetDefaultWidth(500);
    ofxGuiSetDefaultHeight(50);

    // Setup GUI Controls
    gui.setup("WEATHER DASHBOARD");
gui.add(locationInput.setup("City Search", "London"));
gui.add(searchBtn.setup("Get Forecast"));

searchBtn.addListener(this, &ofApp::fetchWeatherData);
}
void ofApp::fetchWeatherData() {
	std::string city = locationInput;

	if (city.empty()) {
		hasError = true;
		statusMessage = "Error: Input cannot be empty.";
		return;
	}

	isLoading = true;
	hasError = false;
	statusMessage = "Fetching weather data...";

	std::string url = "https://api.weatherapi.com/v1/current.json?key=";
	url += apiKey;
	url += "&q=" + city + "&aqi=no";

	ofLoadURLAsync(url, "weatherReq");
}
void ofApp::urlResponse(ofHttpResponse & response) {
	isLoading = false;

	if (response.status == 200) {
		ofJson json = ofJson::parse(response.data.getText());

		if (json.contains("location") && json.contains("current")) {
			cityName = json["location"]["name"].get<std::string>();
			country = json["location"]["country"].get<std::string>();

			tempC = json["current"]["temp_c"].get<float>();
			feelsLikeC = json["current"]["feelslike_c"].get<float>();
			humidity = json["current"]["humidity"].get<int>();
			conditionText = json["current"]["condition"]["text"].get<std::string>();
			statusMessage = "Data successfully loaded!";
		} else {
			hasError = true;
			statusMessage = "Error: Invalid JSON structure.";
		}
	} else if (response.status == 400 || response.status == 404) {
		hasError = true;
		statusMessage = "Error: Location not found. Try another city.";
	} else {
		hasError = true;
		statusMessage = "API Error: HTTP Code " + ofToString(response.status);
	}
}
void ofApp::update() {
	// Logic updates
}

void ofApp::draw() {
		float marginX = 80.0f;
		float startY = 80.0f;

		// Draw Large Screen Header
		ofSetColor(255);
		titleFont.drawString("WEATHER FORECAST", marginX, startY);

		// Position Large GUI Panel on the Left
		float guiY = startY + 50.0f;
		gui.setPosition(marginX, guiY);
		gui.draw();

		// Position Results Card on the Right Half of Screen
		float textX = marginX + 560.0f;
		float lineSpacing = 55.0f;
		float currentY = guiY + 40.0f;

		// Draw Weather Details with High-Resolution TTF Font
		bodyFont.drawString("Location: " + cityName + ", " + country, textX, currentY);
		currentY += lineSpacing;

		bodyFont.drawString("Condition: " + conditionText, textX, currentY);
		currentY += lineSpacing;

		bodyFont.drawString("Temperature: " + ofToString(tempC, 1) + " C", textX, currentY);
		currentY += lineSpacing;

		bodyFont.drawString("Feels Like: " + ofToString(feelsLikeC, 1) + " C", textX, currentY);
		currentY += lineSpacing;

		bodyFont.drawString("Humidity: " + ofToString(humidity) + "%", textX, currentY);
		currentY += lineSpacing + 20.0f;

		// Draw Large Status Banner Background Box
		ofColor bannerColor = ofColor::darkGreen;
		if (isLoading) bannerColor = ofColor::orange;
		if (hasError) bannerColor = ofColor::darkRed;

		float statusWidth = bodyFont.stringWidth("Status: " + statusMessage) + 30.0f;    


		float statusHeight = bodyFont.stringHeight("Status: " + statusMessage) + 20.0f;

		ofSetColor(bannerColor);
		ofDrawRectangle(textX - 10.0f, currentY - statusHeight + 5.0f, statusWidth, statusHeight);

		ofSetColor(255);
		bodyFont.drawString("Status: " + statusMessage, textX, currentY);
	}
