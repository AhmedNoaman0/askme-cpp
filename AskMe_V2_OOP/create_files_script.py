files = [
    "User.h", "User.cpp",
    "Question.h", "Question.cpp",
    "User_Controller.h", "User_Controller.cpp",
    "Question_Controller.h", "Question_Controller.cpp",
    "AskMe_System.h", "AskMe_System.cpp",
    "Helpers.h", "Helpers.cpp"
]

for file in files:
    open(file, "w").close()