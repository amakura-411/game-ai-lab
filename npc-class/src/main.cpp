#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Stats {
  int maxHp;
  int attackPower;
  int defensePower;
};

class NpcCharacter {
  const string name;  // 名前
  int hp;             // HP
  const Stats stats;  // 能力値

 public:
  NpcCharacter(string nm, const Stats& st) : name(std::move(nm)), hp(st.maxHp), stats(st) {}

  // 攻撃
  void attack(NpcCharacter& target) const {
    int damagePoint = damageCalculation(target.stats.defensePower);
    if (damagePoint > 0) {
      cout << name << "が" << target.name << "を攻撃！" << '\n';
      cout << "ダメージ: " << damagePoint << '\n' << '\n';
      target.takeDamage(damagePoint);
    }
  }

  // ステータス表示
  void displayStatus() const {
    cout << "[" << name << "]" << '\n';
    cout << "HP: " << hp << " / " << stats.maxHp << '\n';
    cout << "Attack: " << stats.attackPower << '\n';
    cout << "Defense: " << stats.defensePower << '\n';
    if (isAlive()) {
      cout << "Status: Alive" << '\n';
    } else {
      cout << "Status: Dead" << '\n';
    }
  }

  // 回復
  void restoreHp() {
    if (!isAlive()) {
      showAlreadyDeadMessage();
      return;
    }
    if (hp == stats.maxHp) {
      cout << name << "の体力は満タンだ！" << '\n';
      return;
    }
    int healPoint = -1;
    while (true) {
      cout << "どれくらい回復しますか？" << '\n';
      cin >> healPoint;
      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "数値を入力してください" << '\n';
        continue;
      }
      if (healPoint > 0) {
        break;
      }
      cout << "0より大きい数値を指定してください" << '\n';
    }
    heal(healPoint);
    showHp();
  }

 private:
  [[nodiscard]] auto isAlive() const -> bool {
    return hp > 0;
  }

  void showAlreadyDeadMessage() const {
    cout << name << "はすでに死んでいる！" << '\n';
  }
  void showHp() const {
    cout << name << '\n';
    cout << "HP: " << hp << " / " << stats.maxHp << '\n';
  }
  // ダメージ計算
  [[nodiscard]] auto damageCalculation(int defense) const -> int {
    if (!isAlive()) {
      showAlreadyDeadMessage();
      return 0;
    }
    return std::max(stats.attackPower - defense, 1);
  }

  // ダメージ
  void takeDamage(int damage) {
    hp = std::max(hp - damage, 0);
    showHp();
  }

  // 回復
  void heal(int healPoint) {
    hp = std::min(hp + healPoint, stats.maxHp);
  }
};

// NPC一覧・ステータス表示
void showNpcList(const vector<NpcCharacter>& npcs) {
  cout << "[NPC一覧・ステータス表示]" << '\n';
  for (const auto& npc : npcs) {
    npc.displayStatus();
    cout << '\n';
  }
}

auto main() -> int {
  vector<NpcCharacter> npcCharacters;
  NpcCharacter slime("slime", {3, 1, 1});
  NpcCharacter dragon("ドラゴン", {50, 10, 10});

  npcCharacters.push_back(slime);
  npcCharacters.push_back(dragon);

  while (true) {
    cout << "何をしますか？（数字で選択してください）" << '\n';
    vector<string> actions = {
        "NPC一覧・ステータスを表示する",
        "NPC A が NPC B を攻撃する",
        "NPC B が NPC A を攻撃する",
        "NPC A を回復する",
        "NPC B を回復する",
        "プログラムを終了する",
    };

    int index = 1;
    for (const auto& action : actions) {
      cout << index << ". " << action << '\n';
      index++;
    }
    int option = 0;
    cin >> option;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "数値を入力してください" << '\n';
      continue;
    }

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
        cout << "プログラムを終了します" << '\n';
        return 0;
      default:
        cout << "不正値を検出しました。プログラムを終了します\n" << '\n';
        return -1;
    }
    cout << '\n';
  }
}
