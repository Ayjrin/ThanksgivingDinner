#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <iomanip>

class Guest {
public:
    std::string name;
    std::string favorite_food[3];
    std::string food_being_brought;
    double x, y;
    int car_size;
    bool RSVP;
    int table_size;
    bool host;
    bool operator==(const Guest& other) const {                     //  In order to use the std::find() function with a custom class, you need to define an operator==() for that class.
        return name == other.name;
    }
    // Method to change the RSVP status of the guest
    void changeRSVP(bool rsvp_status) {
        RSVP = rsvp_status;
    }
};

class GuestList {
public:
    std::list<Guest> guests;                                        // So it turns out that linked lists are just built into C++... That makes life so much easier
    Guest* host_guest;

    // Method to set the host based on the guest with the biggest table
    void setHost() {
        host_guest = &*std::max_element(guests.begin(), guests.end(), [](const Guest& a, const Guest& b) {
            return a.table_size < b.table_size;
        });
        host_guest->host = true;
    }

    // Method to assign food to each guest based on their favorite foods and what others are bringing
    void assignFood() {
        std::vector<std::string> food_list;
        for (auto& guest : guests) {
            food_list.push_back(guest.food_being_brought);
        }

        for (auto& guest : guests) {
            for (int i = 0; i < 3; ++i) {
                if (std::find(food_list.begin(), food_list.end(), guest.favorite_food[i]) == food_list.end()) {
                    guest.food_being_brought = guest.favorite_food[i];
                    food_list.push_back(guest.favorite_food[i]);    // push_back appends a new element to the end of a thing. its almost like the standard libraries are really useful.
                    break;
                }
            }
        }
    }

    // Method to calculate the distance between two guests
    double distance(const Guest& a, const Guest& b) {
        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));         // my freshman geometry teacher would be so proud rn. shout out Mr. White!! AND SHOUT OUT PYTHOGORAAAAAAAAAAS!!!!
    }

    // Struct to represent a node in the graph for carpooling
    struct GraphNode {
        Guest* guest;
        double distance;
        bool visited;
    };

    // Method to handle the carpooling logic
    // Method to handle the carpooling logic
void carpool() {
    // Create a complete graph with 10 nodes representing the guests
    std::vector<std::vector<GraphNode>> graph(10, std::vector<GraphNode>(10));

    // Populate the graph with distance values
    int guest1_index = 0;
    for (auto& guest1 : guests) {
        int guest2_index = 0;
        for (auto& guest2 : guests) {
            graph[guest1_index][guest2_index] = {&guest2, distance(guest1, guest2), false};
            guest2_index++;
        }
        guest1_index++;
    }

    // Find the guest with the biggest car
    auto biggest_car_guest = &*std::max_element(guests.begin(), guests.end(), [](const Guest& a, const Guest& b) {
        return a.car_size < b.car_size;
    });

    // If the biggest car belongs to the host, return
    if (biggest_car_guest->host) {
        return;
    }

    // Initialize a vector to store the order of guests for TSP
    std::vector<Guest*> tsp_guest_order;
    for (const auto& guest : guests) {
        if (guest.RSVP) {
            tsp_guest_order.push_back(&const_cast<Guest&>(guest));
        }
    }

    double min_path_cost = std::numeric_limits<double>::max();
    std::vector<Guest*> optimal_guest_order;

    // Brute-force TSP
    do {
        double current_path_cost = 0;
        for (size_t i = 0; i < tsp_guest_order.size() - 1; ++i) {
            current_path_cost += distance(*tsp_guest_order[i], *tsp_guest_order[i + 1]);
        }
        current_path_cost += distance(*tsp_guest_order.back(), *tsp_guest_order.front());

        if (current_path_cost < min_path_cost) {
            min_path_cost = current_path_cost;
            optimal_guest_order = tsp_guest_order;
        }
    } while (std::next_permutation(tsp_guest_order.begin() + 1, tsp_guest_order.end()));

    // Output the carpool details
    std::cout << "Carpool driver: " << biggest_car_guest->name << std::endl;
    for (const auto& guest : optimal_guest_order) {
        std::cout << "- " << guest->name << " - " << guest->food_being_brought << std::endl;
    }
}

    // Method to output the guests who RSVP'ed false
    void outputNotAttending() {
        std::cout << "\nGuests Not Attending" << std::endl;
        for (const auto& guest : guests) {
            if (!guest.RSVP) {
                std::cout << "- " << guest.name << std::endl;
            }
        }
    }

    // Method to output the host
    void outputHost() {
        std::cout << "\nHost:" << std::endl;
        for (const auto& guest : guests) {                          // const - should not be modified within loop, auto - automatically deduce the type of var based on its initializer, & - reference, guest - var, : - range-based loopp syntax (iterating over the elements of the container on right), guests - that container (list) that we are iterating over
            if (guest.host) {
                std::cout << "- " << guest.name << std::endl << std::endl;
                break;
            }
        }
    }

};

int main() {
    GuestList guest_list;

    // Read guest data from the console
    for (int i = 0; i < 10; ++i) {
        Guest guest;
        std::cin >> guest.name;
        for (int j = 0; j < 3; ++j) {
            std::cin >> guest.favorite_food[j];
        }
        std::cin >> guest.x >> guest.y;
      
        std::cin.ignore(); // Ignore the newline character after the coordinates
        std::cin >> guest.car_size >> guest.RSVP >> guest.table_size;
        std::cin.ignore(); // Ignore the newline character after the last input

        guest.host = false;

        guest_list.guests.push_back(guest);
    }

    guest_list.setHost();
    guest_list.outputHost();
    guest_list.assignFood();
    guest_list.carpool();
    guest_list.outputNotAttending();

    return 0;
}

