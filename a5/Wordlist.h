// Wordlist.h

#pragma once

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <Mayank Mayank>
// St.# : <301563549>
// Email: <mayank_mayank@sfu.ca>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

//
// Do not use any other #includes
//
#include "Wordlist_base.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//
// IMPORTANT: no global variables are permitted in this file!
//
// It is okay to define helper functions defined outside the class.
//

class Wordlist : public Wordlist_base
{
    //
    // Use this Node to implement an AVL tree for the word list. You can *add*
    // extra variables/methods/features to this struct if you like, but you must
    // keep its name the same, and also keep the word, count, left, and right
    // variables as defined.
    //
    struct Node
    {
        string word;
        int count;
        int height;
        Node *left;
        Node *right;
    };

    Node *root = nullptr;

    //
    // IMPORTANT: root is the only variable that can be defined in this class.
    // It should point to the top node of your AVL tree. When root == nullptr,
    // the tree is empty.
    //
    // No variables other than root are permitted!
    //
    
    // Function to get the height of the tree
    int height(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }
     
    // A utility function to right rotate subtree rooted with y
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
     
        // Perform rotation
        x->right = y;
        y->left = T2;
     
        // Update heights
        y->height = max(height(y->left),
                        height(y->right)) + 1;
        x->height = max(height(x->left),
                        height(x->right)) + 1;
     
        // Return new root
        return x;
    }
     
    // A utility function to left rotate subtree rooted with x
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
     
        // Perform rotation
        y->left = x;
        x->right = T2;
     
        // Update heights
        x->height = max(height(x->left),
                        height(x->right)) + 1;
        y->height = max(height(y->left),
                        height(y->right)) + 1;
     
        // Return new root
        return y;
    }
     
    // Get Balance factor of node N
    int getBalance(Node *N)
    {
        if (N == NULL)
            return 0;
        return height(N->left) - height(N->right);
    }
     
    // Recursive function to insert a word
    // in the subtree rooted with node and
    // returns the new root of the subtree.
    Node* insert(Node* node, const string& w)
    {
        // 1. Perform the normal BST insertion
        if (node == NULL)
        {
            node = new Node;
            node->word = w;
            node->height = 1;
            node->count = 1;
            node->left = nullptr;  // Initialize left child
            node->right = nullptr; // Initialize right child
            return node;
        }
        if (w < node->word)
            node->left = insert(node->left, w);
        else if (w > node->word)
            node->right = insert(node->right, w);
        else // The word is already present --> increment the count
        {
            node->count++;
            return node;
        }
     
        /* 2. Update height of this ancestor node */
        node->height = 1 + max(height(node->left),
                            height(node->right));
     
        // 3. Get the balance factor of this ancestor node to check whether this node
        //     became unbalanced
        int balance = getBalance(node);
     
        // If this node becomes unbalanced, then
        // there are 4 cases
     
        // Left-Left Case
        if (balance > 1 && w < node->left->word)
            return rightRotate(node);
     
        // Right Right Case
        if (balance < -1 && w > node->right->word)
            return leftRotate(node);
     
        // Left Right Case
        if (balance > 1 && w > node->left->word)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
     
        // Right Left Case
        if (balance < -1 && w < node->right->word)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
     
        /* return the (unchanged) node pointer */
        return node;
    }
    // Reference : https://www.geeksforgeeks.org/insertion-in-an-avl-tree/?ref=lbp
    
    // Search the tree, for a given word
    Node* search(Node* node, string& w) const
    {
        if (node == nullptr || node->word == w)
            return node;

        if (w < node->word)
            return search(node->left, w);

        return search(node->right, w);
    }
    
    // Counts number of nodes in the tree
    int node_count(Node* node) const
    {
        if (node == nullptr)
            return 0;

        return 1 + node_count(node->left) + node_count(node->right);
    }
    
    // Counts the total words in the tree
    void count_sum(Node* node, int& sum) const
    {
        if (node == nullptr)
            return;

        count_sum(node->left, sum);
        sum += node->count;
        count_sum(node->right, sum);
    }
    
    // Checks if the tree is sorted
    bool sort_check(Node* node, string& temp) const
    {
        if (node == nullptr)
            return true;
        
        if (!sort_check(node->left, temp))
            return false;

        if (node->word <= temp)
            return false;

        temp = node->word;

        return sort_check(node->right, temp);
    }
    
    // Helper function for most_frequent, returns the word with the highest count.
    void inOrderTraversal_frequent(Node* node, string& w, int& a) const
    {
        if (node == nullptr)
            return;
        
        inOrderTraversal_frequent(node->left, w, a);
        
        if(node->count > a)
        {
            w = node->word;
            a = node->count;
        }
        
        inOrderTraversal_frequent(node->right, w, a);
    }
    
    // Helper function for num_singletons, returns the number of words qith count = 1
    void inOrderTraversal_singletons(Node* node, int& a) const
    {
        if (node == nullptr)
            return;
        
        inOrderTraversal_singletons(node->left, a);
        
        if(node->count == 1)
            a++;
        
        inOrderTraversal_singletons(node->right, a);
    }
    
    // Helper function for destructor
    void deleteTree(Node* node)
    {
        if (node == nullptr)
            return;
        
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
    
    // Helper function for print_words
    void print_inorder(Node* p, int& count) const
    {
        if (p == nullptr)
            return;
       
        print_inorder(p->left, count);
        
        cout << count << ". {\"" << p->word << "\", " << p->count << "}" <<endl;
        count++;
        
        print_inorder(p->right, count);
    }
    
public:

    // Defaul Constructor
    Wordlist()
    {
        root = nullptr;
    }
    
    // Constructor
    Wordlist(const string &input)
    {
        ifstream fin;
        fin.open(input);
        
        if (fin.fail())
        {
            cout << "Input file stream failed." << endl;
            return;
        }
        
        while(fin.eof() == false)
        {
            string s;
            fin >> s;
            
            if (!s.empty())
                root = insert(root, s);
        }
        
        fin.close();
    }
    
    // Destructor
    virtual ~Wordlist()
    {
        deleteTree(root);
    }
    
    // Returns the number of times w occurs as a word in the word list.
    int get_count(const string &w) const
    {
        string s = w;
        Node* temp = search(root, s);
        
        if(temp == nullptr)
            return 0;
        
        return temp->count;
    }

    // Returns the number of nodes in the word list.
    int num_different_words() const
    {
        int count = node_count(root);
        
        return count;
    }

    // Returns the total number of words in the word list, i.e. the sum of the
    // word counts.
    int total_words() const
    {
        int sum = 0;
        count_sum(root, sum);
        
        return sum;
    }

    // Returns true if the words in the word list are in ascending sorted order,
    // false otherwise.
    bool is_sorted() const
    {
        string temp = "";
        return sort_check(root, temp);
    }

    // Returns a string of the most frequent word in the format "word freq".
    // E.g. if the most frequent word is "the" with count 5437, then "the 5437"
    // is returned.
    //
    // If there is a tie, the first word in the list is returned. For an AVL
    // implementation, this means return the word that occurs first
    // alphabetically.
    //
    // Assumes the list is not empty.
    //
    string most_frequent() const
    {
        if(root != nullptr)
        {
            int freq = 0;
            string word;
            inOrderTraversal_frequent(root, word, freq);
            
            string answer = word + " " + to_string(freq);
            
            return answer;
        }
        else
        {
            string s2 = "The tree is empty";
            return s2;
        }
    }

    // Returns the number of nodes with count 1.
    int num_singletons() const
    {
        int answer = 0;
        inOrderTraversal_singletons(root, answer);
        
        return answer;
    }

    // Adds w to the word list. If w is already in the word list, then increment
    // its count. Otherwise add a new Node (with count 1) at the alphabetically
    // correct location for the word.
    void add_word(const string &w)
    {
       root = insert(root, w);
    }
    
    void print_words() const
    {
        int count = 1;
        print_inorder(root, count);
    }
}; // class Wordlist
