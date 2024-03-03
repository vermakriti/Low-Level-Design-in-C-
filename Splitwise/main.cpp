#include <bits/stdc++.h>
using namespace std;

class User;
class Expense;

enum ExpenseType
{
    EQUAL,
    EXACT,
    PERCENT
};

ExpenseType getType(string &s)
{

    ExpenseType type;
    if (s == "EQUAL")
        type = EQUAL;
    else if (s == "EXACT")
        type = EXACT;
    else
        type = PERCENT;
    return type;
}

vector<string> listOfInput(string &s)
{

    string word;
    stringstream ss(s);
    vector<string> ans;

    while (ss >> word)
    {
        ans.push_back(word);
    }
    return ans;
}

class User
{
    string user_id;
    int contact_no;
    string name;
    string email;

public:
    User()
    {
    }
    User(string user_id, int contact_no, string name, string email)
    {
        this->user_id = user_id;
        this->contact_no = contact_no;
        this->name = name;
        this->email = email;
    }
    User(string user_id)
    {
        this->user_id = user_id;
    }
    string getUserId()
    {
        return user_id;
    }
    int getContactNo()
    {
        return contact_no;
    }
    string getName()
    {
        return name;
    }
    string getEmail()
    {
        return email;
    }
};

class Expense
{
    User paid_user;
    double amount;
    ExpenseType type;
    vector<User> splits;
    vector<double> splits_amount;

public:
    Expense(User paid_user, double &amount, string expense_type, vector<User> splits)
    {
        this->paid_user = paid_user;
        this->amount = amount;
        this->type = getType(expense_type);
        this->splits = splits;
        splits_amount.clear();
    }
    Expense(User &paid_user, double &amount, string expense_type, vector<User> &splits, vector<double> &splits_amount)
    {
        this->paid_user = paid_user;
        this->amount = amount;
        this->type = getType(expense_type);
        this->splits = splits;
        this->splits_amount = splits_amount;
    }
    User getPaidUser()
    {
        return paid_user;
    }
    double getAmount()
    {
        return amount;
    }
    ExpenseType getExpenseType()
    {
        return type;
    }
    vector<User> getSplits()
    {
        return splits;
    }
};

class Split
{
    vector<Expense> expenses;
    map<string, map<string, int>> balance_sheet;

public:
    void splitEqually(User &user, vector<User> &splits, double amount)
    {

        Expense expense(user, amount, "EQUAL", splits);
        expenses.push_back(expense);

        string paid_user_id = user.getUserId();
        int user_count = splits.size();

        for (int i = 0; i < splits.size(); i++)
        {
            double d = amount / user_count;
            string user_id = splits[i].getUserId();
            if (paid_user_id != user_id)
            {
                balance_sheet[paid_user_id][user_id] += d;
                balance_sheet[user_id][paid_user_id] -= d;
            }
        }
    }
    void splitExactly(User &user, vector<User> &splits, vector<double> split_amount, double amount)
    {

        Expense expense(user, amount, "EXACT", splits, split_amount);
        expenses.push_back(expense);

        string paid_user_id = user.getUserId();
        int user_count = splits.size();

        for (int i = 0; i < splits.size(); i++)
        {
            string user_id = splits[i].getUserId();
            balance_sheet[paid_user_id][user_id] += split_amount[i];
            balance_sheet[user_id][paid_user_id] -= split_amount[i];
        }
    }
    void splitByPercent(User &user, vector<User> &splits, vector<double> split_percent, double amount)
    {

        Expense expense(user, amount, "PERCENT", splits, split_percent);
        expenses.push_back(expense);

        string paid_user_id = user.getUserId();
        int user_count = splits.size();

        for (int i = 0; i < splits.size(); i++)
        {
            double d = (amount * split_percent[i]) / 100.0;
            string user_id = splits[i].getUserId();
            if (paid_user_id != user_id)
            {
                balance_sheet[paid_user_id][user_id] += d;
                balance_sheet[user_id][paid_user_id] -= d;
            }
        }
    }
    void show()
    {
        if (balance_sheet.size() == 0)
        {
            cout << "No balances\n";
            return;
        }
        for (auto user : balance_sheet)
        {
            for (auto e : user.second)
            {
                if (e.second < 0)
                    cout << user.first << " owes " << e.first << ": " << abs(e.second) << "\n";
            }
        }
    }
    void showByUserId(string user_id)
    {

        if (balance_sheet.find(user_id) == balance_sheet.end())
        {
            cout << "No balances\n";
            return;
        }
        for (auto user : balance_sheet)
        {
            if (user.first == user_id)
            {
                for (auto e : user.second)
                {
                    if (e.second > 0)
                        cout << e.first << " owes " << user.first << ": " << e.second << "\n";
                    else if (e.second < 0)
                        cout << user.first << " owes " << e.first << ": " << abs(e.second) << "\n";
                }
            }
        }
    }
};

int main()
{
    string expense_type;
    double amount;
    int user_count;
    unordered_map<string, User> users;

    string input;
    Split split;

    while (1)
    {

        getline(cin, input);
        if (input == "exit")
            break;

        vector<string> list = listOfInput(input);

        if (list[0] == "EXPENSE")
        {
            if (users.find(list[1]) == users.end())
            {
                User user(list[1]);
                users[list[1]] = user;
            }
            double amount = 1.0 * stoi(list[2]);
            int user_count = stoi(list[3]);

            vector<User> splits;
            vector<double> split_amount;
            string expense_type = list[user_count + 4];

            for (int i = 4; i < user_count + 4; i++)
            {
                if (users.find(list[i]) == users.end())
                {
                    User user(list[i]);
                    users[list[i]] = user;
                }
                splits.push_back(users[list[i]]);
            }

            if (expense_type != "EQUAL")
            {
                for (int i = user_count + 5; i < 2 * user_count + 5; i++)
                {
                    double d = 1.0 * stoi(list[i]);
                    split_amount.push_back(d);
                }
                if (expense_type == "EXACT")
                    split.splitExactly(users[list[1]], splits, split_amount, amount);
                else
                    split.splitByPercent(users[list[1]], splits, split_amount, amount);
            }
            else
                split.splitEqually(users[list[1]], splits, amount);
        }
        else if (input == "SHOW")
            split.show();
        else
        {
            split.showByUserId(list[1]);
        }
    }
}