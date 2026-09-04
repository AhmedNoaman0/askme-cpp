#include "Question.h"
#include "Helpers.h"

#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;

Question::Question()
{
}

Question::Question(string &line)
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

void Question::Print_Question_To()
{
    string prefix = "";

    if (parent_question_id != -1)
        prefix = "\tThread: ";

    cout << prefix << "Question Id (" << question_id << ")";

    if (!is_anonymous_qs)
        cout << " from user id (" << from_user_id << ")";

    cout << "\tQuestion: " << text;

    if (answer != "")
        cout << prefix << "\tAnswer: " << answer;

    cout << "\n";
}

void Question::Print_Question_from()
{
    cout << "Question Id (" << question_id << ") ";

    if (is_anonymous_qs)
        cout << "-> Anonymous <- ";

    cout << "to user id(" << to_user_id << ") ";
    cout << "Question: " << text;

    if (answer != "")
        cout << " Answer: " << answer << "\n";
    else
        cout << "Not Answered YET\n";
}

string Question::To_Line()
{
    ostringstream oss;

    oss << question_id << ","
        << parent_question_id << ","
        << from_user_id << ","
        << to_user_id << ","
        << is_anonymous_qs << ","
        << text << ","
        << answer;

    return oss.str();
}

int Question::GetId() const
{
    return question_id;
}

void Question::SetId(int id)
{
    this->question_id = id;
}

int Question::GetParentQsId() const
{
    return parent_question_id;
}

void Question::SetParentQsId(int parent_question_id)
{
    this->parent_question_id = parent_question_id;
}

int Question::GetFromUserId() const
{
    return from_user_id;
}

void Question::SetFromUserId(int from_user_id)
{
    this->from_user_id = from_user_id;
}

int Question::GetToUserId() const
{
    return to_user_id;
}

void Question::SetToUserId(int to_user_id)
{
    this->to_user_id = to_user_id;
}

int Question::GetIsAnonymousQs() const
{
    return is_anonymous_qs;
}

void Question::SetIsAnonymousQs(int is_anonymous_qs)
{
    this->is_anonymous_qs = is_anonymous_qs;
}

const string &Question::GetText() const
{
    return text;
}

void Question::SetText(const string &text)
{
    this->text = text;
}

const string &Question::GetAnswer() const
{
    return answer;
}

void Question::SetAnswer(const string &answer)
{
    this->answer = answer;
}