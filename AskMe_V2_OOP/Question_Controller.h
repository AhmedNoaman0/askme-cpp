#pragma once

#include "Question.h"
#include "User.h"

#include <map>
#include <vector>
#include <utility>

class Question_Controller
{
private:
    std::map<int, std::vector<int>> parentQsId_childQsId_map;
    std::map<int, Question> QsId_object_map;
    int last_id;

public:
    const std::map<int, std::vector<int>> &GetParentQsIdChildQsIdMap() const;
    void SetParentQsIdChildQsIdMap(const std::map<int, std::vector<int>> &parentQsId_childQsId_map);

    const std::map<int, Question> &GetQsIdObjectMap() const;
    void SetQsIdObjectMap(const std::map<int, Question> &QsId_object_map);

    int GetLastId() const;
    void SetLastId(int last_id);

    Question_Controller();

    void Load_Quesitons();
    void Update_Questions();

    void Answer_Question(int user_id);

    int Read_Question_Id(int &user_id, bool to_only = false);
    int read_parentQs_id();

    void Ask_Question(User &user, std::pair<int, int> &to_user_pair);

    void print_qs_to_user(int &to_user_id);
    void print_qs_from_user(int &from_user_id);

    void delete_question(int &user_id);
};