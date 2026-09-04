#pragma once

#include "User.h"

#include <string>
#include <map>
#include <utility>

class User_Controller
{
private:
    User current_user;
    int last_id;
    std::map<std::string, User> username_object_map;

public:
    User &GetCurrentUser();
    void SetCurrentUser(const User &current_user);

    int GetLastId() const;
    void SetLastId(int last_id);

    const std::map<std::string, User> &GetUsernameObjectMap() const;
    void SetUsernameObjectMap(const std::map<std::string, User> &username_object_map);

    std::pair<int, int> ReadUserId();
    void Load_Users();
    void Update_User();
    int Login(int trails = 3);
    void SignUp();
    void Print_Users();
};