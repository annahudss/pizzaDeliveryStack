/* * CS21003 Pizza Delivery Coursework 2025/26
 * FILE: pizza_delivery_stack.cpp
 *
 *
 * */

/** ## HEADER FILES ## */
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
// include other header files here if required


/** ## STRUCT DEFINITION(S) ## */
// a data structure to record details of a pizza order to be placed on the delivery stack
struct PizzaOrder {
    int orderReference; // the unique ID generated when the customer completed their order
    int pizzaType; // the type of pizza coded from 1 to 50, e.g., 1 (pepperoni), 2 (BBQ), etc.
    double stackingTime; // the time the pizza was loaded, in milliseconds since mid-day 6th June 2026.
    double deliveryTime; // the time when the pizza is delivered (popped), can be initialised to 0 or -1.
    double deliveryDistance; // the distance from the shop in miles, used for routing priority.
    int compartmentID; // identifies the compartment where the order is stacked, numbered 0 to 15.
    char deliveryAddress[100]; // the target location for the delivery as a fixed-length character array.
    PizzaOrder* next; // points to the next pizza order down in the stack hierarchy
};


/** ## CLASS DEFINITION ## */
// a class to implement the data structure for the pizza delivery stack
class PizzaDeliveryStack
{
private:
    PizzaOrder* top; // points to the order at the top of the stack (closest delivery location)

public:
    PizzaDeliveryStack(); // constructor, initialise the stack to be empty
    ~PizzaDeliveryStack();  // destructor, free up any resources that are still in use by the stack
    void pushOrder(int orderReference, int pizzaType, double stackingTime, int compartmentID, const char deliveryAddress[], double deliveryDistance,     double deliveryTime); // adds a new order to the stack using the data provided
    PizzaOrder* popOrder();  // remove and return (a pointer to) the next pizza order from the top of the stack for delivery
    void displayStack(); // outputs the entire stack of pizza orders to cout
    void logDeliveries(std::string fileName); // appends the historical log of completed deliveries to a specified file on disk
    void reorderStackByDistance(); // reorders the stack using bubble sort so that the shortest delivery distance is at the top
};


/** ## IMPLEMENTATION OF THE METHODS DECLARED IN THE PizzaDeliveryStack CLASS ## */
PizzaDeliveryStack::PizzaDeliveryStack()
{
    top = nullptr;
}

PizzaDeliveryStack::~PizzaDeliveryStack()
{
    while (top != nullptr)
    {
        PizzaOrder* temp = top;
        top = top->next;
        delete temp;
    }
}

void PizzaDeliveryStack::displayStack()
{
    if (top == nullptr)
    {
        cout << "Stack is empty\n";
        return;
    }

    PizzaOrder* current = top;

    while (current != nullptr)
    {
        cout << "\nOrder Ref: " << current->orderReference;
        cout << "\nPizza Type: " << current->pizzaType;
        cout << "\nStacking Time: " << current->stackingTime;
        cout << "\nDelivery Time: " << current->deliveryTime;
        cout << "\nDistance: " << current->deliveryDistance;
        cout << "\nCompartment: " << current->compartmentID;
        cout << "\nAddress: " << current->deliveryAddress;
        cout << "\n------------------------";

        current = current->next;
    }
}

PizzaOrder* PizzaDeliveryStack::popOrder()
{
    if (top == nullptr)
        throw string("Stack underflow");

    PizzaOrder* removed = top;
    top = top->next;

    int flightDuration =
        rand() % (120000 - 12000 + 1) + 12000;

    removed->deliveryTime =
        removed->stackingTime + flightDuration;

    removed->next = nullptr;

    return removed;
}


void PizzaDeliveryStack::pushOrder(
    int orderReference,
    int pizzaType,
    double stackingTime,
    int compartmentID,
    const char deliveryAddress[],
    double deliveryDistance,
    double deliveryTime)
{
    // ---------------- VALIDATION ----------------
    if (pizzaType < 1 || pizzaType > 50)
        throw string("Invalid pizza type");

    if (compartmentID < 0 || compartmentID > 15)
        throw string("Invalid compartment ID");

    // ---------------- CREATE NODE ----------------
    PizzaOrder* newOrder = new PizzaOrder;

    newOrder->orderReference = orderReference;
    newOrder->pizzaType = pizzaType;
    newOrder->stackingTime = stackingTime;
    newOrder->deliveryTime = deliveryTime;
    newOrder->deliveryDistance = deliveryDistance;
    newOrder->compartmentID = compartmentID;

    strcpy(newOrder->deliveryAddress, deliveryAddress);

    newOrder->next = nullptr;

    // ---------------- DELAYED ORDER → BOTTOM ----------------
    if (deliveryTime < 0)
    {
        if (top == nullptr)
        {
            top = newOrder;
        }
        else
        {
            PizzaOrder* current = top;

            while (current->next != nullptr)
                current = current->next;

            current->next = newOrder;
        }
    }
    // ---------------- NORMAL ORDER → TOP ----------------
    else
    {
        newOrder->next = top;
        top = newOrder;
    }
}

void PizzaDeliveryStack::logDeliveries(string fileName)
{
    ofstream file(fileName, ios::app);

    if (!file)
        throw string("File cannot be opened");

    PizzaOrder* current = top;

    while (current != nullptr)
    {
        file << current->orderReference << " "
             << current->pizzaType << " "
             << current->stackingTime << " "
             << current->deliveryTime << " "
             << current->deliveryDistance << " "
             << current->compartmentID << " "
             << current->deliveryAddress
             << endl;

        current = current->next;
    }

    file.close();
}

void PizzaDeliveryStack::reorderStackByDistance()
{
    if (top == nullptr)
        return;

    for (PizzaOrder* i = top; i != nullptr; i = i->next)
    {
        PizzaOrder* minNode = i;

        for (PizzaOrder* j = i->next; j != nullptr; j = j->next)
        {
            if (j->deliveryDistance < minNode->deliveryDistance)
            {
                minNode = j;
            }
        }

        if (minNode != i)
        {
            // swap basic fields
            swap(i->orderReference, minNode->orderReference);
            swap(i->pizzaType, minNode->pizzaType);
            swap(i->stackingTime, minNode->stackingTime);
            swap(i->deliveryTime, minNode->deliveryTime);
            swap(i->deliveryDistance, minNode->deliveryDistance);
            swap(i->compartmentID, minNode->compartmentID);

            // swap address manually (char array)
            char temp[100];
            strcpy(temp, i->deliveryAddress);
            strcpy(i->deliveryAddress, minNode->deliveryAddress);
            strcpy(minNode->deliveryAddress, temp);
        }
    }
}


/** ## MAIN METHOD ## */
int main()
{
    cout << "This is the AeroBites Drone Delivery Test System.\n";
    cout << "Please select from the menu options below.\n";

    PizzaDeliveryStack stack;

    int choice;

    do
    {
        cout << "\n========================\n";
        cout << "1. Push a pizza order\n";
        cout << "2. Pop next pizza order\n";
        cout << "3. Display stack\n";
        cout << "4. Log deliveries\n";
        cout << "5. Reorder by distance\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        cin >> choice;

        try
        {
            switch (choice)
            {
                case 1:
                {
                    int orderRef = 1001;
                    int pizzaType = 5;
                    double stackingTime = 10000;
                    int compartmentID = 3;
                    char address[] = "Dundee";
                    double distance = 4.2;

                    // NORMAL ORDER (top of stack)
                    double deliveryTime = -1;

                    stack.pushOrder(orderRef, pizzaType, stackingTime,
                                    compartmentID, address, distance,
                                    deliveryTime);

                    cout << "Order pushed (normal)\n";
                    break;
                }

                case 2:
                {
                    PizzaOrder* order = stack.popOrder();

                    cout << "Delivered Order: " << order->orderReference << endl;
                    cout << "Delivery Time: " << order->deliveryTime << endl;

                    delete order;
                    
                    break;
                }

                case 3:
                    stack.displayStack();
                    break;

                case 4:
                    stack.logDeliveries("delivery_log.txt");
                    cout << "Deliveries logged\n";
                    break;

                case 5:
                    stack.reorderStackByDistance();
                    cout << "Stack reordered by distance\n";
                    break;

                case 6:
                    cout << "Exiting...\n";
                    break;

                default:
                    cout << "Invalid choice\n";
            }
        }
        catch (string e)
        {
            cout << "Error: " << e << endl;
        }

    } while (choice != 6);

    return 0;
}
