#include <iostream>
#include<bits/stdc++.h>

using namespace std;
//typedef struct state state;

struct state{
    unsigned int numCannibals = 3;
    unsigned int numMissionaries = 3;
    unsigned int G = 0;
    unsigned int H = 0;
    unsigned int F = 0;
    bool boat = 0;
    struct state* prev = NULL;

    bool operator<(const state& n) const {
        return F > n.F; // for the priority queue to order nodes by lowest f_cost
    }
};

//enum transition {F01, F02, F11, f01, f02, b01, b02, b11, b01, b02,};

bool neg_condition(state curState) {
    bool a = false;
    bool b = false;

    if (curState.numMissionaries > 0 && curState.numMissionaries < curState.numCannibals)
        a = true;
    if (curState.numMissionaries < 3 && curState.numMissionaries > curState.numCannibals)
        b = true;
    return a + b;
}

state f10(state curState) {
    // 1 Cannibal move forward
    curState.numCannibals -= 1;
    return curState;
}

state f20(state curState) {
    // 2 Cannibals move forward
    curState.numCannibals -= 2;
    return curState;
}

state f11(state curState) {
    // 1 Cannibal move forward and 1 Missionary move forward
    curState.numCannibals -= 1;
    curState.numMissionaries -= 1;
    return curState;
}

state f01(state curState) {
    // 1 Missionary move forward
    curState.numMissionaries -= 1;
    return curState;
}

state f02(state curState) {
    // 2 Missionaries move forward
    curState.numMissionaries -= 2;
    return curState;
}

state b10(state curState) {
    // 1 Cannibal move backward
    curState.numCannibals += 1;
    return curState;
}

state b20(state curState) {
    // 2 Cannibals move backward
    curState.numCannibals += 2;
    return curState;
}

state b11(state curState) {
    // 1 Cannibal move backward and 1 Missionary move backward
    curState.numCannibals += 1;
    curState.numMissionaries += 1;
    return curState;
}

state b01(state curState) {
    // 1 Missionary move backward
    curState.numMissionaries += 1;
    return curState;
}

state b02(state curState) {
    // 2 Missionaries move backward
    curState.numMissionaries += 2;
    return curState;
}

int getH(state curState) {
    return curState.numMissionaries + curState.numCannibals; // d[cur(x,y) -> goal(0,0)]
}

state setF(state curState, state prevState) {
    curState.prev = new state;
    *curState.prev = prevState;
    curState.boat = !prevState.boat;
    curState.G = prevState.G + 1;
    curState.H = getH(curState);
    curState.F = curState.G + curState.H;
    return curState;
}

bool isGoal(state curState){
    return curState.numMissionaries + curState.numCannibals == 0;
}

bool checkIfExist(priority_queue<state>& pq, const state& node) {
    priority_queue<state> temp_pq = pq;
    while (!temp_pq.empty()) {
        if (temp_pq.top().numCannibals == node.numCannibals &&
            temp_pq.top().numMissionaries == node.numMissionaries &&
            temp_pq.top().boat == node.boat)
            return true;
        temp_pq.pop();
    }
    return false;
}

bool checkIfExist(vector<state> vt, state curState) {
    for (int i = 0; i < vt.size(); i++) {
        if (vt[i].numCannibals == curState.numCannibals &&
            vt[i].numMissionaries == curState.numMissionaries &&
            vt[i].boat == curState.boat)
            return true;
    }
    return false;
}

vector<state> getNeighbors(state curState) {
    vector<state> vt_temp;
    bool boat = curState.boat;
    if (boat == 1) {
        if (curState.numCannibals >= 1) {
            state temp = f10(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numCannibals >= 2) {
            state temp = f20(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numCannibals >= 1 && curState.numMissionaries >= 1) {
            state temp = f11(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numMissionaries >= 1) {
            state temp = f01(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numMissionaries >= 2) {
            state temp = f02(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
    }
    else {
        if (curState.numCannibals < 3) {
            state temp = b10(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numCannibals < 2) {
            state temp = b20(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numCannibals < 3 && curState.numMissionaries < 3) {
            state temp = b11(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numMissionaries < 3) {
            state temp = b01(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
        if (curState.numMissionaries <= 1) {
            state temp = b02(curState);
            temp = setF(temp, curState);
            if (!neg_condition(temp)) {
                vt_temp.push_back(temp);
            }
        }
    }
    return vt_temp;
}

void print(state* goal) {
    cout << goal->numCannibals << " " << goal->numMissionaries << endl;
    do {
        goal = goal->prev;
        cout << goal->numCannibals << " " << goal->numMissionaries << endl;
    } while (goal->prev != NULL);
}

//template <typename T, typename getNeighbors, typename _NeighborEnumerator, typename _Set, typename _SolutionVerifier, typename _Solution, typename _BeamSearch = no_beam_search>
template <typename T>
void astar(T curState, vector<T> (*getNeighbors)(T), bool (*isGoal)(T), void (*print)(T*)) {
    priority_queue <T> open;
    vector<T> close;
    open.push(curState);

    T* goal = new T;
    int isOut = false;

    while(open.size() > 0) {
        curState = open.top();
        //cout << "cur: " << curState.numCannibals << " " << curState.numMissionaries << " " << curState.boat << endl;
        open.pop();

        vector<T> vt_temp = getNeighbors(curState);

        for (T i: vt_temp) {
            //cout << i.numCannibals << " " << i.numMissionaries << " | " << i.prev->numCannibals << " " << i.prev->numMissionaries << endl;
            if (isGoal(i)) {
                goal = &i;
                isOut = true;
                break;
            }
        }
        //cout << "--------------" << endl;

        if (isOut)
            break;

        for (T i: vt_temp) {
            if (!checkIfExist(close, i) && !checkIfExist(open, i)) {
                open.push(i);
            }
        }
        close.push_back(curState);

        /**<
        cout << "Open:" << endl;
        priority_queue<T> temp_pq = open;
        while (!temp_pq.empty()) {
            cout << temp_pq.top().numCannibals << " " << temp_pq.top().numMissionaries << endl;
            temp_pq.pop();
        }
        cout << "=============" << endl;
        */
    }

    print(goal);
}

int main() {
    state curState;
    curState.numCannibals = 3;
    curState.numMissionaries = 3;
    curState.boat = 1;

    astar(curState, &getNeighbors, &isGoal, &print);

    return 0;
}
