#pragma once

#include "User_Controller.h"
#include "Question_Controller.h"

class AskMe_System
{
private:
    User_Controller user_controller;
    Question_Controller question_controller;

public:
    void Print_Qs_To_Me();
    void Print_Qs_From_Me();

    void Answer_Question();
    void Delete_Question();
    void Ask_Question();

    void List_System_Users();

    void Load_Database();
    void AccessSystem();

    int first_menu();
    int second_menu();

    void run();
};