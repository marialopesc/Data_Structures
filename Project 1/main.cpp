/*
 * Header:
 * file name: project_1_251_real
 * author/student: Maria Bezerra
 * netID: 676493398
 * course: CS 251 - spring 2023
 * assignment: Gerrymandering
 * file:
 * 1) districts.txt: has stateNames, and information such as democratic and republican votes for each district inside that state
 * 2) eligible_voters.txt: is organized by stateName and its eligible voters per line.
 */

#include <iostream>
#include "ourvector.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
using namespace std;

//struct to hold the information of the first file (democratics.txt or similar), having 2 ourvectors
// to hold the democratic and republican votes for each district.
struct districtsInfo{
    string stateName;
    int districtNumber;
    ourvector<int> democraticVotes;
    ourvector<int> republicanVotes;
};

//struct that will be holding the second file, with the stateName and the eligibleVoter count.
struct eligibleVotersInfo{
    string stateName;
    int eligibleVoter;

};

//helper function to split the input in words and pushing them back inside vector (items) -> it will facilitate when
// determining what is the command, the 2 files, name of state etc
void splitString(string line, char delimiter, ourvector<string>& items ) {


    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}

//This code is a function that reads a file, stores the information in an object, and prints the number of districts for each state stored in the object.
// It checks if the file can be opened and if it exists, otherwise it returns an error message.
void reading_districts(string districts_File, ourvector<districtsInfo> &statesData_firstFile) {
    ifstream fileDistrict(districts_File);
    ourvector<string> lineRead; //each line of the file
    string values;

    if (fileDistrict.fail() || !fileDistrict.is_open()) {
        cout << "Invalid first file, try again." << endl;
        return;

    }


    cout << "Reading: " << districts_File << endl;
    getline(fileDistrict, values, '\n');
    while (!fileDistrict.eof()) { //
        districtsInfo eachState;
        lineRead.clear();
        splitString(values, ',', lineRead); //split - read lines and put words into statesData


        eachState.stateName = lineRead.at(0);
        for (int i = 1; i < lineRead.size(); i+=3) {

            eachState.democraticVotes.push_back(stoi((lineRead.at(i+1)))); // updating the parameter
            eachState.republicanVotes.push_back(stoi(lineRead.at(i+2))); // updating the parameter

        }

        getline(fileDistrict, values);
        statesData_firstFile.push_back(eachState);
    }

    for (int i = 0; i < statesData_firstFile.size(); ++i) {
        cout << "..." << statesData_firstFile[i].stateName << "...";
        cout << statesData_firstFile.at(i).democraticVotes.size() <<  " districts total" << endl;
    }
    fileDistrict.close();


}


//This code is a function that reads a file, stores the information from the file in an object, and prints the number
// of eligible voters for each state stored in the object.
// This function checks if the file can be opened and if it exists, otherwise it throws an error message.
void reading_eligibleVoters(string eligible_Voters_File, ourvector<districtsInfo>statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile) {
    ifstream fileVoters(eligible_Voters_File);
    ourvector<string> lineRead; //each line of the file
    string values, stateFileCheck;

    if (fileVoters.fail()) {
        cout << "Invalid second file, try again." << endl;
        return;
    }

    cout << "Reading: " << eligible_Voters_File << endl;
    while (getline(fileVoters, values)) {
        lineRead.clear();

        splitString(values, ',', lineRead); //split - read lines and put words into statesDataVoters
        statesData_secondFile.push_back(eligibleVotersInfo()); // updating the parameter      WHY? DON'T GET IT.

        statesData_secondFile.back().stateName = lineRead.at(0);
        statesData_secondFile.back().eligibleVoter = stoi(lineRead.at( 1));
    }

    for (auto & x:statesData_secondFile) {
        for (auto & y: statesData_firstFile) {
            if(x.stateName == y.stateName){
                cout << "..." << x.stateName << "...";
                cout << x.eligibleVoter <<  " eligible voters" << endl;
            }
        }
    }

    fileVoters.close();
}


//This function checks the sizes of two input vectors, statesData_firstFile and statesData_secondFile.
//If they are both not empty, it will return "true", otherwise, false.
bool fileLoad(ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile){

    if(statesData_firstFile.size() != 0 && statesData_secondFile.size() != 0){
        return true;
    }
    else{
        return false;
    }
}


// Reads data from two input files and stores the information in two ourvector structures, but only if the structures are empty,
// otherwise it will prompt the user to start over.
void load(string file1, string file2, ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile){

    if(fileLoad(statesData_firstFile, statesData_secondFile)) {
        cout << "Already read data in, exit and start over." << endl;
        return;
    }


    reading_districts(file1, statesData_firstFile);
    cout << endl;


    if (statesData_firstFile.size() != 0) {
        reading_eligibleVoters(file2, statesData_firstFile, statesData_secondFile);
        cout << endl;
    }
}


//This checks the existence of stateSearched in both "statesData_firstFile" and "statesData_secondFile".
void search(string &stateSearched,ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile) {
    bool found = false;

    if(!fileLoad(statesData_firstFile, statesData_secondFile)) {
        cout << "No data loaded, please load data first." << endl;
        return;
    }

    for (size_t j = 0; j < stateSearched.size(); j++) {
        if (j == 0 || stateSearched[j - 1] == ' ') {
            stateSearched[j] = toupper(stateSearched[j]);
        }
        else{
            stateSearched.at(j) = tolower(stateSearched[j]);
        }
    }
    for (const auto &stateData : statesData_secondFile) {
        if (stateSearched == stateData.stateName) {
            found = true;
            break;
        }
    }

    for (const auto &stateData : statesData_firstFile) {
        if (stateSearched == stateData.stateName) {
            found = true;
            break;
        }
    }



    if (!found) {
        cout << "State does not exist, search again." << endl << endl;
    }
}

void stats(string &stateSearched,ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile){
    int index = -1;

    if(stateSearched == "N/A" || stateSearched.empty()){
        cout << "No state indicated, please search for state first." << endl;

        return;
    }


    for (int i = 0; i < statesData_secondFile.size(); ++i) {
        if (statesData_secondFile.at(i).stateName == stateSearched) {
            index = i;
            break;
        }
    }


//IT IS PRINTING MULTIPLE TIMES THE STATE NAME AND DISTRICTS
    int totalWastedDemoVotes = 0, totalWastedRepVotes = 0, totalVoters = 0;
    string gerrymandering;
    int totalDemoVotes = 0, totalRepVotes = 0, districtQuantity = 0;
    double gap;

/*
 * Below, the function calculates the total number of wasted votes for each political party, the efficiency
 * gap (the difference between the two parties' wasted votes), and the number of eligible voters. If the efficiency
 * gap is greater than or equal to 7% and the number of districts is greater than or equal to 3, the function prints
 * "Gerrymandered: Yes", otherwise it prints "Gerrymandered: "No". If the state is gerrymandered, the function also prints which party
 */

    for (int i = 0; i < statesData_firstFile.size(); ++i) {
        if (statesData_firstFile.at(i).stateName == stateSearched) {

            for (int j = 0; j < statesData_firstFile.at(i).democraticVotes.size(); ++j) {
                int eachDemVote = statesData_firstFile.at(i).democraticVotes.at(j);
                int eachRepVote = statesData_firstFile.at(i).republicanVotes.at(j);

                totalDemoVotes += statesData_firstFile.at(i).democraticVotes.at(j); //calculating the total demo for the ENTIRE state
                totalRepVotes += statesData_firstFile.at(i).republicanVotes.at(j);

                int overHalf = ((statesData_firstFile.at(i).democraticVotes.at(j) + statesData_firstFile.at(i).republicanVotes.at(j)) / 2) + 1;
                if (eachDemVote > eachRepVote) {
                    totalWastedDemoVotes += eachDemVote - overHalf;
                    totalWastedRepVotes += eachRepVote;
                }
                else {
                    totalWastedDemoVotes += eachDemVote;
                    totalWastedRepVotes += eachRepVote - overHalf;
                }
            }
        }
    }

    for (int i = 0; i < statesData_firstFile.size(); ++i) {
        if (statesData_firstFile.at(i).stateName == stateSearched) {
            districtQuantity = statesData_firstFile.at(i).democraticVotes.size() ;
        }}


    totalVoters = totalDemoVotes + totalRepVotes;
    gap = abs(totalWastedRepVotes - totalWastedDemoVotes) / (double)totalVoters;
    if (gap >= 0.07 && districtQuantity >= 3){
        gerrymandering = "Yes";
    }
    else{
        gerrymandering = "No";
    }

    string against;
    if(gerrymandering == "Yes") {
        if (totalDemoVotes > totalRepVotes) {
            against = "Republicans";
        }
        else {
            against = "Democrats";
        }
    }

    cout << "Gerrymandered: " << gerrymandering << endl;
    if(gerrymandering == "Yes"){
        cout << "Gerrymandered against: " << against << endl;
        cout << "Efficiency Factor: " << gap * 100 << "%" << endl;
    }
    cout << "Wasted Democratic votes: " << totalWastedDemoVotes << endl;
    cout << "Wasted Republican votes: " << abs(totalWastedRepVotes) << endl;
    cout << "Eligible voters: " << statesData_secondFile.at(index).eligibleVoter << endl << endl;



}


//Checks if the state searched is in both first and second file. it returns either the stateSearched, or the "default" value N/A
string isInFile(string stateSearched, ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile){
    bool found = false;
    for (int i = 0; i < statesData_firstFile.size(); ++i) {
        if (statesData_firstFile.at(i).stateName == stateSearched){
            found = true;
        }
    }

    for (int j = 0; j < statesData_firstFile.size(); ++j) {
        if (statesData_firstFile.at(j).stateName == stateSearched){
            found = true;
        }
    }

    if(found){
        return stateSearched;
    }
    else{
        return "N/A";
    }
}


/*
 * It searches the stateName of the first file and outputs the results of the voting percentage of each district in the form of a bar chart.
 * If stateSearched is found in statesData_firstFile, it uses the democraticVotes and republicanVotes of each district to calculate the voting
 * percentage for both parties. The rounded down percentage for each party is then printed as the number of 'D's and 'R's, respectively.
 * If the size of statesData_secondFile is not 0, the function will run the plotting.
 */
void plot(string &stateSearched,ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile) {
    int demo, rep, total;
    double demoPercentage, repPercentage;


    for (int i = 0; i < statesData_firstFile.size(); ++i) {
        if(statesData_secondFile.size()!= 0){
        if (statesData_firstFile.at(i).stateName == stateSearched) {
            for (int j = 0; j < statesData_firstFile.at(i).democraticVotes.size(); ++j) {
                demo = statesData_firstFile.at(i).democraticVotes.at(j);
                rep = statesData_firstFile.at(i).republicanVotes.at(j);

                total = rep + demo;
                demoPercentage = floor(demo / (double)total * 100); //rounding down the value

                repPercentage = (double)100 - demoPercentage;

                cout << "District: " << j+1 << endl;
                for (int x = 0; x < demoPercentage; ++x) {
                    cout << "D";
                }
                for (int y = 0; y < repPercentage; ++y) {
                    cout << "R";
                }
                cout << endl;
            }
        }
    }}


}


/*
 * The function 'commandMenu' will serve as the main input interface for the program. It will process the user's input by utilizing the 'splitString'
 * helper function and will control the execution flow by calling the appropriate functions based on the input.
 */
void commandMenu(ourvector<districtsInfo> &statesData_firstFile, ourvector<eligibleVotersInfo> &statesData_secondFile) {
    string input, file_1, file_2, stateSearched = "N/A";
    ourvector<string> commandVector;
    bool keepRunning = true;

    do {

        cout << "Data loaded? ";
        if (fileLoad(statesData_firstFile, statesData_secondFile)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        cout << "State: ";
        cout << isInFile(stateSearched, statesData_firstFile, statesData_secondFile);
        cout << endl;

        cout << "Enter command: ";
        getline(cin, input);
        splitString(input, ' ', commandVector);
        cout << "-----------------------------" << endl << endl;


        if(commandVector.at(0) == "load") {
            file_1 = commandVector.at(1); //district.txt
            file_2 = commandVector.at(2); //eligible_voters.txt
            load(file_1, file_2, statesData_firstFile, statesData_secondFile);

        }
        else if (commandVector.at(0) == "search") {
            if(commandVector.size() >= 3){
                stateSearched = commandVector.at(1) + " " + commandVector.at(2);
            }
            else{
                stateSearched = commandVector.at(1);
            }

            fileLoad(statesData_firstFile, statesData_secondFile);
            search(stateSearched, statesData_firstFile, statesData_secondFile);
        }

        else if (commandVector.at(0) == "plot") {
            plot(stateSearched, statesData_firstFile, statesData_secondFile);
        }

        else if (commandVector.at(0) == "stats") {
            stats(stateSearched, statesData_firstFile, statesData_secondFile);

        } else if (commandVector.at(0) == "exit") {
            //??                          //HOW TO MAKE IT GO BACK TO MENU, ONCE YOU TYPE EXIT???
            keepRunning = false;
        }
        commandVector.clear();
    } while (keepRunning); //commandVector.at(0) != "exit"

}

int main() {
    string eligible_Voters_File;
    string districts_File;
    ourvector<districtsInfo> statesData_firstFile; // district
    ourvector<eligibleVotersInfo> statesData_secondFile; //holds the info from the file Voters


    //where our program begins.
    cout << "Welcome to the Gerrymandering App!" << endl;
    commandMenu(statesData_firstFile, statesData_secondFile);

    return 0;
}
