#include "CodeSnippetsManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <iomanip>
#include <vector>


void CodeSnippetsManager::AddSnippet( const string& tag , const string& code ){

    snippets[tag]=code;                                        //setting key-value pair
}


void CodeSnippetsManager::RetrieveSnippet( const string& tag){

    auto it = snippets.find(tag);                 //it is iterator. it is a inbuilt in STL for map.
    if( it != snippets.end()){
        cout << "Snippet for tag " << tag << ":" << endl;
        cout << it->second << endl;
    }
    else{
        cout << "No Snippets found for tag " << tag << "." << endl;
    }
}


void CodeSnippetsManager::FindToRetrieveSnippet(const string& substring) {
    vector<string> matchingTags;

    // Iterate through snippets to find tags containing the substring
    for (const auto& entry : snippets) {
        const string& tag = entry.first;
        if (tag.find(substring) != string::npos) {
            matchingTags.push_back(tag);
        }
    }

    // Display matching tags
    if (matchingTags.empty()) {
        cout << "No tags found containing the substring '" << substring << "'." << endl;
    } else {
        cout << "Tags containing the substring '" << substring << "':" << endl;
        for (const string& tag : matchingTags) {
            cout << "- " << tag << endl;
        }

        // Ask user to choose a tag
        string chosenTag;
        cout << "Enter the tag you want to retrieve code for: ";
        cin >> chosenTag;

        // Retrieve and display code for the chosen tag
        RetrieveSnippet(chosenTag);
    }
}


void CodeSnippetsManager::RemoveSnippet(const string& substring) {
    vector<string> matchingTags;

    // Iterate through snippets to find tags containing the substring
    for (const auto& entry : snippets) {
        const string& currentTag = entry.first;
        if (currentTag.find(substring) != string::npos) {
            matchingTags.push_back(currentTag);
        }
    }

    // Display matching tags
    if (matchingTags.empty()) {
        cout << "No tags found containing the substring '" << substring << "'." << endl;
    } else {
        cout << "Tags containing the substring '" << substring << "':" << endl;
        for (const string& tag : matchingTags) {
            cout << "- " << tag << endl;
        }

        // Ask user to choose a tag
        string chosenTag;
        cout << "Enter the tag you want to remove: ";
        cin >> chosenTag; 

        auto it = snippets.find(chosenTag);
        if (it != snippets.end()) {
            snippets.erase(it); // Deleting the snippet from the map
            cout << "Snippet with tag '" << chosenTag << "' removed." << endl;
        } else {
            cout << "No Snippet found for tag '" << chosenTag << "'." << endl;
        }   
    }
}


void CodeSnippetsManager::EditSnippetTag(const string& substring) {
    vector<string> matchingTags;

    // Iterate through snippets to find tags containing the substring
    for (const auto& entry : snippets) {
        const string& tag = entry.first;
        if (tag.find(substring) != string::npos) {
            matchingTags.push_back(tag);
        }
    }

    // Display matching tags
    if (matchingTags.empty()) {
        cout << "No tags found containing the substring '" << substring << "'." << endl;
    } else {
        cout << "Tags containing the substring '" << substring << "':" << endl;
        for (const string& tag : matchingTags) {
            cout << "- " << tag << endl;
        }

        // Ask user to choose a tag
        string chosenTag;
        cout << "Enter the tag ";
        cin >> chosenTag;

        auto it = snippets.find(chosenTag);
        if (it != snippets.end()) {
            cout << "Enter the new tag for the snippet with tag '" << chosenTag << "':" << endl;
            string newTag;
            cin >> newTag;

            if (snippets.find(newTag) == snippets.end()) {
                // Update the tag for the given snippet
                snippets[newTag] = it->second;
                snippets.erase(chosenTag);
                cout << "Tag for the snippet '" << chosenTag << "' changed to '" << newTag << "'." << endl;
            } else {
                cout << "The new tag is already used for another snippet." << endl;
            }
        } else {
            cout << "No Snippet found for tag '" << chosenTag << "'." << endl;
        }
    }
}



void CodeSnippetsManager::ViewAllSnippets() {
    // Check if there are any snippets
    if (snippets.empty()) {
        cout << "No snippets to display." << endl;
        return;
    }

    // Print each snippet
    for (const auto& entry : snippets) {
        cout << "Tag: " << entry.first << endl;
        cout << "Code: " << entry.second << endl << endl;
    }
}

bool CodeSnippetsManager :: saveToFile( const string& filename){

    ofstream outfile(filename);
    if( !outfile ){                                                       //writing and storing the snippet in a file
        cout << "Error: Unable to open file for writing." << endl;
        return false;
    }

    for( const auto& entry : snippets ){                                //inbuilt something
        outfile << "Tag: " << entry.first << endl;
        outfile << "Code: " << entry.second << endl;
    }

    outfile.close();
    cout << "Snippets saved to the file: " << filename << endl;
    
    return true;
}


bool CodeSnippetsManager::loadFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Unable to open file for reading." << endl;                          //reaading snippet from file
        return false;
    }

    snippets.clear();
    string line;
    string currentTag;
    string currentCode;

    while (getline(inFile, line)) {
        if (line.find("Tag: ") == 0) {
            if (!currentTag.empty() && !currentCode.empty()) {
                snippets[currentTag] = currentCode;
                currentTag.clear();
                currentCode.clear();
            }
            currentTag = line.substr(5);
        }
        else if (line.find("Code: ") == 0) {
            currentCode = "";
            while (getline(inFile, line) && !line.empty()) {
                currentCode += line + "\n";
            }
        }
    }

    if (!currentTag.empty() && !currentCode.empty()) {
        snippets[currentTag] = currentCode;
    }

    inFile.close();
    cout << "Snippets loaded from file: " << filename << endl;
    return true;
}


bool CodeSnippetsManager::IsDuplicateTag(const string& tag) {
    // Check if the tag already exists in the snippets map
    if (snippets.find(tag) != snippets.end()) {
        return true; // Duplicate tag found
    }
    return false; // No duplicate tag found
}


bool CodeSnippetsManager::IsDuplicateCode(const string& code) {
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

void CodeSnippetsManager::EditSnippet(const string& substring) {
    vector<string> matchingTags;

    // Iterate through snippets to find tags containing the substring
    for (const auto& entry : snippets) {
        const string& tag = entry.first;
        if (tag.find(substring) != string::npos) {
            matchingTags.push_back(tag);
        }
    }

    // Display matching tags
    if (matchingTags.empty()) {
        cout << "No tags found containing the substring '" << substring << "'." << endl;
    } else {
        cout << "Tags containing the substring '" << substring << "':" << endl;
        for (const string& tag : matchingTags) {
            cout << "- " << tag << endl;
        }

        // Ask user to choose a tag
        string chosenTag;
        cout << "Enter the tag you want to edit snippet for: ";
        cin >> chosenTag;

        // Check if the chosen tag is valid
        auto it = snippets.find(chosenTag);
        if (it != snippets.end()) {
            // Enter the new code for the snippet
            cout << "Enter the new code for the snippet with tag '" << chosenTag << "':" << endl;
            string newCode;
            string line;

            // Read lines until the delimiter "!!" is encountered
            while (getline(cin, line) && line != "!!") {
                newCode += line + "\n";
            }

            // Check if the new code is not a duplicate under any other tag
            bool isDuplicate = false;
            for (const auto& entry : snippets) {
                const string& tag = entry.first;
                if (tag != chosenTag && entry.second == newCode) {
                    isDuplicate = true;
                    break;
                }
            }

            // Update the snippet if the new code is not a duplicate under any other tag
            if (!isDuplicate) {
                snippets[chosenTag] = newCode;
                cout << "Snippet with tag '" << chosenTag << "' edited." << endl;
            } else {
                cout << "Error: Code snippet already exists under another tag." << endl;
            }
        } else {
            cout << "Error: No snippet found for tag '" << chosenTag << "'." << endl;
        }
    }
}






