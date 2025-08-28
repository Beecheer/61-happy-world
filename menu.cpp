//
// Created by zhangzhiwen on 25-8-27.
//

#include "menu.h"
#include <iostream>
#include <cstdlib>   // exit()
#include <conio.h> // 用于_getch()函数
#include "time_table.h"

int Quit();


void Menu::run()
{
    while (true)
    {
        cout << "\n\n\n========== " << title << " ==========\n";
        for (auto& [fst, snd] : options)
        {
            cout << fst << ". " << snd.first << endl;
        }
        cout << "===================================\n";
        cout << "please choose:";

        int choice;
        cin >> choice;

        if (options.contains(choice))
        {
            options[choice].second(); // 执行对应操作
            if (choice == 0) break; // 0 为返回上级/退出
        }
        else
        {
            cout << "Invalid input! Please try again.\n";
        }
    }
}

static Menu admin_menu("admin menu");
static Menu customer_menu("customer menu");
static Menu main_menu("ticket management system");

// ========== 管理员子菜单 ==========
void adminMenu()
{
    // Menu admin_menu("管理员菜单");
    admin_menu.addOption(1, "新增车次", []()
    {
        std::string no;
        cout << "\n>>> 执行新增车次\n" << ">>>请输入要增加的车次\n";
        cin >> no;
        TimeTables.AddTimeTable(no);
    });

    admin_menu.addOption(2, "删除车次", []()
    {
        std::string no;
        cout << "\n>>> 执行删除车次\n" << ">>>请输入要删除的车次\n";
        cin >> no;
        TimeTables.DeleteTimeTable(no);
    });

    admin_menu.addOption(3, "修改车次", []()
    {
        cout << "\n>>> 执行修改车次\n" << ">>>请查询后删除再添加/doge\n";
    });

    admin_menu.addOption(4, "查看车次", []()
    {
        std::string no;
        cout << "\n>>> 执行查看车次\n" << ">>>请输入要查看的车次\n";
        cin >> no;
        TimeTables.ShowInfo(no);
    });

    admin_menu.addOption(5, "查看所有车次", []()
    {
        cout << "\n>>> 执行查看所有车次\n";
        TimeTables.ShowTimeTables();
    });

    admin_menu.addOption(6, "查看日志", []()
    {
        cout << "\n>>> 执行查看日志\n";
        char name[15];
        TimeTables.GenerateLogFileName(name);
        TimeTables.ReadFromFile(name);
    });

    admin_menu.addOption(0, "返回主菜单", []()
    {
        char choice;
        cout << "\n>>> 是否保存日志(Y/n)?\n";
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            char name[15];
            cout << "\n>>> 正在生成日志\n";
            TimeTables.GenerateLogFileName(name);
            TimeTables.WriteToFile(name);
            cout << "\n>>> 已生成日志\n";
        }
    }); // 空函数，返回上级
    admin_menu.run();
}

// ========== 顾客子菜单 ==========
void customerMenu()
{
    // Menu customer_menu("顾客菜单");
    customer_menu.addOption(1, "查询车次", []()
    {
        int i;
        cout << ">>> 执行查询车次\n" << ">>> 请输入查询方式：\n" << "1.按车次查询\n" << "2.按终点站查询\n";
        cin >> i;
        if (i == 1)
        {
            std::string no;
            cout << "\n>>> 执行按车次查询\n" << ">>> 请输入要查询的车次\n";
            cin >> no;
            TimeTables.Query(no);
        }
        else if (i == 2)
        {
            std::string no;
            cout << "\n>>> 执行按终点站查询\n" << ">>> 请输入要查询的终点站\n";
            cin >> no;
            TimeTables.QueryByLastStation(no);
        }
        else
        {
            cout << "Invalid input! Please try again.\n";
        }
    });

    customer_menu.addOption(2, "购票", []()
    {
        std::string no;
        cout << ">>> 执行购票\n" << ">>> 请输入要购买的车次\n";
        cin >> no;
        TimeTables.TicketOrder(no);
    });

    customer_menu.addOption(3, "退票", []()
    {
        std::string no;
        cout << ">>> 执行退票\n" << ">>> 请输入要退票的车次\n";
        cin >> no;
        TimeTables.TicketDelete(no);
    });

    customer_menu.addOption(0, "返回主菜单", []()
    {
        cout << "\n>>> 确定退出(Y/n)?\n";
        char choice;
        cin >> choice;
        if (choice == 'Y' || choice == 'y')
        {
            cout << "\n已退出\n";
        }
        else
        {
            cout << "不退出也得退出:(\n";
        }
        char name[15];
        TimeTables.GenerateLogFileName(name);
        TimeTables.WriteToFile(name);
    }); // 返回
    customer_menu.run();
}

// ========== 主菜单 ==========
void mainMenu()
{
    TimeTables.ReadFromFile("bus.txt");
    // TimeTables.InitializationPassagerMode();

    // Menu main_menu("车站车次信息管理系统");
    main_menu.addOption(1, "Admin", Signin);
    main_menu.addOption(2, "Customer", customerMenu);
    main_menu.addOption(0, "Exits", Quit);
    main_menu.run();
}

std::string getPassword() {
    std::string password;
    char ch;

    // std::cout << "请输入密码: ";

    while (true) {
        ch = _getch(); // 无回显地读取字符

        // 如果按下回车键，结束输入
        if (ch == '\r' || ch == '\n') {
            std::cout << std::endl;
            break;
        }
        // 如果按下退格键，删除最后一个字符
        else if (ch == '\b') {
            if (!password.empty()) {
                password.pop_back();
                std::cout << "\b \b"; // 回退光标，输出空格，再回退光标
            }
        }
        // 其他字符，添加到密码中并显示*
        else {
            password.push_back(ch);
            std::cout << '*';
        }
    }

    return password;
}



void Signin()
{
    const string correctUser = "admin";
    const string correctPass = "123";

    string username, password;

    while (true)
    {
        cout << "please enter your username: \n";
        cin >> username;

        cout << "please enter your password: \n";
        password = getPassword();

        // 校验
        if (username == correctUser && password == correctPass)
        {
            cout << "登录成功！" << endl;
            adminMenu(); // 进入管理员菜单
            break;
        }
        else
        {
            cout << "用户名或密码错误，请重试！\n" << endl;
        }
    }
}

int Quit()
{
    char ch;
    cout << "\n\n\n确定退出系统?(Y/n)\n";
    cin >> ch;
    if (ch == 'Y' || ch == 'y')
    {
        TimeTables.WriteToFile("bus.txt");
        cout << "Bye!\n";
        exit(0);
    }
    else
    {
        main_menu.run();
    }
    return 0;
}