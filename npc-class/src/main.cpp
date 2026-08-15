#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Stats {
  int maxHp;
  int attackPower;
  int defensePower;
};

class NpcCharacter {

  string name; // 名前
  int hp;      // HP
  Stats stats; // 能力値

public:
  NpcCharacter(const string &n, const Stats &st) {
    this->name = n;
    this->hp = st.maxHp;
    this->stats = st;
  }

  // 攻撃
  void attack(NpcCharacter &target) const {
    int damagePoint = damageCalculation(target.stats.defensePower);
    if (damagePoint > 0) {
      cout << name << "が" << target.name << "を攻撃！" << endl;
      cout << "ダメージ: " << damagePoint << endl << endl;
      target.takeDamage(damagePoint);
    }
  }

  // ステータス表示
  void displayStatus() const {
    cout << "[" << name << "]" << endl;
    cout << "HP: " << hp << " / " << stats.maxHp << endl;
    cout << "Attack: " << stats.attackPower << endl;
    cout << "Defense: " << stats.defensePower << endl;
    if (isAlive()) {
      cout << "Status: Alive" << endl;
    } else {
      cout << "Status: Dead" << endl;
    }
  };

  // 回復
  void restoreHp() {
    if (!isAlive()) {
      showAlreadyDeadMessage();
      return;
    }
    if (hp == stats.maxHp) {
      cout << name << "の体力は満タンだ！" << endl;
      return;
    }
    int healPoint = -1;
    while (true) {
      cout << "どれくらい回復しますか？" << endl;
      cin >> healPoint;
      if (healPoint > 0)
        break;
      cout << "0より大きい数値を指定してください" << endl;
    }
    heal(healPoint);
    showHp();
  }

private:
  bool isAlive() const { return hp > 0; }

  void showAlreadyDeadMessage() const {
    cout << name << "はすでに死んでいる！" << endl;
  }
  void showHp() const {
    cout << name << endl;
    cout << "HP: " << hp << " / " << stats.maxHp << endl;
  }
  // ダメージ計算
  int damageCalculation(int defense) const {
    if (!isAlive()) {
      showAlreadyDeadMessage();
      return 0;
    }
    return max(stats.attackPower - defense, 1);
  }

  // ダメージ
  void takeDamage(int damage) {
    hp = max(hp - damage, 0);
    showHp();
  }

  // 回復
  void heal(int healPoint) { hp = min(hp + healPoint, stats.maxHp); }
};

// NPC一覧・ステータス表示
void showNpcList(const vector<NpcCharacter> &npcs) {
  cout << "[NPC一覧・ステータス表示]" << endl;
  for (const auto &npc : npcs) {
    npc.displayStatus();
    cout << endl;
  }
}

int main() {

  vector<NpcCharacter> npcCharacters;
  NpcCharacter slime("slime", {3, 1, 1});
  NpcCharacter dragon("ドラゴン", {50, 10, 10});

  npcCharacters.push_back(slime);
  npcCharacters.push_back(dragon);

  while (true) {
    cout << "何をしますか？（数字で選択してください）" << endl;
    vector<string> actions = {
        "NPC一覧・ステータスを表示する",
        "NPC A が NPC B を攻撃する",
        "NPC B が NPC A を攻撃する",
        "NPC A を回復する",
        "NPC B を回復する",
        "プログラムを終了する",
    };

    int index = 1;
    for (const auto &action : actions) {
      cout << index << ". " << action << endl;
      index++;
    }
    int option = 0;
    cin >> option;
    switch (option) {
    case 1:
      showNpcList(npcCharacters);
      break;
    case 2:
      npcCharacters[0].attack(npcCharacters[1]);
      break;
    case 3:
      npcCharacters[1].attack(npcCharacters[0]);
      break;
    case 4:
      npcCharacters[0].restoreHp();
      break;
    case 5:
      npcCharacters[1].restoreHp();
      break;
    case 6:
      cout << "プログラムを終了します" << endl;
      return 0;
    default:
      cout << "不正値を検出しました。プログラムを終了します\n" << endl;
      return -1;
    }
    cout << endl;
  };
}
