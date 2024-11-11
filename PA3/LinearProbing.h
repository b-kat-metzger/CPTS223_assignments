#ifndef LINEAR_PROBING_H
#define LINEAR_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include "Employee.h"
#include "utils.h"

using namespace std;

// this inplementation follows Figure 5.14 in textbook for quadratic probing
template <typename HashedObj> 
class ProbingHash
{
  public:
    explicit ProbingHash( int size = 101 ) : array( nextPrime( size ) ), currentSize{ 0 }
      { makeEmpty( ); }

    bool contains( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.16 in textbook for quadratic probing
        return isActive(findPos(x));
    }

    void makeEmpty( )
    {
        // TODO: refer to Figure 5.15 in textbook for quadratic probing
        currentSize = 0;
        for(auto & entry: array){
            entry.info = EMPTY;
        }
    }

    bool insert( const HashedObj & x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
        int currentPos = findPos(x);
        if(isActive(currentPos)){
            return false;
        }
        array[currentPos].element =x;
        array[currentPos].info=ACTIVE;

        //rehash
        if(++currentSize> array.size()/2){
            rehash();
        }
        return true;
    }
    
    bool insert( HashedObj && x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
        // this "insert" function accepts *Rvalues*
        // so needs to use "move" (slightly different from the above one)
         int currentPos = findPos(std::move(x));
        if(isActive(currentPos)){
            return false;
        }
        array[currentPos].element =std::move(x);
        array[currentPos].info=ACTIVE;

        //rehash
        if(++currentSize> array.size()/2){
            rehash();
        }
        return true;
       
    }

    bool remove( const HashedObj & x )
    {
        // TODO: refer to Figure 5.17 in textbook for quadratic probing
        //we are using lazy deletion here, array[currentPos] does not get deleted, but instead the info is set to DELETE
        int currentPos = findPos(x);
        if(!isActive(currentPos)){
            return false;
        }
        array[currentPos].info = DELETED;
        //although the memory is not physically deleted, we need to treat this element as deleted so it is not included in currentSize
        currentSize--;
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
        return array.size();
    }

    enum EntryType { ACTIVE, EMPTY, DELETED };

  private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;

        HashEntry( const HashedObj & e = HashedObj{ }, EntryType i = EMPTY )
          : element{ e }, info{ i } { }
        
        HashEntry( HashedObj && e, EntryType i = EMPTY )
          : element{ std::move( e ) }, info{ i } { }
    };
    
    vector<HashEntry> array;
    int currentSize;

    bool isActive( int currentPos ) const
      { return array[ currentPos ].info == ACTIVE; }

    int findPos( const HashedObj & x ) const
    {
        // TODO: refer to Figure 5.16 in textbook for quadratic probing,
        // we need a version of linear probing that finds the position with the linear probing resolution

        int offset =1;
        int currentPos = myhash(x);
        while(array[currentPos].info !=EMPTY&&array[currentPos].element!=x){
            currentPos+=offset;
            offset+=2;
            if(currentPos>=array.size()){
                currentPos-=array.size();
            }
        }
        return currentPos;
    }

    void rehash( )
    {
        // TODO: refer to Figure 5.22 in textbook for qudratic probing
        vector<HashEntry>oldArray = array;
        array.resize(nextPrime(2*oldArray.size()));
        for(auto & entry: array){
            entry.info = EMPTY;
        }
        //copy table
        currentSize = 0;
        for(auto & entry: oldArray){
            if(entry.info==ACTIVE){
                insert(std::move(entry.element));
            }
        }
    }

    size_t myhash( const HashedObj & x ) const
    {
        static hash<HashedObj> hf;
        return hf( x ) % array.size( );
    }


    double loadFactor()
    {
        // TODO: compute the load factor of hash table, defined on Page 198 of textbook
        return readCurrentSize()/readArraySize();
    }
};

#endif
