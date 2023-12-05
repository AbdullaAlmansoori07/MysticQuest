#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
public:
    int level;
    int experience;
    int health;
    int attack;
    int defense;
    vector<string> inventory;

    Player() : level(1), experience(0), health(100), attack(10), defense(5) {}
};

class Enemy {
public:
    string type;
    int health;
    int attack;
    int defense;
    int experienceReward;

    Enemy(string t, int exp) : type(t), health(50), attack(8), defense(3), experienceReward(exp) {}
};

class Location {
public:
    string name;
    string description;
    vector<Enemy> enemies;
    vector<string> possibleEvents;

    Location(string n, string desc, vector<Enemy> e, vector<string> events) : name(n), description(desc), enemies(e), possibleEvents(events) {}
};

void levelUp(Player &player) {
    cout << "Congratulations! You leveled up!\n";
    player.level++;
    player.attack += 2;
    player.defense += 1;
    player.health = 100;  // Restore health on level up
}

void battle(Player &player, Enemy &enemy) {
    cout << "A wild " << enemy.type << " appears!\n";

    while (player.health > 0 && enemy.health > 0) {
        // Player's turn
        cout << "1. Attack\n2. Defend\n";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                enemy.health -= player.attack - enemy.defense;
                cout << "You dealt damage to the " << enemy.type << "!\n";
                break;
            case 2:
                player.defense += 2;
                cout << "You defend and gain extra defense!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

        // Enemy's turn
        player.health -= enemy.attack - player.defense;
        cout << "The " << enemy.type << " attacks you!\n";

        // Display current status
        cout << "Your Health: " << player.health << "\t" << enemy.type << " Health: " << enemy.health << "\n\n";
    }

    if (player.health > 0) {
        cout << "Congratulations! You defeated the " << enemy.type << "!\n";
        player.experience += enemy.experienceReward;

        // Level up if player has enough experience
        if (player.experience >= player.level * 10) {
            levelUp(player);
        }
    } else {
        cout << "Game Over. You were defeated by the " << enemy.type << ".\n";
    }
}

void handleEvent(Player &player, const string &event) {
    // Implement specific actions based on the event
    if (event == "You discover a mysterious stone.") {
        cout << "You touch the mysterious stone and feel a surge of power!\n";
        player.attack += 3;
        cout << "Your attack has been increased!\n";
    } else if (event == "A friendly traveler gives you a healing potion.") {
        cout << "The traveler offers you a healing potion. Your health is restored!\n";
        player.health = min(100, player.health + 20);  // Cap health at 100
    }
    // Add more event actions as needed
}

void exploreLocation(Player &player, Location &location) {
    cout << "Exploring " << location.name << "...\n";
    cout << location.description << "\n";

    // Random chance of encountering enemies
    for (Enemy &enemy : location.enemies) {
        if (rand() % 2 == 0) {
            battle(player, enemy);
        }
    }

    // Random events
    if (!location.possibleEvents.empty() && rand() % 3 == 0) {
        int eventIndex = rand() % location.possibleEvents.size();
        string event = location.possibleEvents[eventIndex];
        cout << "Random Event: " << event << "\n";
        handleEvent(player, event);
    }

    // Add items to player's inventory
    cout << "You find some items:\n";
    player.inventory.push_back("Health Potion");
    player.inventory.push_back("Attack Boost");
    player.inventory.push_back("Defense Boost");

    cout << "Items added to your inventory!\n";
}

int main() {
    srand(time(0));  // Seed for random number generation

    cout << "Welcome to Mystic Quest!\n";

    Player player;

    // Initial location
    Location startingLocation("Forest", "You find yourself in a dense forest.",
                              {
                                      Enemy("Goblin", 5),
                                      Enemy("Wolf", 8),
                                      Enemy("Skeleton", 10),
                                      Enemy("Spider", 7),
                                      Enemy("Bandit", 12)
                              },
                              {
                                      "You discover a mysterious stone.",
                                      "A friendly traveler gives you a healing potion."
                              }
    );

    cout << "Your journey begins...\n";

    // Game loop
    while (player.health > 0) {
        exploreLocation(player, startingLocation);

        // Display player stats
        cout << "Player Stats - Level: " << player.level << " | Experience: " << player.experience << " | Health: " << player.health << "\n";

        // Display inventory
        cout << "Current Inventory:\n";
        for (const string &item : player.inventory) {
            cout << "- " << item << "\n";
        }

        cout << "Do you want to continue your journey? (yes/no)\n";
        string continueJourney;
        cin >> continueJourney;

        if (continueJourney != "yes") {
            cout << "Thanks for playing Mystic Quest!\n";
            break;
        }
    }

    return 0;
}