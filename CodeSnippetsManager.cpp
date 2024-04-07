#include "CodeSnippetsManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <vector>


void CodeSnippetsManager::AddSnippet( const string& tag , const string& code ){

    snippets[tag]=code;                                        //setting key-value (Tag - Code)
}


string CodeSnippetsManager::FindToRetrieveSnippet( const string& substring ) {

    vector<string> matchingTags;

    // Iterate through all snippets to find tags of Snippets containing the substring
    for (const auto& entry : snippets) {
        const string& tag = entry.first;
        if (tag.find(substring) != string::npos) {
            matchingTags.push_back(tag);
        }
    }

    // Display matching tags for options
    if (matchingTags.empty()) {
        cout << "No tags found like this or containing the substring like this " << substring << "'." << endl;
        return "";          // Return an empty string to indicate no matching tags found
    } else {
        cout << endl << "Tags containing the substring " << substring << "':" << endl;
        for (const string& tag : matchingTags) {
            cout << "- " << tag << endl;
        }
        cout << endl;

        // Asking user to choose a tag
        string tagToRetrieve;
        cout << "Enter the tag : ";
        cin >> tagToRetrieve;

        //taking user chosen input tag
        auto it = snippets.find(tagToRetrieve);
        if (it == snippets.end()) {
            cout << "Error: No Snippet found for tag '" << tagToRetrieve << "'." << endl;
            return "";         // Return an empty string to indicate error
        }

        return tagToRetrieve;
    }
}


void CodeSnippetsManager::RetrieveSnippet( const string& tag ){

    auto it = snippets.find(tag);                 //iterate to find the tag
    if( it != snippets.end()){
        cout << "Snippet for tag " << tag << ":" << endl << endl;
        cout << it->second << endl;
    }
    else{
        cout << "No Snippets found for tag " << tag << "." << endl;
    }
}


void CodeSnippetsManager::RemoveSnippet( const string& substring ) {

    string tag = FindToRetrieveSnippet(substring);
    
    // Check if the tag is empty and indicating an error 
    if (tag.empty()) {
        return;             // Exit the function without further processing
    }

    auto it = snippets.find(tag);
    if (it != snippets.end()) {
        snippets.erase(it);                           // Deleting the snippet from the map
        cout << endl << "Snippet with tag '" << tag << "' removed." << endl;
    } else {
        cout << "Error: No Snippet found for tag '" << tag << "'." << endl;
    }   
}


void CodeSnippetsManager::EditSnippetTag( const string& substring ) {

    string tag = FindToRetrieveSnippet(substring);
    
    // Check if the tag is empty and indicating an error 
    if (tag.empty()) {
        return;                                // Exit the function without further processing
    }

    auto it = snippets.find(tag);
    if (it != snippets.end()) {
        cout << "Enter the new tag for the snippet with tag '" << tag << "':" << endl << endl;
        string newTag;
        cin >> newTag;

        if (!newTag.empty()) {
            if (snippets.find(newTag) == snippets.end()) {
                // Update the tag for the given snippet
                snippets[newTag] = it->second;
                snippets.erase(tag);
                cout << "Tag for the snippet '" << tag << "' changed to '" << newTag << "'." << endl;
            } else {
                cout << "Error: The new tag is already used for another snippet." << endl;
            }
        } else {
            cout << "Error: Invalid new tag." << endl;
        }
    } else {
        cout << "Error: No Snippet found for tag '" << tag << "'." << endl;
    }
}

void CodeSnippetsManager::EditSnippet( const string& substring ) {

    string tag = FindToRetrieveSnippet(substring);

    // Check if the chosen tag is valid
    auto it = snippets.find(tag);
    if (it != snippets.end()) {
        // Enter the new code for the snippet
        cout << "Enter the new code for the snippet with tag '" << tag << "':" << endl << endl;
        string newCode;
        string line;
        cin.ignore();

        // Read lines until "!!" is encountered
        while (getline(cin, line) && line != "!!") {
            newCode += line + "\n";
        }

        // Check if the new code is not a duplicate under any other tag
        bool isDuplicate = false;
        for (const auto& entry : snippets) {
            const string& otherTag = entry.first;
            if (otherTag != tag && entry.second == newCode) {
                isDuplicate = true;
                break;
            }
        }

        // Update the snippet if the new code is not a duplicate under any other tag
        if (!isDuplicate) {
            snippets[tag] = newCode;
            cout << endl << "Snippet with tag '" << tag << "' edited." << endl;
        } else {
            cout << "Error: Code snippet already exists under another tag." << endl;
        }
    } else {
        cout << "Error: No snippet found for tag '" << tag << "'." << endl;
    }
}


void CodeSnippetsManager::ViewAllSnippets() {
    // Check if there are any snippets
    if (snippets.empty()) {
        cout << "No snippets to display." << endl;
        return;
    }

    // Print each snippet
    cout << "==================================================" << endl;
    cout << "                   All Snippets                   " << endl;
    cout << "==================================================" << endl;
    cout << endl;
    for (const auto& entry : snippets) {
        cout << "Tag: " << entry.first << endl;
        cout << "-------" << endl;
        cout << entry.second << endl;
        cout << "__________________________________________________" << endl << endl;
    }
    cout << "==================================================" << endl;
}


bool CodeSnippetsManager :: saveToFile( const string& filename ){

    ofstream outfile(filename);
    if( !outfile ){                                      //writing and storing the snippet in a file
        cout << "Error: Unable to open file for writing." << endl;
        return false;
    }

    for( const auto& entry : snippets ){                         //inbuilt something
        outfile << "Tag: " << entry.first << endl;
        outfile << "Code: " << entry.second << endl;
    }

    outfile.close();
    cout << "Snippets saved to the file: " << filename << endl;
    
    return true;
}


bool CodeSnippetsManager::loadFromFile( const string& filename ) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Unable to open file for reading." << endl;
        return false;
    }

    snippets.clear();
    string line;
    string currentTag;
    string currentCode;

    while (getline(inFile, line)) {
        if (line.find("Tag: ") == 0) {

            // If we have already read a tag and code, add them to the snippets map
            if (!currentTag.empty() && !currentCode.empty()) {
                snippets[currentTag] = currentCode;
            }
            // Extract the tag from the line
            currentTag = line.substr(5);

        } else if (line.find("Code: ") == 0) {
            // Extract the code from the line

            currentCode = line.substr(6) + "\n"; // Append newline for the first line of code
            // Read remaining lines of code until an empty line is encountered

            while (getline(inFile, line) && !line.empty()) {
                currentCode += line + "\n";
            }
        }
    }

    // Add the last tag and code pair to the snippets map
    if (!currentTag.empty() && !currentCode.empty()) {
        snippets[currentTag] = currentCode;
    }

    inFile.close();
    cout << "Snippets loaded from file: " << filename << endl;
    return true;
}


bool CodeSnippetsManager::IsDuplicateTag( const string& tag ) {

    // Check if the tag already exists in the snippets map
    if (snippets.find(tag) != snippets.end()) {
        return true; // Duplicate tag found
    }
    return false; // No duplicate tag found
}


bool CodeSnippetsManager::IsDuplicateCode( const string& code ) {

    // Iterate through existing snippets

    for (const auto& entry : snippets) {
        const string& existingCode = entry.second;
        if (existingCode == code) {
            // Identical code found in a different snippet
            cout << "-" << entry.first << "." << endl;
            return true;
        }
    }
    
    // No duplicate code found
    return false;
}






