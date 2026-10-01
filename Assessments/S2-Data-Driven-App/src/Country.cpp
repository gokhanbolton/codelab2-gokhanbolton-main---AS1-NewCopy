#include "Country.h"

Country::Country() {
	commonName = "N/A";
	officialName = "N/A";
	capital = "N/A";
	region = "N/A";
	subregion = "N/A";
	currency = "N/A";
	population = 0;
}

void Country::parseFromJson(const ofJson & item) {
	if (item.empty()) return;

	// Country Name Extraction
	if (item.contains("name")) {
		if (item["name"].is_object() && item["name"].contains("common")) {
			commonName = item["name"]["common"].get<std::string>();
			officialName = item["name"].value("official", commonName);
		} else if (item["name"].is_string()) {
			commonName = item["name"].get<std::string>();
			officialName = commonName;
		}
	}

	// Capital City Parsing
	if (item.contains("capital")) {
		if (item["capital"].is_array() && !item["capital"].empty()) {
			capital = item["capital"][0].get<std::string>();
		} else if (item["capital"].is_string()) {
			capital = item["capital"].get<std::string>();
		}
	} else {
		capital = "None";
	}

	// Region & Subregion
	region = item.value("region", "N/A");
	subregion = item.value("subregion", "N/A");

	// Currency Deserialisation
	currency = "N/A";
	if (item.contains("currencies")) {
		// Case 1: Object format (e.g. {"TRY": {"name": "Turkish lira", "symbol": "₺"}})
		if (item["currencies"].is_object() && !item["currencies"].empty()) {
			for (auto it = item["currencies"].begin(); it != item["currencies"].end(); ++it) {
				std::string code = it.key();
				std::string currName = "";
				std::string symbol = "";

				if (it.value().is_object()) {
					currName = it.value().value("name", "");
					symbol = it.value().value("symbol", "");
				} else if (it.value().is_string()) {
					currName = it.value().get<std::string>();
				}

				currency = code;
				if (!currName.empty()) currency += " - " + currName;
				if (!symbol.empty()) currency += " (" + symbol + ")";
				break;
			}
		}
		// Case 2: Array format (e.g. [{"code": "TRY", "name": "Turkish lira", "symbol": "₺"}])
		else if (item["currencies"].is_array() && !item["currencies"].empty()) {
			auto firstCurr = item["currencies"][0];
			if (firstCurr.is_object()) {
				std::string code = firstCurr.value("code", "");
				std::string currName = firstCurr.value("name", "");
				std::string symbol = firstCurr.value("symbol", "");

				currency = code.empty() ? currName : code;
				if (!code.empty() && !currName.empty()) currency += " - " + currName;
				if (!symbol.empty()) currency += " (" + symbol + ")";
			} else if (firstCurr.is_string()) {
				currency = firstCurr.get<std::string>();
			}
		}
	}

	// Population
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

	font.drawString("Currency: " + currency, x, currentY);
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
std::string Country::getCurrency() const { return currency; }
int Country::getPopulation() const { return population; }