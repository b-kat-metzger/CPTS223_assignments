#include <map>
#include <unordered_map>
#include "generateUsers.hpp"
using namespace std;


map<string, User> buildMapByUserName(vector<User> users) {
    map<string, User> usersMap;
    //cout << "TODO" << endl;
    while(users.size()>0){
        string uName = users.back().userName;
        usersMap.insert(pair<string ,User>(uName,users.back()));
        users.pop_back();   
    }
    

    return usersMap;
}


map<string, User> buildMapByEmail(vector<User> users) {
    map<string, User> usersMap;
    //cout << "TODO" << endl;
    while(users.size()>0){
        string uEmail= users.back().email;
        usersMap.insert(pair<string,User>(uEmail,users.back()));
        users.pop_back();
    }

    return usersMap;
}


void printMap(map<string, User> aMap) {
    //cout << "TODO" << endl;
    for(const auto& i:aMap){
        cout << i.first << "-> ";
    }
    cout<<endl;
}


bool isMapSorted(map<string, User> aMap) {
    //cout << "TODO" << endl;
    if ( aMap.empty() )
        return true;
    map<string,User>::iterator itr = aMap.begin();
    string prev = itr->first;
    itr++;
    for(itr; itr!=aMap.end();itr++){
        if(itr->first < prev){
            return false;
        }
        prev = itr->first;
    }
    

    return true;
}


bool testSearchByKey(map<string, User> aMap, string keyToSearch) {
    //cout << "TODO" << endl;
    //key is found
    if(aMap.find(keyToSearch)!=aMap.end()||(aMap.end()->first ==keyToSearch)){
        return true;
    }
    else{
        return false;
    }
}


bool testDeleteByKey(map<string, User> aMap, string keyToDelete) {
    //cout << "TODO" << endl;
    if(aMap.empty()){
        cout << "Map is empty! Cannot remove key '" <<keyToDelete << "'"<<endl;
        return false;
    }
    aMap.erase(keyToDelete);
    //return the inverse of testSearchByKey because if it returns true, then the key still exists in the map so we did not remove it
    //if it returns false, then the key has been successfully removed and we want to return true
    return !testSearchByKey(aMap,keyToDelete);
}


void printActiveUsers(map<string, User> aMap) {
    int activeThreshold = 800;
    //cout << "TODO" << endl;
    cout << "Users with more than " <<activeThreshold << " tweets: "<<endl;
    cout << "\tUsername\tTweets" <<endl;
    for(auto const&i:aMap){
        if(i.second.numPosts > 800){
            string uName = i.first;
            if(uName.length()>12){
                uName = uName.substr(0,10);
            }
            cout << '\t' << uName << '\t' <<i.second.numPosts << endl;
        }
    }
}


void printMostPopularCategory(map<string, User> aMap) {    
    //cout << "TODO" << endl;
    unordered_map<string,int> mostViewed;
    for(const auto&i: aMap){
        mostViewed[i.second.mostViewedCategory]++;
    }
    int max = mostViewed.begin()->second;
    string mCategory = mostViewed.begin()->first;
    for(const auto&c:mostViewed){
        if(c.second>max){
            max = c.second;
            mCategory=c.first;
        }
    }
    cout << "Most popular category: " << mCategory << ". It was selected " <<max << " times. " <<endl;
}


int main()
{
    int numUsers = 10;
    vector<User> users = generateUsers(numUsers);


    cout << "Build map with username as key" << endl;
    map<string, User> mapByUserName = buildMapByUserName(users);
    if ( mapByUserName.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;


    cout << "Print \"mapByUserName\" map:" << endl;
    printMap(mapByUserName);
    cout << endl;


    string keyToSearch = "smith55";
    cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByUserName, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    string keyToDelete = "smith55";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByUserName, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    cout << "Test if map's key is sorted" << endl;
    if ( isMapSorted(mapByUserName) )
        cout << "  Order test passed!" << endl << endl;
    else
        cout << "  Order test failed!" << endl << endl;


    cout << "Print usernames with more than 800 tweets:" << endl;
    printActiveUsers(mapByUserName);
    cout << endl;

    cout << "Print the most popular category" << endl;
    printMostPopularCategory(mapByUserName);
    cout << endl;


    cout << " ============================================================================== " << endl << endl;


    cout << "Build map with username as key" << endl;
    map<string, User> mapByEmail = buildMapByEmail(users);
    if ( mapByEmail.size() == numUsers )
        cout << "  Built successfully." << endl << endl;
    else
        cout << "  Built unsuccessfully." << endl << endl;
    

    keyToSearch = "kat@gmail.com";
    cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
    if ( testSearchByKey(mapByEmail, keyToSearch) )
        cout << "  Search successfully." << endl << endl;
    else
        cout << "  Search unsuccessfully." << endl << endl;


    keyToDelete = "kat@gmail.com";
    cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
    if ( testDeleteByKey(mapByEmail, keyToDelete) )
        cout << "  Delete successfully." << endl << endl;
    else
        cout << "  Delete unsuccessfully." << endl << endl;


    return 0;
}