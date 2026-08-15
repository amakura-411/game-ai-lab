#include <iostream>
#include <string>
#include <vector>
using namespace std;
// 商品の構造体
struct Product {
  string id;     // 商品ID
  string name;   // 商品名
  int price;     // 価格
  int quantity;  // 在庫数
};

void displayTitle(const string& title) {
  cout << "[" << title << "]" << '\n';
}
bool isNonNegative(int num) {
  return num > 0;
}

void showProduct(const Product& product) {
  /**
   * ID: 002
   * 商品名: みかん
   * 価格: 150円
   * 在庫: 5個
   */
  cout << "商品ID:  " << product.id << '\n';
  cout << "商品名:  " << product.name << '\n';
  cout << "商品価格:" << product.price << '\n';
  cout << "在庫数:  " << product.quantity << '\n' << '\n';
}

Product* searchById(const string& id, vector<Product>& products) {
  for (auto& product : products) {
    if (product.id == id) {
      return &product;
    };
  };
  return nullptr;
}

void showProductById(vector<Product>& products) {
  displayTitle("商品の検索");

  string id;
  cout << "探したい商品IDは？" << '\n';
  cin >> id;

  Product* matching;

  matching = searchById(id, products);
  if (matching == nullptr) {
    cout << "条件に合致する商品がありませんでした" << '\n';
  } else {
    cout << "1件見つかりました\n\n" << '\n';
    showProduct(*matching);
  }
}

// const 参照
void showAll(const vector<Product>& products) {
  displayTitle("商品一覧");

  for (const auto& product : products) {
    showProduct(product);
  };
}

//
void arrival(vector<Product>& products) {
  displayTitle("商品の入荷");

  string id;
  cout << "入荷する商品IDは？" << '\n';
  cin >> id;

  Product* matching;

  matching = searchById(id, products);
  if (matching == nullptr) {
    Product newProduct;
    newProduct.id = id;
    cout << "入荷する商品名は？" << '\n';
    cin >> newProduct.name;
    int price = -1;
    while (true) {
      cout << "入荷する商品の価格は？" << '\n';
      cin >> price;
      cout << price << '\n';
      if (isNonNegative(price)) {
        break;
      }
      cout << "0より大きい数値を設定してください" << '\n';
    }
    newProduct.price = price;
    int qua = -1;
    while (true) {
      cout << "入荷する商品の在庫数は？" << '\n';
      cin >> qua;
      if (isNonNegative(qua)) {
        break;
      }
      cout << "0より大きい数値を設定してください" << '\n';
    }
    newProduct.quantity = qua;
    products.push_back(newProduct);
  } else {
    int qua = -1;
    while (true) {
      cout << "入荷する商品の在庫数は？" << '\n';
      cin >> qua;
      if (isNonNegative(qua)) {
        break;
      }
      cout << "0より大きい数値を設定してください" << '\n';
    }
    matching->quantity = matching->quantity + qua;
  }
  showAll(products);
}

void sell(vector<Product>& products) {
  displayTitle("商品の購入");

  string id;
  cout << "購入する商品IDは？" << '\n';
  cin >> id;

  Product* matching;

  matching = searchById(id, products);
  if (matching == nullptr) {
    cout << "条件に合致する商品がありませんでした" << '\n';
  } else {
    int qua = -1;
    while (true) {
      cout << "購入数は？" << '\n';
      cin >> qua;
      if (!isNonNegative(qua)) {
        cout << "0より大きい数値を設定してください" << '\n';
        continue;
      }
      if (matching->quantity >= qua) {
        break;
      }
      cout << "在庫数よりも多く設定されました。（現在の在庫数: " << matching->quantity << "）"
           << '\n';
    }
    matching->quantity = matching->quantity - qua;
  }
  showAll(products);
}

void displayAmount(const vector<Product>& products) {
  displayTitle("在庫金額");

  int amount = 0;
  for (const auto& product : products) {
    amount = amount + (product.price * product.quantity);
  };
  cout << "合計金額:" << amount << '\n';
}

//

int main() {
  vector<Product> products = {
      {"id1", "nameA", 1000, 10},
      {"id2", "nameB", 1500, 5},
      {"id3", "nameC", 800, 13},
      {"id4", "nameD", 300, 20},
  };

  while (true) {
    cout << "何をしますか？（数字で選択してください）" << '\n';
    // CLIのメニュー表示

    vector<string> actions = {
        "商品一覧を表示する", "商品IDから商品を検索する",   "商品を入荷する",
        "商品を販売する",     "全商品の在庫金額を表示する", "プログラムを終了する"};

    int index = 1;
    for (const auto& action : actions) {
      cout << index << ". " << action << '\n';
      index++;
    }

    int option = 0;
    cin >> option;
    switch (option) {
      case 1:
        showAll(products);
        break;
      case 2:
        showProductById(products);
        break;
      case 3:
        arrival(products);
        break;
      case 4:
        sell(products);
        break;
      case 5:
        displayAmount(products);
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
