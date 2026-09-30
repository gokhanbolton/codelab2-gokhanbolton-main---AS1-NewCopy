#include "Country.h"

Country::Country() {
	commonName = "N/A";
	officialName = "N/A";
	capital = "N/A";
	region = "N/A";
	subregion = "N/A";
	population = 0;
}

void Country::parseFromJson(const ofJson & item) {
	if (item.empty()) return;

	// Ulke Adi
	if (item.contains("name")) {
		if (item["name"].is_object() && item["name"].contains("common")) {
			commonName = item["name"]["common"].get<std::string>();
			officialName = item["name"].value("official", commonName);
		} else if (item["name"].is_string()) {
			commonName = item["name"].get<std::string>();
			officialName = commonName;
		}
	}

	// Baskent
	if (item.contains("capital")) {
		if (item["capital"].is_array() && !item["capital"].empty()) {
			capital = item["capital"][0].get<std::string>();
		} else if (item["capital"].is_string()) {
			capital = item["capital"].get<std::string>();
		}
	} else {
		capital = "None";
	}

	// Bolge & Alt Bolge
	region = item.value("region", "N/A");
	subregion = item.value("subregion", "N/A");

	// Nufus
	population = item.value("population", 0);
}

void Country::draw(float x, float y, ofTrueTypeFont & font) {
	float lineSpacing = 42.0f;
	float currentY = y;

	font.drawString("Common Name: " + commonName, x, currentY);
	currentY += lineSpacing;

	font.drawString("Official Name: " + officialName, x, currentY);
	currentY += lineSpacing;

	font.drawString("Capital: " + capital, x, currentY);
	currentY += lineSpacing;

	font.drawString("Region: " + region + " (" + subregion + ")", x, currentY);
	currentY += lineSpacing;

	font.drawString("Population: " + ofToString(population), x, currentY);
}

std::string Country::getCommonName() const { return commonName; }
std::string Country::getOfficialName() const { return officialName; }
std::string Country::getCapital() const { return capital; }
std::string Country::getRegion() const { return region; }
std::string Country::getSubregion() const { return subregion; }
int Country::getPopulation() const { return population; }
