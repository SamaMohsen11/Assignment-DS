#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Book {
    int id;
    string title;
    string author;

    Book() {}
    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
    }
};



class BST {
private:

    struct Node {
        Book book;
        Node* left;
        Node* right;

        Node(Book b) {
            book = b;
            left = right = nullptr;
        }
    };

    Node* root;
    int searchSteps;

    Node* insert(Node* node, Book b) {
        if (!node) return new Node(b);

        if (b.id < node->book.id)
            node->left = insert(node->left, b);
        else if (b.id > node->book.id)
            node->right = insert(node->right, b);

        return node;
    }

    Node* search(Node* node, int id) {
        if (!node) return nullptr;

        searchSteps++;

        if (node->book.id == id)
            return node;

        if (id < node->book.id)
            return search(node->left, id);

        return search(node->right, id);
    }

    Node* findMin(Node* node) {
        while (node && node->left)
            node = node->left;
        return node;
    }

    Node* del(Node* node, int id) {
        if (!node) return node;

        if (id < node->book.id)
            node->left = del(node->left, id);

        else if (id > node->book.id)
            node->right = del(node->right, id);

        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;

            Node* temp = findMin(node->right);
            node->book = temp->book;
            node->right = del(node->right, temp->book.id);
        }

        return node;
    }

    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout <<"Id: "<< node->book.id << "  "
         <<"Title: "<< node->book.title << "  "
          <<"Author: "<< node->book.author<<endl<<endl;
         
        inorder(node->right);
    }

    void range(Node* node, int l, int r) {
        if (!node) return;

        if (node->book.id > l)
            range(node->left, l, r);

        if (node->book.id >= l && node->book.id <= r)
            cout << node->book.id << " " << node->book.title << endl;

        if (node->book.id < r)
            range(node->right, l, r);
    }

    void closest(Node* node, int id, Book &best) {
        if (!node) return;

        if (abs(node->book.id - id) < abs(best.id - id))
            best = node->book;

        if (id < node->book.id)
            closest(node->left, id, best);
        else
            closest(node->right, id, best);
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

public:

    BST() {
        root = nullptr;
        searchSteps = 0;
    }

    void insert(Book b) { root = insert(root, b); }

    void search(int id) {
        searchSteps = 0;
        Node* r = search(root, id);

        if (r)
            cout << "BST Found: " << r->book.title
                 << " | Steps: " << searchSteps << endl;
        else
            cout << "BST Not Found | Steps: " << searchSteps << endl;
    }

    void deleteBook(int id) { root = del(root, id); }

    void inorder() { inorder(root); }

    void rangeSearch(int l, int r) { range(root, l, r); }

    void closestID(int id) {
        Book best(1e9, "", "");
        closest(root, id, best);
        cout << "Closest: " << best.id << " " << best.title << endl;
    }

    int getHeight() { return height(root); }
};



class AVL {
private:

    struct Node {
        Book book;
        Node* left;
        Node* right;
        int h;

        Node(Book b) {
            book = b;
            left = right = nullptr;
            h = 1;
        }
    };

    Node* root;
    int searchSteps;

    int H(Node* n) { return n ? n->h : 0; }

    int balance(Node* n) {
        return n ? H(n->left) - H(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->h = 1 + max(H(y->left), H(y->right));
        x->h = 1 + max(H(x->left), H(x->right));

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->h = 1 + max(H(x->left), H(x->right));
        y->h = 1 + max(H(y->left), H(y->right));

        return y;
    }

    Node* insert(Node* node, Book b) {
        if (!node) return new Node(b);

        if (b.id < node->book.id)
            node->left = insert(node->left, b);
        else if (b.id > node->book.id)
            node->right = insert(node->right, b);
        else
            return node;

        node->h = 1 + max(H(node->left), H(node->right));

        int bal = balance(node);

        if (bal > 1 && b.id < node->left->book.id)
            return rightRotate(node);

        if (bal < -1 && b.id > node->right->book.id)
            return leftRotate(node);

        if (bal > 1 && b.id > node->left->book.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bal < -1 && b.id < node->right->book.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, int id) {
        if (!node) return nullptr;

        searchSteps++;

        if (node->book.id == id)
            return node;

        if (id < node->book.id)
            return search(node->left, id);

        return search(node->right, id);
    }

    void inorder(Node* node) {
        if (!node) return;

        inorder(node->left);
        cout << "Id: "<<node->book.id << "  "
           <<"Title: "  << node->book.title << "  "
         <<"Author: " << node->book.author << endl<<endl;
        inorder(node->right);
    }

    int height(Node* node) {
        return H(node);
    }
    Node* findMin(Node* node) {
    while (node->left)
        node = node->left;
    return node;
}

Node* del(Node* node, int id) {

    if (!node)
        return node;

    if (id < node->book.id)
        node->left = del(node->left, id);

    else if (id > node->book.id)
        node->right = del(node->right, id);

    else {

        // one child or no child
        if (!node->left || !node->right) {

            Node* temp;

            if (node->left)
                temp = node->left;
            else
                temp = node->right;

            // no child
            if (!temp) {
                temp = node;
                node = nullptr;
            }
            else {
                *node = *temp;
            }

            delete temp;
        }

        // two children
        else {

            Node* temp = findMin(node->right);

            node->book = temp->book;

            node->right = del(node->right, temp->book.id);
        }
    }

    if (!node)
        return node;

    // update height
    node->h = 1 + max(H(node->left), H(node->right));

    int bal = balance(node);

    // LL
    if (bal > 1 && balance(node->left) >= 0)
        return rightRotate(node);

    // LR
    if (bal > 1 && balance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RR
    if (bal < -1 && balance(node->right) <= 0)
        return leftRotate(node);

    // RL
    if (bal < -1 && balance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

public:

    AVL() {
        root = nullptr;
        searchSteps = 0;
    }

    void insert(Book b) { root = insert(root, b); }

    void search(int id) {
        searchSteps = 0;
        Node* r = search(root, id);

        if (r)
            cout << "AVL Found: " << r->book.title
                 << " | Steps: " << searchSteps << endl;
        else
            cout << "AVL Not Found | Steps: " << searchSteps << endl;
    }

    void inorder() { inorder(root); }

    int getHeight() { return height(root); }
    void deleteBook(int id) {
    root = del(root, id);
}
};

int main() {

    BST bst;
    AVL avl;

Book randomBooks[] = {
    {110, "The Lean Startup", "Eric Ries"},
    {40, "Deep Work", "Cal Newport"},
    {180, "Digital Minimalism", "Cal Newport"},
    {20, "Rich Dad Poor Dad", "Robert Kiyosaki"},
    {150, "The Mountain Is You", "Brianna Wiest"},
    {90, "The 7 Habits of Highly Effective People", "Stephen Covey"},
    {60, "Think and Grow Rich", "Napoleon Hill"},
    {130, "Can't Hurt Me", "David Goggins"},
    {10, "Atomic Habits", "James Clear"},
    {200, "The Art of War", "Sun Tzu"},
    {80, "Ikigai", "Hector Garcia"},
    {50, "The Power of Habit", "Charles Duhigg"},
    {170, "Think Like a Monk", "Jay Shetty"},
    {30, "The Psychology of Money", "Morgan Housel"},
    {140, "Mindset", "Carol Dweck"},
    {70, "The Alchemist", "Paulo Coelho"},
    {160, "Make Your Bed", "William McRaven"},
    {100, "Start With Why", "Simon Sinek"},
    {190, "The Four Agreements", "Don Miguel Ruiz"},
    {120, "Zero to One", "Peter Thiel"}
};

Book sortedBooks[] = {
    {10, "Atomic Habits", "James Clear"},
    {20, "Rich Dad Poor Dad", "Robert Kiyosaki"},
    {30, "The Psychology of Money", "Morgan Housel"},
    {40, "Deep Work", "Cal Newport"},
    {50, "The Power of Habit", "Charles Duhigg"},
    {60, "Think and Grow Rich", "Napoleon Hill"},
    {70, "The Alchemist", "Paulo Coelho"},
    {80, "Ikigai", "Hector Garcia"},
    {90, "The 7 Habits of Highly Effective People", "Stephen Covey"},
    {100, "Start With Why", "Simon Sinek"},
    {110, "The Lean Startup", "Eric Ries"},
    {120, "Zero to One", "Peter Thiel"},
    {130, "Can't Hurt Me", "David Goggins"},
    {140, "Mindset", "Carol Dweck"},
    {150, "The Mountain Is You", "Brianna Wiest"},
    {160, "Make Your Bed", "William McRaven"},
    {170, "Think Like a Monk", "Jay Shetty"},
    {180, "Digital Minimalism", "Cal Newport"},
    {190, "The Four Agreements", "Don Miguel Ruiz"},
    {200, "The Art of War", "Sun Tzu"}
};
    for (int i = 0; i < 20; i++) {
        bst.insert(randomBooks[i]);
        avl.insert(randomBooks[i]);
    }

    int choice;

    while (true) {

        cout << "\nSMART LIBRARY SYSTEM\n";
        cout << "1. Insert Book\n";
        cout << "2. Search (Compare BST & AVL)\n";
        cout << "3. Delete Book\n";
        cout << "4. Display BST\n";
        cout << "5. Display AVL\n";
        cout << "6. Range Search\n";
        cout << "7. Closest ID\n";
        cout << "8. Show Comparison\n";
        cout << "9. Exit\n";
        cout << "Choice: ";

        cin >> choice;

        if (choice == 1) {
            int id; string t, a;
            cout << "ID: "; cin >> id;
            cout << "Title: "; cin >> t;
            cout << "Author: "; cin >> a;

            Book b(id, t, a);
            bst.insert(b);
            avl.insert(b);
        }

        else if (choice == 2) {

            int id;
            cout << "Enter ID: ";
            cin >> id;

            cout << "\n===== RANDOM DATA SEARCH =====\n";

            BST bst1;
            AVL avl1;

            for (int i = 0; i < 20; i++) {
                bst1.insert(randomBooks[i]);
                avl1.insert(randomBooks[i]);
            }

            bst1.search(id);
            avl1.search(id);

            cout << "\n===== SORTED DATA SEARCH =====\n";

            BST bst2;
            AVL avl2;

            for (int i = 0; i < 20; i++) {
                bst2.insert(sortedBooks[i]);
                avl2.insert(sortedBooks[i]);
            }

            bst2.search(id);
            avl2.search(id);
        }

        else if (choice == 3) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;

            bst.deleteBook(id);
            avl.deleteBook(id);

            cout << "Deleted Successfully\n";
        }

        else if (choice == 4) bst.inorder();

        else if (choice == 5) avl.inorder();

        else if (choice == 6) {
            int l, r;
            cin >> l >> r;
            bst.rangeSearch(l, r);
        }

        else if (choice == 7) {
            int id;
            cin >> id;
            bst.closestID(id);
        }

        else if (choice == 8) {

            cout << "\n===== RANDOM DATA COMPARISON =====\n";

            BST bst1;
            AVL avl1;

            for (int i = 0; i < 20; i++) {
                bst1.insert(randomBooks[i]);
                avl1.insert(randomBooks[i]);
            }

            cout << "BST Height: " << bst1.getHeight() << endl;
            cout << "AVL Height: " << avl1.getHeight() << endl;

            cout << "\n===== SORTED DATA COMPARISON =====\n";

            BST bst2;
            AVL avl2;

            for (int i = 0; i < 20; i++) {
                bst2.insert(sortedBooks[i]);
                avl2.insert(sortedBooks[i]);
            }

            cout << "BST Height: " << bst2.getHeight() << endl;
            cout << "AVL Height: " << avl2.getHeight() << endl;
        }

        else break;
    }

    return 0;
}