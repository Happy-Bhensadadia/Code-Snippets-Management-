#include "CodeSnippetsManager.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>

int main(){

    CodeSnippetsManager manager;

    //system("color 0F");
    if( manager.loadFromFile("snippets.txt")){
        cout << "Ready to run" << endl;
    }
    else {
        cout << "No saved snippets found. Starting from an empty manager" << endl;
    } 

    while ( true ){
        cout << endl;
        cout << endl;
        cout << endl;
        //system("color 0C");
        cout << "1. Add Snippet" << endl;                //insertion in map(hashtable)
        cout << "2. Retrieve Sippet" << endl;            //searching in map(hashtable)
        cout << "3. Remove Snippet" << endl;             //deletion in map(hashtable)
        cout << "4. Edit Snippet" << endl;
        cout << "5. Edit Snippet Tag" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
    
        int choise;
        cin >> choise;

        if( choise == 1 ){
            //system("color 0A");
            string tag , code;
            cout << "Enter Tag: " ;
            cin >> tag;
            cin.ignore();
            cout << "Enter code snippet:\n";
            cout << "(Enter !! at the end of the code snippet)" << endl;
            string line;
            code = "";
            while(getline(cin,line) && line != "!!"){                       //while loop to get multiple lines as input
                code += line + "\n";
            }
            manager.AddSnippet(tag,code);
            cout << "Snippet Added." << endl;

        }
        else if( choise == 2 ){
            //system("color 0E");
            string tag;
            cout << "Enter Tag to retrieve Snippet: ";
            cin >> tag;
            manager.RetrieveSnippet(tag);
        }
        else if( choise == 3 ){
            //system("color 0C");
            cout << "Enter the tag for the snippet you want to remove." << endl;
            cout << "Tag: ";
            string tag;
            cin >> tag;
            manager.RemoveSnippet(tag);
        }
        else if ( choise == 4 ) {
            string tag;
            cout << "Enter the tag for the snippet you want to edit: ";
            cin >> tag;
            cin.ignore(); // Clear input buffer
            manager.EditSnippet(tag);
        }
       else if (choise == 5) {
            string tag;
            cout << "Enter the tag for the snippet you want to edit: ";
            cin >> tag;
            manager.EditSnippetTag(tag);
        }
        else if( choise == 6 ){
            //system("color 0D");
            manager.saveToFile("snippets.txt");
            cout << "Exiting the program." << endl;
            break;
        }
        else{
            //system("color 0B");
            cout << "Invalid choise. Please choose a valid option." << endl;
        }
    }


    return 0;
}