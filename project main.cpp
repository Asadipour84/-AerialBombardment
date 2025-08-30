#include <iostream> 
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <algorithm>
#include <fstream>
// #include <cstdlib>
using namespace std;

/////////// airplain at Y = 10
/////////// Y building = 15 - 27              building ha - 5 vahed az aval o akhar fasele   (45, )
/////////// no of buildings = 5
/////////// ground = (40, 28) - (119, 28)

///////////        | # # |
///////////        | # # |
struct User {
    string username;
    string password;
};

struct leaderboard{
    string username;
    int score;
};

int loadUsers(User users[]) {
    ifstream file("usernames.txt");
    int count = 0;
    while (file >> users[count].username >> users[count].password) {
        count++;
    }
    file.close();
    return count;
}

int loadLeader(leaderboard leaderUser[]) {
    ifstream file("leaderboard.txt");
    int count = 0;
    while (file >> leaderUser[count].username >> leaderUser[count].score) {
        count++;
    }
    file.close();
    return count;
}

void saveUsers(User users[], int count) {
    ofstream file("usernames.txt");
    for (int i = 0; i < count; i++) {
        file << users[i].username << " " << users[i].password <<endl;
    }
    file.close();
}

void saveLeader(leaderboard leader_users[], int leader_count)
{
    ofstream file("leaderboard.txt");
    for (int i = 0; i < leader_count ; i++)
    {
        file << leader_users[i].username <<" "<< leader_users[i].score <<endl;
    }
    file.close();
}

void print_leader()
{
    ifstream leaderboard("leaderboard.txt");

    string result;

    while (getline(leaderboard, result))
    {
        cout<<result<<endl;
    }
        

    leaderboard.close();
}

void sort_leaderboard(leaderboard leaderUsers[], int leaderCount) {
    for (int i = 0; i < leaderCount - 1; i++) {
        for (int j = 0; j < leaderCount - 1 - i; j++) {
            if (leaderUsers[j].score > leaderUsers[j + 1].score) {
                swap(leaderUsers[j].score, leaderUsers[j + 1].score);
            }
        }
    }
}


const int startpoint_x = 40;
const int plane_x = 8;
const int plane_y = 10;
const int build_count = 5;
const int min_building = 10;   ////  + (0 - 8) -> building height

int airplane_coord[2] = {8, 10}; ////{ x or x + 6 , y } //////nok e airplane coord
int bomb_coord[2] = {-1, -1}; ///////{ planeX - 3 , planeY }
int plane_dir = 1;

int 
build_x [build_count][2] = {0} ,
build_height [build_count] = {0} , 
build_color [build_count] = {0};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

 ///////////// speed {slow= 1000ms , normal  = 500ms , speedy = 250ms}
///////////////   {slow = 0, normal = 1, speedy = 2}



enum key {
    none,
    space,
    esc,
    left_arrow,
    right_arrow
};

int set_speed(int speed)
{
    if (speed == 0)
    {
        return 750;
    }
    else if (speed == 1)
    {
        return 500;
    }
    else ///////speed == 2
    {
        return 250;
    }
}

key getKey() {
    if (_kbhit()) 
    {
        int ch = _getch(); 
        if (ch == 27) 
        { 
            return esc;
        }
        else if (ch == ' ') 
        {
            return space;
        }
        else if (ch == 0 || ch == 224) 
        { 
            int arrow = _getch();
            if (arrow == 75) 
            {
                return left_arrow;
            }
            else if (arrow == 77) 
            {
                return right_arrow;
            }
        }
        }
    return none; 
}

void returning()
{
    char returning;
    cout<<endl;
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                      cout<<"\nDo you want to go back? ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE); /*blue-ish*/     cout<<" enter [m] or [M] for the main menu ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                                   cout<<"//";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE); /*blue-ish*/     cout<<" enter [q] or [Q] to quit ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                                   cout<<"// ";
    SetConsoleTextAttribute(hConsole, 7); ///reset
    
    cin>>returning;

    if (returning == 'q' || returning == 'Q')
    {
        exit(0);
    }
    while (returning != 'm' && returning != 'M')
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                      cout<<"\ninvalid input! ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE); /*blue-ish*/     cout<<" enter [m] or [M] for the main menu ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                      cout<<"//";
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE); /*blue-ish*/     cout<<" enter [q] or [Q] to quit ";
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);                                      cout<<"// ";
        SetConsoleTextAttribute(hConsole, 7); ///reset

        cin>>returning;
    
        if(returning == 'm' || returning == 'M')
        {
            break; 
        }
        if (returning == 'q' || returning == 'Q')
        {
            exit(0);
        }
    }


    system("cls");
}

int mainMenu()
{
    // system("cls");

    SetConsoleTextAttribute(hConsole, 2); ////green
    cout<<"\n<Game Options>\n";
    SetConsoleTextAttribute(hConsole, 7); ////reset white
    cout<<"1- Start game\n"<<"2- Rules\n"<<"3- Leaderboard\n"<<"4- Change passcode\n";
    SetConsoleTextAttribute(hConsole, 4); //red
    cout<<"5- Exit\n\n";
    SetConsoleTextAttribute(hConsole, 15); ////reset white
        
    int menu;
    cout<<"Enter a number from 1 to 5: ";
    cin>>menu;
    SetConsoleTextAttribute(hConsole, 7);
    
    while (menu < 1 || menu > 5)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
        cout<<"invalid input\n";
        SetConsoleTextAttribute(hConsole, 0);

        cout<<"Enter a number from 1 to 5: ";
        cin>>menu;

        if(menu >= 1 && menu <= 5)
            break;
    }

    return menu;
}

void gotoxy(int x, int y) 
{
    COORD coord;
    coord.X = startpoint_x + x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void print_ground()
{
    gotoxy(-1, 28);
    for(int i =39; i < 120; i++)
    {
        cout<<"_";
    }

}

void print_wall(int x = -2)
{
    for(int i = 0; i < 29; i++)
    {
        gotoxy(x, i);
        cout<<"|";
    }
}

void print_rules()
{
    SetConsoleTextAttribute(hConsole, 6); /*orange*/       cout<<"We're gonna destroy some buildings!!\n";
    SetConsoleTextAttribute(hConsole, 7);                  cout<<"There wil be a jet flying over the buildings to destroy them. Tap";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    cout<<" Space ";
    SetConsoleTextAttribute(hConsole, 7);                   cout<<"to drop the bombs. You can adjust the speed by pressing the";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    cout<<" Left and Right Arrow keys. ";
    SetConsoleTextAttribute(hConsole, 7);                   cout<<"You can always quit the game by pressing ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    cout<<" Esc key.\n";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    cout<<"Happy gaming!!!";
    SetConsoleTextAttribute(hConsole, 7);
}

void inGame_rules(){
    gotoxy(-40, 1);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);          cout<<"\t+ ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);        cout<<"Space ";
    SetConsoleTextAttribute(hConsole, 7);                       cout<<"for bomb"<<endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);          cout<<"\t+ ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);        cout<<"<-";
    SetConsoleTextAttribute(hConsole, 7);                       cout<<" & ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);        cout<<"->";
    SetConsoleTextAttribute(hConsole, 7);                       cout<<" keys for speed"<<endl;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);          cout<<"\t+ ";
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);        cout<<"Esc ";
    SetConsoleTextAttribute(hConsole, 7);                       cout<<"to exit";
}

void warning_dialog()
{
    //// 5 ta khat baad
    gotoxy(-40, 9);
    SetConsoleTextAttribute(hConsole, 6); ///orange
    cout<<"\tWarning!"<<endl;
    cout<<"\tYour bomb hit the GROUND!"<<endl;
    cout<<"\tNot the buildings!";
    SetConsoleTextAttribute(hConsole, 7);
}

void clear_warning()
{
    gotoxy(-40, 9);
    cout<<"\t        "<<endl;
    cout<<"\t                         "<<endl;
    cout<<"\t                  ";
}

int cheering = 0;
void cheering_dialog(int a){
    cheering = a;
    //// 5 ta khat baad
    gotoxy(-40, 9);
    SetConsoleTextAttribute(hConsole, 3); ///cyan
    cout<<"\tCongrats!"<<endl;
    cout<<"\tYou destroyed 1 building!"<<endl;
    cout<<"\tNo. of stories: ";
    SetConsoleTextAttribute(hConsole, 6); ///orange
    cout<<a;
    SetConsoleTextAttribute(hConsole, 7);
}

void clear_cheer()
{
    gotoxy(-40, 9);
    cout<<"\t         "<<endl;
    cout<<"\t                         "<<endl;
    cout<<"\t                  ";
}


void print_airplane(int x = airplane_coord[0], int y = airplane_coord[1])
{
    if (plane_dir)
    {
        gotoxy(x - 7, y -1);     cout << "E \\___  ";
        gotoxy(x - 7, y);        cout << " \\==-_')";
        // airplane_coord[0] = x + 6;
        // airplane_coord[1] = y;
    }
    else
    {
        gotoxy(x, y -1);     cout << "  ___/ 3";
        gotoxy(x, y);        cout << "('_-==/ ";
        // airplane_coord[0] = x;
        // airplane_coord[1] = y;
    }
}

void remove_airplane(int x = airplane_coord[0], int y = airplane_coord[1])
{
    if (plane_dir)
    {
        gotoxy(x - 9 , y -1);     cout << "        ";
        gotoxy(x - 9, y);         cout << "        ";
        // airplane_coord[0] = x + 6;
        // airplane_coord[1] = y;
    }
    else
    {
        gotoxy(x+2, y -1);     cout << "        ";
        gotoxy(x+2, y);        cout << "        ";
        // airplane_coord[0] = x;
        // airplane_coord[1] = y;
    }
}

void print_building(int x[][2], int height[], int color[]) {

    for(int i = 0 ; i < build_count ; i++)
    {
        SetConsoleTextAttribute(hConsole, color[i]);
        
        for (int y = 28; y > height[i] ; --y) 
        {
            if ( y == (height[i] +1) )
            {
                gotoxy(x[i][0], y);
                cout << "_______";
            }
            else
            {
                gotoxy(x[i][0], y);
                cout << "| # # |";
            }
            
        }
    }   
    
    SetConsoleTextAttribute(hConsole, 7);
}

void remove_building(int x[][2], int height[], int build_num) { ////////////// remove_building( xs , heights , build no. 2)

    for (int y = 28; y > height[build_num] ; --y) 
    {
        if (y == 28)
        {
            gotoxy(x [build_num][0], y);
            cout<<"_______";
            continue;
        }
        gotoxy(x [build_num][0], y);
        cout<< "       ";
    }
    build_x [build_num][0] = -40;
    build_x [build_num][1] = build_x [build_num][0] + 6;
    build_height [build_num] = -40;
}

void print_bomb(int x = bomb_coord[0], int y = bomb_coord[1])
{
    gotoxy(x, y);
    cout<<"@";
}

void clear_bomb(int x = bomb_coord[0], int y = bomb_coord[1])
{
    gotoxy(x, y);
    cout<<" ";
}

int main ()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");


    // ///////////////////////////////////////////////////////////////////////////////first page - passcode validation - sign in
    
    User users[5];
    leaderboard leaderUsers[5];
    int userCount = loadUsers(users);
    int leaderCount = loadLeader(leaderUsers);

    string username, password;
    cout << "Enter username: ";
    cin >> username;

    /////////////////username vojud darad ya na
    int userIndex = -1;
    for (int i = 0; i < userCount; i++) 
    {
        if (users[i].username == username) {
            userIndex = i;
            break;
        }
    }
    ///////passcode dorost gereftn
    if (userIndex == -1) 
    { 
        do {
            cout << "Enter a passcode: ";
            cin >> password;
        } while (password.length() != 4);

        users[userCount].username = username;
        users[userCount].password = password;
        userCount++;
    } 
    else 
    { 
        cout << "Enter passcode: ";
        cin >> password;
        

        for (int i = 0; i < 3 ; i++)
        {
            if (users[userIndex].password == password && password.length() == 4) 
            {
                break;
            }
            else
            {
                cout << "Incorrect passcode. try again: ";
                cin>> password;
            }

            if (i == 2 && (users[userIndex].password != password || password.length() != 4))   
                exit(0);        
        }
        
    }

    saveUsers(users, userCount);

    
    // if (findLeader == -1)
    // {
    //     leaderUsers[leaderCount].username = username;
    //     leaderUsers[leaderCount].score =score;
    // }
    // else
    // {
    //     leaderUsers[findLeader].score = score;
    // }



    system("cls");
    SetConsoleTextAttribute(hConsole, 3); ///blue-ish
    cout<<"Welcome to Aerial Bombardment!\n\n";
    SetConsoleTextAttribute(hConsole, 5); 
    cout<<"You have signed in as ";
    SetConsoleTextAttribute(hConsole, 6); //orange
    cout<< username<<endl;
    SetConsoleTextAttribute(hConsole, 7);

    while(true)
    {
        // system("cls"); 

        
        int menu = mainMenu();

        
                
        if (menu == 5) ////////////////////////////////////////exit
            exit(0);
    
        else if (menu == 4)//////////////////////////////////passcode change
        {
            system("cls");
            string newPassword = "";
    
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout<<"enter your new passcode: ";
            SetConsoleTextAttribute(hConsole, 7);
            cin>>newPassword;
            while (newPassword.length() != 4) 
            {
                cout << "Passcode must be 4 digits. Try again: ";
                cin >> newPassword;
            }
            users[userIndex].password = newPassword;
            // for (int i = 0; i < userCount ; i ++)
    
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            cout<<"passcode has changed successfully!";
            SetConsoleTextAttribute(hConsole, 7);

            saveUsers(users, userCount);

            returning();
            
        }
        else if (menu == 3)/////////////////////////////////////////////leaderboard
        {
            system("cls");

            print_leader();
            /////////////////////
            returning();
    
        }
        else if (menu == 2)/////////////////////////////rules
        {
            system("cls");
    
            print_rules();

            returning();
    
        }
        else if (menu == 1)///////////////////////////////////////////////////////////////////////////////start game
        {
            int findLeader = -1;
            for (int i = 0; i < leaderCount; i++) 
            {
                if (leaderUsers[i].username == username) {
                    findLeader = i;
                    break;
                }
            }

            system("cls");
            srand(time(0));
            int speed = 1;
            int plane_speed = set_speed(speed);
            bool running = true;
            int warn_screen = 0, cheer_screen = 0;
            int score = 0;
            // leader_users[0].username = username;
            // leader_users[0]

            print_ground();
            print_wall();
            inGame_rules();

            for(int i = 0; i < build_count; i++)
            {
                build_x[i][0] = 13 + 12*i;
                build_x [i][1] = build_x [i][0] + 6;
                build_height[i] = min_building + rand() % 7 ;
                build_height[i] = 28 - build_height[i];
                build_color[i] = 4 + rand() % 3 ;
            }
            print_building(build_x, build_height, build_color); 

            bool first0_w = false, first0_c =false;
            
            ///////////////////animation
            while(running)
            {
                bool firstBomb = false;
                
                if ( (build_x[0][0] < 0) && (build_x[1][0] < 0) && (build_x[2][0] < 0) && (build_x[3][0] < 0) && (build_x[4][0] < 0) ) //////winning dialog
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                        
                    }
                    saveLeader(leaderUsers, leaderCount);

                    system("cls");
                    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);      cout<<"\t~ You Won!~\t Your score: "<<score;
                    returning();

                }
                
                key k = getKey();

                ////////////////////special keys detection
                if (k == esc) 
                {
                    running = false; ///////////returning
                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    system("cls");
                    returning();
                }
                else if (k == space && bomb_coord[0] == -1 && bomb_coord[1] == -1) //////bomb
                {
                    firstBomb = true;
                    if (plane_dir)
                    {
                        bomb_coord[0] = airplane_coord[0] - 3;
                    }
                    else
                    {
                        bomb_coord[0] =airplane_coord[0] + 3;
                    }
                    bomb_coord[1] = airplane_coord[1] + 1;
                    gotoxy(bomb_coord[0], bomb_coord[1]);
                    cout<<"@";
                }
                else if (k == left_arrow && plane_dir == 1)
                {
                    speed--;
                    if (speed < 0)
                    {
                        speed = 0;
                    }
                    plane_speed= set_speed(speed);
                }
                else if (k == left_arrow && plane_dir == 0)
                {
                    speed++;
                    if (speed > 2)
                    {
                        speed = 2;
                    }
                    plane_speed= set_speed(speed);
                }
                else if (k == right_arrow && plane_dir == 1)
                {
                    speed++;
                    if (speed > 2)
                    {
                        speed = 2;
                    }
                    plane_speed= set_speed(speed);
                }
                else if (k == right_arrow && plane_dir == 0)
                {
                    speed--;
                    if (speed < 0)
                    {
                        speed = 0;
                    }
                    plane_speed= set_speed(speed);
                }



                /////dialogs
                if (warn_screen)
                {
                    warning_dialog();
                    warn_screen--;
                    if (warn_screen == 0)
                    {
                        first0_w = true;
                    }
                }
                else 
                {
                    if (first0_w)
                    {
                        clear_warning();
                        first0_w =false;
                    }
                    
                }
                
                if (cheer_screen)
                {
                    cheering_dialog(cheering);
                    cheer_screen--;
                    if (cheer_screen == 0)
                    {
                        first0_c = true;
                    }
                }
                else 
                {
                    if (first0_c)
                    {
                        clear_cheer();
                        cheering = 0;
                        first0_c =false;
                    }
                    
                }
                




                ///////////////// harekate plane
                print_airplane();
                if(plane_dir == 1)
                {
                    airplane_coord[0] += 2;
                }
                else
                {
                    airplane_coord[0] -= 2;
                }
                

                ////////// raft o bargasht plane

                if (airplane_coord[0] > 77)
                {
                    remove_airplane();
                    plane_dir = 0;
                    airplane_coord[0] -= 7;
                    airplane_coord[1]++;
                }
                if (airplane_coord[0] <= 2)
                {
                    remove_airplane();
                    plane_dir = 1;
                    airplane_coord[0] += 7;
                    airplane_coord[1]++;
                    
                }

                //////////// barkhord e plane   ///////losing dialog
                if ((airplane_coord[0] >= build_x[0][0] && airplane_coord[0] <= build_x[0][1] ) && (airplane_coord[1] >= build_height[0]+1))
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                    }
                    saveLeader(leaderUsers, leaderCount);
                    
                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);      cout<<"\t~ You Lost!~\t Your score: "<<score;
                    returning();
                }
                else if ((airplane_coord[0] >= build_x[1][0] && airplane_coord[0] <= build_x[1][1] ) && (airplane_coord[1] == build_height[1]+1))
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                    }
                    saveLeader(leaderUsers, leaderCount);

                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);      cout<<"\t~ You Lost!~\t Your score: "<<score;
                    returning();
                }
                else if ((airplane_coord[0] >= build_x[2][0] && airplane_coord[0] <= build_x[2][1] ) && (airplane_coord[1] == build_height[2]+1))
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                    }
                    saveLeader(leaderUsers, leaderCount);

                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);      cout<<"\t~ You Lost!~\t Your score: "<<score;
                    returning();
                }
                else if ((airplane_coord[0] >= build_x[3][0] && airplane_coord[0] <= build_x[3][1] ) && (airplane_coord[1] == build_height[3]+1))
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                    }
                    saveLeader(leaderUsers, leaderCount);

                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);      cout<<"\t~ You Lost!~\t Your score: "<<score;
                    returning();
                }
                else if ((airplane_coord[0] >= build_x[4][0] && airplane_coord[0] <= build_x[4][1] ) && (airplane_coord[1] == build_height[4]+1))
                {
                    running = false; 

                    airplane_coord[0] = plane_x;
                    airplane_coord[1] = plane_y;
                    plane_dir = 1;

                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;

                    if (findLeader == -1) /////////////saving score
                    {
                        leaderUsers[leaderCount].username = username;
                        leaderUsers[leaderCount].score =score;
                        leaderCount++;
                        sort_leaderboard(leaderUsers, leaderCount);
                    }
                    else
                    {
                        if (score > leaderUsers[findLeader].score)
                        {
                            leaderUsers[findLeader].score = score;
                            sort_leaderboard(leaderUsers, leaderCount);
                        }
                    }
                    saveLeader(leaderUsers, leaderCount);

                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);      cout<<"\t~ You Lost!~\t Your score: "<<score;
                    returning();
                }


                ///////////////////harekate bomb

                if (bomb_coord[1] != -1 && !firstBomb)
                {
                    clear_bomb();

                    bomb_coord[1]++;
                    
                    print_bomb();
                }

                //////////////////////barkhord bomb

                if (bomb_coord[1] == 27)
                {
                    /////////////warning be zamin khordan dialog
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    warning_dialog();
                    warn_screen = 7;
                }
                else if((bomb_coord[1] == (build_height[0] + 1)) && (bomb_coord[0] >= build_x[0][0]) && (bomb_coord[0] <= build_x[0][1])) 
                {
                    cheering_dialog(28 - build_height[0]);
                    cheer_screen = 7;
                    remove_building(build_x, build_height, 0); ///////////////tashvigh khane kharab kardan dialog
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1; 
                    score += 200;
                }
                else if((bomb_coord[1] == (build_height[1] + 1)) && (bomb_coord[0] >= build_x[1][0]) && (bomb_coord[0]<= build_x[1][1]))
                {
                    cheering_dialog(28 - build_height[1]);
                    cheer_screen = 7;
                    remove_building(build_x, build_height, 1);
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    score += 200;
                    
                }
                else if((bomb_coord[1] == (build_height[2] + 1)) && (bomb_coord[0]>= build_x[2][0]) && (bomb_coord[0]<= build_x[2][1]))
                {
                    cheering_dialog(28 - build_height[2]);
                    cheer_screen = 7;
                    remove_building(build_x, build_height, 2);
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    score += 200;
                    
                }
                else if((bomb_coord[1] == (build_height[3] + 1)) && (bomb_coord[0]>= build_x[3][0]) && (bomb_coord[0]<= build_x[3][1]))
                {
                    cheering_dialog(28 - build_height[3]);
                    cheer_screen = 7;
                    remove_building(build_x, build_height, 3);
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    score += 200;
                    
                }
                else if((bomb_coord[1] == (build_height[4] + 1)) && (bomb_coord[0]>= build_x[4][0]) && (bomb_coord[0]<= build_x[4][1]))
                {
                    cheering_dialog(28 - build_height[4]);
                    cheer_screen = 7;
                    remove_building(build_x, build_height, 4);
                    clear_bomb();
                    bomb_coord[0] = -1;
                    bomb_coord[1] = -1;
                    score += 200;
                }
            

                

                
                Sleep(plane_speed);
                remove_airplane();
            }
            
            system("cls");
            
    
            ///////////////////////////////////
            // returning();
    
        }
    }
    return 0;
}