
#include <stdlib.h>
#include <array>
#include <iostream>
#include <fstream>
#include <time.h>
template <typename T1, typename T2>
class ArrayNode {
public:
    ArrayNode():mName{},mPoints{}{}
    ArrayNode(T1 newName, T2 newPoints):mName(newName),mPoints(newPoints){}
    T1 getName()const{return mName;}
    T2 getPoints()const{return mPoints;}

    void setName(const T1 newName){mName=newName;}
    void setPoints(const T2 newPoints){mPoints=newPoints;}


private:
    T1 mName;
    T2 mPoints;
};


template <typename T1, typename T2>
class Array {
public:
    Array();
    ~Array();
    ArrayNode<T1,T2>* getList(){return mList;}
    int getSize()const{return mSize;}
    int getMaxSize()const{return maxSize;}
    void insertAtFront(T1 newName, T2 newPoints);
    ArrayNode<T1,T2>* makeNode(T1 newName, T2 newPoints);
    void setSize(const int newSize){mSize=newSize;}
    void setMaxSize(const int newMaxSize){maxSize=newMaxSize;}
    void displayProfiles();
    void exportProfiles();
private:
    ArrayNode<T1,T2>* mList;
    int mSize;
    int maxSize;

};

template <typename T1, typename T2>
inline Array<T1, T2>::Array()
{
    mSize=0;
    maxSize=150;    
    mList =new ArrayNode<T1,T2>[maxSize];
    std::ifstream FILE("profiles.csv");
    if(!FILE.is_open()){
        std::cout << "Error opening file: 'profiles.csv'" << std::endl;
        return;
    }
    T1 name;
    T2 points;
    std::string temp;
    
    while(std::getline(FILE,temp,',')){
        name=temp;
        std::getline(FILE,temp,'\n');
        points=atoi(temp.c_str());
        insertAtFront(name,points);
        mSize++;
        }
    
    std::cout << "'profiles.csv' successfully loaded '"<<getSize()<<" profiles'" << std::endl;
    //displayProfiles();
    FILE.close();
}

template <typename T1, typename T2>
inline Array<T1, T2>::~Array()
{
    delete[] mList;
}

template <typename T1, typename T2>
inline void Array<T1, T2>::insertAtFront(T1 newName, T2 newPoints)
{
    if(mSize>=maxSize){
        std::cout << "Cannot insert new profile, array is full." <<std::endl;
        return;
    }
    for(int i=mSize;i>0;i--){
        mList[i]=mList[i-1];
    }
    ArrayNode<T1,T2>*newNode = makeNode(newName,newPoints);
    mList[0]=*newNode;
    this->setSize(getSize()+1);
    delete(newNode);
}

template <typename T1, typename T2>
inline ArrayNode<T1, T2> *Array<T1, T2>::makeNode(T1 newName, T2 newPoints)
{
    ArrayNode<T1,T2>* node = new ArrayNode<T1,T2>(newName,newPoints);
    return node;
}

template <typename T1, typename T2>
inline void Array<T1, T2>::displayProfiles()
{
    for(int i = 0; i < getSize();i++){
        std::cout << mList[i].getName() << ": " << mList[i].getPoints() << " points" << std::endl;
    }
}

template <typename T1, typename T2>
inline void Array<T1, T2>::exportProfiles()
{
    std::ofstream FILE("profiles.csv");
    ArrayNode<T1,T2>*players = this->getList();
    for(int i = 0; i < this->getSize();i++){
        FILE << players[i].getName()<<", "<<players[i].getPoints();
        if(i<getSize()-1){
            FILE << std::endl;
        }
    }
    FILE.close();
}
