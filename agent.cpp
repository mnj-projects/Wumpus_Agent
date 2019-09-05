#include <vector>
#include <tuple>
#include <map>
#include <algorithm>

using namespace std;

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

vector<tuple<int,int>> get_compliment(vector<tuple<int,int>> minuend, vector<tuple<int,int>> subtrahend){
    vector<tuple<int,int>> difference;
    set_difference(minuend.begin(), minuend.end(), subtrahend.begin(), subtrahend.end(),inserter(difference, difference.begin()));
    return difference;
}

vector<tuple<int,int>> get_intersection(vector<tuple<int,int>> vec1, vector<tuple<int,int>> vec2){
    vector<tuple<int,int>> intersection;
    set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(),inserter(intersection, intersection.begin()));
    return intersection;
}

class Agent
{
private:
    vector<tuple<int,int>> OK = {make_tuple(3,0), make_tuple(2,0), make_tuple(3,1)};
    vector<tuple<int,int>> visited = {make_tuple(3,0)};
    vector<tuple<int,int>> possible_wumpus;
    vector<tuple<int,int>> possible_pit;
    vector<tuple<int,int>> possible_gold;
    vector<tuple<int,int>> wumpus_sensed;
    vector<tuple<int,int>> pit_sensed;
    vector<tuple<int,int>> gold_sensed;
    map<tuple<int,int>, vector<string>> history = {{make_tuple(3,0),{}}};
    tuple<int,int,int> state = {make_tuple(3,0,8)};

public:
    void move(){

        if(OK.size() > visited.size()){
            tuple<int,int> point = make_tuple(get<0>(state),get<1>(state));
            vector<tuple<int,int>> possible_moves = get_intersection(get_compliment(OK,visited), get_adjacents(point));
            while(possible_moves.size() > 0){
                tuple<int,int> newpos = possible_moves.back();
                possible_moves.pop_back();
                goto_adjacent(newpos);
            }
        }
    }

    void goto_adjacent(tuple<int,int> pos){
        int dxn = get_dxn(pos);
        if(get<2>(state) == dxn){
            //order the game move
            //return
        }else{
            //order the game rotate to the new direction and move
            //return
        }
    }

    int get_dxn(tuple<int,int> pos){
        int x_agent = get<0>(state);
        int y_agent = get<1>(state);
        int x_pos = get<0>(pos);
        int y_pos = get<1>(pos);

        if(x_agent == x_pos){
            if(y_pos > y_agent){
                return 8;
            }else{
                return 2;
            }
        }else if(y_agent == y_pos){
            if(x_pos > x_agent){
                return 4;
            }else{
                return 6;
            }
        }
    }
};
