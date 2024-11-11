#ifndef SEPARATE_CHAINING_H
#define SEPARATE_CHAINING_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <functional>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

template <typename HashedObj>
class ChainingHash
{
  public:
    explicit ChainingHash( int size = 101 ) : currentSize{ 0 }
      { theLists.resize( 101 ); }

    bool contains( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.9 in textbook
        auto & whichList = theLists[myhash(x)];
        return find(begin(whichList),end(whichList),x)!=end(whichList);
    }

    void makeEmpty( )
    {
        // TODO: refer to Figure 5.9 in textbook
        for(auto & thisList: theLists){
            thisList.clear();
        }
    }

    bool insert( const HashedObj & x )
    {
        // TODO: refer to Figure 5.10 in textbook
        // this "insert" function accepts Lvalues
        auto & whichList = theLists[myhash(x)];
        if(find(begin(whichList),end(whichList),x)!=end(whichList)){
            return false;
        }
        whichList.push_back(x);

        //rehash
        if(++currentSize> theLists.size()){
            rehash();
        }
        return true;
    }
    
    bool insert( HashedObj && x )
    {
        // TODO: this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
        auto & whichList = theLists[myhash(x)];
        if(find(begin(whichList),end(whichList),std::move(x))!=end(whichList)){
            return false;
        }
        whichList.push_back(std::move(x));

        //rehash
        if(++currentSize> theLists.size()){
            rehash();
        }
        return true;
    }

    bool remove( const HashedObj & x )
    {
        // TODO: refer to Figure 5.9 in textbook
        auto & whichList = theLists[myhash(x)];
        auto itr = find(begin(whichList),end(whichList),x);

        if(itr==end(whichList)){
            return false;
        }
        whichList.erase(itr);
        --currentSize;
        return true;
    }

    double readLoadFactor() 
    {
        return loadFactor();
    }

    double readCurrentSize() 
    {
        return currentSize;
    }

    double readArraySize() 
    {
        return theLists.size();
    }

  private:
    vector<list<HashedObj>> theLists;   // The array of Lists
    int currentSize;

    void rehash( )
    {
        // TODO: refer to Figure 5.22 in textbook
        vector<list<HashedObj>>oldLists = theLists;

        //create a new double-sided empty table
        theLists.resize(nextPrime(2*theLists.size()));
        for(auto & thisList: theLists){
            thisList.clear();
        }

        //copy table
        currentSize = 0;
        for(auto & thisList: oldLists){
            for(auto & x: thisList){
                insert(std::move(x));
            }
        }
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % theLists.size( );
    }

    double loadFactor()
    {
        // TODO: compute the load factor of hash table, defined on Page 198 of textbook
        return readCurrentSize()/readArraySize();
    }
};

#endif
