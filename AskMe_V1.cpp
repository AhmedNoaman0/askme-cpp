#include<iostream>
#include<vector>
#include<map>
using namespace std;

struct User
{
    int id;
    string username;
    string name;
    string email;
    int password;
    bool allow_anonymous_qs;
};

struct Question
{
    int question_id;
    int parent_question_id; // if it's a parent_qs -> -1
    int from_user_id;
    int to_user_id;
    int is_anonymous_qs;
    string text;
    Question()
    {

    }
    Question(int from_id,int to_id,string _text)
    {
        from_user_id = from_id;
        to_user_id = to_id;
        text = _text;
    }
};

struct User_Controller
{
    User current_user;
    int last_id = 0;
    map<string,User> username_object_map;

    pair<int,int> ReadUserId()
    {
        cout<<"Enter Used id or -1 to cancel";
        int user_id;
        cin>>user_id;
        if(user_id == -1)
            return make_pair(-1,-1);
        for(auto& pair : username_object_map )
        {
            if(pair.second.id == user_id)
                return make_pair(pair.second.id,pair.second.allow_anonymous_qs);
        }
        cout << "User ID not found. Please try again.\n";
        return ReadUserId();
    }


    void Login()
    {
        while (true)
        {
            cout<<"Enter usename & Password";
            cin>>current_user.username>>current_user.password;
            if(!username_object_map.count(current_user.username))
            {
                cout<<"\nInvalid Username or Password. Try again \n\n";
                continue;
            }
            User user_exist = username_object_map[current_user.username];

            if(user_exist.password != current_user.password)
            {
                cout<<"\nInvalid Username or Password. Try again \n\n";
                continue;
            }
            current_user = user_exist;
            break;
        }
        
        
    }
    void SignUp()
    {
        //* code a logic for the same username is used

        cout << "Enter user name (no spaces): ";
        cin >> current_user.username;
        cout << "Enter password: ";
        cin >> current_user.password;
        cout << "Enter your name: ";
        cin >> current_user.name;
        cout << "Enter your email: ";
        cin >> current_user.email;
        cout << "Allow anonymous questions?: (0 or 1) ";
        cin >> current_user.allow_anonymous_qs;

        current_user.id = ++last_id;
        username_object_map[current_user.username] = current_user;
        cout << "User added successfully.\n";
        Login();
    }


};

struct Question_Controller
{
    map<int,vector<int>> parentQsId_childQsId_map; // thread

    map<int,Question> QsId_object_map; // to access object by his id

    int last_id; // auto incrment 
    Question_Controller()
    {
        last_id = 0;
    }
    int read_parentQs_id()
    {
        cout<<"For thread question enter question id or -1 for new questions: ";
        int qs_id;
        cin>>qs_id;
        if(qs_id == -1)
            return -1;
        if (!QsId_object_map.count(qs_id)){
            cout << "No thread question with such ID. Try again\n";
            return read_parentQs_id();}
        return qs_id;
        
    }
    void Ask_Question(User& user,pair<int,int>& to_user_pair)
    {
        Question question;
        if(!to_user_pair.second){
            cout<<"Note: Anonymous questions are not allowed for this user\n";
            question.is_anonymous_qs = 0;}
        else{
            cout << "Is anonymous questions?: (0 or 1): ";
            cin >> question.is_anonymous_qs;
        }
        question.parent_question_id = read_parentQs_id();
        cout << "Enter question text: ";
        cin.ignore(); // ignore "/n" (caused by cin)
        getline(cin, question.text);
        question.from_user_id = user.id;
        question.to_user_id = to_user_pair.first;
        question.question_id = ++last_id;
        QsId_object_map[question.question_id] = question;
        // thread
        if(question.parent_question_id == -1) // case 1 this is parent qs
            parentQsId_childQsId_map[question.question_id].push_back(question.question_id);
        else
            parentQsId_childQsId_map[question.parent_question_id].push_back(question.question_id);
    }

};


struct AskMe_System
{
    User_Controller user_controller;
    Question_Controller question_controller;

    void Ask_Question()
    {
        pair to_user_id = user_controller.ReadUserId();
        if(to_user_id.first == -1)
            return;
        question_controller.Ask_Question(user_controller.current_user,to_user_id);
    }
    
    void AccessSystem()
    {
        int choice = first_menu();
        if(choice == 1)
            user_controller.Login();
        else if (choice == 2)
            user_controller.SignUp();
    }

    int first_menu()
    {
        int num = 5;
        while (num != 1 && num != 2)
        {        
            cout<<"Menu: \n\t 1:Login\n\t 2:Sign Up \nEnter number in range 1 - 2: ";
            cin>>num;
        }
        return num;
    }

    int second_menu()
    {
        cout<<"Menu: \n\t 1: Print Questions To Me \n\t 2: Print Questions From Me"
            <<"\n\t 3: Answer Question \n\t 4: Delete Question \n\t 5: Ask Question"
            <<"\n\t 6: List System Users \n\t 7: Feed \n\t 8: Logout"
            <<"\nEnter number in range 1 - 8: ";
        int num;
        cin>>num;
        return num;
    }
    
    void run()
    {
        AccessSystem();
        while (true)
        {
            int choice = second_menu();
            if(choice == 5)
                Ask_Question();
        }
    }

};


int main()
{
    AskMe_System service;
    service.run();
    return 0;
}