#include "User_Controller.h"
#include "Helpers.h"

#include <iostream>
#include <algorithm>

using namespace std;

/*
    User& GetCurrentUser();
    void SetUserId(const User& current_user);

*/

User &User_Controller::GetCurrentUser()
{
    return current_user;
}

void User_Controller::SetCurrentUser(const User &current_user)
{
    this->current_user = current_user;
}

int User_Controller::GetLastId() const
{
    return last_id;
}

void User_Controller::SetLastId(int last_id)
{
    this->last_id = last_id;
}

const map<string, User> &User_Controller::GetUsernameObjectMap() const
{
    return username_object_map;
}

void User_Controller::SetUsernameObjectMap(const map<string, User> &username_object_map)
{
    this->username_object_map = username_object_map;
}

pair<int, int> User_Controller::ReadUserId()
{
    cout << "Enter Used id or -1 to cancel";

    int user_id;
    cin >> user_id;

    if (user_id == -1)
        return make_pair(-1, -1);

    for (auto &pair : username_object_map)
    {
        if (pair.second.GetId() == user_id)
            return make_pair(
                pair.second.GetId(),
                pair.second.GetAllowAnonymousQs());
    }

    cout << "User ID not found. Please try again.\n";

    return ReadUserId();
}

void User_Controller::Load_Users()
{
    username_object_map.clear();
    last_id = 0;

    string path = "data/users.txt";
    vector<string> lines = ReadFileLines(path);

    for (auto &line : lines)
    {
        User user(line);

        last_id = max(last_id, user.GetId());

        username_object_map[user.GetUsername()] = user;
    }
}

void User_Controller::Update_User()
{
    vector<string> lines;
    string path = "data/users.txt";

    for (auto &pair : username_object_map)
        lines.push_back(pair.second.ToLine());

    WriteFileLines(path, lines);
}

int User_Controller::Login(int trails)
{
    Load_Users();
    bool valid_exist = false;
    User user_exist;
    while (trails--)
    {
        string name, pass;

        cout << "Enter usename & Password";
        cin >> name >> pass;

        current_user.SetUserName(name);
        current_user.SetPasswword(pass);

        if (!username_object_map.count(current_user.GetUsername()))
        {
            cout << "\nInvalid Username or Password. Try again \n\n";
            continue;
        }

        user_exist = username_object_map[current_user.GetUsername()];

        if (user_exist.GetPassword() != current_user.GetPassword())
        {
            cout << "\nInvalid Username or Password. Try again \n\n";
            continue;
        }
        valid_exist = true;
        break;
    }
    if (valid_exist)
    {
        current_user = user_exist;
        return 1;
    }
    return -1;
}

void User_Controller::SignUp()
{
    string username;

    while (true)
    {
        cout << "Enter user name (no spaces): ";
        cin >> username;

        if (username_object_map.count(username))
            cout << "Already used. Try again\n";
        else
            break;
    }

    current_user.Read_User(username, ++last_id);

    username_object_map[current_user.GetUsername()] = current_user;

    cout << "User added successfully.\n";

    Update_User();
    // Login();
}

void User_Controller::Print_Users()
{
    for (auto &pair : username_object_map)
    {
        pair.second.Print();
    }
}