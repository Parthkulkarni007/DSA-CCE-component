
#include <iostream> 
#include <string> 
#include <limits> 
using namespace std; 
 
// Node of doubly linked list 
struct Node { 
    string text; 
    Node* prev; 
    Node* next; 
 
    Node(string t) { 
        text = t; 
        prev = NULL; 
        next = NULL; 
    } 
}; 
 
struct TextEditor {
    Node* head; 
    Node* current; 
 
    // Delete redo history after current node 
    void clearRedoHistory() { 
        Node* temp = current->next; 
 
        while (temp != NULL) { 
            Node* toDelete = temp; 
            temp = temp->next; 
            delete toDelete; 
        } 
 
        current->next = NULL; 
    } 
 
    // Add a new version of text 
    void addState(string newText) { 
        clearRedoHistory(); 
 
        Node* newNode = new Node(newText); 
        newNode->prev = current; 
        current->next = newNode; 
        current = newNode; 
    } 
 
    // Constructor 
    TextEditor() { 
        head = new Node(""); 
        current = head; 
    } 
 
    // Destructor 
    ~TextEditor() { 
        Node* temp = head; 
 
        while (temp != NULL) { 
            Node* nextNode = temp->next; 
            delete temp; 
            temp = nextNode; 
        } 
    } 
 
    // Write text 
    void write(string s) { 
        addState(current->text + s); 
    } 
 
    // Delete last N characters 
    void deleteChars(int n) { 
        if (n <= 0) { 
            cout << "Enter a positive number.\n"; 
            return; 
        } 
 
        string t = current->text; 
 
        if (t.empty()) { 
            cout << "Nothing to delete.\n"; 
            return; 
        } 
 
        if (n > (int)t.length()) { 
            n = (int)t.length(); 
        } 
 
        t.erase(t.length() - n); 
        addState(t); 
    } 
 
    // Undo operation 
    void undo() { 
        if (current->prev == NULL) { 
            cout << "Nothing to undo.\n"; 
            return; 
        } 
 
        current = current->prev; 
        cout << "Undo successful.\n"; 
    } 
 
    // Redo operation 
    void redo() { 
        if (current->next == NULL) { 
            cout << "Nothing to redo.\n"; 
            return; 
        } 
 
        current = current->next; 
        cout << "Redo successful.\n"; 
    } 
 
    // Display current text 
    void display() { 
        cout << "\nCurrent Text: \"" 
             << current->text << "\"\n"; 
    } 
 
    // Display version history 
    void showHistory() { 
        Node* temp = head; 
        int i = 0; 
 
        cout << "\nVersion History:\n"; 
 
        while (temp != NULL) { 
            if (temp == current) 
                cout << " -> "; 
            else 
                cout << "    "; 
 
            cout << i << ": \"" << temp->text << "\"\n"; 
 
            temp = temp->next; 
            i++; 
        } 
    } 
}; 
 
int main() { 
    TextEditor editor; 
    int choice; 
 
    do { 
        cout << "\n===== TEXT EDITOR UNDO/REDO =====\n"; 
        cout << "1. Write text\n"; 
        cout << "2. Delete last N characters\n"; 
        cout << "3. Undo\n"; 
        cout << "4. Redo\n"; 
        cout << "5. Display text\n"; 
        cout << "6. Show history\n"; 
        cout << "0. Exit\n"; 
        cout << "Enter your choice: "; 
 
        if (!(cin >> choice)) { 
            cout << "Invalid input. Exiting.\n"; 
            break; 
        } 
 
        switch (choice) { 
            case 1: { 
                string s; 
 
                cout << "Enter text to write: "; 
 
                cin.ignore( 
                    numeric_limits<streamsize>::max(), 
                    '\n' 
                ); 
 
                getline(cin, s); 
                editor.write(s); 
 
                cout << "Text written successfully.\n"; 
                break; 
            } 
 
            case 2: { 
                int n; 
 
                cout << "Enter number of characters to delete: "; 
 
                if (cin >> n) { 
                    editor.deleteChars(n); 
                } else { 
                    cout << "Invalid number.\n"; 
                    cin.clear(); 
                    cin.ignore( 
                        numeric_limits<streamsize>::max(), 
                        '\n' 
                    ); 
                } 
 
                break; 
            } 
 
            case 3: 
                editor.undo(); 
                break; 
 
            case 4: 
                editor.redo(); 
                break; 
 
            case 5: 
                editor.display(); 
                break; 
 
            case 6: 
                editor.showHistory(); 
                break; 
 
            case 0: 
                cout << "Program ended.\n"; 
                break; 
 
            default: 
                cout << "Invalid choice. Try again.\n"; 
        } 
 
    } while (choice != 0); 
 
    return 0; 
}
