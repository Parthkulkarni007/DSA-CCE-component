

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string text;
    Node* prev;
    Node* next;
};

class TextEditor {
private:
    Node* head;     // first (empty) version; head->prev is always the last version
    Node* current;  // version shown on screen

    Node* createNode(string t) {
        Node* n = new Node;
        n->text = t;
        n->prev = n;
        n->next = n;
        return n;
    }

    // Delete all versions after current (until we come back to head)
    void clearRedoHistory() {
        while (current->next != head) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        head->prev = current;   // current is now the last node
    }

    void addState(string newText) {
        clearRedoHistory();
        Node* node = createNode(newText);
        node->prev = current;
        node->next = head;      // last node points back to head (circular)
        current->next = node;
        head->prev = node;
        current = node;
    }

public:
    TextEditor() {
        head = createNode("");
        current = head;
    }

    ~TextEditor() {
        Node* temp = head->next;
        while (temp != head) {
            Node* nxt = temp->next;
            delete temp;
            temp = nxt;
        }
        delete head;
    }

    void write(string s) {
        addState(current->text + s);
    }

    void deleteChars(int n) {
        string t = current->text;
        if (t.empty()) {
            cout << "Nothing to delete.\n";
            return;
        }
        if (n > (int)t.size()) n = t.size();
        t.erase(t.size() - n);
        addState(t);
    }

    void undo() {
        if (current == head) {          // first version reached
            cout << "Nothing to undo.\n";
            return;
        }
        current = current->prev;
    }

    void redo() {
        if (current->next == head) {    // last version reached
            cout << "Nothing to redo.\n";
            return;
        }
        current = current->next;
    }

    void display() {
        cout << "\nCurrent Text: \"" << current->text << "\"\n";
    }

    void showHistory() {
        cout << "\nVersion History:\n";
        Node* t = head;
        int i = 0;
        do {
            if (t == current) cout << " -> ";
            else cout << "    ";
            cout << i << ": \"" << t->text << "\"\n";
            t = t->next;
            i++;
        } while (t != head);
    }
};

int main() {
    TextEditor editor;
    int choice;

    do {
        cout << "\n===== TEXT EDITOR (UNDO/REDO) =====\n";
        cout << "1. Write text\n";
        cout << "2. Delete last N characters\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Display text\n";
        cout << "6. Show history\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string s;
            cout << "Enter text: ";
            cin.ignore();
            getline(cin, s);
            editor.write(s);
        } else if (choice == 2) {
            int n;
            cout << "How many characters to delete? ";
            cin >> n;
            editor.deleteChars(n);
        } else if (choice == 3) {
            editor.undo();
        } else if (choice == 4) {
            editor.redo();
        } else if (choice == 5) {
            editor.display();
        } else if (choice == 6) {
            editor.showHistory();
        } else if (choice != 0) {
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    cout << "Program ended.\n";
    return 0;
}
