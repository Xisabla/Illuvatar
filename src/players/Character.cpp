#include "players/Character.h"


using namespace std;

Character::Character(Map& map, Point point, Faction faction): map(map), point(point), faction(faction) {
    this->map.getTile(this->point).setCharacter(this);
}

Character::~Character() {
    this->map.getTile(this->point).unsetCharacter();
}

vector<string>& Character::getMsgList() { return this->msgList; }

void Character::setMsgList(vector<string>& msgList) {
    this->msgList = move(msgList);
}

void Character::addMsg(string msg) {
    this->msgList.push_back(msg);
}

void Character::addMsgList(vector<string>& msgList) {
    move(msgList.begin(), msgList.end(), back_inserter(this->msgList));
}

string Character::getRandomMsg() {
    if (this->msgList.empty()) {
        cout << "error at Character::getRandomMsg()" << endl;
        exit(1);
    }
    return this->msgList[unirand::getValue(0, this->msgList.size() - 1)];
}

string Character::dropRandomMsg() {
    if (this->msgList.empty()) {
        cout << "error at Character::dropRandomMsg()" << endl;
        exit(1);
    }
    int pos = unirand::getValue(0, this->msgList.size() - 1);
    string msg = this->msgList[pos];
    this->msgList.erase(this->msgList.begin() + pos - 1);
    return msg;
}

void Character::dropMsgList() {
    this->msgList.clear();
}

bool Character::gotMsg() {
    return !this->msgList.empty();
}

bool Character::gotOneMsg() {
    return this->msgList.size() == 1;
}

bool Character::gotLotOfMsgs() {
    return this->msgList.size() > 1;
}