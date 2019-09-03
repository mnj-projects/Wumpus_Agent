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

class WumpusGame
{
private:
    string board[4][4];
    tuple<int, int> agent_pos = make_tuple(3, 0);
    map<string, int> dxn_map = {{"up", 8}, {"down", 2}, {"left", 4}, {"right", 6}};
    int agent_dxn = 8;
    bool agent_has_arrow = true;
    string agent_sense[];
    string game_parts[5] = {"Pit", "Wumpus", "Pit", "Gold", "Pit"};
    vector<tuple<int, int>> game_parts_pos;

    tuple<int, int> invalid_pos[3] = {make_tuple(3, 0), make_tuple(3, 1), make_tuple(2, 0)};

public:
    tuple<string[], tuple<int, int>> move_agent(int dxn) {}
    void rotate_agent(string dxn)
    {
        if (int value = dxn_map[dxn])
        {
            agent_dxn = value;
        }
    }

    void remove_wumpus()
    {
        for (int i = 0; i < game_parts_pos.size(); i++)
        {
            if (board[get<0>(game_parts_pos[i])][get<1>(game_parts_pos[i])] == "Wumpus")
            {
                game_parts_pos.erase(game_parts_pos.begin() + i);
                board[get<0>(game_parts_pos[i])][get<1>(game_parts_pos[i])] = " ";
            }
        }
    }

    void fire_arrow()
    {
        if (agent_has_arrow)
        {
            tuple<int, int> wumpus_pos = find_element_pos(game_parts_pos, board, "Wumpus");
            if (agent_dxn == 8 && get<1>(agent_pos) == get<1>(wumpus_pos) && get<0>(agent_pos) > get<0>(wumpus_pos))
            {
                //remove wumpus from game
            }
            else if (agent_dxn == 2 && get<1>(agent_pos) == get<1>(wumpus_pos) && get<0>(agent_pos) < get<0>(wumpus_pos))
            {
                //remove wumpus
            }
            else if (agent_dxn == 4 && get<0>(agent_pos) == get<0>(wumpus_pos) && get<1>(agent_pos) > get<1>(wumpus_pos))
            {
                //remove wumpus
            }
            else if (agent_dxn == 6 && get<0>(agent_pos) == get<0>(wumpus_pos) && get<1>(agent_pos) < get<1>(wumpus_pos))
            {
                //remove wumpus
            }
        }
    }

    void startGame()
    {
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                if (make_tuple(row, col) == invalid_pos[0] || make_tuple(row, col) == invalid_pos[1] || make_tuple(row, col) == invalid_pos[2])
                {
                }
                else
                {
                    if ((rand() % 2) == 1)
                    {
                        board[row][col] = game_parts[(rand() % sizeof(game_parts) / sizeof(game_parts[0]))];
                        if (board[row][col] != "Gold")
                        {
                            game_parts_pos.push_back(make_tuple(row, col));
                        }
                    }
                    else
                    {
                        board[row][col] = " ";
                    }
                }
            }
        }
    }

    void show_status()
    {
        cout << "----------------------------------------";
        for (int row = 0; row < 4; row++)
        {
            for (int col = 0; col < 4; col++)
            {
                cout << "| " << board[row][col];
            }
            cout << " |" << endl;
        }
    }

    bool check_game_over()
    {
        if (find_element_vector(game_parts_pos, agent_pos))
        {
            cout << "GAME OVER!!" << endl;
            if (board[get<0>(agent_pos)][get<1>(agent_pos)] == "Wumpus")
            {
                cout << "You got eaten by the Wumpus!!" << endl;
            }
            else
            {
                cout << "You slipped through a Pit!!" << endl;
            }
            return true;
        }
        else if (board[get<0>(agent_pos)][get<1>(agent_pos)] == "Gold")
        {
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

    return 0;
}