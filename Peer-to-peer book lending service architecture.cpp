// backend architecture for a peer-to-peer book lending service

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <ctime>

using namespace std;

// class of the user
class User
{
    int score;
  string name;
    
    
public:
    User (string name, int score)
    {
        this->name = name;
        this->score = score;
    }
    void setName(string name)
    {
        name = name;
    }
    void addScore(int score)
    {
        score += score;
    }
    string getName()
    {
        return name;
    }
    int getScore()
    {
        return score;
    }
};

// class of a book
class Book{
    string name;
    string book_author;
    string year;
    string book_owner;
    string book_holder;
    bool goodCondition; 
    time_t return_deadline; // returns deadline which is 30 days after book is borrowed
    vector <string> history; // stores history of previous book users
  
  public:
    Book (string n, string b_a, string b_o, string y)
    {
        name = n;
        book_author = b_a;
        book_owner = b_o;
        year = y;
        goodCondition = true; // true if the book is in good condtition
        
    }
      void setHolder(string b_h)
      {
        book_holder = b_h;
      }
      string getHolder()
      {
        return book_holder;
      }
      void setReturnDeadline()
      {
        return_deadline = 2592000 + time(0); // 30 days after book is borrowed
    }
      time_t getReturnDeadline()
      {
        return return_deadline;
    }
   void IncludeInHistory(string p)
   {
        history.push_back(p);
    }
    void setCondition(bool g)
    {
        goodCondition = g;
    }
  bool isGood()
     {
        return goodCondition;
    }
    string getAuthor()
    {
        return book_author;
    }
    string getName()
    {
        return name;
    }
    string getOwner()
    {
        return book_owner;
    }
    string getYear(){
        return year;
    }
    vector <string> getHistory(){
        return history;
    }
    bool isAvailable(){
        return (book_holder == " ");
    }
};


// To find out if the user is registered
int findPerson(string user_name, vector<User> user)
{
    for (int j = 0; j < user.size(); j++)
{
        if (user_name == user[j].getName()) 
{
       return j;
}
    }
    return -1;
}

// To find out if a book is registered
int findBook(string name, string book_author, string year, vector<Book> book)
{
    for (int i = 0; i < book.size(); i++)
{
        if (name == book[i].getName() && book_author == book[i].getAuthor() && year == book[i].getYear())
            return i;
}
    return -1;
}

// For a book to be registered
void bookRegistration(string worker, string bookName, string book_author, string year, vector <User>& user, vector <Book>& book)
{
    Book tempBook(bookName, book_author, worker, year);
    book.push_back(tempBook);
    
    int index = findPerson(worker, user);
    
    if (index != -1)
{
        user[index].addScore(1);
    }
    else
{
        User temp(worker, 1);
        user.push_back(temp);
    }
}

// To request a book to be borrowed
void bookRequested(string person_borrowing, string bookName, string book_author, string year, vector<User>& user, vector <Book>& book)
{
    int i = findBook(bookName, book_author, year, book);
    if (i == -1)
        cout << bookName << " by " << book_author <<  " is not one of the registered books \n" << endl;

    else if (!book[i].isAvailable())
    {
        cout << bookName << " by " << book_author << "released in"<< year <<" is currently unavailable. This book has been borrowed by " << book[i].getHolder() << endl;
        time_t deadline = book[i].getReturnDeadline();
        tm *timePtr = localtime(&deadline);
        cout << " Leave your email with the nearest worker. We will be in touch as soon as the book is available. If not, check in again after "<< (timePtr->tm_mon)+1 << "/" << (timePtr->tm_mday) << "/" << (timePtr->tm_year)+1900 << "\n" << endl;
    }
    else
    {
        book[i].setHolder(person_borrowing);
        string lender = book[i].getOwner();
        int j = findPerson(lender,user);
        user[j].addScore(5);
        book[i].setReturnDeadline();
        time_t deadline = book[i].getReturnDeadline();
        tm *timePtr = localtime(&deadline);
        cout << "This book is to be returned by " << (timePtr->tm_mon)+1 << "/" << (timePtr->tm_mday) << "/" << (timePtr->tm_year)+1900 << endl;
    }
}
       
// To return a borrowed book 
void bookReturn(string person_returning, string bookName, string book_author, string year, bool goodCondition, vector<User>& user, vector <Book>& book)
{
    int i = findBook(bookName, book_author, year, book);
    book[i].setHolder("");
    
    book[i].IncludeInHistory(person_returning);
    
    int j = findPerson(person_returning, user);
    
// To determine the score to be allotted to the person returning the book based on the book's condition
    if(goodCondition)
{
        user[j].addScore(2);
    }
    else
{
        user[j].addScore(-10);
    }
    
    
// To determine score to be deducted for not meeting deadline
    time_t present = time(0)/60/60/24;
    time_t deadline = book[i].getReturnDeadline()/60/60/24;
    if(present > deadline){
        user[j].addScore(-2 * (int)(present - deadline));
    }
}

// To print history of previous book users
void printHistory(string bookName, string book_author, string year, vector<Book> book)
{
    int i = findBook(bookName, book_author, year, book);
    if (i == -1)
        cout << bookName << " by " << book_author << "released in" << year << " is not one of the registered books. " << endl;
    
    else{
        vector <string> history = book[i].getHistory();
        if (history.empty())
            cout << bookName << " by " << book_author << " released in " << year << " has never been borrowed" << endl;
        else {
            for (int i = 0; i < history.size(); i++)
{
                cout << history[i] << endl;
            }
        }
    }
}

void printScores(vector <User> user) // To print scores of those registered
{
    for (int i = 0; i < user.size(); i++)
{
        cout << user[i].getName() << " has a score of  " << user[i].getScore() << endl;
    }
}

// To find a book by its title
vector <Book> findBookByName(string book_title, vector<Book> books_list)
{
    vector<Book> list;
    for (int i = 0; i < books_list.size(); i++)
{
        if (books_list[i].getName() == book_title && books_list[i].isAvailable())
{
            list.push_back(books_list [i]);
        }
    }
    return list;
}

// To find book by author’s name
vector <Book> findBookByAuthor(string book_author, vector<Book> books_list)
{
    vector<Book> list;
    for (int i = 0; i < books_list.size(); i++){
        if (books_list[i].isAvailable() && books_list[i].getAuthor() == book_author)
{
            list.push_back(books_list [i]);
        }
    }
    return list;
}

// To find books by its released year
vector <Book> findBookByYear(string year, vector<Book> books_list)
{
    vector<Book> list;
    for (int i = 0; i < books_list.size(); i++)
{
        if (books_list[i].getYear() == year  && books_list[i].isAvailable())
{
            list.push_back(books_list[i]);
        }
    }
    return list;
}

