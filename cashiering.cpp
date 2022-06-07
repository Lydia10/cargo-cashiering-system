#include <iostream>
#include <iomanip>
#include <cctype>
#include <string>
#include <ctime>
#include <vector>
using namespace std;

// Function prototypes
void containerNumber(int &);
int getDimensionsAndVolume();
int calculateVolume(int, int, int);
double calculateShippingCost(int);
double calculateDeliveryCost(int);
double addAnotherPackage(double, double);
void calculateTotalCost(double);
void displayCurrentDate();

// global variables to keep track of the total number of packages
int containerNum = 0;

//Global vectors to store each package's volume, shipping cost, and delivery fee
vector<int> volumeRecord;
vector<double> shippingCostRecord;
vector<double> deliveryFee;


int main(){
  // Display company information and ask for customer's name
  cout << "****East County Cargo Transport****\n\n";
  cout << "Cashiering system 2.0\n";
  cout << "Starting Transactions - date - ";
  displayCurrentDate();
  cout << "\n\nStarting at Transaction #1" << endl << endl;
  cout << "Start in Customer(y/n):";

  string answer, name;

  getline(cin, answer);
  if(answer == "y" || answer == "Y"){
    cout << "\nEnter customer's name: ";
    getline(cin, name);
  }

  cout << "\nCustomer - " << name << endl << endl;

  int volume = getDimensionsAndVolume();
  volumeRecord.push_back(volume);

  double singlePackageCost = calculateShippingCost(volume);
  shippingCostRecord.push_back(singlePackageCost);

  double deliveryCost = calculateDeliveryCost(volume);
  deliveryFee.push_back(deliveryCost);

  double allPackagesCost = addAnotherPackage(singlePackageCost, deliveryCost);

  cout << "\n\n\nEast County Cargo Transport" << endl << endl;
  cout << "123 First Street\nEl Cajon, CA 92071\n\nCustomer Receipt\n\n";
  cout << "Customer Name: " << name << endl << endl;

  for (int index = 0; index < containerNum; index++){
    cout << "Container #" << index + 1  << " - " << volumeRecord.at(index) << " cu ft" << setw(38) << shippingCostRecord.at(index) << endl;
    cout << "Shipping:" << setw(52) << deliveryFee.at(index) << endl << endl;
  }
  calculateTotalCost(allPackagesCost);
  return 0;
}

// keep a total of container numbers
void containerNumber(int &num){
  num++;
}
// get dimensions from the user and calculate the volume
int getDimensionsAndVolume(){
  int length, width, height, volume;
  const int MAX_VOLUME = 65;
  bool isTrue = true;

  containerNumber(containerNum);

  while(isTrue){
    cout << "Enter dimensions for container #" << containerNum << "(in feet):\nHeight: ";
    cin >> height;
    cout << "\nLength: ";
    cin >> length;
    cout << "\nWidth: ";
    cin >> width;

    // Call the calculateVolume function
    volume = calculateVolume(length, width, height);

    // Display the volume
    cout << "\nVolume of container #" << containerNum << " is " << volume << " cu ft";

    // Validate the volume
    if(volume > MAX_VOLUME){
      cout << "\nPackages cannot be larger than 65 cubic feet. Please enter valid dimensions." << endl;
    }
    else{
      isTrue = false;
    }
  }
  return volume;
}

// Calculate volume
int calculateVolume(int length, int width, int height){
  int vol = length * width * height;
  return vol;
}

// Calculate the shipping cost according to different volumes
double calculateShippingCost(int vol){
  double shippingCost;
  int SMALL_SIZE = 15, LARGE_SIZE = 45;
  const double SMALL_SIZE_PRICE = 1.50, MEDIUM_SIZE_PRICE = 2.50, LARGE_SIZE_PRICE = 3.00;
  cout << setprecision(2) << fixed;

  if( vol < SMALL_SIZE){
    shippingCost = vol * SMALL_SIZE_PRICE;
    cout << "\nSmall Package ($1.50 per cu ft): $" << shippingCost << endl;
  }
  else if(vol <= LARGE_SIZE ){
    shippingCost = vol * MEDIUM_SIZE_PRICE;
    cout << "\nMedium Package ($2.50 per cu ft): $" << shippingCost << endl;
  }
  else{
    shippingCost = vol * LARGE_SIZE_PRICE;
    cout << "\nLarge Package ($3.00 per cu ft): $" << shippingCost << endl;
  }
  return shippingCost;
}

double calculateDeliveryCost(int vol){
  //Delivery options
  cout << "\nHow is this container to be shipped:" << endl << endl;
  cout << "(1) Standard-(one to two weeks)- No change to the price" << endl;
  cout << "(2) Fast Ground - (3 to 5 business days) - Extra $1.50 per cubic foot" << endl;
  cout << "(3) Air - (1 to 2 business days) - Only applies to packages under 30 cubic feet "
    "- Extra $3.00 per cubic foot" << endl << endl;
  cout << "\nDelivery: ";
  string choice;
  cin >> choice;
  double deliveryCost;

  if(vol >= 30 && choice == "3"){
    cout << "Air delivery only applies to packages under 30 cubic feet." << endl;
    cout << "Please choose standard shipping or fast ground shipping: ";
    cin >> choice;
  }


  if(choice == "1"){
    deliveryCost = 0.00;
    cout << "\nStandard: $" << deliveryCost;
  }
  else if(choice == "2"){
    deliveryCost = vol * 1.50;
    cout << "\nFast Ground ($1.50 per cu ft): $" << deliveryCost;
  }
  else if(choice == "3"){
    deliveryCost = vol * 3.00;
    cout << "\nAir ($3.00 per cu ft): $" << deliveryCost;
  }
  return deliveryCost;
}

//ask the user if he/she wants to add another package and calculate all packages' shipping cost
double addAnotherPackage(double cost, double fee){
  char answer;
  double allPackagesCost = cost + fee;
  while(true){
    cout << "\n\nAdd another package(Y/N): ";
    cin >> answer;
    cout << endl;
    if(answer == 'Y' || answer == 'y'){
      int vol = getDimensionsAndVolume();
      volumeRecord.push_back(vol);
      double shippingCost = calculateShippingCost(vol);
      shippingCostRecord.push_back(shippingCost);
      double deliveryCost = calculateDeliveryCost(vol);
      deliveryFee.push_back(deliveryCost);
      allPackagesCost = shippingCost + deliveryCost + allPackagesCost;
    }
    else
      break;
  }
  return allPackagesCost;
}

//calculate the total cost(including tax)
void calculateTotalCost(double cost){
  const double SALES_TAX = 0.0775;
  double tax = cost * SALES_TAX;
  double total = cost + tax;
  cout << "SubTotal" << setw(53) << cost << endl;
  cout << "Sales Tax - 7.75%" << setw(44) << tax << "\n\n";
  cout << "Total" << setw(56) << total << endl << endl;
}

//Display date
void displayCurrentDate(){
  time_t now = time(0);
  tm *date = localtime(&now);
  cout << (date->tm_mon)+1 << "/" << (date->tm_mday) << "/" << (date->tm_year)+1900 << endl;
}


