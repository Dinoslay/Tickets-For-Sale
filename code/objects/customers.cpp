#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Customer {
    string name;
    int patience; // 0-100
    int importance; // 1 = low, 3 = high
    int budget;
    bool rejected = false;
};

struct Ticket {
    string route;
    int basePrice;
    int dayPrice; // Changes daily
};

struct Event {
    string description;
    int reputationImpact;
    int moneyImpact;
};

struct Player {
    int money = 1000;
    int reputation = 50; // 0-100
    int weeklyBills = 200;
};

map<string, vector<string>> trainMap = {
    {"A", {"B"}},
    {"B", {"C"}},
    {"C", {}}
};

vector<Ticket> generateTickets() {
    return {
        {"A->B", rand() % 50 + 50},
        {"B->C", rand() % 50 + 50},
        {"A->C", rand() % 100 + 100} // combined route
    };
}

Customer generateCustomer() {
    int importance = rand() % 3 + 1;
    int patience = 30 + (importance * 10);
    int budget = 50 + (importance * 50);
    return {"Customer", patience, importance, budget};
}

void handleEvent(Player& player) {
    int roll = rand() % 3;
    if (roll == 0) {
        cout << "Homeless person asks for a free ticket.\n";
        player.reputation += 2;
    } else if (roll == 1) {
        cout << "You unknowingly sold a ticket to a criminal. Government fines you.\n";
        player.money -= 100;
        player.reputation -= 5;
    } else {
        cout << "Government introduces new transportation tax.\n";
        player.weeklyBills += 50;
    }
}

void processCustomer(Customer& c, const Ticket& t, Player& player) {
    cout << "Customer wants to buy ticket for " << t.route << " for $" << t.dayPrice << endl;

    if (t.dayPrice > c.budget) {
        cout << "Too expensive. Customer rejected.\n";
        c.rejected = true;
        c.patience -= 10;
        player.reputation -= 1;
    } else {
        cout << "Customer buys the ticket.\n";
        player.money += t.dayPrice;
        c.rejected = false;
        player.reputation += 1;
    }

    if (c.patience <= 0) {
        cout << "Customer lost all patience and left angrily.\n";
        player.reputation -= 3;
    }
}

void payBills(Player& player) {
    cout << "Paying weekly bills: $" << player.weeklyBills << endl;
    player.money -= player.weeklyBills;
}

int main() {
    srand(time(0));
    Player player;

    for (int day = 1; day <= 7; ++day) {
        cout << "\n--- Day " << day << " ---\n";
        auto tickets = generateTickets();

        Customer c = generateCustomer();
        handleEvent(player);

        // Let's assume customer needs A->C
        Ticket ticket = tickets[2]; // A->C
        processCustomer(c, ticket, player);

        if (day % 7 == 0) {
            payBills(player);
        }

        cout << "Money: $" << player.money << " | Reputation: " << player.reputation << "\n";
    }

    return 0;
}
