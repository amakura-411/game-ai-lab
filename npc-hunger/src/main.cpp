
#include <cstdio>
#include <random>

int random_num(int min, int max) {
  std::random_device seed;      // 非決定論的な乱数生成器
  std::mt19937 engine(seed());  // メルセンヌ・ツイスタ
  std::uniform_int_distribution<int> range(min, max);

  return range(engine);
}

int hunger_increase(int hunger) {
  // 空腹度ランダムな数値分増加させる
  int increase_amount = random_num(1, 10);
  hunger += increase_amount;
  printf("空腹度が%d上がった（現在の空腹度: %d）\n", increase_amount, hunger);

  return hunger;
}

int hunger_decrease(int hunger, char name[]) {
  // 空腹度をランダムな数値分減少させる
  int decrease_amount = random_num(1, 3);
  hunger -= decrease_amount;

  printf("%sはリンゴを食べた。空腹度が%d回復！（現在の空腹度：%d）\n", name, decrease_amount,
         hunger);

  return hunger;
}

int hitpoint_decrease(int hit_point, char name[]) {
  int hp_deacrease = random_num(1, 3);
  hit_point -= hp_deacrease;
  printf("%sの空腹は限界だ！ HPが%d減少！ (現在のHP:%d)\n", name, hp_deacrease, hit_point);

  return hit_point;
}

int main() {
  char name[50];
  printf("あなたの名前は？\n");
  scanf("%s", name);

  const int MAX_TURNS = 10;
  const int ACTION_THRESHOLD = 5;
  const int HUNGER_THRESHOLD = 10;
  int current_turn = 1;
  int hunger = 0;
  int hit_point = 5;

  while (current_turn <= MAX_TURNS) {
    // ターン数の表示
    printf("%dターン目\n", current_turn);
    printf("%sのHP:%d\n", name, hit_point);

    // 空腹度を1 ~ 5までのランダムな数値分増加させる
    hunger = hunger_increase(hunger);

    if (hunger >= ACTION_THRESHOLD) {
      printf("%sの行動：食事\n", name);

      hunger = hunger_decrease(hunger, name);
    } else {
      printf("%sの行動：待機\n", name);
    }

    if (hunger >= HUNGER_THRESHOLD) {
      hunger = 0;
      hit_point = hitpoint_decrease(hit_point, name);
    }

    if (hit_point <= 0) {
      printf("%sは力尽きた\n", name);
      printf("GAME OVER\n");
      break;
    }

    current_turn += 1;
  };

  if (hit_point > 0) {
    printf("GAME CLEAR\n");
  }
}
