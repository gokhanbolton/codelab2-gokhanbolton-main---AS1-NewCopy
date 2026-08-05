#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

// Function to load jokes from file into a vector of pairs (setup, punchline)
std::vector<std::pair<std::string, std::string>> loadJokes(const std::string& filename) {
    std::vector<std::pair<std::string, std::string>> jokes;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        size_t qPos = line.find('?');
        if (qPos != std::string::npos) {
            std::string setup = line.substr(0, qPos + 1);
            std::string punchline = line.substr(qPos + 1);
            jokes.push_back({setup, punchline});
        }
    }
    return jokes;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));
    auto jokes = loadJokes("randomJokes.txt");

    if (jokes.empty()) {
        std::cout << "Error: Could not load jokes from randomJokes.txt\n";
        return 1;
    }

    std::cout << "Type 'Alexa, tell me a joke' to hear a joke, or 'quit' to exit.\n\n";

    std::string userInput;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, userInput);

        if (userInput == "quit" || userInput == "Quit") {
            std::cout << "Goodbye!\n";
            break;
        } else if (userInput == "Alexa, tell me a joke") {
            int randomIndex = std::rand() % jokes.size();
            std::cout << "\nSetup: " << jokes[randomIndex].first << "\n";
            std::cout << "[Press Enter to reveal the punchline...]";
            std::cin.get();
            std::cout << "Punchline: " << jokes[randomIndex].second << "\n\n";
        } else {
            std::cout << "Command not recognized. Try typing: Alexa, tell me a joke\n";
        }
    }

    return 0;
}