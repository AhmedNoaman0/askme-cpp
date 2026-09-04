#include "AskMe_System.h"

#include <iostream>

using namespace std;

void AskMe_System::Print_Qs_To_Me()
{
    int id = user_controller.GetCurrentUser().GetId();
    question_controller.print_qs_to_user(id);
}

void AskMe_System::Print_Qs_From_Me()
{
    int id = user_controller.GetCurrentUser().GetId();
    question_controller.print_qs_from_user(id);
}

void AskMe_System::Answer_Question()
{
    int id = user_controller.GetCurrentUser().GetId();
    question_controller.Answer_Question(id);
}

void AskMe_System::Delete_Question()
{
    int id = user_controller.GetCurrentUser().GetId();

    question_controller.delete_question(id);
    question_controller.Update_Questions();
}

void AskMe_System::Ask_Question()
{
    pair<int, int> to_user_id = user_controller.ReadUserId();

    if (to_user_id.first == -1)
        return;

    question_controller.Ask_Question(
        user_controller.GetCurrentUser(),
        to_user_id);
}

void AskMe_System::List_System_Users()
{
    user_controller.Print_Users();
}

void AskMe_System::Load_Database()
{
    question_controller.Load_Quesitons();
    user_controller.Load_Users();
}

void AskMe_System::AccessSystem()
{
    int valid = -1;
    while (valid == -1)
    {
        int choice = first_menu();
        if (choice == 1)
            valid = user_controller.Login();
        else if (choice == 2)
            user_controller.SignUp();
    }
}

int AskMe_System::first_menu()
{
    int num = 5;

    while (num != 1 && num != 2)
    {
        cout << "Menu: \n\t 1:Login\n\t 2:Sign Up "
             << "\nEnter number in range 1 - 2: ";

        cin >> num;
    }

    return num;
}

int AskMe_System::second_menu()
{
    cout << "Menu: \n\t 1: Print Questions To Me "
         << "\n\t 2: Print Questions From Me"
         << "\n\t 3: Answer Question "
         << "\n\t 4: Delete Question "
         << "\n\t 5: Ask Question"
         << "\n\t 6: List System Users "
         << "\n\t 7: Feed "
         << "\n\t 8: Logout"
         << "\nEnter number in range 1 - 8: ";

    int num;
    cin >> num;

    return num;
}

void AskMe_System::run()
{
    Load_Database();
    AccessSystem();

    while (true)
    {
        Load_Database();

        int choice = second_menu();

        if (choice == 1)
            Print_Qs_To_Me();
        else if (choice == 2)
            Print_Qs_From_Me();
        else if (choice == 3)
            Answer_Question();
        else if (choice == 4)
            Delete_Question();
        else if (choice == 5)
            Ask_Question();
        else if (choice == 6)
            List_System_Users();
        // else if(choice == 7) // TODO: Print all users Feed
        else if (choice == 8)
            AccessSystem();
    }
}