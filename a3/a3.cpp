// a3.cpp

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
// Do not #include any other files!
//
#include "Announcement.h"
#include "JingleNet_announcer.h"
#include "Queue_base.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

class Queue : public Queue_base<Announcement>
{
    struct Node
    {
        Announcement data;
        Node *next;
    };
    
    Node *head = nullptr; // always points to the front node of queue
    Node *tail = nullptr; // always points to the back node of queue
    int num_elements = 0;
    
public:
    // put x on the back of the queue
    void enqueue(const Announcement &x)
    {
        if (empty())
        {
            head = new Node{x, nullptr};
            tail = head;
        }
        else
        {
            tail->next = new Node{x, nullptr};
            tail = tail->next;
        }
        num_elements++;
    }
    
    // remove the front element; error if queue is empty
    void dequeue()
    {
        if(empty())
            throw runtime_error("dequeue: queue is empty");
       
        if (head == tail)
        {
            tail = nullptr;
        }
        Node *temp = head;
        head = head->next;
        delete temp;
        
        num_elements--;
    }
    
    // return a reference to the front element; error if queue is empty
    const Announcement &front() const
    {
        if(empty())
            throw runtime_error("front: queue is empty");
        return head->data;
    }
    
    // return true if stack is empty; default implementation is to check if
    // size() is 0
    bool empty() const { return size() == 0; }
    
    // return the number of elements in the queue
    int size() const { return num_elements; }
    
    // return a pointer to the head
    Node* get_headptr()
    {
        if(empty())
            throw runtime_error("front: queue is empty");
        return head;
    }
    
    ~Queue()
    {
        while (!empty())
            dequeue();
    }
};

class JingleNet
{
private:
    
    Queue Santa;
    Queue Reindeer;
    Queue Elf2;
    Queue Elf1;
    Queue Snowman;
    
public:
    
    void send(const Announcement& s)
    {
        if(s.get_rank() == Rank::SANTA)
            Santa.enqueue(s);
        else if(s.get_rank() == Rank::REINDEER)
            Reindeer.enqueue(s);
        else if(s.get_rank() == Rank::ELF2)
            Elf2.enqueue(s);
        else if(s.get_rank() == Rank::ELF1)
            Elf1.enqueue(s);
        else
            Snowman.enqueue(s);
    }
    
    void remove_all(const string& username)
    {
        Queue temp;
        
        // Removing from the Santa Queue
        while(!Santa.empty())
        {
            if(Santa.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Santa.get_headptr()->data);
            
            Santa.dequeue();
        }
        while(!temp.empty())
        {
            Santa.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        // Removing from the Reindeer Queue
        while(!Reindeer.empty())
        {
            if(Reindeer.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Reindeer.get_headptr()->data);
            
            Reindeer.dequeue();
        }
        while(!temp.empty())
        {
            Reindeer.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Removing from the Elf2 Queue
        while(!Elf2.empty())
        {
            if(Elf2.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Elf2.get_headptr()->data);
            
            Elf2.dequeue();
        }
        while(!temp.empty())
        {
            Elf2.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Removing from the Elf1 Queue
        while(!Elf1.empty())
        {
            if(Elf1.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Elf1.get_headptr()->data);
            
            Elf1.dequeue();
        }
        while(!temp.empty())
        {
            Elf1.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Removing from the Snowman Queue
        while(!Snowman.empty())
        {
            if(Snowman.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Snowman.get_headptr()->data);
            
            Snowman.dequeue();
        }
        while(!temp.empty())
        {
            Snowman.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
    }
    
    void promote_announcements(const string& username)
    {
        Queue temp;
        
        // Promoting from the Reindeer Queue
        while(!Reindeer.empty())
        {
            if(Reindeer.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Reindeer.get_headptr()->data);
            else{
                Announcement temp1 = Reindeer.get_headptr()->data;
                Announcement temp2(temp1.get_sender_name(), Rank::SANTA, temp1.get_text() );
                Santa.enqueue(temp2);
            }
            Reindeer.dequeue();
        }
        while(!temp.empty())
        {
            Reindeer.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Promoting from the Elf2 Queue
        while(!Elf2.empty())
        {
            if(Elf2.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Elf2.get_headptr()->data);
            else{
                Announcement temp1 = Elf2.get_headptr()->data;
                Announcement temp2(temp1.get_sender_name(), Rank::REINDEER, temp1.get_text() );
                Reindeer.enqueue(temp2);
            }
            Elf2.dequeue();
        }
        while(!temp.empty())
        {
            Elf2.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Promoting from the Elf1 Queue
        while(!Elf1.empty())
        {
            if(Elf1.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Elf1.get_headptr()->data);
            else{
                Announcement temp1 = Elf1.get_headptr()->data;
                Announcement temp2(temp1.get_sender_name(), Rank::ELF2, temp1.get_text() );
                Elf2.enqueue(temp2);
            }
            Elf1.dequeue();
        }
        while(!temp.empty())
        {
            Elf1.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
        
        //Promoting from the Snowman Queue
        while(!Snowman.empty())
        {
            if(Snowman.get_headptr()->data.get_sender_name() != username)
                temp.enqueue(Snowman.get_headptr()->data);
            else{
                Announcement temp1 = Snowman.get_headptr()->data;
                Announcement temp2(temp1.get_sender_name(), Rank::ELF1, temp1.get_text() );
                Elf1.enqueue(temp2);
            }
            Snowman.dequeue();
        }
        while(!temp.empty())
        {
            Snowman.enqueue(temp.get_headptr()->data);
            temp.dequeue();
        }
    }
    
    void announce(const int& i)
    {
        int n = i;
        
        while(Santa.size() != 0 && n != 0)
        {
            jnet.announce(Santa.front());
            Santa.dequeue();
            n--;
        }
        
        while(Reindeer.size() != 0 && n != 0)
        {
            jnet.announce(Reindeer.front());
            Reindeer.dequeue();
            n--;
        }
        
        while(Elf2.size() != 0 && n != 0)
        {
            jnet.announce(Elf2.front());
            Elf2.dequeue();
            n--;
        }
        
        while(Elf1.size() != 0 && n != 0)
        {
            jnet.announce(Elf1.front());
            Elf1.dequeue();
            n--;
        }
        
        while(Snowman.size() != 0 && n != 0)
        {
            jnet.announce(Snowman.front());
            Snowman.dequeue();
            n--;
        }
    }
};

int main(int argc, char *argv[])
{
    // Check that the user provided a filename.
    if (argc != 2)
    {
        cout << "Usage: " << argv[0] << " <filename>" << endl;
        //
        // Returning a non-zero value from main indicates the program ended
        // abnormally. We don't care about main return values, but in some cases
        // they are useful. If this program was used as part of a shell script,
        // then the script might check this return value in an if-statement.
        //
        return 1;
    }
    
    // Initializing the JiggleNet Network
    JingleNet network;
    
    //
    // Read the contents of the file named by argv[1]
    //
    string filename = argv[1];
    
    ifstream infile(filename);
    string line;

    while (getline(infile, line))
        {
            // getting the command
            size_t pos = line.find(' ');
            string command = line.substr(0, pos);
            line = line.substr(pos + 1);
            
            if(command == "SEND")
            {
                Announcement a(line);
                network.send(a);
            }
                
            
            if(command == "REMOVE_ALL")
            {
                // getting the username
                string username = line;
                
                network.remove_all(username);
            }
            
            if(command == "PROMOTE_ANNOUNCEMENTS")
            {
                // getting the username
                string username = line;
                network.promote_announcements(username);
            }

            if(command == "ANNOUNCE")
            {
                // getting the number of announcements to be made
                int n = stoi(line);
                
                network.announce(n);
            }
        }
}
