#include <bits/stdc++.h>
using namespace std;

vector<string> find_details(string &input)
{
    string word;
    vector<string> ans;
    stringstream ss(input);

    while (ss >> word)
    {
        ans.push_back(word);
    }
    return ans;
}

vector<string> value(string &input)
{
    string word;
    vector<string> ans;
    stringstream ss(input);

    while (getline(ss, word, ','))
    {
        ans.push_back(word);
    }
    return ans;
}

class User
{
    int borrowed_till_now;
    string user_id;

public:
    User()
    {
    }
    User(string user_id)
    {
        borrowed_till_now = 0;
        this->user_id = user_id;
    }
    string getUserId()
    {
        return user_id;
    }
    int getBorrowedTillNowCount()
    {
        return borrowed_till_now;
    }
    void setBorrowedTillNowCount()
    {
        ++borrowed_till_now;
    }
};

class BookDetail
{
    int book_id;
    string title;
    vector<string> authors;
    vector<string> publishers;

public:
    BookDetail()
    {
    }
    BookDetail(int book_id, string title, vector<string> authors, vector<string> &publishers)
    {
        this->book_id = book_id;
        this->title = title;
        this->authors = authors;
        this->publishers = publishers;
    }
    int getBookId()
    {
        return book_id;
    }
    string getTitle()
    {
        return title;
    }
    vector<string> getAuthors()
    {
        return authors;
    }
    vector<string> getPublishers()
    {
        return publishers;
    }
};

class BookItem : public BookDetail
{
    string book_item_id;

public:
    BookItem() : BookDetail()
    {
    }
    BookItem(string book_item_id, int book_id, string title, vector<string> authors, vector<string> publishers) : BookDetail(book_id, title, authors, publishers)
    {
        this->book_item_id = book_item_id;
    }
    string getBookItemId()
    {
        return book_item_id;
    }
};

class Rack
{
    vector<BookItem> books;

public:
    Rack()
    {
        books.clear();
    }
    void addBook(string book_item_id, int book_id, string title, vector<string> authors, vector<string> publishers)
    {
        BookItem bookItem(book_item_id, book_id, title, authors, publishers);
        books.push_back(bookItem);
    }
    int getAvailableBookCount()
    {
        return books.size();
    }
    int getBookId()
    {
        return books[0].getBookId();
    }
    string getBookItemId()
    {
        return books[0].getBookItemId();
    }
    string getBookItemTitle()
    {
        return books[0].getTitle();
    }
    vector<string> getAuthors()
    {
        return books[0].getAuthors();
    }
    vector<string> getPublishers()
    {
        return books[0].getPublishers();
    }
    BookItem getBookItem()
    {
        return books[0];
    }
    bool isAuthorIdPresent(string author_id)
    {
        vector<string> authors = books[0].getAuthors();
        for (int i = 0; i < authors.size(); i++)
        {
            if (authors[i] == author_id)
                return true;
        }
        return false;
    }
};
class BookLending
{

    User user;
    map<BookItem, string> books;

public:
    BookLending(User &user, BookItem bookItem, string due_date)
    {
        this->user = user;
        user.setBorrowedTillNowCount();
        books[bookItem] = due_date;
    }
    User getUser()
    {
        return user;
    }
    string getUserId()
    {
        return user.getUserId();
    }
    void setBookItem(BookItem bookItem, string due_date)
    {
        books[bookItem] = due_date;
    }
    void setBorrowedTillNowCount()
    {
        user.setBorrowedTillNowCount();
    }
    int getBorrowedTillNowCount()
    {
        return user.getBorrowedTillNowCount();
    }
};

class Library
{
    int rack_count;
    vector<Rack> racks;
    list<BookLending> users;
    unordered_map<string, int> book_copies;
    unordered_map<int, int> books;

public:
    Library(int rack_count)
    {
        this->rack_count = rack_count;
        racks.resize(rack_count);

        for (int i = 0; i < rack_count; i++)
        {
            Rack rack;
            racks[i] = rack;
        }
    }
    int isBookCopyPresent(string &book_copy_id)
    {
        return book_copies.find(book_copy_id) != book_copies.end();
    }
    int isBookPresent(int book_id)
    {
        return books.find(book_id) != books.end();
    }
    vector<int> addBook(int &book_id, string &title, vector<string> &authors, vector<string> &publishers, vector<string> &book_copy)
    {
        vector<int> rack_no;
        int space_available = 0;

        for (int i = 0; i < rack_count; i++)
        {
            if (racks[i].getAvailableBookCount() == 0)
                space_available++;
        }
        if (space_available < book_copy.size())
            return rack_no;

        int b = 0, i = 0;
        while (i < rack_count && b < book_copy.size())
        {
            book_copies[book_copy[b]]++;
            books[book_id]++;
            if (racks[i].getAvailableBookCount() == 0)
            {
                racks[i].addBook(book_copy[b++], book_id, title, authors, publishers);
                rack_no.push_back(i + 1);
            }
            ++i;
        }
        return rack_no;
    }
    vector<int> searchByBookId(int book_id, string &title, vector<string> &authors, vector<string> &publishers, vector<string> &book_copy)
    {

        vector<int> rack_no;
        for (int i = 0; i < rack_count; i++)
        {
            if (racks[i].getAvailableBookCount())
            {
                if (racks[i].getBookId() == book_id)
                {
                    title = racks[i].getBookItemTitle();
                    authors = racks[i].getAuthors();
                    publishers = racks[i].getPublishers();
                    book_copy.push_back(racks[i].getBookItemId());
                    rack_no.push_back(i + 1);
                }
            }
        }
        return rack_no;
    }
    vector<int> searchByAuthorId(string &author_id, vector<string> &title, vector<vector<string>> &authors, vector<vector<string>> &publishers, vector<string> &book_copy, vector<int> &book_id)
    {

        vector<int> rack_no;
        for (int i = 0; i < rack_count; i++)
        {
            if (racks[i].getAvailableBookCount())
            {
                if (racks[i].isAuthorIdPresent(author_id))
                {
                    title.push_back(racks[i].getBookItemTitle());
                    authors.push_back(racks[i].getAuthors());
                    publishers.push_back(racks[i].getPublishers());
                    book_id.push_back(racks[i].getBookId());
                    book_copy.push_back(racks[i].getBookItemId());
                    rack_no.push_back(i + 1);
                }
            }
        }
        return rack_no;
    }
    int removeBook(string &book_copy_id)
    {
        for (int i = 0; i < rack_count; i++)
        {
            if (racks[i].getBookItemId() == book_copy_id)
            {
                Rack rack;
                racks[i] = rack;
                return i + 1;
            }
        }
        return 0;
    }
    int borroewByBookId(string &user_id, int book_id, string due_date)
    {
        for (int i = 0; i < rack_count; i++)
        {
            if (racks[i].getAvailableBookCount() && racks[i].getBookId() == book_id)
            {
                int found = 0;
                for (auto it = users.begin(); it != users.end(); ++it)
                {
                    if (it->getUserId() == user_id)
                    {
                        if (it->getBorrowedTillNowCount() == 5)
                            return -1;
                        it->setBorrowedTillNowCount();
                        it->setBookItem(racks[i].getBookItem(), due_date);
                        found = 1;
                        break;
                    }
                }
                if (!found)
                {
                    User user(user_id);
                    BookLending bookLending(user, racks[i].getBookItem(), due_date);
                    users.push_back(bookLending);
                }
                Rack rack;
                racks[i] = rack;
                return i + 1;
            }
        }
        return 0;
    }
};

int main()
{

    int book_id;
    string book_copy_id;
    string input, title;
    vector<string> detail, authors, publishers, book_copy;

    getline(cin, input);
    detail = find_details(input);

    Library library(stoi(detail[1]));
    cout << "Created library with " << detail[1] << " racks\n";

    while (1)
    {
        getline(cin, input);
        if (input == "exit")
            break;
        detail = find_details(input);

        if (detail[0] == "add_book")
        {
            book_id = stoi(detail[1]);
            title = detail[2];
            authors = value(detail[3]);
            publishers = value(detail[4]);
            book_copy = value(detail[5]);
            vector<int> rack = library.addBook(book_id, title, authors, publishers, book_copy);
            if (rack.size() == 0)
                cout << "Rack not available\n";
            else
            {
                cout << "Added Book to racks: ";
                for (int i = 0; i < rack.size(); i++)
                {
                    if (i == rack.size() - 1)
                        cout << rack[i] << "\n";
                    else
                        cout << rack[i] << ",";
                }
            }
        }
        else if (detail[0] == "search")
        {
            if (detail[1] == "book_id")
            {
                string title;
                vector<int> rack_no;
                vector<string> authors, publishers, book_copy;
                rack_no = library.searchByBookId(stoi(detail[2]), title, authors, publishers, book_copy);
                for (int i = 0; i < rack_no.size(); i++)
                {
                    cout << "Book Copy: " << book_copy[i] << " " << detail[2] << " " << title << " ";
                    for (int j = 0; j < authors.size(); j++)
                    {
                        if (j == authors.size() - 1)
                            cout << authors[j] << " ";
                        else
                            cout << authors[j] << ",";
                    }
                    for (int j = 0; j < authors.size(); j++)
                    {
                        if (j == publishers.size() - 1)
                            cout << publishers[j] << " ";
                        else
                            cout << publishers[j] << ",";
                    }
                    cout << rack_no[i] << "\n";
                }
            }
            else if (detail[1] == "author_id")
            {
                vector<string> title;
                vector<int> rack_no, book_id;
                vector<string> book_copy;
                vector<vector<string>> authors, publishers;
                rack_no = library.searchByAuthorId(detail[2], title, authors, publishers, book_copy, book_id);
                for (int i = 0; i < rack_no.size(); i++)
                {
                    cout << "Book Copy: " << book_copy[i] << " " << book_id[i] << " " << title[i] << " ";
                    for (int j = 0; j < authors[i].size(); j++)
                    {
                        if (j == authors[i].size() - 1)
                            cout << authors[i][j] << " ";
                        else
                            cout << authors[i][j] << ",";
                    }
                    for (int j = 0; j < publishers[i].size(); j++)
                    {
                        if (j == publishers[i].size() - 1)
                            cout << publishers[i][j] << " ";
                        else
                            cout << publishers[i][j] << ",";
                    }
                    cout << rack_no[i] << "\n";
                }
            }
        }
        else if (detail[0] == "remove_book_copy")
        {
            int rack_no = library.removeBook(detail[1]);
            if (rack_no)
                cout << "Removed book copy: book_copy6 from rack: " << rack_no << "\n";
            else
                cout << "Invalid Book Copy ID\n";
        }
        else if (detail[0] == "borrow_book")
        {
            if (library.isBookPresent(stoi(detail[1])))
            {
                int rack_no = library.borroewByBookId(detail[2], stoi(detail[1]), detail[3]);
                if (rack_no == 0)
                    cout << "Not available\n";
                else if (rack_no == -1)
                    cout << "Overlimit\n";
                else
                    cout << "Borrowed Book from rack: " << rack_no << "\n";
            }
            else
                cout << "Invalid Book ID\n";
        }
        else if (detail[0] == "borrow_book_copy")
        {
        }
    }
}
