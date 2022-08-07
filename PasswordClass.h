#include <string>
using namespace std;

class PasswordList {
  public:
    struct PasswordNode {
      string pw;
      string org;
      string user;
      struct PasswordNode *next;
    };
    PasswordNode *head;

  public:
    //Constructor!
    PasswordList() {
      head = nullptr;
    }
    ~PasswordList() {
      //delete all the data if node gets 
    }
    void appendNode(string org, string pw, string user); //add node to list
    void deleteNode(string org); // delete node from list
    bool editUser(string org, string newUser); // edit the username
    bool editPassword(string org, string newPw); //edit the password
    void displayNode(string org); //display all contents of node
    void displayList(); // display all nodes and contents
    struct PasswordNode findMatchingNode(string org);
};