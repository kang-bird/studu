#include "interface.h"

namespace study {

void MainWindow::SetInterfaceTable() {
  name_table_str_ =
      "                                              TRANSACTIONS              "
      "                                 ";

  table_str_ =
      "╔═══════════════════════════════════════════════════════════════════════"
      "════════════════════════════════╗|"
      "║                                     Please choose type of container   "
      "                                ║|"
      "║  1. Hash table                                                        "
      "                                ║|"
      "║  2. Binary search trees                                               "
      "                                ║|"
      "║  3. Exit                                                              "
      "                                ║|"
      "║  4. Research                                                          "
      "                                ║|"
      "╚═══════════════════════════════════════════════════════════════════════"
      "════════════════════════════════╝|";
}

void MainWindow::HelpTable() {
  table_str_ =
      "╔═══════════════════════════════════════════════════════════════════════"
      "════════════════════════════════╗|"
      "║                                                 HELP                  "
      "                                ║|"
      "║  SET <key> <surname> <name> <year> <city> <coins> EX <life time>      "
      "                   Add element  ║|"
      "║  GET <key>                                                     Get "
      "the value associated with the key  ║|"
      "║  EXISTS <key>                                                         "
      "         Check if object exist  ║|"
      "║  DEL <key>                                                            "
      "             Delete the record  ║|"
      "║  UPDATE <key> <surname> <name> <year> <city> <coins> *                "
      "          Update elements data  ║|"
      "║  KEYS                                                                 "
      "              Get all the keys  ║|"
      "║  RENAME <old key> <new key>                                           "
      "                    Rename key  ║|"
      "║  TTL <key>                                                            "
      "       Show elements life time  ║|"
      "║  FIND <surname> <name> <year> <city> <coins> *                        "
      "                  Find element  ║|"
      "║  SHOWALL                                                              "
      "               Get all records  ║|"
      "║  UPLOAD <file path>                                                   "
      "       Upload data from a file  ║|"
      "║  EXPORT <file path>                                                   "
      "         Save the data to file  ║|"
      "║  CLEAR                                                                "
      "                 Clear storage  ║|"
      "║  STORAGE                                                              "
      "                Change storage  ║|"
      "║  HELP                                                                 "
      "                      Get help  ║|"
      "║  EXIT                                                                 "
      "     Enter to exit the program  ║|"
      "║                                                                       "
      "                                ║|"
      "║  *𝘐𝘧 𝘺𝘰𝘶 𝘸𝘢𝘯𝘵 𝘵𝘰 𝘴𝘬𝘪𝘱 𝘵𝘩𝘦 𝘧𝘪𝘦𝘭𝘥 𝘶𝘴𝘦 𝘢 𝘥𝘢𝘴𝘩 '-'                        "
      "                                ║|"
      "╚═══════════════════════════════════════════════════════════════════════"
      "════════════════════════════════╝|";
}

// Вывод главного окна
void MainWindow::Show() {
  SetInterfaceTable();
  OutputTab();
  ScanInput();
  HelpTable();
  while (exit_ == false) {
    if (refresh_ == true) {
      OutputTab();
      refresh_ = false;
    }
    TableCommandRead();
  }
}

// Вывод таблицы в терминале
void MainWindow::OutputTab() {
  std::cout.flush();
  std::cin.clear();
  system("clear");
  std::string delimiter = "|";
  std::cout << color_text_.Rize(name_table_str_, kRed, kWhite, "Bold")
            << std::endl;
  size_t last = kZero;
  size_t next;
  while ((next = table_str_.find(delimiter, last)) != std::string::npos) {
    std::cout << color_text_.Rize(table_str_.substr(last, next - last),
                                  "Light Red", kWhite)
              << std::endl;
    last = next + 1;
  }
}

//  Выбор действия
void MainWindow::ScanInput() {
  int num_input = ConvertInput(Input());
  static AVL avl;
  static HashTable hash_table;
  switch (num_input) {
    case 1:
      storage_ = &hash_table;
      std::cout << color_text_.Rize("Hash table storage was set", kBlack,
                                    kGreen)
                << std::endl;
      break;
    case 2:
      storage_ = &avl;
      std::cout << color_text_.Rize("AVL storage was set", kBlack, kGreen)
                << std::endl;
      break;
    case 3:
      exit_ = true;
      std::cout << color_text_.Rize("          Programm Exit          ",
                                    "Light Red", kWhite)
                << std::endl;
      break;
    case 4:
      exit_ = true;
      std::cout << color_text_.Rize("          Start Research         ",
                                    "Light Red", kWhite)
                << std::endl;
      Research();
      break;
    default:
      PrintError("Error, incorrect choose. Try again.");
      ScanInput();
      break;
  }
}

// Чтение команды
void MainWindow::TableCommandRead() {
  std::string input_line = Input();
  if (input_line == "EXIT" || input_line == "exit") {
    exit_ = true;
  } else if (input_line == "HELP" || input_line == "help") {
    refresh_ = true;
  } else {
    ParseComand(input_line);
  }
}

// Парсинг команды
void MainWindow::ParseComand(const std::string& input_str) {
  std::string command = input_str.substr(0, input_str.find(" "));
  std::transform(command.begin(), command.end(), command.begin(), ::toupper);
  if (command == "SET") {
    AddElement(input_str);
  } else if (command == "GET") {
    GetElement(input_str);
  } else if (command == "EXISTS") {
    ExistElement(input_str);
  } else if (command == "DEL") {
    DeleteElement(input_str);
  } else if (command == "UPDATE") {
    UpdateElement(input_str);
  } else if (command == "KEYS") {
    ShowKeys(input_str);
  } else if (command == "RENAME") {
    RenameKey(input_str);
  } else if (command == "TTL") {
    ShowTTL(input_str);
  } else if (command == "FIND") {
    FindElement(input_str);
  } else if (command == "SHOWALL") {
    ShowAll(input_str);
  } else if (command == "UPLOAD") {
    UploadData(input_str);
  } else if (command == "EXPORT") {
    ExportData(input_str);
  } else if (command == "STORAGE") {
    Show();
  } else if (command == "CLEAR") {
    ClearStorage();
  } else {
    PrintError("ERROR: invalid command");
  }
}

// MARK: --БЛОК ОРАБОТКИ КОМАНД--

// Добавление элемента
void MainWindow::AddElement(const std::string& input_str) {
  bool correct = true;
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() == 7 || tokens.size() == 9) {
    if (tokens.size() == 9 && tokens[7] != "EX") {
      PrintError("ERROR: add 'EX' before <life time> parametr");
      correct = false;
    } else {
      if (tokens.size() == 9 && !NumCheck(tokens[8])) {
        correct = false;
      } else if (NumCheck(tokens[4]) && NumCheck(tokens[6])) {
        student_t student = {tokens[3], tokens[2], ConvertInput(tokens[4]),
                             tokens[5], ConvertInput(tokens[6])};
        int time_life = -1;
        if (tokens.size() == 9) time_life = ConvertInput(tokens[8]);
        value_t record_value = {student, std::time(nullptr), time_life};
        record_t element = {tokens[1], record_value};
        try {
          if (storage_->Set(element)) {
            std::cout << color_text_.Rize(" OK ", kBlack, kGreen) << std::endl;
          } else {
            PrintError("ERROR: such a key already exists");
          }
        } catch (...) {
          PrintError("Set failed");
        }
      } else {
        correct = false;
      }
    }
  } else {
    PrintError("ERROR: incorrect number of parameters");
    correct = false;
  }
  if (correct == false) {
    PrintStringResult(
        "usage: SET <key> <surname> <name> <year> <city> <coins> EX <life "
        "time>");
  }
}

// Получение элемента
void MainWindow::GetElement(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: GET <key>");
  } else {
    storage_->Get(tokens[1]);
  }
}

// Проверка существования элемента
void MainWindow::ExistElement(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: EXISTS <key>");
  } else {
    std::string result = (storage_->Exist(tokens[1])) ? "true" : "false";
    PrintStringResult(result);
  }
}

// Удаление элемента
void MainWindow::DeleteElement(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: DEL <key>");
  } else {
    std::string result = (storage_->Del(tokens[1])) ? "true" : "false";
    PrintStringResult(result);
  }
}

// Обновление элемента
void MainWindow::UpdateElement(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 7) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult(
        "usage: UPDATE <key> <surname> <name> <year> <city> <coins>");
  } else {
    if (((tokens[4] == "-") || NumCheck(tokens[4])) &&
        ((tokens[6] == "-") || NumCheck(tokens[6]))) {
      UpdateString(&tokens, 4, 6);
      student_t student = {tokens[3], tokens[2], ConvertInput(tokens[4]),
                           tokens[5], ConvertInput(tokens[6])};
      value_t record_value = {student, -1, -1};
      record_t element = {tokens[1], record_value};
      if (storage_->Update(element)) {
        std::cout << color_text_.Rize(" OK ", kBlack, kGreen) << std::endl;
      } else {
        PrintError("ERROR: such a key doesn't exists");
      }
    } else {
      PrintStringResult(
          "usage: UPDATE <key> <surname> <name> <year> <city> <coins>");
    }
  }
}

// Вывод всех ключей
void MainWindow::ShowKeys(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 1) {
    PrintError("ERROR: сommand must be without parameters");
    PrintStringResult("usage: KEYS");
  } else {
    storage_->Keys();
  }
}

// Переименование ключа
void MainWindow::RenameKey(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 3) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: RENAME <old key> <new key>");
  } else {
    std::string result =
        (storage_->Rename(tokens[1], tokens[2])) ? "OK" : "Error";
    PrintStringResult(result);
  }
}

// Поиск элемента по маске
void MainWindow::FindElement(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 6) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult(
        "usage: UPDATE <key> <surname> <name> <year> <city> <coins>");
  } else {
    if (((tokens[3] == "-") || NumCheck(tokens[3])) &&
        ((tokens[5] == "-") || NumCheck(tokens[5]))) {
      UpdateString(&tokens, 3, 5);
      student_t student = {tokens[2], tokens[1], ConvertInput(tokens[3]),
                           tokens[4], ConvertInput(tokens[5])};
      storage_->Find(student);
    } else {
      PrintStringResult(
          "usage: UPDATE <key> <surname> <name> <year> <city> <coins>");
    }
  }
}

// Просмотра оставшегося времени жизни элемента
void MainWindow::ShowTTL(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: TTL <key>");
  } else {
    int result = storage_->TTL(tokens[1]);
    PrintStringResult((result > -1) ? std::to_string(result) : "(null)");
  }
}

// Получение всех записей
void MainWindow::ShowAll(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 1) {
    PrintError("ERROR: сommand must be without parameters");
    PrintStringResult("usage: SHOWALL");
  } else {
    PrintStringResult(
        "№ | Last name |   First name   | Year |  City   | Number of coins |");
    storage_->ShowAll();
  }
}

// Загрузка файла
void MainWindow::UploadData(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: UPLOAD <file path>");
  } else {
    try {
      size_t cout = storage_->Upload(tokens[1]);
      std::cout << color_text_.Rize("OK " + std::to_string(cout), kBlack,
                                    kGreen)
                << std::endl;
    } catch (...) {
      PrintError("ERROR: bad file");
    }
  }
}

// Выгрузка базы
void MainWindow::ExportData(const std::string& input_str) {
  std::vector<std::string> tokens = SplitString(input_str);
  if (tokens.size() != 2) {
    PrintError("ERROR: incorrect number of parameters");
    PrintStringResult("usage: UPLOAD <file path>");
  } else {
    size_t num_str = storage_->Export(tokens[1]);
    std::cout << color_text_.Rize("OK " + std::to_string(num_str), kBlack,
                                  kGreen)
              << std::endl;
  }
}

// Отчистка базы
void MainWindow::ClearStorage() {
  storage_->Clear();
  std::cout << color_text_.Rize("Storage was cleared", kBlack, kGreen)
            << std::endl;
}

// MARK: БЛОК ФУНКЦИЙ ДЛЯ ИСЛЕДОВАНИЯ

void MainWindow::Research() {
  AVL avl;
  HashTable hash_table;
  int num_repeat = StartTest(&avl, &hash_table);
  if (num_repeat != -1) {
    std::cout << color_text_.Rize("          Start Hash-table test          ",
                                  kBlack, kGreen)
              << std::endl;
    Test(num_repeat, &hash_table);
    std::cout << color_text_.Rize("           Start AVL tree test           ",
                                  kBlack, kGreen)
              << std::endl;
    Test(num_repeat, &avl);
  }
}

int MainWindow::StartTest(DataBaseClass* avl, DataBaseClass* hash_table) {
  int result = -1;
  std::cout << "Enter the number of items to generate: " << std::endl;
  std::string input_line = Input();
  std::vector<std::string> tokens = SplitString(input_line);
  int num_gen = 0;
  if (tokens.size() == 1 && (num_gen = ConvertInput(tokens[0])) > 0) {
    std::cout << "Enter the number of repetitions of one action: " << std::endl;
    std::string input_line_repeat = Input();
    tokens = SplitString(input_line_repeat);
    int num_repeat = 0;
    if (tokens.size() == 1 && (num_repeat = ConvertInput(tokens[0])) > 0) {
      CreateTree(num_gen, hash_table);
      CreateTree(num_gen, avl);
      result = num_repeat;
    } else {
      PrintError("ERROR: incorrect input");
    }
  } else {
    PrintError("ERROR: incorrect input");
  }
  return result;
}

// Создание базы рандомных элементов
void MainWindow::CreateTree(int num_gen, DataBaseClass* tree) {
  while (num_gen > 0) {
    record_t element = CreateRandomElement();
    tree->Set(element);
    num_gen--;
  }
}

// Создание одной рандомной записи
record_t MainWindow::CreateRandomElement() {
  const key_t key = std::to_string(RandomNumber(0, 100000));
  const std::string surname = std::to_string(RandomNumber(0, 1000));
  const std::string name = std::to_string(RandomNumber(0, 100));
  const int year = RandomNumber(1900, 2022);
  const std::string city = std::to_string(RandomNumber(0, 100));
  const int coins = RandomNumber(0, 1000);
  student_t student = {name, surname, year, city, coins};
  value_t record_value = {student, std::time(nullptr), -1};
  record_t element = {key, record_value};
  return element;
}

// Тестирование Добавления элемента
double MainWindow::TestSet(int repeat_num, DataBaseClass* tree) {
  double result;
  auto begin = clock();
  CreateTree(repeat_num, tree);
  auto end = clock();
  result = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  return result;
}

// Тестирование Получение элемента
double MainWindow::TestGet(int repeat_num, DataBaseClass* tree) {
  double result;
  auto begin = clock();
  for (int i = kZero; i < repeat_num; i++) {
    const std::string key = std::to_string(RandomNumber(0, 100000));
    tree->Get(key);
  }
  auto end = clock();
  result = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  return result;
}

// Тестирование Удаления элемента
double MainWindow::TestDel(int repeat_num, DataBaseClass* tree) {
  double result;
  auto begin = clock();
  for (int i = kZero; i < repeat_num; i++) {
    const key_t key = std::to_string(RandomNumber(0, 100000));
    tree->Del(key);
  }
  auto end = clock();
  result = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  return result;
}

// Тестирование вывод всей базы
double MainWindow::TestShowAll(int repeat_num, DataBaseClass* tree) {
  double result;
  auto begin = clock();
  for (int i = kZero; i < repeat_num; i++) {
    tree->ShowAll();
  }
  auto end = clock();
  result = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  return result;
}

// Тестирование Поиск элемента
double MainWindow::TestFind(int repeat_num, DataBaseClass* tree) {
  double result;
  auto begin = clock();
  for (int i = kZero; i < repeat_num; i++) {
    tree->Find({"-", "-", -1, "-", -1});
  }
  auto end = clock();
  result = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
  return result;
}

void MainWindow::Test(int num_repeat, DataBaseClass* tree) {
  std::vector<double> vector_time = {0.0, 0.0, 0.0, 0.0, 0.0};
  std::cout.clear(std::ios_base::badbit);
  vector_time[0] = TestSet(num_repeat, tree);
  vector_time[1] = TestGet(num_repeat, tree);
  vector_time[2] = TestDel(num_repeat, tree);
  vector_time[3] = TestShowAll(num_repeat, tree);
  vector_time[4] = TestFind(num_repeat, tree);
  std::cout.clear(std::ios_base::goodbit);

  std::cout << "Average time Set, sec:       " +
                   std::to_string(vector_time[0] / num_repeat)
            << std::endl;
  std::cout << "Average time Get, sec:       " +
                   std::to_string(vector_time[1] / num_repeat)
            << std::endl;
  std::cout << "Average time Delete, sec:    " +
                   std::to_string(vector_time[2] / num_repeat)
            << std::endl;
  std::cout << "Average time Show all, sec:  " +
                   std::to_string(vector_time[3] / num_repeat)
            << std::endl;
  std::cout << "Average time Find, sec:      " +
                   std::to_string(vector_time[4] / num_repeat)
            << std::endl;
}

// Генерация рандомного числа
int MainWindow::RandomNumber(int min, int max) {
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(generator);
}

// MARK: --БЛОК ДОПОЛНИТЕЛЬНЫХ ФУНКЦИЙ--

// Печать ошибки
void MainWindow::PrintError(const std::string& str) {
  std::cout << color_text_.Rize(str, kBlack, kRed) << std::endl;
}

// Разделение строки на токены
std::vector<std::string> MainWindow::SplitString(const std::string& input_str) {
  std::vector<std::string> result;
  std::string token;
  std::istringstream iss(input_str);
  while (std::getline(iss, token, ' ')) result.push_back(token);
  return result;
}

// Ввод данных
std::string MainWindow::Input() {
  std::string input_str;
  if (!std::getline(std::cin, input_str)) {
    exit(0);
  }
  std::cin.clear();
  return input_str;
}

// Проверка на корректный ввод числа
int MainWindow::ConvertInput(const std::string& input_str) {
  int result = 0;
  if ((input_str == "-1") || NumCheck(input_str)) {
    result = std::stoi(input_str);
  }
  return result;
}

// Обработка маски
void MainWindow::UpdateString(std::vector<std::string>* old_token, int j,
                              int k) {
  for (int i = 0; i <= k; i++) {
    if ((*old_token)[i] == "-") {
      if (i == j || i == k) {
        (*old_token)[i] = "-1";
      } else {
        (*old_token)[i] = "";
      }
    }
  }
}

}  // namespace study
