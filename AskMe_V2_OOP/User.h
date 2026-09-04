#pragma once
#include <string>
#include <vector>

class User
{
private:
    int id;
    std::string username;
    std::string password;
    std::string name;
    std::string email;
    int allow_anonymous_qs;

    std::vector<int> questions_to_me_ids;
    std::vector<int> questions_from_me_ids;

public:
    User();
    User(std::string &line);
    void Print();
    std::string ToLine();
    void Read_User(const std::string &username, int id);

    int GetId() const;
    void SetId(int id);

    int GetAllowAnonymousQs() const;
    void SetAllowAnonymousQs(int allow_anonymous_qs);

    const std::string &GetUsername() const;
    void SetUserName(const std::string &username);

    const std::string &GetPassword() const;
    void SetPasswword(const std::string &password);

    const std::string &GetName() const;
    void SetName(const std::string &name);

    const std::string &GetEmail() const;
    void SetEmail(const std::string &email);

    const std::vector<int> &GetQuestionsToMeIds() const;
    void SetQuestionsToMeIds(std::vector<int> questions_to_me_ids);

    const std::vector<int> &GetQuestionsFromMeIds() const;
    void SetQuestionsFromMeIds(std::vector<int> questions_from_me_ids);

    void AddQuestionToMeId(int question_id);
    void AddQuestionFromMeId(int question_id);
};
