#include "User.h"
#include <cassert>
#include "Helpers.h"
using namespace std;

User::User()
{
}

User::User(string &line)
{
    vector<string> fields = SplitString(line);
    assert(fields.size() == 6);

    id = stoi(fields[0]);
    username = fields[1];
    password = fields[2];
    name = fields[3];
    email = fields[4];
    allow_anonymous_qs = stoi(fields[5]);
}

#include "User.h"
#include "Helpers.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

void User::Print()
{
    cout << "ID: " << id << "\tName: " << name << "\n";
}

string User::ToLine()
{
    ostringstream oss;

    oss << id << "," << username << "," << password << ","
        << name << "," << email << "," << allow_anonymous_qs;

    return oss.str();
}

void User::Read_User(const string &username, int id)
{
    SetUserName(username);
    SetId(id);

    string str;

    cout << "Enter password: ";
    cin >> str;
    SetPasswword(str);

    cout << "Enter your name: ";
    cin >> str;
    SetName(str);

    cout << "Enter your email: ";
    cin >> str;
    SetEmail(str);

    cout << "Allow anonymous questions?: (0 or 1) ";
    int num;
    cin >> num;
    SetAllowAnonymousQs(num);
}

// Getters & Setters

int User::GetId() const
{
    return id;
}

void User::SetId(int id)
{
    this->id = id;
}

int User::GetAllowAnonymousQs() const
{
    return allow_anonymous_qs;
}

void User::SetAllowAnonymousQs(int allow_anonymous_qs)
{
    this->allow_anonymous_qs = allow_anonymous_qs;
}

const string &User::GetUsername() const
{
    return username;
}

void User::SetUserName(const string &username)
{
    this->username = username;
}

const string &User::GetPassword() const
{
    return password;
}

void User::SetPasswword(const string &password)
{
    this->password = password;
}

const string &User::GetName() const
{
    return name;
}

void User::SetName(const string &name)
{
    this->name = name;
}

const string &User::GetEmail() const
{
    return email;
}

void User::SetEmail(const string &email)
{
    this->email = email;
}

const vector<int> &User::GetQuestionsToMeIds() const
{
    return questions_to_me_ids;
}

void User::SetQuestionsToMeIds(vector<int> questions_to_me_ids)
{
    this->questions_to_me_ids = questions_to_me_ids;
}

const vector<int> &User::GetQuestionsFromMeIds() const
{
    return questions_from_me_ids;
}

void User::SetQuestionsFromMeIds(vector<int> questions_from_me_ids)
{
    this->questions_from_me_ids = questions_from_me_ids;
}

void User::AddQuestionToMeId(int question_id)
{
    questions_to_me_ids.push_back(question_id);
}

void User::AddQuestionFromMeId(int question_id)
{
    questions_from_me_ids.push_back(question_id);
}