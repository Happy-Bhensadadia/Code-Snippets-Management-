#ifndef CODE_SNIPPETS_MANAGER_H
#define CODE_SNIPPETS_MANAGER_H

#include <string>
#include <map>
using namespace std;

//Declare the methods of class manager - Add, Retrieve, saveTofile, loadfromfile
class CodeSnippetsManager{
    private:
        map <string, string> snippets;

    public :

        void AddSnippet(const string& tag , const string& code);
        void RetrieveSnippet(const string& tag);
        void RemoveSnippet( const string& tag);
        void EditSnippet( const string& tag);
        void EditSnippetTag( const string& tag);

        bool saveToFile(const string& filename);
        bool loadFromFile(const string& filename);
        bool IsDuplicateTag(const string& tag);
        bool IsDuplicateCode();
        void ViewAllSnippets();
};


#endif //CODE_SNIPPETS_MANAGER_H