#include "CodeSnippetsManager.h"
#include <iostream>
#include <stdlib.h>
#include <windows.h>

int main(){

    CodeSnippetsManager manager;

    
    cout << endl;
    if( manager.loadFromFile("snippets.txt")){
        cout << "Ready to run" << endl;
    }
    else {
        cout << "No saved snippets found. Starting from an empty manager" << endl;
    } 

    while ( true ){

        cout << endl;
        cout << endl;
        
        cout << "1. Add Snippet" << endl;                //insertion in map(hashtable)
        cout << "2. Retrieve Sippet" << endl;            //searching in map(hashtable)
        cout << "3. Remove Snippet" << endl;             //deletion in map(hashtable)
        cout << "4. Edit Snippet Code" << endl;
        cout << "5. Edit Snippet Tag" << endl;
        cout << "6. View All Snippets" << endl;
        cout << "0. Exit" << endl; 
        cout <<endl;
        cout << "Choose an option: ";
    
        int choise;
        cin >> choise;

        if (choise == 1) {

            string tag, code;
            cout << "Enter Tag: ";
            cin >> tag;
            if (!manager.IsDuplicateTag(tag)) {
                cin.ignore();
                cout << "Enter code snippet:" << endl;
                cout << "(Enter !! at the end of the code snippet)" << endl << endl;

                string line;
                code = "";
                while (getline(cin, line) && line != "!!") {
                    code += line + "\n";
                }
                if (!manager.IsDuplicateCode(code)) {
                    manager.AddSnippet(tag, code);
                    cout << endl;
                    cout << "Snippet Added." << endl;
                } else {
                    cout << "Error: Code snippet already exists under above shown tag." << endl;
                }
            } else {
                cout << "Error: A snippet with tag '" << tag << "' already exists." << endl;
            }
        }
        else if( choise == 2 ){

            string tag;
            cout << "Enter Tag to retrieve Snippet. ";
            cout << "Tag: ";
            cin >> tag;
            cin.ignore();
            string chosen = manager.FindToRetrieveSnippet(tag);
            manager.RetrieveSnippet(chosen);
            manager.saveToFile(chosen);
        }
        else if( choise == 3 ){

            cout << "Enter the tag for the snippet you want to remove." << endl;
            cout << "Tag: ";
            string tag;
            cin >> tag;
            manager.RemoveSnippet(tag);
        }
        else if ( choise == 4 ) {

            string tag;
            cout << "Enter the tag for the snippet you want to edit. " << endl;
            cout << "Tag: ";
            cin >> tag;
            cin.ignore(); // Clear input buffer
            manager.EditSnippet(tag);
        }
       else if (choise == 5) {

            string tag;
            cout << "Enter the tag for the snippet you want to edit. " << endl;
            cout << "Tag: ";
            cin >> tag;
            manager.EditSnippetTag(tag);
        }
        else if ( choise == 6 ){

            string tag;
            manager.ViewAllSnippets();
        }
        else if( choise == 0 ){

            manager.saveToFile("snippets.txt");
            cout << endl << "Exiting the program." << endl;
            break;
        }
        else{

            cout << "Invalid choise. Please choose a valid option." << endl;
        }
    }


    return 0;
}