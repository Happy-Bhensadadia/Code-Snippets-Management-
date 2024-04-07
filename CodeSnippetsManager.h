#ifndef CODE_SNIPPETS_MANAGER_H
#define CODE_SNIPPETS_MANAGER_H

#include <string>
#include <map>
using namespace std;

/*Declare the methods of class manager - Add, Retrieve, Remove, EditSnippet, EditSnippetTag, ViewAllSnippets,
  FindToRetrieveSnippet, saveToFile, loadFromFile, IsDuplicateTag, IsduplicateCode*/
  
class CodeSnippetsManager{
    private:
        map <string, string> snippets;

    public :

        void AddSnippet(const string& tag , const string& code);
        void RetrieveSnippet(const string& tag);
        void RemoveSnippet( const string& tag);
        void EditSnippet( const string& tag);
        void EditSnippetTag( const string& tag);
        void ViewAllSnippets();
        string FindToRetrieveSnippet(const string& substring);

        bool saveToFile(const string& filename);
        bool loadFromFile(const string& filename);
        bool IsDuplicateTag(const string& tag);
        bool IsDuplicateCode(const string& code);

};


#endif //CODE_SNIPPETS_MANAGER_H




/* there is a issue that we can address is that we are having a function called IsDuplicateTag 
which we are calling in the function AddSnippet which takes ccare that there is no snippet added under same tag 
can we do the same for checking the code of snippets if we do so then we wont be able to check that in other fuctions
like edittag, edit code, or retrieve or remove because we hadn't allowed the code to be same neitheer the tag ..........
.................think on this*/