#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "PasswordClass.h"
#include <sstream>
using namespace std;


void CheckFileOpen(fstream fileName);
void LoadLinkedList(PasswordList &, ifstream&);
void LoadTextFile(PasswordList, ofstream&);
PasswordList::PasswordNode* SearchList(PasswordList, string org);
void PresentMenu();
void ProcessInput(int userInput, PasswordList &);

int main() {
  PasswordList passwordData;
  const string PW_HOLDER_TEXT = "passwordstorage.txt";
  ifstream file;
  ofstream outputFile;
  file.open(PW_HOLDER_TEXT);
  
  //first load all contents from file into linked list
  LoadLinkedList(passwordData, file);
  
  //display menu and process user's choice
  PresentMenu();
  int userInput;
  string orgName;
  cin >> userInput; 
  ProcessInput(userInput, passwordData);
  
  //Load contents of linked list onto passwordstorage.txt file
  outputFile.open(PW_HOLDER_TEXT);
  LoadTextFile(passwordData, outputFile);
  cout << "Success! Exiting Now." << endl;
  exit(EXIT_SUCCESS);
}

void PresentMenu() {
  cout << endl << "Welcome to your password manager!" << endl;
  cout << "----------------------MENU--------------------" << endl;
  cout << "Please enter number of operation you'd like to perform" << endl;
  cout << "(1) Retrieve Password" << endl;
  cout << "(2) Update Password" << endl;
  cout << "(3) Delete Password" << endl;
  cout << "(4) Add Password" << endl;
  cout << "(5) Exit Program" << endl << endl;
}

void ProcessInput(int userInput, PasswordList &passwordData) {
  string orgName;
  int newInput;
  PasswordList::PasswordNode* node;
  switch (userInput) {
    case 1: {//Retrieving Password
      cout << "Enter name of organization: ";
      cin >> orgName;
      cout << endl << "Retrieving Password..." << endl;
      //find match org in passwordlist
      node = SearchList(passwordData, orgName);
      cout << "Password for " << orgName << ": " << node->pw << endl;
      cout << "Returning to menu..." << endl;
      PresentMenu();
      cin >> newInput;
      ProcessInput(newInput, passwordData);
      break;
      }
    case 2: { //Update Password
      string newPw;
      cout << "Enter name of organization: ";
      cin >> orgName;
      cout << endl << "Retrieving Password..." << endl;
      node = SearchList(passwordData, orgName);
      cout << "Password for " << orgName << ": " << node->pw << endl;
      cout << "Enter new password: ";
      cin >> newPw;
      node->pw = newPw;
      cout << "Changing Password..." << endl << "The new password for " << orgName << " is " << node->pw << endl;
      cout << "Success! Returning to menu..." << endl;
      PresentMenu();
      cin >> newInput;
      ProcessInput(newInput, passwordData);
      break;
    }
    case 3: { //Delete Password
      char userInput;
      cout << "Enter name of organization: ";
      cin >> orgName;
      node = SearchList(passwordData, orgName);
      cout << "Password Found. Are you sure you'd like to delete this password? (Y/N) ";
      cin >> userInput;
      if ((userInput == 'Y') || (userInput == 'y')){
        passwordData.deleteNode(orgName);
        cout << "The password has been deleted." << endl;
        cout << "Returning to menu..." << endl;
        PresentMenu();
        cin >> newInput;
        ProcessInput(newInput, passwordData);
      } 
      else if ((userInput == 'N') || (userInput == 'n')){
        cout << "Operation dismissed." << endl;
        cout << "Returning to menu..." << endl;
        PresentMenu();
        cin >> newInput;
        ProcessInput(newInput, passwordData);
      }
      else {
        cout << "Invalid input. Password not deleted. Returning to menu." << endl;
        PresentMenu();
        cin >> newInput;
        ProcessInput(newInput, passwordData);
      }
      break;
    }
    case 4: { //Add Password
      char userInput;
      string newPw;
      string newUsername;
      cout << "Enter name of organization: ";
      cin >> orgName;
      cout << "Enter username: ";
      cin >> newUsername;
      cout << "Enter password: ";
      cin >> newPw;
      cout << "Is this entry correct? (Y/N)" << endl <<
        "Organization: " << orgName << endl <<
        "Username: " << newUsername << endl << 
        "Password: " << newPw << endl;
      cin >> userInput;
      if(userInput == 'Y' || userInput == 'y'){
        passwordData.appendNode(orgName, newPw, newUsername);
      }
      else if (userInput == 'N' || userInput == 'n') {
        cout << "Password not added. Returning to menu." << endl;
      }
      else {
        cout << "Invalid entry. Returning to menu." << endl;
        PresentMenu();
        cin >> newInput;
        ProcessInput(newInput, passwordData);
      }
      break;
    }
    case 5: { //exit program
      cout << "Ending Program." << endl;
      return;
      break;
    }
    default: { //invalid input
      cout << "Error: Invalid Input" << endl;
      cout << "Please try again." << endl;
      PresentMenu();
      cin >> newInput;
      ProcessInput(newInput, passwordData);
    }
  }
}

void CheckFileOpen(ifstream &file) {
  if (file.fail()) {
    cout << "The file/passwords could not be accessed." << endl;
    exit(EXIT_FAILURE);
  }
}

//create linked list with text file data
void LoadLinkedList(PasswordList &passwords, ifstream &file) {

  string data;
  string orgData;
  string userData;
  string passwordData;
  CheckFileOpen(file);
  while (!(file.eof())) {
    file >> data;
    istringstream fileLine(data);
    getline(fileLine, orgData, ',');
    getline(fileLine, userData, ',');
    getline(fileLine, passwordData);
    passwords.appendNode(orgData, passwordData, userData);
  };
  file.close();
  
  return;
}

//load all contents of linked list into an output to store
void LoadTextFile(PasswordList passwords, ofstream& file) {
  PasswordList::PasswordNode *ptrNode;
  ptrNode = passwords.head;
  while (ptrNode->next) {
    file << ptrNode->org << "," << ptrNode->user << "," << ptrNode->pw << endl;
    ptrNode = ptrNode->next;
  }
  file << ptrNode->org << "," << ptrNode->user << "," << ptrNode->pw;
  file.close();
}

//find node in linked list using the organization name
PasswordList::PasswordNode* SearchList(PasswordList list, string searchOrg) {
  int newInput;
  PasswordList::PasswordNode* searchNode;
  searchNode = list.head;

  while (searchNode->org != searchOrg) {
    if(searchNode->next) {
      searchNode = searchNode->next;
    }
    else { //if it's the last node in the list
      cout << "Could not find any passwords with matching organizations." << endl;
      cout << "Returning to menu..." << endl;
      PresentMenu();
      cin >> newInput;
      ProcessInput(newInput, list);
    }
  }
  return searchNode;
}