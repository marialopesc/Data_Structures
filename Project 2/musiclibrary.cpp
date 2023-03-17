/// TODO Update File Header
///* Header:
// * file name: musiclibrary.cpp
// * author/student: Maria Bezerra
// * netID: 676493398
// * course: CS 251 - spring 2023
// * assignment: Music Library
/// Assignment details and provided code are created and
/// owned by Adam T Koehler, PhD - Copyright 2023.
/// University of Illinois Chicago - CS 251 Spring 2023

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <cctype>



using namespace std;

// INSERTS GIVEN HELPERS CODE BELOW - DO NOT REMOVE
#include "helpers.cpp"
// INSERTS GIVEN HELPERS CODE ABOVE - DO NOT REMOVE

//
// NOTE TO STUDENTS:
// You may use the functions in the helpers file,
// but you may not modify the file or its contents in any way whatsoever.
//

//
// STUDENT CODE MAY GO BELOW THIS LINE
//


struct albumData{ //value of the map albumName
    set<string> artistName;
    set<string> songTitles;
};

//Function read the file and stores the information inside map
void readingFiles(map<string, albumData> &albumNamesMap, string remains) { //key of map is the albumName
    ifstream fileMusic(remains);
    string albumLine, nextLine; // it will hold line read from file


    if (fileMusic.is_open()) {
        while (!fileMusic.eof()) {
            albumData informationObject;

            getline(fileMusic, albumLine);
            if (albumLine.empty()) {  //last line is empty, preventing to go into an unecessary loop
                continue;
            }

            getline(fileMusic, nextLine);

            while (!fileMusic.fail() && nextLine != albumLine) {

                if (isalpha(nextLine[0])) {  //checking if first letter is a word
                    informationObject.artistName.insert(nextLine);
                }
                    //otherwise, it will store the digit starting lines as songs
                else if(isdigit(nextLine[0])){
                    informationObject.songTitles.insert(nextLine);
                }
                getline(fileMusic, nextLine);
            }
            albumNamesMap[albumLine] = informationObject;   //stores the key as albumName, and add the object the struct as a value

        }
    }
    else if (!fileMusic.is_open() && !remains.empty()){
        cout <<"Error: Could not open music library file - " << remains << endl;
    }

    fileMusic.close();


}

//This function prints the names of all albums in a map of album data, along with the names of the associated artists and songs.
void printStatsExtension(map<string, albumData> &albumNamesMap, string remains){
    albumData info;
    cout << "Your Current Music Library Includes" << endl;
    cout << "===================================" << endl;
    for (auto &x : albumNamesMap) {
        cout << x.first << endl;    //first is album Name
        for (auto &artist : x.second.artistName) {
            cout <<" " << artist << endl;
        }

        //cout << albumNamesMap[x.first].artistName << endl;
        for (auto &y: x.second.songTitles) {    //second is ......
            cout << "   " << y << endl;
        }
    }
    cout << endl;


}

//This function calculates basic statistics for a music library, such as the number of albums, unique artists,
// and unique songs, and prints them, and optionally prints more detailed statistics if the input argument indicates (-d)
void stats(map<string, albumData> &albumNamesMap, string remains){
    set<string> artistTemp;
    set<string> songTemp;


    for ( auto &x: albumNamesMap) {
        for(auto &y: x.second.artistName){ //accessing the value (second) artistName and
            // inserting inside the temp set
            artistTemp.insert(y);
        }
    }

    //for each loop to get size of totalSongs
    for ( auto &a: albumNamesMap) {
        for(auto &b: a.second.songTitles){
            songTemp.insert(b);
        }
    }
    cout << "Overall Music Library Stats" << endl;
    cout << "===========================" << endl;
    cout << "Total Records: " << albumNamesMap.size() << endl;
    cout << "Total Unique Artists: " << artistTemp.size() << endl;
    cout << "Total Songs: " << songTemp.size() << endl << endl;

    if(remains == "-d") {
        printStatsExtension(albumNamesMap, remains);
    }
}

//function that exports the current music library to txt file provided by user, default file: musicdatabase.txt
void exportFunction(map<string, albumData> &albumNamesMap, string &remains){
    ofstream fileName;
    if(remains.empty()){
        remains = "musicdatabase.txt";
    }

    // ios::out -> flag opens the file for output, allowing to write to the file.
    // ios::trunc -> the contents of the file will be deleted when the file is opened
    fileName.open(remains, ios::out | ios::trunc);

    if(fileName.is_open()) {
        for (auto &x : albumNamesMap) {
            fileName << x.first << endl;    //first is album Name
            for (auto &artist : x.second.artistName) {
                fileName << artist << endl;
            }

            for (auto &y: x.second.songTitles) {    //second is ......
                fileName <<y << endl;
            }
            fileName << x.first << endl;
        }

        }
        fileName.close();
}


//This function searches for albums in the music database that match the search terms specified by the user, using the
// boolean operators (+ and -) to indicate whether an album name should be included or excluded in the search results.
void search_Album(map<string, albumData> &albumNamesMap,string secondWord){
    cout << "Your search results exist in the following albums: " << endl;
    set<string> firstSet, secondSet;
    string firstSearch;
    char sign;


    while(!secondWord.empty()) {
        secondSet.clear();
        splitFirstWord(secondWord, firstSearch, secondWord);

        if (firstSearch[0] == '+') {
            firstSearch = firstSearch.substr(1);
            sign = '+';
        }
        if (firstSearch[0] == '-') {
            firstSearch = firstSearch.substr(1);
            sign = '-';
        }

        for (const auto &x: albumNamesMap) {
            firstSearch[0] = ::toupper(firstSearch[0]);
            if (x.first.find(firstSearch) != string::npos) {
                secondSet.insert(x.first);
            }
        }


        if(sign == '-'){
            set <string> resultInter;
            set_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }
        else if(sign == '+'){
            set <string> resultInter;
            set_intersection(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }
        else{
            set <string> resultInter;
            set_union(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }

    }

    //printing out the result
    for (const auto &x : firstSet) {
        cout << x << endl;
    }


    cout << endl;
}

//A function that searches for album names containing a given artist name and returns the albums in which the artist
// name was found, with the ability to perform set operations
void search_Artist(map<string, albumData> &albumNamesMap,string secondWord){
    cout << "Your search results exist in the following albums: " << endl;
    set<string> firstSet, secondSet;
    string firstSearch;
    char sign;



    while(!secondWord.empty() && secondWord != " ") {

        secondSet.clear();
        splitFirstWord(secondWord, firstSearch, secondWord);

        //assigning and removing the signs for firstSearch
        if (firstSearch[0] == '+') {
            firstSearch = firstSearch.substr(1);
            sign = '+';
        }
        if (firstSearch[0] == '-') {
            firstSearch = firstSearch.substr(1);
            sign = '-';
        }

        for (const auto &x: albumNamesMap) {
            firstSearch[0] = ::toupper(firstSearch[0]);
            for (auto &y: x.second.artistName) {
                if (y.find(firstSearch) != string::npos) {
                    secondSet.insert(x.first);
                }
            }
        }


        if(sign == '-'){
            set <string> resultInter;
            set_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }
        else if(sign == '+'){
            set <string> resultInter;
            set_intersection(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;

        }
        else{
            set <string> resultInter;
            set_union(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }

    }


    //printing out the result
    for (const auto &x : firstSet) {
        cout << x << endl;
    }


    cout << endl;


}

//A function that searches for album names containing a given song name and returns the albums in which the song
// name was found, with the ability to perform set operations
void search_Song(map<string, albumData> &albumNamesMap,string secondWord) {
    cout << "Your search results exist in the following albums: " << endl;
    set<string> firstSet, secondSet;
    string firstSearch;
    char sign;


    while(!secondWord.empty() && secondWord != " ") {

        secondSet.clear();
        splitFirstWord(secondWord, firstSearch, secondWord);

        //assigning and removing the signs for firstSearch
        if (firstSearch[0] == '+') {
            firstSearch = firstSearch.substr(1);
            sign = '+';
        }
        if (firstSearch[0] == '-') {
            firstSearch = firstSearch.substr(1);
            sign = '-';
        }

        for (const auto &x: albumNamesMap) {
            firstSearch[0] = ::toupper(firstSearch[0]);
            for (auto &y: x.second.songTitles) {
                if (y.find(firstSearch) != string::npos) {
                    secondSet.insert(x.first);
                }
            }
        }


        if(sign == '-'){
            set <string> resultInter;
            set_difference(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }
        else if(sign == '+'){
            set <string> resultInter;
            set_intersection(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;

        }
        else{
            set <string> resultInter;
            set_union(firstSet.begin(), firstSet.end(), secondSet.begin(), secondSet.end(), inserter(resultInter, resultInter.end()));
            firstSet = resultInter;
        }

    }


    //printing out the result
    for (const auto &x : firstSet) {
        cout << x << endl;
    }


    cout << endl;
}

int main() {

        // TODO: Declare any necessary variables for the music library
        map<string, albumData> albumNamesMap; //key albumNames, value songs inside that album
        string userEntry;
        string command, remains, searchFor, secondWord, thirdWord, fourthWord, fifthWord, sixthWord;


    // Display welcome message once per program execution
        cout << "Welcome to the Music Library App" << endl;
        cout << "--------------------------------" << endl;

        // Stay in menu until exit command
        do {
            cout << endl;
            cout << "Enter a command (help for help): " << endl;
            getline(cin, userEntry);
            cout << endl;

            // Split the user entry into two pieces
            splitFirstWord(userEntry, command, remains);
            tolower(command);


            // take an action, one per iteration, based on the command
            if (command == "help") {
                helpCommand();
            }
            else if (command == "clear") {
                albumNamesMap.clear();
            }
            else if (command == "export") {
                exportFunction(albumNamesMap, remains);
            }
            else if (command == "load") {
                readingFiles(albumNamesMap, remains);
            }
            else if (command == "stats") {
                stats(albumNamesMap, remains);
            }
            else if (command == "search") {

                splitFirstWord(remains, searchFor, secondWord); //splits the remain into searchFor(album/song/artist) and what to look for

                //error message if it isn't specifying what to search for
                if (secondWord.empty()) {
                    cout << "Error: Search terms cannot be empty." << endl << "No results found." << endl << endl;
                    continue;
                }
                if (searchFor == "album") {
                    search_Album(albumNamesMap, secondWord);
                }
                else if (searchFor == "artist") {
                    search_Artist(albumNamesMap, secondWord);
                }
                else if (searchFor == "song") {
                    search_Song(albumNamesMap, secondWord);

                }

            }

        } while (command != "exit");

        cout << "Thank you for using the Music Library App" << endl;
        return 0;
    }

