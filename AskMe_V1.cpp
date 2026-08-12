#include<iostream>
#include<vector>
#include<map>
#include<sstream>
#include<fstream>
#include<cassert>
#include <algorithm>
using namespace std;

// ^ --------------------------- Helper Functions ---------------------------
vector<string> ReadFileLines(string& path)
{
    vector<string> lines;
    fstream fin(path);
    string line;
    if(fin.fail())
    {
        cout<<"Cant open the file :( \n\n";
        return lines;
    }
    while (getline(fin,line))
    {
        if(line.size() == 0) // if the line is empty -> ignore this line :)
            continue;
        lines.push_back(line);
    }
    fin.close();
    return lines;
}
// vector<string> SplitString(const string& line)
// {
//     vector<string> fields;
//     istringstream iss(line);
//     string field;

//     while (getline(iss,field,','))
//         fields.push_back(field);

//     if (fields.size() == 6) // leave the answer field as "" if it's empty.
//         fields.push_back("");

//     return fields;
// }
// 1,2,3,4,why you say,ok; ,why,""
vector<string>SplitString(string& line,string delimiter = ",")
{
    vector<string> fields;
    string field;
    int pos = 0;
    while ((pos = (int) line.find(delimiter)) != -1) // if not exist find() -> returns -1
    {
        field = line.substr(0,pos); // we remove the previous field, so next one we start from index 0
        fields.push_back(field);
        line.erase(0,pos + delimiter.length());
    }
    fields.push_back(line); // after finshing, we need to add last field "ok"
    return fields;
}


void WriteFileLines(string& path,vector<string>& lines) // to do a bool append or overwrite
{
    ofstream fout(path);
    if(fout.fail()){
        cout << "\n\nERROR: Can't open the file\n\n";
        return;}

    for(auto& line : lines)
        fout<<line<<"\n";
    fout.close();
}


// ^ --------------------------- Main Entites --------------------------------


struct User
{
    int id;
    string username;
    string password;
    string name;
    string email;
    int allow_anonymous_qs;

    vector<int> questions_to_me_ids;
    vector<int> questions_from_me_ids;

    User()
    {

    }
    User(string& line)
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
    string Toline()
    {
        ostringstream oss;
        oss << id <<","<< username << ","<< password << ","<< name << ","<< email << "," << allow_anonymous_qs;
        return oss.str();
    }

};

struct Question
{
    int question_id;
    int parent_question_id; // if it's a parent_qs -> -1
    int from_user_id;
    int to_user_id;
    int is_anonymous_qs;
    string text;
    string answer;
    Question()
    {

    }
    Question(string& line)
    {
        vector<string> fields = SplitString(line);
        assert(fields.size() == 7);

        question_id = stoi(fields[0]);
        parent_question_id = stoi(fields[1]);
        from_user_id = stoi(fields[2]);
        to_user_id = stoi(fields[3]);
        is_anonymous_qs = stoi(fields[4]);
        text = fields[5];
        answer = fields[6];

    }
    void Print_Question_To() // qs to a specific user (not me)
    {
        string prefix = ""; // to write thread or question

        if(parent_question_id != -1)
            prefix = "\tThread: ";

        cout<<prefix<<"Question Id ("<<question_id<<")";

        if(!is_anonymous_qs)
            cout<<" from user id ("<<from_user_id<<")";

        cout<<"\tQuestion: "<<text;

        if(answer != "")
            cout<<prefix<<"\tAnswer: "<<answer;

        cout<<"\n";
    }
    void Print_Question_from()
    {

        cout<<"Question Id ("<<question_id<<") ";
        if(is_anonymous_qs)
            cout<<"-> Anonymous <- ";
        cout<<"to user id("<<to_user_id<<") ";
        cout<<"Question: "<<text;
        if(answer != "")
            cout<<" Answer: "<<answer<<"\n";
        else
            cout<<"Not Answered YET\n";
    }
    string To_Line()
    {
        ostringstream oss;
        oss<<question_id<<","<<parent_question_id<<","<<from_user_id<<","<<to_user_id<<","
        <<is_anonymous_qs<<","<<text<<","<<answer;
        return oss.str();
    }

};


// ^ --------------------------- Controllers ---------------------------------


struct User_Controller
{
    User current_user;
    int last_id;
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

    void Load_Users()
    {
        username_object_map.clear();
        last_id = 0;
        string path = "data/users.txt";
        vector<string> lines = ReadFileLines(path);
        for(auto& line : lines)
        {
            User user(line);
            last_id = max(last_id,user.id);
            username_object_map[user.username] = user;
        }
    }
    void Update_User()
    {
        vector<string> lines;
        string path = "data/users.txt";
        for(auto &pair : username_object_map)
            lines.push_back(pair.second.Toline());
        WriteFileLines(path,lines);
    }
    
    void Login()
    {
        Load_Users();
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
        Update_User();
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
    void Load_Quesitons()
    {
        QsId_object_map.clear();
        parentQsId_childQsId_map.clear();
        last_id = 0;

        string path = "data/questions.txt";
        vector<string> lines = ReadFileLines(path);
        for(auto& line : lines)
        {
            Question question(line);
            QsId_object_map[question.question_id] = question;
            last_id = max(last_id,question.question_id);
            if(question.parent_question_id != -1) // in case of child qs, we need to add child to map
                parentQsId_childQsId_map[question.parent_question_id].push_back(question.question_id);
            else
                parentQsId_childQsId_map[question.question_id].push_back(question.question_id);
        }
        
    }
    void Update_Questions()
    {
        string path = "data/questions.txt";
        vector<string> lines;
        for(auto& pair : QsId_object_map)
            lines.push_back(pair.second.To_Line());

        WriteFileLines(path,lines);
    }
    
    void Answer_Question(int user_id)
    {
        Load_Quesitons();
        int question_id = Read_Question_Id(user_id,true);
        if(question_id == -1)
            return;
        Question& question = QsId_object_map[question_id];
        question.Print_Question_To();
        if(question.answer != "")
            cout<<"\nWarning: Already answerd. Answer will be updated\n";
        cout<<"Enter Answer: ";
        cin.ignore();
        getline(cin,question.answer);
        Update_Questions();
    }
    
    int Read_Question_Id(int &user_id, bool to_only = false)
    {
        cout<<"Enter Question id or -1 to cancel";
        int qs_id;
        cin>>qs_id;
        if(qs_id == -1)
            return -1;
        if(!QsId_object_map.count(qs_id)){
            cout << "No thread question with such ID. Try again.\n";
            return Read_Question_Id(user_id,to_only);}
        
        Question &question = QsId_object_map[qs_id];

        if((question.to_user_id != user_id) && to_only){
            cout << "This question is not for you.\n";
            return Read_Question_Id(user_id,to_only);}
        else if((question.from_user_id != user_id) && (question.to_user_id != user_id))
        {
            cout << "This question is not related to you.\n";
            return Read_Question_Id(user_id,to_only);}
        return qs_id;
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
    void Ask_Question(User& user,pair<int,int>& to_user_pair) // ! warning
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
        user.questions_from_me_ids.push_back(question.question_id); //! ##### new

        Update_Questions();
    }
    void print_qs_to_user(int& to_user_id)
    {
        for(auto pair : QsId_object_map)
        {
            if(pair.second.to_user_id == to_user_id)
                pair.second.Print_Question_To();
        }
    }
    void print_qs_from_user(int& from_user_id)
    {
        for(auto& pair : QsId_object_map)
        {
            if(pair.second.from_user_id == from_user_id)
                pair.second.Print_Question_from();
        }
    }

    void delete_question(int& user_id)
    {
        int question_id = Read_Question_Id(user_id) ;
        
        if(question_id == -1)
            return;
        
        vector<int> ids_to_remove;

        // Delete all threads in case of parent qs
        if(QsId_object_map[question_id].parent_question_id == -1)
        {
            ids_to_remove = parentQsId_childQsId_map[question_id];
            parentQsId_childQsId_map.erase(question_id);
            ids_to_remove.push_back(question_id);
        }
        else // in case of child qs
        {
            auto& children = parentQsId_childQsId_map[QsId_object_map[question_id].parent_question_id];
            auto it = find(children.begin(), children.end(), question_id); // target index
            children.erase(it);
            ids_to_remove.push_back(question_id);
        }

        for(auto id : ids_to_remove) // remove questions from main map
            QsId_object_map.erase(id);

        Update_Questions();

    }

};

struct AskMe_System
{
    User_Controller user_controller;
    Question_Controller question_controller;

    void Print_Qs_To_Me()
    {
        question_controller.print_qs_to_user(user_controller.current_user.id);
    }
    
    void Print_Qs_From_Me()
    {
        question_controller.print_qs_from_user(user_controller.current_user.id);
    }
    
    void Answer_Question()
    {
        // cout<<"Enetr Question id or -1 to cancel";
        // int qs_id;
        // cin>>qs_id;
        // if(qs_id == -1)
        //     return;
        question_controller.Answer_Question(user_controller.current_user.id);
    }
    
    void Delete_Question()
    {
        question_controller.delete_question(user_controller.current_user.id);
        question_controller.Update_Questions();
    }

    void Ask_Question()
    {
        pair to_user_id = user_controller.ReadUserId();
        if(to_user_id.first == -1)
            return;
        question_controller.Ask_Question(user_controller.current_user,to_user_id);
    }

    void Load_Database()
    {
        question_controller.Load_Quesitons();
        user_controller.Load_Users();

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
        Load_Database();
        AccessSystem();
        while (true)
        {
            Load_Database();
            int choice = second_menu();
            if(choice == 1)
                Print_Qs_To_Me();
            else if(choice == 2)
                Print_Qs_From_Me();
            else if(choice == 3)
                Answer_Question();
            else if(choice == 4)
                Delete_Question();
            else if(choice == 5)
                Ask_Question();
            else if(choice == 8)
                AccessSystem();
        }
    }

};


int main()
{
    AskMe_System service;
    service.run();
    return 0;
}