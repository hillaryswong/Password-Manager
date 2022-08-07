#ifndef PASSWORD_CLASS_H
#define PASSWORD_CLASS_H
#include <iostream>
#include <string>
#include <iomanip>
#include "PasswordClass.h"
using namespace std;

//add node to end of list or create list
void PasswordList::appendNode(string orgName, string pwData, string userData) {
  
  PasswordNode *newNode;
  PasswordNode *ptrNode;

  newNode = new PasswordNode;
  newNode->org = orgName;
  newNode->pw = pwData;
  newNode->user = userData;

  if (!head) { //if list empty, store node as head
    head = newNode;
  }
  else { // store new node at end of list
    ptrNode = head;
    while(ptrNode->next) {
      ptrNode = ptrNode->next;
    }
    ptrNode->next = newNode;
  }
}

//delete individual nodes that match organization name
void PasswordList::deleteNode(string searchOrg) {

  PasswordNode *previous;
  PasswordNode *ptrNode;

  //check if the head of the list is equal
  ptrNode = head;
  previous = nullptr;
  if (ptrNode->org == searchOrg) {
    delete ptrNode;
    return;
  }
  else if (ptrNode->next != nullptr) {
    previous = ptrNode;
    ptrNode = ptrNode->next;
    while (ptrNode) {
      if (ptrNode->org == searchOrg) {
        //link the previous to this ptrNode's next
        if (ptrNode->next != nullptr) {
          previous->next = ptrNode->next;
          delete ptrNode;
          return;
        }
        else { //if it's at the end of list
          previous->next = nullptr;
          delete ptrNode->next;
          return;
        }
      }
      else {
        previous = ptrNode;
        ptrNode = ptrNode->next;
      }
    }
  }
}

//display all nodes in the list
void PasswordList::displayList(){

  PasswordList::PasswordNode *ptrNode;
  ptrNode = head;
  while (ptrNode) {
    cout << ptrNode->org << " " << ptrNode->user << " " << ptrNode->pw << endl;
    if(ptrNode->next) {
      ptrNode = ptrNode->next;
    }
    else {
      break;
    }
  }
}

#endif