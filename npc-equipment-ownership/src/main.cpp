#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Equipment {
 public:
  const string name;
  const int attackBonus;

  Equipment(string name, int attackBonus) : name(std::move(name)), attackBonus(attackBonus) {}

  ~Equipment() {
    cout << name << " destroyed\n";
  }

  void showStatus() const {
    cout << name << '\n';
    cout << "Attack Bonus: " << attackBonus << '\n';
  }
};

class NpcCharacter {
 public:
  const string name;
  const int attackPower;
  unique_ptr<Equipment> equipment;

  NpcCharacter(string name, int attackPower) : name(std::move(name)), attackPower(attackPower) {}
  NpcCharacter(const NpcCharacter&) = delete;
  NpcCharacter(NpcCharacter&&) noexcept = default;
  NpcCharacter& operator=(const NpcCharacter&) = delete;
  NpcCharacter& operator=(NpcCharacter&&) = delete;

  ~NpcCharacter() {
    cout << name << " destroyed\n";
  }

  void showStatus() const {
    cout << "[" << name << "]\n";
    cout << "Base Attack: " << attackPower << '\n';
    cout << "Equipment: ";
    if (equipment == nullptr) {
      cout << "None\n";
    } else {
      equipment->showStatus();
      cout << "Total Attack: " << attackPower + equipment->attackBonus << '\n' << '\n';
    }
  }

  void equip(unique_ptr<Equipment> equ) {
    equipment = std::move(equ);
  }
};

void viewEquipmentList(const vector<unique_ptr<Equipment>>& list) {
  int index = 1;
  for (const auto& pe : list) {
    cout << "No." << index << '\n';
    pe->showStatus();
    index++;
    cout << "\n";
  }
}

void viewNpcCharacter(const vector<NpcCharacter>& characters) {
  for (const auto& chara : characters) {
    chara.showStatus();
    cout << "\n";
  }
}

int inputNum(int min, int max) {
  int num = 0;
  while (true) {
    if (min == max) {
      return min;
    }
    cout << min << " ~ " << max << "までの数字を入力してください\n";

    if (!(cin >> num)) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    if (num < min || max < num) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    return num;
  }
}

void viewBeforeAfter(const string& label, vector<unique_ptr<Equipment>>& equipmentList,
                     NpcCharacter& npcCharacter) {
  cout << "[" << label << "]\n";
  cout << "移動元:\n";
  viewEquipmentList(equipmentList);

  cout << "移動先:\n";
  npcCharacter.showStatus();
}

void equip(vector<unique_ptr<Equipment>>& equipmentList, NpcCharacter& npcCharacter) {
  viewEquipmentList(equipmentList);
  if (equipmentList.empty()) {
    cout << "装備可能な装備品がありません！\n";
    return;
  }
  cout << "何番の装備を " << npcCharacter.name << " に装備させますか？\n";
  int eIndex = inputNum(1, static_cast<int>(equipmentList.size()));
  viewBeforeAfter("移動前", equipmentList, npcCharacter);
  if (npcCharacter.equipment != nullptr) {
    cout << "現在の装備品を装備袋に戻します\n";
    equipmentList.push_back(std::move(npcCharacter.equipment));
  }
  npcCharacter.equip(std::move(equipmentList[eIndex - 1]));
  equipmentList.erase(equipmentList.begin() + eIndex - 1);
  viewBeforeAfter("移動後", equipmentList, npcCharacter);
}

void viewBeforeAfter(const string& label, NpcCharacter& from, NpcCharacter& to) {
  cout << "[" << label << "]\n";
  cout << "移動元:\n";
  from.showStatus();
  cout << "移動先:\n";
  to.showStatus();
}

void giveEquipmentTo(vector<unique_ptr<Equipment>>& equipmentList, NpcCharacter& from,
                     NpcCharacter& to) {
  if (from.equipment == nullptr) {
    cout << "装備品がありません！\n";
    return;
  }

  viewBeforeAfter("移動前", from, to);
  if (to.equipment != nullptr) {
    equipmentList.push_back(std::move(to.equipment));
  }

  to.equip(std::move(from.equipment));

  viewBeforeAfter("移動後", from, to);
}

void testTemporaryScope() {
  cout << "一時スコープ開始\n";

  {
    auto npc = NpcCharacter("Test", 100);
    auto equipment = make_unique<Equipment>("Tesh Sword", 100);
    npc.equip(std::move(equipment));
    cout << "スコープ内\n";
  }

  cout << "一時スコープ終了\n";
}

auto main() -> int {
  vector<NpcCharacter> npcCharacters;
  npcCharacters.emplace_back("slime", 3);
  npcCharacters.emplace_back("dragon", 10);
  vector<unique_ptr<Equipment>> equipmentList;
  vector<string> actions = {
      "NPC一覧・装備状態を表示",
      "装備品を生成する",
      "NPC A に装備させる",
      "NPC B に装備させる",
      "NPC A から NPC B へ装備を渡す",
      "NPC B から NPC A へ装備を渡す",
      "一時テスト: 一時スコープを抜けた瞬間に破棄される",
      "プログラムを終了する",

  };

  while (true) {
    int index = 1;
    for (const auto& action : actions) {
      cout << index << ". " << action << '\n';
      index++;
    }

    int option = inputNum(1, static_cast<int>(actions.size()));

    switch (option) {
      case 1:
        viewNpcCharacter(npcCharacters);
        break;
      case 2: {
        string name = "Iron Sword";
        equipmentList.push_back(make_unique<Equipment>(name, 5));
        cout << name << "を作った!\n";
        break;
      };
      case 3:
        equip(equipmentList, npcCharacters[0]);
        break;
      case 4:
        equip(equipmentList, npcCharacters[1]);
        break;
      case 5:
        giveEquipmentTo(equipmentList, npcCharacters[0], npcCharacters[1]);
        break;
      case 6:
        giveEquipmentTo(equipmentList, npcCharacters[1], npcCharacters[0]);
        break;
      case 7:
        testTemporaryScope();
        break;
      case 8:
        cout << "プログラムを終了します\n";
        return 0;
      default:
        return -1;
    }
    cout << '\n';
  }
}
