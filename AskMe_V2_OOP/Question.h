#pragma once

#include <string>

class Question
{
private:
    int question_id;
    int parent_question_id;
    int from_user_id;
    int to_user_id;
    int is_anonymous_qs;
    std::string text;
    std::string answer;

public:
    Question();
    Question(std::string &line);

    void Print_Question_To();
    void Print_Question_from();
    std::string To_Line();

    int GetId() const;
    void SetId(int id);

    int GetParentQsId() const;
    void SetParentQsId(int parent_question_id);

    int GetFromUserId() const;
    void SetFromUserId(int from_user_id);

    int GetToUserId() const;
    void SetToUserId(int to_user_id);

    int GetIsAnonymousQs() const;
    void SetIsAnonymousQs(int is_anonymous_qs);

    const std::string &GetText() const;
    void SetText(const std::string &text);

    const std::string &GetAnswer() const;
    void SetAnswer(const std::string &answer);
};