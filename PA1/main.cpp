/*
ADVANTAGES/DISADVANTAGES LINKED LIST
One advantage of using a linked list is that they don't use additional/unused memory to store elements. 
Elements added/removed get their memory allocated/deallocated when the element leaves the scope


One disadvantage of using a linked list is that you cannot access every element of the list at once and have to access
each element one at a time and to find an element you have to iterate through the list
ADVANTAGES/DISADVANTAGES ARRAY
One advantage of using an array is that you have access to all elements of the array at any time and can which has better
time complexity than using a linked list or another dynamic memory structure.

One disadvantage of using an array is that they are a fixed size which can waste space and may lack space to hold many elements
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <limits>
#include <string.h>
#include "linkedList.hpp"
#include "array.h"
#include <vector>

using namespace std;


int main()
{

    string userName, newCommandToAdd, newDescriptionToAdd,oldCommandTodelete;
    int selection;
    LinkedList<string,string>list;
    Array<std::string,int> profile;
    ArrayNode<std::string,int>* players = profile.getList();
    list.loadFromFile();
    //list.printList();
    while (true)
    {
        cout << "Please select an option listed below:\n";
        cout << "1. Game Rules\n2. Play Game\n3. Load Previous Game\n4. Add Command\n5. Remove Command\n6. Exit\n";
        cout << "Your selection: ";
        cin >> selection;     
        if (cin.fail()) // the input is not an integer
        {
            cout << "Your selection is invalid. Please select again." << endl;
            cout << "=============================================================================" << endl << endl;
            cin.clear();
            cin.ignore();
        }
        else
        {
            switch (selection)
            {
                case 1: // Game Rules
                {
                    cout << "================================= Game Rule ===================================" << endl;
                    cout << "To play the game, select \"2\" where you will be prompted for your name and number of questions.\n";
                    cout << "Each question presents a specific Linux command where you will be able to choose from 3 different options. Each correct answer yields a point.\n";
                    cout << "You can also add and delete commands as needed.\n";
                    cout << "================================= Game Rule ===================================" << endl << endl;
                    
                    break;
                }

                case 2: case 3: // 2. Play Game; 3. Load Previous Game
                {
                    bool returningPlayer = false;
                    int points = 0, numQuestions=0, playerIndex=0;
                    
                    cout << "Please enter your name: ";
                    cin >> userName;
                    for(int i =0; i <profile.getSize();i++){
                        if(players[i].getName()==userName){
                            returningPlayer = true;
                            points = players[i].getPoints();
                            playerIndex=i;
                        }
                    }
                    if((selection==3)&&!returningPlayer){
                        cout << "Existing player '" <<userName << "' not found. Creating new data for player" << endl;
                    }
                    while(numQuestions <5 || numQuestions >30){
                        cin.clear();
                        cin.ignore();
                        cout <<endl << "Please select how many questions you would like to be asked (5-30): ";
                        cin >> numQuestions;
                        cout << endl;
                    }
                    cout << endl << endl << endl;
                    
                    for(int i = 0; i < numQuestions;i++){
                        int guess=0;
                        int correctAnswer = ((rand()%3)+1);
                        Node<string,string>* randomCorrect = list.selectRandom();

                        vector<string>takenCommands;
                        takenCommands.push_back(randomCorrect->getCommand());
                        bool used;
                        cout << randomCorrect->getCommand() <<endl;
                        for(int j=1;j<=3;j++){
                            if(j==correctAnswer){
                                cout << j <<". " << randomCorrect->getDescription() <<endl;
                            }
                            else{
                                Node<string,string>* randomIncorrect = list.selectRandom();
                                do{
                                    used=false;
                                    randomIncorrect=list.selectRandom();
                                    for(string command: takenCommands){
                                        if(randomIncorrect->getCommand()==command){
                                            used=true;
                                            break;
                                        }
                                    }
                                }while(used);
                                takenCommands.push_back(randomIncorrect->getCommand());
                                cout << j << ". " << randomIncorrect->getDescription() <<endl;
                            }
                        }
                        cout << "Select which option matches the command: ";
                        cin >> guess;
                        cin.clear();
                        cin.ignore();
                        if(guess==correctAnswer){
                            points+=1;
                            cout <<"Correct. You have been awarded 1 point! Your point total is " << points <<endl<<endl;
                        }
                        else{
                            points -=1;
                            cout <<"Womp womp. You have lost 1 point. Your point total is " <<points <<endl<<endl;
                        }
                    }
                    cout <<"Game over. Player '" << userName << "' has " <<points <<" points." <<endl;
                    if(returningPlayer){
                        players[playerIndex].setPoints(points);
                    }
                    else{
                        profile.insertAtFront(userName,points);
                    }
                    break;
                }

                case 4: // Add Command
                {
                    cin.clear();
                    cin.ignore();
                    cout << "To add a command to the library, please enter the command name that you would add: ";
                    std::getline(cin,newCommandToAdd);
                    //cout << newCommandToAdd << endl;
                    //check if command is a duplicate
                    Node<std::string,std::string>*pCur=list.getpHead();
                    while(pCur!=nullptr){
                        if(pCur->getCommand()==newCommandToAdd){
                            cout << "Error! Command already exists: '" <<pCur->getCommand()<<"'" <<std::endl;
                            break;
                        }
                        pCur=pCur->getpNext();
                    }
                    if(pCur==nullptr){
                        cout << "Write the description for the command: ";
                        cin.clear();
                        std::getline(cin,newDescriptionToAdd);
                       
                       // cout << newDescriptionToAdd << endl;
                        newDescriptionToAdd = '\"' + newDescriptionToAdd + '\"';
                        list.insertAtFront(newCommandToAdd,newDescriptionToAdd);
                        list.printList();
                        
                    }
                    break;
                }

                case 5: // Remove Command
                {
                    cout << "Please enter the name of the command that you would remove: ";
                    cin.clear();
                    cin.ignore();
                    std::getline(cin,oldCommandTodelete);
                    list.removeNode(oldCommandTodelete);
                    break;
                }
                    
                case 6: // Exit
                {
                    list.exportList();
                    profile.exportProfiles();
                    return 0;
                }


            } // end of switch(selection)
        } // end of else: check (cin.fail())
        
    } // end of while(true)
} // end of int main()

