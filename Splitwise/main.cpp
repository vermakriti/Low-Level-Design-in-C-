#include<bits/stdc++.h>
using namespace std;

enum ExpenseType
{
    EQUAL,
    EXACT,
    PERCENT
};

ExpenseType getType(string &s){

    ExpenseType type;
    if (s == "EQUAL")
        type = EQUAL;
    else if(s == "EXACT")
        type = EXACT;
    else
        type = PERCENT;
    return type;
}

vector<int> listOfInput(string &s){

    string word;
    stringstream ss(s);
    vector<int> ans;

    while(ss >> word){
        ans.push_back(word);
    }
    return ans;
}

class User{

    public:

        string user_id;
        int contact_no;
        string name;
        string email;

        User(string user_id, int contact_no, string name, string email){
            this->user_id = user_id;
            this->contact_no = contact_no;
            this->name = name;
            this->email = email;
        }
};

class Group{

    public:
        map<string, User> user_map;
        map<string, map<string, double>> balance_sheet;

        void add_user(string user_id,int contact_no, string name, string email){
            User user(user_id, contact_no, name, email);
            
        }
}

class Expense
{

public:
    string paid_user_id;
    User paid_by;
    double amount;
    ExpenseType type;
    vector<string> users;
    vector<int> splits;

    Expense(string user_id, double amount, string expense_type, vector<string> users)
    {
        this->user_id = user_id;
        this->amount = amount;
        this->type = getType(expense_type);
        this->users = users;
    }
};

class Split{

    public :
        vector<Expense> expenses;
        map<string, User> userMap;
        map<string, map<string, double>> balance_sheet;



}

int
main()
{

    string input;
    Split split;

    while (1)
    {
        getline(cin, input);
        vector<int> list = listOfInput(input);

        if(list[0] == "exit")
            break;
        if(list[0] == "EXPENSE"){

        }   
        else{

        } 
    }
}