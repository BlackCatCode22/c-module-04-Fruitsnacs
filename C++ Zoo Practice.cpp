// Alex Lopez
// Cit-66
// 3-1-2025


#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// Base Animal Class
class Animal {
protected:
    string name;
    int age;
    string species;
public:
    Animal(string n, int a, string s) : name(n), age(a), species(s) {}
    virtual void displayInfo() const {
        cout << species << " named " << name << ", Age: " << age << endl;
    }
    string getSpecies() const { return species; }
    string getName() const { return name; }
    int getAge() const { return age; }
};

// Subclasses
class Hyena : public Animal {
public:
    Hyena(string n, int a) : Animal(n, a, "Hyena") {}
};

class Lion : public Animal {
public:
    Lion(string n, int a) : Animal(n, a, "Lion") {}
};

class Tiger : public Animal {
public:
    Tiger(string n, int a) : Animal(n, a, "Tiger") {}
};

class Bear : public Animal {
public:
    Bear(string n, int a) : Animal(n, a, "Bear") {}
};

// Function to process file data
void processAnimals(const string& filename, vector<Animal*>& animals, map<string, int>& speciesCount) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        int age;
        string gender, species, born, color, temp, location;
        float weight;

        iss >> age >> temp >> gender >> species >> temp >> born >> temp;
        getline(iss, color, ',');
        iss >> weight >> temp >> temp;
        getline(iss, location);

        string name = "Unknown";  // Assign a placeholder name

        if (species == "hyena") animals.push_back(new Hyena(name, age));
        else if (species == "lion") animals.push_back(new Lion(name, age));
        else if (species == "tiger") animals.push_back(new Tiger(name, age));
        else if (species == "bear") animals.push_back(new Bear(name, age));

        speciesCount[species]++;
    }
    file.close();
}

// Function to write report
void generateReport(const string& filename, const vector<Animal*>& animals, const map<string, int>& speciesCount) {
    ofstream file(filename);
    for (const auto& pair : speciesCount) {
        file << pair.first << "s: " << pair.second << "\n";
        for (const auto& animal : animals) {
            if (animal->getSpecies() == pair.first) {
                file << "  - " << animal->getName() << ", Age: " << animal->getAge() << "\n";
            }
        }
    }
    file.close();
}

int main() {
    vector<Animal*> animals;
    map<string, int> speciesCount;

    processAnimals("arrivingAnimals.txt", animals, speciesCount);
    generateReport("newAnimals.txt", animals, speciesCount);

    // Clean up memory
    for (Animal* animal : animals) delete animal;

    cout << "Report generated successfully!" << endl;
    return 0;
}
