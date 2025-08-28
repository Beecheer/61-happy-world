//
// Created by zhangzhiwen on 25-8-27.
//

#ifndef MENU_H
#define MENU_H

#include <map>
#include <functional>
#include <string>
#include <utility>
using namespace std;

// ========== 通用菜单类 ==========
class Menu
{
    string title;
    map<int, pair<string, function<void()>>> options;

public:
    explicit Menu(string t) : title(move(t))
    {
    }

    void addOption(const int key, const string& desc, const function<void()>& action)
    {
        options[key] = {desc, action};
    }

    void run();
};

void adminMenu();
void customerMenu();
void mainMenu();
void Signin();


#endif //MENU_H
