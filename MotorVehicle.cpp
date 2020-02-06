#include <iostream>
#include <string>
#include <vector>

using namespace std;


//this is our base class called MotorVehicle
class MotorVehicle
{

    private:
        // if we want to edit any of these variables, we have to add a public function to access private data members
        // this adds an extra layer of security because you can't access any private data unless you have a public function to do so
        int tickets;
        // in C the string data type doesn't exist, this is a benefit of C++ using the string data type
        // it is a benefit because we do not have to dynamically allocate memory using malloc for different sized strings
        string make;
        string license;

    public:

        // constructor function, this is a function which allows us to initialize objects of the MotorVehicle class to store values into the private data members
        MotorVehicle (int existingTickets, string vehicleMake, string licensePlate)
        {
            tickets = existingTickets;
            make = vehicleMake;
            license = licensePlate;
        }


        // Do-nothing virtual destructor
        // (makes sure that deletes of child class objects are handled properly)
        virtual ~MotorVehicle(){};

        virtual void print()=0;

        // the below three  return (get) functions are used in the print statements in the child classes car and truck

        // this will return the total number of tickets that the vehicle has
        int return_tickets()
        {
            return tickets;
        }

        // this will return the make of the vehicle (ex. toyota, honda, tesla)
        string return_make()
        {
            return make;
        }

        // this will return the license plate of the vehicle
        string return_license()
        {
            return license;
        }

        // the following three functions are setter functions would be used to change the private data members of the MotorVehicle class for a  particular object
        // however, these three functions are not called in our main program and are just to illustrate that we would need to use these functions if we ever wanted to change the value of the private data members
        void change_tickets(int ticketTotal)
	    {
            tickets = ticketTotal;
        }

        void change_make(string brand)
	    {
            make = brand;
        }

        void change_license(string licenseID)
	    {
            license = licenseID;
        }


};

// this is a child class of MotorVehicle called Car
// child classes inherit the public methods and data members of the base class (MotorVehicle)
class Car : public MotorVehicle
{       
    private:

        // adding private data member to Car subclass to denote whether the car is a sedan(4 door) or a coup(2 door)
        string bodyStyle;

    public:


        // this will return the body style of the car, called in our print() function below

        string return_bodyStyle()
        {
            return bodyStyle;
        }


        // although the below function is not called elsewhere in the program, we would need this if we wanted to change the value of the bodyStyle for a particular car object
        void change_bodyStyle(string body)
        {
           bodyStyle = body;
        }



        //the private members in MotorVehicle cannot be directly accessed in the child class Car
        // we access these private data members of our base class by calling (and in this case overloading) our constructor from the parent class MotorVehicle
        // the constructor in our base class initializes the private data members tickets, make, and license
        // in this instance, we are adding a string variable called bodyStyle to denote whether the car is a sedan or a coup
        // this is an example of method overloading
        Car(string sedanOrCoup, int tickets, string newMake, string newLicense) : MotorVehicle(tickets, newMake, newLicense)
	    {
            bodyStyle = sedanOrCoup;
        }

        // here we are demonstrating polymorphism as we have two functions (both constructors for our Car class)
        // and the second constructor here is given in the instance where we do not know if the car is a Sedan or a Coup
         Car(int tickets, string newMake, string newLicense) : MotorVehicle(tickets, newMake, newLicense)
	    {
            bodyStyle = "body style unknown";
        }



        // this print function will be called in our main function
        // used to print out the data member values of car objects
        void print()
        {
            cout << "This is a car -> " << "Car body style: " << return_bodyStyle()  << " | Tickets: "  << return_tickets() << " | Make: " << return_make() << " | License: " << return_license() << endl;
        }

};

// this is a subclass/child class of MotorVehicle called Truck
class Truck : public MotorVehicle 
{

        // here we have a child class constructor calling our base class constructor from MotorVehicle
    public:
        
        Truck(int tickets, string newMake, string newLicense) : MotorVehicle(tickets, newMake, newLicense)
    	{
        }

        // this print function will be called in our main function
        // used to print out the data member values of truck objects
        void print()
        {
            cout << "This is a truck ->" << " Tickets: "  << return_tickets() << " | Make: " << return_make() << " | License: " << return_license() << endl;
        }
};


int main (){

        // The below illustrates how we can store different (but related) objects (Cars and Trucks) in a single vector
        // These will be on the heap memory, so we must take care to clean up when we are done
         vector<MotorVehicle*> database;

        ///// Here we are dynamically creating a bunch of database records to store in our vector
        //representing a bunch of cars and trucks that have tickets.
        // this is calling our second car constructor as we do not know if the car is a sedan or a coup
        database.push_back((MotorVehicle*)new Car(100,"Toyota","abc-123"));
        // this is calling the first car constructor as we know that the car object has bodyStyle sedan
        database.push_back((MotorVehicle*)new Car("Sedan",20,"Buick","pdq-xyz"));
        // here we are creating a truck object and storing it into our database vector
        database.push_back((MotorVehicle*)new Truck(50,"Ford","987A xHx"));


        // Print number of vehicles in data base:
        cout << "Number of vehicle records in database: " << database.size() << endl;

        // Print out all of the motor vehicles using class specific print function
        // here we are using polymorphism as the correct print function is being called based on whether the object is a Car or a Truck
        for(size_t record=0; record<database.size(); ++record)
        {
                database[record]->print();
        }


        // Cleanup when your are done (free dynamically allocated memory)
        for(size_t record=0; record < database.size(); ++record)
        {
                delete database[record];
        }

}
