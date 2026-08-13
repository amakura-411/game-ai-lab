
#include "stdio.h"
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

int main() {

  // CLIのメニュー表示
  printf("何をしますか？（数字で選択してください）\n\n");

  std::vector<std::string> actions = {"商品一覧を表示する",
                                      "商品IDから商品を検索する",
                                      "商品を入荷する",
                                      "商品を販売する",
                                      "全商品の在庫金額を表示する",
                                      "プログラムを終了する"};

  int index = 0;
  for (const auto &action : actions) {
    printf("%d. %s\n", index + 1, action.c_str());
    index++;
  }

  int option = 0;
  scanf("%d", &option);
  switch (option) {
  case 1:
    printf("1番!!");
    break;
  case 2:

  case 6:
    printf("プログラムを終了します");
    return 1;
  default:
    printf("不正値を検出しました。プログラムを終了します");
    return -1;
  }
}
