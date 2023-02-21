#include "viewer.h"

namespace study {

MainWindow::MainWindow() :
box_(Gtk::Orientation::HORIZONTAL, 3),
draw_box_(Gtk::Orientation::VERTICAL, 8),
buttons_box_(Gtk::Orientation::HORIZONTAL, 2),
learn_box_(Gtk::Orientation::VERTICAL, 8),
test_box_(Gtk::Orientation::VERTICAL, 8),
box_test_result_(Gtk::Orientation::VERTICAL, 5) {
    set_title("MLP");
    set_resizable(false);
    box_.set_margin(16);
    set_child(box_);
    // Разделение окна на три части
    box_.append(draw_box_);
    box_.append(test_box_);
    box_.append(learn_box_);
    draw_box_.set_margin(3);
    learn_box_.set_margin(3);
    test_box_.set_margin(3);

    // Добавление виджетов в box обучения
    AddButtonChooseFile();
    AddNameFileLearn();
    CreateButtonMethods();
    CreateNumberEpoch();
    CreateNumberLayers();
    AddLearnButton();
    AddTextError();
    CreateButtonReport();
    CreateButtonCrossValid();
    AddTextCrossValid();

    // Добавление виджетов в box тестировния
    AddNameFileTest();
    CreateButtonParametr();
    AddButtonTest();
    CreateLabelsResult();
    AddPredictArea();
    CreateButtonWeight();

    // Добавление виджетов в box рисования
    AddDrawArea();
    AddButtons();
}

MainWindow::MainWindow(Controller* c) : MainWindow() {
    ctrl_ = c;
}

// MARK: /* --БЛОК РАЗМЕЩЕНИЕ ОБЪЕКТОВ-- */

// Добавление области рисования
void MainWindow::AddDrawArea() {
    draw_box_.append(frame_scribble_);
    frame_scribble_.set_expand(true);
    drag_ = Gtk::GestureDrag::create();
    drag_->set_button(GDK_BUTTON_PRIMARY);
    drawing_area_scribble_.add_controller(drag_);

    /* set a minimum size */
    drawing_area_scribble_.set_content_width(400);
    drawing_area_scribble_.set_content_height(400);
    frame_scribble_.set_child(drawing_area_scribble_);

    drawing_area_scribble_.set_draw_func(
        sigc::mem_fun(*this, &MainWindow::on_drawingarea_scribble_draw));

    /* Connect signal handlers */
    drawing_area_scribble_.signal_resize().connect(
        sigc::mem_fun(*this, &MainWindow::on_drawingarea_scribble_resize));

    drag_->signal_drag_begin().connect(
        sigc::mem_fun(*this, &MainWindow::on_drawingarea_scribble_drag_begin));
    drag_->signal_drag_update().connect(
        sigc::mem_fun(*this, &MainWindow::on_drawingarea_scribble_drag_update));
    drag_->signal_drag_end().connect(
        sigc::mem_fun(*this, &MainWindow::on_drawingarea_scribble_drag_end));
}

// Добавление кнопок под область рисования
void MainWindow::AddButtons() {
    buttons_box_.append(button_clear_image_);
    button_clear_image_.set_label("Clear");
    button_clear_image_.set_expand(true);
    buttons_box_.append(button_image_);
    button_image_.set_label("Predict");
    button_image_.set_expand(true);
    draw_box_.append(buttons_box_);
    load_image_.set_label("Load Image");
    load_image_.set_expand(true);
    draw_box_.append(load_image_);
    button_image_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickCreateImage));
    button_clear_image_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickClearImage));
    load_image_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickChooseImage));
}
// Добавление кнопки выбора метода
void MainWindow::CreateButtonMethods() {
    Gtk::Box box1_(Gtk::Orientation::HORIZONTAL, 2);
    Gtk::Label label;
    label.set_text("Method: ");
    box1_.append(label);

    Glib::RefPtr<Gtk::ListStore> refTreeModel;
    refTreeModel = Gtk::ListStore::create(methods_);
    combo_methods_.set_model(refTreeModel);
    Gtk::TreeModel::Row row = *(refTreeModel->append());
    row[methods_.row_name_] = "Matrix";
    combo_methods_.set_active(0);
    row = *(refTreeModel->append());
    row[methods_.row_name_] = "Graph";
    combo_methods_.pack_start(methods_.row_name_);
    combo_methods_.set_hexpand(true);
    box1_.append(combo_methods_);
    learn_box_.append(box1_);
    current_methods_ = "Matrix";
    combo_methods_.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::ClickChooseMethod));
}
// Добавление кнопки выбора кол-ва эпох
void MainWindow::CreateNumberEpoch() {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    Gtk::Label label;
    label.set_text("Number of epochs: ");
    label.set_xalign(0.07);
    label.set_hexpand(true);
    box.append(label);
    auto adjustment = Gtk::Adjustment::create(1.0, 1.0, 10.0, 1.0, 2.0, 0.0);
    num_ephoch_.configure(adjustment, 1.0, 0);
    num_ephoch_.set_hexpand(true);
    box.append(num_ephoch_);
    learn_box_.append(box);
}
// Добавление кнопки выбора кол-ва скрытых слоев
void MainWindow::CreateNumberLayers() {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    Gtk::Label label;
    label.set_text("Number of hidden layers: ");
    label.set_xalign(0.07);
    label.set_hexpand(true);
    box.append(label);

    auto adjustment = Gtk::Adjustment::create(2.0, 2.0, 5.0, 1.0, 1.0, 0.0);
    num_layers_.configure(adjustment, 1.0, 0);
    num_layers_.set_hexpand(true);
    box.append(num_layers_);
    learn_box_.append(box);
    num_layers_.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::ClickChooseLayer));
}
// Добавление кнопки выбора числа к-групп для кросс-валидации
void MainWindow::CreateButtonCrossValid() {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    Gtk::Label label;
    label.set_text("Number k-group: ");
    label.set_xalign(0.07);
    label.set_hexpand(true);
    box.append(label);

    auto adjustment = Gtk::Adjustment::create(2.0, 2.0, 10.0, 1.0, 2.0, 0.0);
    num_group_.configure(adjustment, 1.0, 0);
    num_group_.set_hexpand(true);
    box.append(num_group_);
    learn_box_.append(box);
    learn_cross_group_.set_label("Learn cross valid");
    learn_cross_group_.set_hexpand(true);
    learn_box_.append(learn_cross_group_);
    learn_cross_group_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickLearnCrossValid));
}

// Добавление кнопки выбора значение параметра для тестирования
void MainWindow::CreateButtonParametr() {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    Gtk::Label label;
    label.set_text("Parametr for test: ");
    label.set_xalign(0.07);
    label.set_hexpand(true);
    box.append(label);
    auto adjustment = Gtk::Adjustment::create(1.0, 0.1, 1.0, 0.1, 0.1, 0.0);
    parametr_test_.configure(adjustment, 1, 1);
    parametr_test_.set_hexpand(true);
    box.append(parametr_test_);
    test_box_.append(box);
}
// Добавление кнопки сохранение и загрузка весов
void MainWindow::CreateButtonWeight() {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    save_weights_.set_label("Save weights");
    save_weights_.set_hexpand(true);
    box.append(save_weights_);
    save_weights_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::SaveWeights));
    read_weights_.set_label("Read weights");
    read_weights_.set_hexpand(true);
    box.append(read_weights_);
    read_weights_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::OpenFileWeights));
    test_box_.append(box);
}
// Добавление результатов тестирования
void MainWindow::CreateLabelsResult() {
    result_test_.set_label("Test results\n");
    result_test_.set_label_align(0.5);
    test_box_.append(result_test_);
    result_test_.set_child(box_test_result_);
    AddResults("Average accuracy: \n", &label_accuracy_);
    AddResults("Precision: \n", &label_precision_);
    AddResults("Recall: \n", &label_recall_);
    AddResults("F-measure: \n", &label_measure_);
    AddResults("Total time spent: \n", &label_time_);
}
// Добавление текста
void MainWindow::AddResults(const std::string& str, Gtk::Label* label) {
    Gtk::Box box(Gtk::Orientation::HORIZONTAL, 2);
    box_test_result_.append(box);
    Gtk::Label label_text;
    std::string markup;
    markup = g_markup_printf_escaped("<span size='110%%'>%s</span>", str.c_str());
    label_text.set_markup(markup);
    label_text.set_xalign(0.01);
    label_text.set_hexpand(true);
    label->set_hexpand(true);
    box.append(label_text);
    label->set_xalign(0.95);
    box.append(*label);
}
// Добавление виджета для контрольных значений ошибки для каждой эпохи обучения
void MainWindow::AddTextError() {
    Gtk::ScrolledWindow scrolled_window;
    Gtk::Frame frame_error;
    frame_error.set_label("Errors for each epoch, %");
    frame_error.set_child(scrolled_window);
    frame_error.set_label_align(0.5);
    text_view_.set_editable(false);
    text_view_.set_pixels_above_lines(15);
    error_ephoch_ = Gtk::TextBuffer::create();
    error_ephoch_->set_text("");
    text_view_.set_buffer(error_ephoch_);
    scrolled_window.set_child(text_view_);
    learn_box_.append(frame_error);
}

// Добавление виджета для значений ошибки для кросс обучения
void MainWindow::AddTextCrossValid() {
    Gtk::ScrolledWindow scrolled_window;
    Gtk::Frame frame;
    frame.set_label("Result cross valid");
    frame.set_child(scrolled_window);
    frame.set_label_align(0.5);
    text_cross_valid_.set_editable(false);
    text_cross_valid_.set_pixels_above_lines(15);
    res_cross_valid_ = Gtk::TextBuffer::create();
    res_cross_valid_->set_text("");
    text_cross_valid_.set_buffer(res_cross_valid_);
    scrolled_window.set_child(text_cross_valid_);
    learn_box_.append(frame);
}

// Добавление области вывода результата
void MainWindow::AddPredictArea() {
    letter_.set_label("Possible character");
    letter_.set_label_align(0.5);
    letter_.set_expand(true);
    test_box_.append(letter_);
}

// Добавление имени файла для обучения
void MainWindow::AddNameFileLearn() {
    learn_file_.set_hexpand(true);
    learn_box_.append(learn_file_);
}
// Добавление имени файла для тестирования
void MainWindow::AddNameFileTest() {
    test_file_.set_hexpand(true);
    test_box_.append(test_file_);
}

// Добавление кнопки выбора файла для обучения и тестирования
void MainWindow::AddButtonChooseFile() {
    load_learn_file_.set_label("Chose file for learn");
    learn_box_.append(load_learn_file_);
    load_test_file_.set_label("Chose file for test");
    test_box_.append(load_test_file_);
    load_learn_file_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickChooseLearnFile));
    load_test_file_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickChooseTestFile));
}

// Добавление кнопки создания графика
void MainWindow::CreateButtonReport() {
    save_report_.set_label("Error Change Graph ");
    save_report_.set_hexpand(true);
    learn_box_.append(save_report_);
    save_report_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickSaveReport));
}
// Добавление кнопок обучения с прежними весами и с новыми
void MainWindow::AddLearnButton() {
    learn_new_.set_label("Learn new weights");
    learn_.set_label("Learn");
    learn_.set_hexpand(true);
    Gtk::Box learn_box(Gtk::Orientation::HORIZONTAL, 2);
    learn_box.append(learn_);
    learn_box.append(learn_new_);
    learn_box_.append(learn_box);
    learn_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickLearn));
    learn_new_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickLearnNew));
}

// Добавление кнопки тестирования
void MainWindow::AddButtonTest() {
    test_.set_label("Test");
    test_box_.append(test_);
    test_.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::ClickTest));
}

// MARK: /* --БЛОК ОРАБОТКИ СИГНАЛОВ-- */

// Сохранение картинки
void MainWindow::ClickCreateImage() {
    std::shared_ptr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create(surface_, 0, 0, 400, 400);
    pixbuf = pixbuf->rotate_simple(Gdk::Pixbuf::Rotation::COUNTERCLOCKWISE);
    pixbuf = pixbuf->flip(false);
    pixbuf = pixbuf->scale_simple(28, 28, Gdk::InterpType::HYPER);
    size_t x = 0;
    income_t income;
    auto p = pixbuf->get_pixels();
    while (x < income.size() && x <  pixbuf->get_width() * pixbuf->get_height()) {
        unsigned char temp = ~((*(p + x * 4) + *(p + x * 4 + 1) + *(p + x * 4 + 2)) / 3);
        income[x] = (double)temp / 255.0;
        x += 1;
    }
    ChangePredictLetter(ctrl_->Predict(income) + 'A');
}

// Отчстка изображения
void MainWindow::ClickClearImage() {
    scribble_create_surface();
    drawing_area_scribble_.queue_draw();
}
// Выбор BMP-изображения
void MainWindow::ClickChooseImage() {
    selected_image_ = Gtk::FileChooserNative::create("Please choose a file",
                                                        *this, Gtk::FileChooserNative::Action::OPEN);
    selected_image_->set_modal(true);
    selected_image_->signal_response().connect(sigc::mem_fun(*this, &MainWindow::ClickOpenImage));
    selected_image_->show();
}
// Загрузка BMP-изображения
void MainWindow::ClickOpenImage(int response_id) {
    selected_image_->hide();
    if (response_id == Gtk::ResponseType::ACCEPT) {
        // очищаем поле
        ClickClearImage();
        // получаем имя файла
        std::string file_name_;
        file_name_ = selected_image_->get_file()->get_parse_name();
        // создаём буфер на базе файла
        std::shared_ptr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file(file_name_);
        // отображаем в окне
        std::shared_ptr<Cairo::Context> ctx = Cairo::Context::create(surface_);
        Gdk::Cairo::set_source_pixbuf(ctx, pixbuf->scale_simple(400, 400, Gdk::InterpType::HYPER), 0, 0);
        ctx->paint();
        drawing_area_scribble_.queue_draw();
        // предсказываем символ
        ClickCreateImage();
    }
}
// Выбор файла для обучения
void MainWindow::ClickChooseLearnFile() {
    selected_file_learn_ = Gtk::FileChooserNative::create("Please choose a file",
                                                        *this, Gtk::FileChooserNative::Action::OPEN);
    selected_file_learn_->set_modal(true);
    selected_file_learn_->signal_response().connect(sigc::mem_fun(*this, &MainWindow::ClickOpenLearnFile));
    selected_file_learn_->show();
}

// Загрузка файла для обучения
void MainWindow::ClickOpenLearnFile(int response_id) {
    selected_file_learn_->hide();
    if (response_id == Gtk::ResponseType::ACCEPT) {
        file_learn_ = selected_file_learn_->get_file()->get_parse_name();
        std::string name_learn_file = selected_file_learn_->get_file()->get_basename();
        std::string markup;
        markup = g_markup_printf_escaped("<span size='90%%' color='grey'>%s</span>", name_learn_file.c_str());
        learn_file_.set_markup(markup);
    }
}

// Выбор файла для тестирования
void MainWindow::ClickChooseTestFile() {
    selected_file_test_ = Gtk::FileChooserNative::create("Please choose a file",
                                                        *this, Gtk::FileChooserNative::Action::OPEN);
    selected_file_test_->set_modal(true);
    selected_file_test_->signal_response().connect(sigc::mem_fun(*this, &MainWindow::ClickOpenTestFile));
    selected_file_test_->show();
}
// Загрузка файла для тестирования
void MainWindow::ClickOpenTestFile(int response_id) {
    selected_file_test_->hide();
    if (response_id == Gtk::ResponseType::ACCEPT) {
        file_test_ = selected_file_test_->get_file()->get_parse_name();
        std::string name_test_file = selected_file_test_->get_file()->get_basename();
        std::string markup;
        markup = g_markup_printf_escaped("<span size='90%%' color='grey'>%s</span>", name_test_file.c_str());
        test_file_.set_markup(markup);
    }
}
// Обучение
void MainWindow::ClickLearn() {
    if (file_learn_.size()) {
        SetParamsLearnError();
    }
}

void MainWindow::ClickLearnNew() {
    if (file_learn_.size()) {
        ctrl_->UpdateWigthts();
        SetParamsLearnError();
    }
}

void MainWindow::SetParamsLearnError() {
    Parametrs parametr;
    error_ephoch_vec_.clear();
    std::string result = "";
    for (int i = 0; i < num_ephoch_.get_value(); i++) {
        ctrl_->LearnFromFile(file_learn_);
        if (file_test_.size()) {
            ctrl_->TestFromFile(file_test_);
            parametr = ctrl_->GetParametrs();
            double res_num = parametr.error * 100.0 / (parametr.error + parametr.correct);
            error_ephoch_vec_.push_back(res_num);
            result += std::to_string(res_num).substr(0, std::to_string(res_num).find(".") + 3) + "% ";
            error_ephoch_->set_text(result);
        }
    }
}

// Тестирование файла
void MainWindow::ClickTest() {
    if (file_test_.size()) {
        Parametrs parametr;
        FilePrepTest(file_test_, parametr_test_.get_value());
        auto begin = clock();
        ctrl_->TestFromFile(kNameTest);
        auto end = clock();
        double time = static_cast<double>(end - begin) / CLOCKS_PER_SEC;
        label_time_.set_label(std::to_string(time));
        parametr = ctrl_->GetParametrs();
        double accuracy = 1 - parametr.average_accuracy;
        label_accuracy_.set_label(std::to_string(accuracy));
        double precision = parametr.correct * 100.0 /(parametr.error + parametr.correct);
        label_precision_.set_label(std::to_string(precision));
        double recall = precision;
        label_recall_.set_label(std::to_string(recall));
        double measure = 0.0;
        if ((precision + recall) != 0.0) {
            measure = 2.0 * (precision * recall) / (precision + recall);
        }
        label_measure_.set_label(std::to_string(measure));
        system(("rm " + static_cast<std::string>(kNameTest)).c_str());
    }
}

// Обучения с применением кросс-валидации
void MainWindow::ClickLearnCrossValid() {
    if (file_learn_.size()) {
        res_cross_valid_->set_text(ctrl_->CrossValid(file_learn_, num_group_.get_value()));
    }
}
// Сохранение весов
void MainWindow::SaveWeights() {
    system("mkdir -p setting");
    std::string path = std::filesystem::current_path();
    std::string file = path + "/setting/weight.csv";
    ctrl_->SaveWeights(file);
}
// Открытие окна для выбора файла с весами
void MainWindow::OpenFileWeights() {
    selected_file_weight_ = Gtk::FileChooserNative::create("Please choose a file",
                                                        *this, Gtk::FileChooserNative::Action::OPEN);
    selected_file_weight_->set_modal(true);
    selected_file_weight_->signal_response().connect(sigc::mem_fun(*this, &MainWindow::ReadWeights));
    selected_file_weight_->show();
}

// Чтение весов
void MainWindow::ReadWeights(int response_id) {
    selected_file_weight_->hide();
    if (response_id == Gtk::ResponseType::ACCEPT) {
        std::string file_name = selected_file_weight_->get_file()->get_parse_name();
        ctrl_->LoadWeights(file_name);
    }
}

// Выбор стратегии при смене метода
void MainWindow::ClickChooseMethod() {
    const auto iter = combo_methods_.get_active();
    if (iter) {
       const auto row = *iter;
       if (row) {
           if (row[methods_.row_name_] == "Matrix") {
               ctrl_->SetMatrixStrategy();
           } else {
               ctrl_->SetGraphStrategy();
           }
       }
    }
}

// Рисование графика ошибки
void MainWindow::ClickSaveReport() {
    ClickClearImage();
    std::shared_ptr<Cairo::Context> ctx = Cairo::Context::create(surface_);
    ctx->save();
    ctx->translate(20, 380);
    ctx->scale(3.5, 3.5);
    ctx->set_font_size(3);
    for (int i = 0; i < 10; i++) {
        ctx->move_to(i*10, 3);
        ctx->show_text(std::to_string(i+1));
        ctx->move_to(-5, -i*10-9);
        ctx->show_text(std::to_string((i+1)*10));
    }
    ctx->stroke();
    ctx->restore();

    ctx->translate(20, 380);
    ctx->scale(3.5, -3.5);
    ctx->save();
    ctx->set_source_rgb(0, 0, 0);
    ctx->set_line_width(0.5);
    ctx->move_to(0, 0);
    ctx->line_to(0, 400);
    ctx->move_to(0, 0);
    ctx->line_to(400, 0);
    ctx->stroke();
    ctx->set_line_width(0.3);
    ctx->set_source_rgb(1, 0, 0);
    ctx->move_to(0, error_ephoch_vec_[0]);
    for (int i = 1; i < error_ephoch_vec_.size(); i++) {
        ctx->line_to(i*10, error_ephoch_vec_[i]);
    }
    ctx->stroke();
    ctx->restore();
    drawing_area_scribble_.queue_draw();
}

void MainWindow::ClickChooseLayer() {
    ctrl_->SetHideSize(num_layers_.get_value());
}

// MARK: /* --БЛОК ВСПОМОГАТЕЛЬНЫХ ФУНКЦИЙ-- */

// Изменение буквы в окне
void MainWindow::ChangePredictLetter(char symbol) {
    std::string markup;
    Gtk::Label letter;
    char letter_predict = symbol;
    letter.set_xalign(0.5);
    markup = g_markup_printf_escaped("<span size='500%%' color='red'><b>%c</b></span>", letter_predict);
    letter.set_markup(markup);
    letter_.set_child(letter);
}

// MARK: /* --БЛОК ОРАБОТКИ СИГНАЛОВ ДЛЯ ОБЛАСТИ РИСОВАНИЯ-- */

void MainWindow::on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr,
  int, int) {
  cr->set_source(surface_, 0, 0);
  cr->paint();
}

// Create a new surface of the appropriate size to store our scribbles.
void MainWindow::scribble_create_surface() {
  surface_ = Cairo::ImageSurface::create(Cairo::Surface::Format::ARGB32,
    drawing_area_scribble_.get_width(), drawing_area_scribble_.get_height());
  auto cr = Cairo::Context::create(surface_);
  cr->set_source_rgb(1, 1, 1);
  cr->paint();
}

void MainWindow::on_drawingarea_scribble_resize(int /* width */, int /* height */) {
  scribble_create_surface();
}

void MainWindow::on_drawingarea_scribble_drag_begin(double start_x, double start_y) {
  start_x_ = start_x;
  start_y_ = start_y;
  scribble_draw_brush(start_x_, start_y_);
}

void MainWindow::on_drawingarea_scribble_drag_update(double offset_x, double offset_y) {
  scribble_draw_brush(start_x_ + offset_x, start_y_ + offset_y);
}

void MainWindow::on_drawingarea_scribble_drag_end(double offset_x, double offset_y) {
  scribble_draw_brush(start_x_ + offset_x, start_y_ + offset_y);
}

// Draw a rectangle on the screen.
void MainWindow::scribble_draw_brush(double x, double y) {
  if (!surface_ ||
       surface_->get_width() != drawing_area_scribble_.get_width() ||
       surface_->get_height() != drawing_area_scribble_.get_height())
    scribble_create_surface();
  const Gdk::Rectangle update_rect((int)x - 15, (int)y - 15, 30, 30);
  auto cr = Cairo::Context::create(surface_);
  Gdk::Cairo::add_rectangle_to_path(cr, update_rect);
  cr->fill();
  drawing_area_scribble_.queue_draw();
}

}  // namespace study

