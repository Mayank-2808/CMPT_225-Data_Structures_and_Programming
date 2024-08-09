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

class Wordlist : public Wordlist_base
{
    struct Node
    {
        string word;
        int count;
        Node *next;
    };
    
    Node* head;
    
public:
    
    Wordlist()
    {
        head = nullptr;
    }
    
    Wordlist(const string &input): Wordlist()
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
            if(s.length()== 0)
                break;
            add_word(s);
        }
    }
    
    ~Wordlist()
    {
        while(head != nullptr)
        {
            Node* p = head;
            head = head->next;
            
            delete p;
        }
    }
    
    int get_count(const string &w) const
    {
        Node* p = head;
        int c = 0;
        
        while(p != nullptr)
        {
            if(p->word == w)
            {
                c = p->count;
                break;
            }
            p = p->next;
        }
        
        return c;
    }
    
    int num_different_words() const
    {
        int c = 0;
        Node* p = head;
        
        while(p != nullptr)
        {
            c++;
            p = p->next;
        }
        
        return c;
    }
    
    int total_words() const
    {
        int total = 0;
        Node* p = head;
        
        while(p != nullptr)
        {
            int c = p->count;
            total += c;
            p = p->next;
        }
        
        return total;
    }
    
    bool is_sorted() const
    {
        Node* p = head;
        
        while(p->next != nullptr)
        {
            if(p->word > p->next->word)
                return false;
            p = p->next;
        }
        
        return true;
    }
    
    string most_frequent() const
    {
        if(head != nullptr)
        {
            Node* p = head;
            string answer = p->word;
            p = p->next;
            
            while(p!=nullptr)
            {
                if(get_count(answer) < get_count(p->word))
                    answer = p->word;
                p = p->next;
            }
            
            string s1 = answer + " ";
            int i = get_count(answer);
            s1 += to_string(i);
            
            return s1;
        }
        else
        {
            string s2 = "The list is empty";
            return s2;
        }
    }
    
    int num_singletons() const
    {
        int answer = 0;
        Node* p = head;
        
        while(p != nullptr)
        {
            if(p->count == 1)
                answer++;
            p = p->next;
        }
       
        return answer;
    }
    
    void add_word(const string &w)
    {
        Node* p = head;
        
        if(contains(w))
        {
            while(p != nullptr)
            {
                if(p->word == w)
                {
                    p->count += 1;
                    return;
                }
                p = p->next;
            }
        }
        else
        {
            if(head == nullptr)
            {
                Node* temp = new Node();
                temp->word = w;
                temp->count = 1;
                
                temp->next = nullptr;
                head = temp;
            }
            
            for(;p != nullptr; p = p->next)
            {
                if(p->word < w && p->next == nullptr)
                {
                    Node* temp = new Node;
                    temp->word = w;
                    temp->count = 1;
                    
                    p->next = temp;
                    temp->next = nullptr;
                    
                    break;
                }
                else if(p->word > w && p == head)
                {
                    Node* temp = new Node;
                    temp->word = w;
                    temp->count = 1;
                    
                    Node* s = head;
                    temp->next = s;
                    head = temp;
                    
                    break;
                }
                else if(p->word < w && p->next->word > w)
                {
                    Node* temp = new Node;
                    temp->word = w;
                    temp->count = 1;
                    
                    temp->next = p->next;
                    p->next = temp;
                    
                    break;
                }
            }
        }
    }
    
    void print_words() const
    {
        Node* p = head;
        int count = 1;
        
        while(p != nullptr)
        {
            cout << count << ". {\"" << p->word << "\", " << p->count << "}" <<endl;
            count++;
            p = p->next;
        }
    }
}; // class Wordlist
