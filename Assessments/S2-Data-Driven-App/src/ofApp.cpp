#include "ofApp.h"

void ofApp::setup() {
	ofSetBackgroundColor(25, 30, 40);
	ofRegisterURLNotification(this);

	// Fontlari sistemden yukle
	bodyFont.load(OF_TTF_SANS, 20);
	titleFont.load(OF_TTF_SANS, 32);

	// GUI boyutlandirma
	ofxGuiSetDefaultWidth(450);
	ofxGuiSetDefaultHeight(45);

	// GUI Kurulumu
	gui.setup("COUNTRY FACTS DASHBOARD");
	gui.add(countryInput.setup("Country", "Italy"));
	gui.add(searchBtn.setup("Search Country"));

	searchBtn.addListener(this, &ofApp::fetchCountryData);
}

void ofApp::fetchCountryData() {
	std::string query = countryInput;

	// Temizlik
	ofStringReplace(query, "\n", "");
	ofStringReplace(query, "\r", "");
	query = ofTrim(query);

	if (query.empty()) {
		hasError = true;
		statusMessage = "Error: Please enter a country name.";
		return;
	}

	// Bosluklari URL bicimine cevir
	ofStringReplace(query, " ", "%20");

	isLoading = true;
	hasError = false;
	statusMessage = "Fetching country data...";

	std::string url = "https://www.apicountries.com/name/" + query;
	ofLoadURLAsync(url, "countryReq");
}

void ofApp::urlResponse(ofHttpResponse & response) {
	isLoading = false;

	if (response.status == 200) {
		try {
			std::string rawData = response.data.getText();
			ofJson json = ofJson::parse(rawData);

			ofJson item;
			if (json.is_array() && !json.empty()) {
				item = json[0];
			} else if (json.is_object()) {
				item = json;
			}

			if (!item.empty() && (item.contains("name") || item.contains("capital"))) {
				// Veriyi Country nesnesine aktar (OOP)
				currentCountry.parseFromJson(item);

				hasError = false;
				statusMessage = "Country loaded successfully!";
			} else {
				hasError = true;
				statusMessage = "Error: Country not found.";
			}

		} catch (const std::exception & e) {
			hasError = true;
			statusMessage = "Parsing Error: " + std::string(e.what());
		}
	} else if (response.status == 404) {
		hasError = true;
		statusMessage = "Error: Country not found (404).";
	} else {
		hasError = true;
		statusMessage = "API Error: HTTP Code " + ofToString(response.status);
	}
}

void ofApp::update() {
}

void ofApp::draw() {
	float marginX = 60.0f;
	float startY = 70.0f;

	// Baslik
	ofSetColor(255);
	titleFont.drawString("COUNTRY FACTS VIEWER", marginX, startY);

	// Sol Panel: GUI
	float guiY = startY + 40.0f;
	gui.setPosition(marginX, guiY);
	gui.draw();

	// Sag Panel: Country Nesnesini cizdir
	float textX = marginX + 500.0f;
	float currentY = guiY + 35.0f;

	ofSetColor(255);
	currentCountry.draw(textX, currentY, bodyFont);

	// Durum Karti
	float statusY = currentY + (42.0f * 5) + 20.0f;

	ofColor bannerColor = ofColor::darkGreen;
	if (isLoading) bannerColor = ofColor::orange;
	if (hasError) bannerColor = ofColor::darkRed;

	float statusWidth = bodyFont.stringWidth("Status: " + statusMessage) + 30.0f;
	float statusHeight = bodyFont.stringHeight("Status: " + statusMessage) + 20.0f;

	ofSetColor(bannerColor);
	ofDrawRectangle(textX - 10.0f, statusY - statusHeight + 5.0f, statusWidth, statusHeight);

	ofSetColor(255);
	bodyFont.drawString("Status: " + statusMessage, textX, statusY);
}
