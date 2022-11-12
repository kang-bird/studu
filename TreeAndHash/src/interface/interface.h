#ifndef SRC_INTERFACE_INTERFACE_H_
#define SRC_INTERFACE_INTERFACE_H_

#include "../AVL/self_balancing_binary_search_tree.h"
#include "../hash_table/hash_table.h"

namespace study {

class MainWindow {
 public:
  void Show();

 protected:
  void OutputTab();
  void TableCommandRead();
  void ScanInput();
  void ParseComand(const std::string& input_str);

  /* --БЛОК ОРАБОТКИ КОМАНД-- */
  void AddElement(const std::string& input_str);
  void GetElement(const std::string& input_str);
  void ExistElement(const std::string& input_str);
  void DeleteElement(const std::string& input_str);
  void UpdateElement(const std::string& input_str);
  void ShowKeys(const std::string& input_str);
  void RenameKey(const std::string& input_str);
  void FindElement(const std::string& input_str);
  void ShowTTL(const std::string& input_str);
  void ShowAll(const std::string& input_str);
  void UploadData(const std::string& input_str);
  void ExportData(const std::string& input_str);
  void ClearStorage();
  void Research();

  /* --БЛОК ФУНКЦИЙ ДЛЯ ИСЛЕДОВАНИЯ-- */
  int StartTest(DataBaseClass* avl, DataBaseClass* hash_table);
  void Test(int num_repeat, DataBaseClass* tree);
  void CreateTree(int num_gen, DataBaseClass* tree);
  double TestSet(int repeat_num, DataBaseClass* tree);
  double TestGet(int repeat_num, DataBaseClass* tree);
  double TestDel(int repeat_num, DataBaseClass* tree);
  double TestShowAll(int repeat_num, DataBaseClass* tree);
  double TestFind(int repeat_num, DataBaseClass* tree);
  record_t CreateRandomElement();
  int RandomNumber(int min, int max);

  /* --БЛОК ДОПОЛНИТЕЛЬНЫХ ФУНКЦИЙ-- */
  void HelpTable();
  void SetInterfaceTable();
  std::vector<std::string> SplitString(const std::string& input_str);
  std::string Input();
  int ConvertInput(const std::string& input_str);
  bool IsNumber(const std::string& str);
  void UpdateString(std::vector<std::string>* old_token, int j, int k);
  void PrintError(const std::string& str);

 protected:
  DataBaseClass* storage_ = nullptr;
  Color color_text_;
  bool exit_ = false;
  bool refresh_ = true;
  std::string table_str_;
  std::string name_table_str_;

  const std::string kBlack = "Black";  // константа черного цвета
  const std::string kRed = "Red";  // константа красного цвета
  const std::string kGreen = "Green";  // константа зелёного цвета
  const std::string kLightGray = "Light Gray";  // константа светло серого
  const std::string kWhite = "White";  // константа белого
};

}  // namespace study

#endif  // SRC_INTERFACE_INTERFACE_H_
