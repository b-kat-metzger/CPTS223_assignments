#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

using std::ifstream;



// Template class: the node in the linked list
template <typename T1, typename T2>
class Node {
public:
    Node() : mpNext(nullptr),mCommand{}, mDescription{}{}
    Node(T1 command, T2 description);
    void setCommand(const T1 newCommand);
    void setDescription(const T2 newDescription);
    void setpNext( Node<T1,T2>* newNode);

    T1 getCommand() const;
    T2 getDescription() const;
    Node<T1,T2>* getpNext()const;
private:
    T1 mCommand;
    T2 mDescription;
    Node<T1,T2>* mpNext;
};

// Define the linked list class
template <typename T1, typename T2>
class LinkedList {
    public:
    LinkedList():mpHead(nullptr){}
    ~LinkedList();
    LinkedList(const LinkedList<T1,T2>&c);
    void insertAtFront(T1 newCommand, T2 newDescription);

    void loadFromFile();
    void printList();
    Node<T1,T2>* makeNode(T1 newCommand,T2 newDescription);
    Node<T1,T2>* removeNode(T1 command);
    void setpHead(Node<T1,T2>* newNode);
    Node<T1,T2>* getpHead()const;
    Node<T1,T2>* selectRandom();
    void exportList();

    private:
    Node<T1,T2>* mpHead;


};


#include "linkedList.hpp"


template <typename T1, typename T2>
inline Node<T1,T2>::Node(T1 command, T2 description){
    mCommand = command;
    mDescription = description;
}

template <typename T1, typename T2>
void Node<T1, T2>::setCommand(const T1 newCommand)
{
    mCommand = newCommand;
}

template <typename T1, typename T2>
void Node<T1, T2>::setDescription(const T2 newDescription)
{
    mDescription = newDescription;
}

template <typename T1, typename T2>
void Node<T1, T2>::setpNext(Node<T1,T2> *newNode)
{
    mpNext = newNode;
}

template <typename T1, typename T2>
T1 Node<T1, T2>::getCommand() const
{
    return mCommand;
}

template <typename T1, typename T2>
Node<T1, T2> *Node<T1, T2>::getpNext() const
{
    return mpNext;
}

template <typename T1, typename T2>
T2 Node<T1, T2>::getDescription() const
{
    return mDescription;
}

template<typename T1, typename T2>
inline LinkedList<T1,T2>::~LinkedList(){
    Node<T1,T2>* pCur = mpHead;
    while(pCur!=nullptr){
        Node<T1,T2>* temp = pCur;
        pCur=pCur->getpNext();
        delete(temp);
    }
}

template <typename T1, typename T2>
LinkedList<T1, T2>::LinkedList(const LinkedList<T1, T2> &c)
{
    Node<T1,T2>* pMem = nullptr, *pCur = c.getpHead(), *pPrev = nullptr;
    while(pCur!=nullptr){
        T1 newCommand = *(pCur->getCommand());
        T2 newDescription = *(pCur->getDescription());
        pMem = new Node<T1,T2>(newCommand, newDescription);
        if(pPrev==nullptr){
            mpHead=pMem;
        }
        else{
            pPrev->setpNext(pMem);
        }
        pCur=pCur->getpNext();
        pPrev=pMem;
    }
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::insertAtFront(T1 newCommand, T2 newDescription)
{
    Node<T1,T2>*pMem=makeNode(newCommand, newDescription);
    if(pMem!=nullptr){
        pMem->setpNext(mpHead);
        mpHead=pMem;
    }
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::loadFromFile()
{
    ifstream FILE("commands.csv");
    if(!FILE.is_open()){
        std::cout << "Could not open file" <<std::endl;
        return;
    }
    T1 newCommand;
    T1 newDescription;
    std::string temp;
   while(std::getline(FILE,temp,',')){
        newCommand=temp;
        std::getline(FILE,temp,'\n');
        newDescription=temp;
        this->insertAtFront(newCommand,newDescription);
   
    }
    std::cout << "'commands.csv' successfully loaded into list" <<std::endl;
    FILE.close();
}

template <typename T1, typename T2>
void LinkedList<T1, T2>::printList()
{
    Node<T1,T2>* pCur=mpHead;
    while(pCur!=nullptr){
        std::cout << pCur->getCommand() << ": " << pCur->getDescription() << std::endl;
        pCur=pCur->getpNext();
    }
}

template <typename T1, typename T2>
Node<T1, T2> *LinkedList<T1, T2>::makeNode(T1 newCommand, T2 newDescription)
{
    Node<T1,T2>* pMem= new Node<T1,T2>(newCommand,newDescription);
    return pMem;
}

template <typename T1, typename T2>
Node<T1, T2> *LinkedList<T1, T2>::removeNode(T1 command)
{
    Node<T1,T2>* pCur = mpHead, *pPrev = nullptr;
        while(pCur!=nullptr){
        if((pCur->getCommand())==(command)){
            if(pPrev==nullptr){
                mpHead=pCur->getpNext();
                
            }
            else{
                pPrev->setpNext(pCur->getpNext());
            }
            delete pCur;
            std::cout << "Command removed: '" <<command <<"'"<<std::endl<<std::endl;
            return mpHead;
           
        }
       
        pPrev=pCur;
        pCur=pCur->getpNext();
    }
    std::cout << "Command not found. No command removed."<<std::endl;
    return nullptr;
}

template <typename T1, typename T2>
inline Node<T1, T2> *LinkedList<T1, T2>::getpHead() const
{
    return mpHead;
}

template <typename T1, typename T2>
inline Node<T1, T2> *LinkedList<T1, T2>::selectRandom()
{
    if(mpHead==nullptr){
        return nullptr;
    }
    srand(time(NULL));
    int randIndex = 0;
    randIndex = (rand()% 30);
    Node<T1,T2>* pCur=mpHead;
    for(int i = 0; i< randIndex;i++){
        pCur=pCur->getpNext();
    }
    return pCur;
    if(pCur==nullptr){
            std::cout << "Error: Random node selected from commands list" <<std::endl;
            return nullptr;
        }
    return nullptr;
}

template <typename T1, typename T2>
inline void LinkedList<T1, T2>::exportList()
{
    std::ofstream FILE("commands.csv");
    Node<T1,T2>* pCur=mpHead;
    while(pCur!=nullptr){
        FILE << pCur->getCommand()<<"," <<pCur->getDescription();
        if(pCur->getpNext()!=nullptr){
            FILE << std::endl;
        }
        pCur=pCur->getpNext();
    }
    FILE.close();
}
