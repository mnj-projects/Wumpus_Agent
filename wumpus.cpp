#include <iostream>
#include <tuple>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

bool find_element_vector(vector<tuple<int, int>> vec, tuple<int, int> element)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] == element)
        {
            return true;
        }
    }
    return false;
}

tuple<int, int> find_element_pos(vector<tuple<int, int>> vec, string board[4][4], string element)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (board[get<0>(vec[i])][get<1>(vec[i])] == element)
        {
            return vec[i];
        }
    }
}

bool check_valid_pos(tuple<int, int> pos, int size)
{
    int x = get<0>(pos);
    int y = get<1>(pos);
    if (x >= 0 && x <= 3 && y >= 0 && y <= 3)
    {
        return true;
    }
    return false;
}

void generate_tuple_validate(tuple<int, int> pos, int dx, int dy, vector<tuple<int, int>> * container)
{
    tuple<int, int> new_pos;
    get<0>(new_pos) = get<0>(pos) + dx;
    get<1>(new_pos) = get<1>(pos) + dy;
    if (check_valid_pos(new_pos, 4))
    {
        container->push_back(new_pos);
    }
}

vector<tuple<int, int>> get_adjacents(tuple<int, int> pos)
{
    vector<tuple<int, int>> adjacents;

    generate_tuple_validate(pos,1,0,&adjacents);
    generate_tuple_validate(pos,-1,0,&adjacents);
    generate_tuple_validate(pos,0,1,&adjacents);
    generate_tuple_validate(pos,0,-1,&adjacents);

    return adjacents;
}

class WumpusGame
{
private:
    bool game_status = true; //not over
    bool wumpus = true;
    string board[4][4];
    tuple<int, int> agent_pos = make_tuple(3, 0);
    map<string, int> dxn_map = {{"up", 8}, {"down", 2}, {"left", 4}, {"right", 6}};
    int agent_dxn = 8;
    bool agent_has_arrow = true;
    vector<string> agent_sense;
    vector<string> game_parts = {"P", "W", "P", "G", "P"};
    vector<tuple<int, int>> game_parts_pos;
    tuple<int, int> invalid_pos[3] = {make_tuple(3, 0), make_tuple(3, 1), make_tuple(2, 0)};

public:
    void startGame(vector<string> sense_recorder)
    {
        generateBoard();
        showStatus();

        while (game_status)
        {
            string command;
            cin >> command;
            if (command.compare("move") == 0)
            {
                sense_recorder = move_agent();
                //cout << sense_recorder[0] << endl;
            }
            else if (command.compare("fire") == 0)
                fire_arrow();
            else if (command.compare("rotateup") == 0)
                rotate_agent("up");
            else if (command.compare("rotatedown") == 0)
                rotate_agent("down");
            else if (command.compare("rotateleft") == 0)
                rotate_agent("left");
            else if (command.compare("rotateright") == 0)
                rotate_agent("right");
            else if (command.compare("grab") == 0)
                grab_gold();
            else if (command.compare("exit") == 0 || command.compare("quit") == 0)
            {
                exit(0);
            }
            else
                cout << "The list of commands are move, fire , rotateup , rotatedown , rotateleft , rotateright , grab & exit" << endl;
        }
    }

    bool compare_with_game_objects(string name, vector<string> game_objects, string *feeling)
    {
        for (int i = 0; i < game_objects.size(); i++)
        {
            if (name.compare(game_objects[i]) == 0)
            {
                *feeling = game_objects[i];
                return true;
            }
        }
        return false;
    }

    void update_senses()
    {
        agent_sense.clear();
        string feel;
        vector<tuple<int, int>> adjacent_pos = get_adjacents(agent_pos);
        vector<string> unique_game_objects = {"P", "W", "G"};
        for (int i = 0; i < adjacent_pos.size(); i++)
        {
            if (compare_with_game_objects(board[get<0>(adjacent_pos[i])][get<1>(adjacent_pos[i])], unique_game_objects, &feel))
            {
                agent_sense.push_back(feel);
            }
            continue;
        }
        for (int i = 0; i < agent_sense.size(); i++)
        {
            if(agent_sense[i] == "P"){
                cout << "You feel a breeze" << endl;
            }
            else if (agent_sense[i] == "W"){
                cout << "You smell a wumpus " << endl;
            }
            else if (agent_sense[i] == "G"){
                cout << "You see glitter on the walls" << endl;
            }
           // cout << "Sensed " << agent_sense[i] << endl;
        }
        
    }

    vector<string> move_agent()
    {
        tuple<int, int> new_pos;

        if (agent_dxn == 8)
        {
            new_pos = make_tuple(get<0>(agent_pos) - 1, get<1>(agent_pos));
        }
        else if (agent_dxn == 2)
        {
            new_pos = make_tuple(get<0>(agent_pos) + 1, get<1>(agent_pos));
        }
        else if (agent_dxn == 4)
        {
            new_pos = make_tuple(get<0>(agent_pos), get<1>(agent_pos) - 1);
        }
        else
        {
            new_pos = make_tuple(get<0>(agent_pos), get<1>(agent_pos) + 1);
        }

        check_validity_update_board(new_pos, 4);
        update_senses();
        return agent_sense;
    }

    void check_validity_update_board(tuple<int, int> pos, int size)
    {
        if (check_valid_pos(pos, size))
        {
            tuple<int, int> prev_agent_pos = agent_pos;
            agent_pos = pos;
            if (!check_game_over())
            {
                board[get<0>(prev_agent_pos)][get<1>(prev_agent_pos)] = " ";
                board[get<0>(agent_pos)][get<1>(agent_pos)] = "A";
                cout << get<0>(agent_pos) << "," << get<1>(agent_pos) << endl;
                showStatus();
            }
            else
            {
                game_status = false;
            }
        }
    }

    void rotate_agent(string dxn)
    {
        if (int value = dxn_map[dxn])
        {
            agent_dxn = value;
        }
        cout << "Agent rotated to: " << agent_dxn << endl;
    }

    void remove_wumpus()
    {
        for (int i = 0; i < game_parts_pos.size(); i++)
        {
            if (board[get<0>(game_parts_pos[i])][get<1>(game_parts_pos[i])] == "W")
            {
                board[get<0>(game_parts_pos[i])][get<1>(game_parts_pos[i])] = " ";
                game_parts_pos.erase(game_parts_pos.begin() + i);
                showStatus();
                cout << "You have slain the mighty Wumpus" << endl;
                break;
            }
        }
    }

    bool grab_gold()
    {
        cout << get<0>(agent_pos) << " " << get<1>(agent_pos) << endl;
        if(board[get<0>(agent_pos)][get<1>(agent_pos)] == "G"){
            return true;
            //check_game_over();
            game_status = false;
        }
        else{
            cout << "No gold here" << endl;
            return false;
           // check_game_over();
        }
    }

    void fire_arrow()
    {
        if (agent_has_arrow)
        {
            tuple<int, int> wumpus_pos = find_element_pos(game_parts_pos, board, "W");
            if (agent_dxn == 8 && get<1>(agent_pos) == get<1>(wumpus_pos) && get<0>(agent_pos) > get<0>(wumpus_pos))
            {
                remove_wumpus();
            }
            else if (agent_dxn == 2 && get<1>(agent_pos) == get<1>(wumpus_pos) && get<0>(agent_pos) < get<0>(wumpus_pos))
            {
                remove_wumpus();
            }
            else if (agent_dxn == 4 && get<0>(agent_pos) == get<0>(wumpus_pos) && get<1>(agent_pos) > get<1>(wumpus_pos))
            {
                remove_wumpus();
            }
            else if (agent_dxn == 6 && get<0>(agent_pos) == get<0>(wumpus_pos) && get<1>(agent_pos) < get<1>(wumpus_pos))
            {
                remove_wumpus();
            }

            agent_has_arrow = false;
        }
    }

    void generateBoard()
    {
        vector<string> empty_places(8, "");
        game_parts.insert(game_parts.end(), empty_places.begin(), empty_places.end());
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (make_tuple(row, col) == invalid_pos[1] || make_tuple(row, col) == invalid_pos[2])
                {
                    continue;
                }
                else if (make_tuple(row, col) == invalid_pos[0])
                {
                    board[row][col] = "A";
                }
                else
                {
                    int index = (rand() % 8);//game_parts.size());
                    board[row][col] = game_parts[index];
                    game_parts.erase(game_parts.begin() + index);
                    if (board[row][col] != "G" && board[row][col] != "")
                    {
                        game_parts_pos.push_back(make_tuple(row, col));
                    }
                }
            }
        }
    }

    void showStatus()
    {
        cout << "----------------------------------------" << endl;
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                cout << " | " << board[row][col];
            }
            cout << " | " << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    bool check_game_over()
    {
        if (find_element_vector(game_parts_pos, agent_pos))
        {
            cout << "GAME OVER!!" << endl;
            if (board[get<0>(agent_pos)][get<1>(agent_pos)] == "W")
            {
                cout << "You got eaten by the Wumpus!!" << endl;
            }
            else
            {
                cout << "You slipped through a Pit!!" << endl;
            }
            return true;
        }
        else if (grab_gold())
        {
            cout << "You have grabbed the gold, well played" << endl;
            cout << "You Won!!" << endl;
            cout << "Well Played!!" << endl;
            return true;
        }
        else
        {
            return false;
        }
    }
};

int main()
{
    WumpusGame game;
    vector<string> agents_feelings;
    game.startGame(agents_feelings);

    return 0;
}