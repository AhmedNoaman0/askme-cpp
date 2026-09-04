#include "Question_Controller.h"
#include "Helpers.h"

#include <iostream>
#include <algorithm>

using namespace std;

const map<int, std::vector<int>> &Question_Controller::GetParentQsIdChildQsIdMap() const
{
    return parentQsId_childQsId_map;
}
void Question_Controller::SetParentQsIdChildQsIdMap(const map<int, std::vector<int>> &parentQsId_childQsId_map)
{
    this->parentQsId_childQsId_map = parentQsId_childQsId_map;
}

const map<int, Question> &Question_Controller::GetQsIdObjectMap() const
{
    return QsId_object_map;
}
void Question_Controller::SetQsIdObjectMap(const map<int, Question> &QsId_object_map)
{
    this->QsId_object_map = QsId_object_map;
}

int Question_Controller::GetLastId() const
{
    return last_id;
}
void Question_Controller::SetLastId(int last_id)
{
    this->last_id = last_id;
}

Question_Controller::Question_Controller()
{
    last_id = 0;
}

void Question_Controller::Load_Quesitons()
{
    QsId_object_map.clear();
    parentQsId_childQsId_map.clear();
    last_id = 0;

    string path = "data/questions.txt";
    vector<string> lines = ReadFileLines(path);

    for (auto &line : lines)
    {
        Question question(line);

        QsId_object_map[question.GetId()] = question;

        last_id = max(last_id, question.GetId());

        if (question.GetParentQsId() != -1)
            parentQsId_childQsId_map[question.GetParentQsId()]
                .push_back(question.GetId());
        else
            parentQsId_childQsId_map[question.GetId()]
                .push_back(question.GetId());
    }
}

void Question_Controller::Update_Questions()
{
    string path = "data/questions.txt";
    vector<string> lines;

    for (auto &pair : QsId_object_map)
        lines.push_back(pair.second.To_Line());

    WriteFileLines(path, lines);
}

void Question_Controller::Answer_Question(int user_id)
{
    Load_Quesitons();

    int question_id = Read_Question_Id(user_id, true);

    if (question_id == -1)
        return;

    Question &question = QsId_object_map[question_id];

    question.Print_Question_To();

    if (question.GetAnswer() != "")
        cout << "\nWarning: Already answerd. Answer will be updated\n";

    cout << "Enter Answer: ";

    string str;
    cin.ignore();
    getline(cin, str);

    question.SetAnswer(str);

    Update_Questions();
}

int Question_Controller::Read_Question_Id(int &user_id, bool to_only)
{
    cout << "Enter Question id or -1 to cancel";

    int qs_id;
    cin >> qs_id;

    if (qs_id == -1)
        return -1;

    if (!QsId_object_map.count(qs_id))
    {
        cout << "No thread question with such ID. Try again.\n";
        return Read_Question_Id(user_id, to_only);
    }

    Question &question = QsId_object_map[qs_id];

    if ((question.GetToUserId() != user_id) && to_only)
    {
        cout << "This question is not for you.\n";
        return Read_Question_Id(user_id, to_only);
    }
    else if ((question.GetFromUserId() != user_id) &&
             (question.GetToUserId() != user_id))
    {
        cout << "This question is not related to you.\n";
        return Read_Question_Id(user_id, to_only);
    }

    return qs_id;
}

int Question_Controller::read_parentQs_id()
{
    cout << "For thread question enter question id or -1 for new questions: ";

    int qs_id;
    cin >> qs_id;

    if (qs_id == -1)
        return -1;

    if (!QsId_object_map.count(qs_id))
    {
        cout << "No thread question with such ID. Try again\n";
        return read_parentQs_id();
    }

    return qs_id;
}

void Question_Controller::Ask_Question(
    User &user,
    pair<int, int> &to_user_pair)
{
    Question question;

    if (!to_user_pair.second)
    {
        cout << "Note: Anonymous questions are not allowed for this user\n";
        question.SetIsAnonymousQs(0);
    }
    else
    {
        cout << "Is anonymous questions?: (0 or 1): ";

        int num;
        cin >> num;

        question.SetIsAnonymousQs(num);
    }

    question.SetParentQsId(read_parentQs_id());

    cout << "Enter question text: ";

    cin.ignore();

    string text;
    getline(cin, text);

    question.SetText(text);
    question.SetFromUserId(user.GetId());
    question.SetToUserId(to_user_pair.first);
    question.SetId(++last_id);

    QsId_object_map[question.GetId()] = question;

    // thread
    if (question.GetParentQsId() == -1)
        parentQsId_childQsId_map[question.GetId()]
            .push_back(question.GetId());
    else
        parentQsId_childQsId_map[question.GetParentQsId()]
            .push_back(question.GetId());

    user.AddQuestionFromMeId(question.GetId());

    Update_Questions();
}

void Question_Controller::print_qs_to_user(int &to_user_id)
{
    for (auto pair : QsId_object_map)
    {
        if (pair.second.GetToUserId() == to_user_id)
            pair.second.Print_Question_To();
    }
}

void Question_Controller::print_qs_from_user(int &from_user_id)
{
    for (auto &pair : QsId_object_map)
    {
        if (pair.second.GetFromUserId() == from_user_id)
            pair.second.Print_Question_from();
    }
}

void Question_Controller::delete_question(int &user_id)
{
    int question_id = Read_Question_Id(user_id);

    if (question_id == -1)
        return;

    vector<int> ids_to_remove;

    // Delete all threads in case of parent qs
    if (QsId_object_map[question_id].GetParentQsId() == -1)
    {
        ids_to_remove = parentQsId_childQsId_map[question_id];

        parentQsId_childQsId_map.erase(question_id);

        ids_to_remove.push_back(question_id);
    }
    else
    {
        auto &children =
            parentQsId_childQsId_map[QsId_object_map[question_id].GetParentQsId()];

        auto it = find(children.begin(), children.end(), question_id);

        children.erase(it);

        ids_to_remove.push_back(question_id);
    }

    for (auto id : ids_to_remove)
        QsId_object_map.erase(id);

    Update_Questions();
}