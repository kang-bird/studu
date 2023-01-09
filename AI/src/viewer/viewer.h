#ifndef SRC_VIEWER_VIEWER_H_
#define SRC_VIEWER_VIEWER_H_

#include "../types.h"
#include "../controller/controller.h"
#include <ctime>

namespace study {

class MainWindow : public Gtk::Window {
 public:
    MainWindow();
    explicit MainWindow(Controller* c);
    ~MainWindow() {}

 private:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord {
     public:
          ModelColumns() { add(row_name_); }
          Gtk::TreeModelColumn<Glib::ustring> row_name_;
    };
    Controller* ctrl_;

 private:
    /* -------ДОБАВЛЕНИЕ ОБЪЕКТОВ------- */
    void AddDrawArea();
    void AddButtons();
    void CreateButtonMethods();
    void CreateNumberEpoch();
    void CreateNumberLayers();
    void CreateButtonParametr();
    void CreateButtonWeight();
    void CreateButtonCrossValid();
    void CreateLabelsResult();
    void AddResults(const std::string& str, Gtk::Label* label);
    void AddTextError();
    void AddPredictArea();
    void AddNameFileLearn();
    void AddNameFileTest();
    void AddButtonChooseFile();
    void AddLearnButton();
    void AddTextCrossValid();
    void CreateButtonReport();
    void AddButtonTest();

    /* -------ФУНКЦИЯ РИСОВАНИЯ------- */
    void on_drawingarea_scribble_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

    /* --БЛОК ОРАБОТКИ СИГНАЛОВ ДЛЯ ОБЛАСТИ РИСОВАНИЯ-- */
    void on_drawingarea_scribble_resize(int width, int height);
    void on_drawingarea_scribble_drag_begin(double start_x, double start_y);
    void on_drawingarea_scribble_drag_update(double offset_x, double offset_y);
    void on_drawingarea_scribble_drag_end(double offset_x, double offset_y);
    void scribble_draw_brush(double x, double y);

    /* --БЛОК ОРАБОТКИ СИГНАЛОВ-- */
    void scribble_create_surface();
    void ClickCreateImage();
    void ClickClearImage();
    void ClickChooseImage();
    void ClickChooseLearnFile();
    void ClickChooseTestFile();
    void ClickChooseLayer();
    void ClickOpenImage(int response_id);
    void ClickOpenLearnFile(int response_id);
    void ClickOpenTestFile(int response_id);
    void ClickChooseMethod();
    void ClickTest();
    void ClickLearn();
    void ClickLearnNew();
    void ClickLearnCrossValid();
    void OpenFileWeights();
    void SaveWeights();
    void ReadWeights(int response_id);
    void ClickSaveReport();
    /* --ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ-- */
    void ChangePredictLetter(char symbol);
    void SetParamsLearnError();


 private:
    ModelColumns methods_;
    double start_x_ = 0.0;
    double start_y_ = 0.0;
    std::string file_learn_, file_test_;
    std::vector<double> error_ephoch_vec_ = {0};
    Glib::ustring current_methods_;

    /* -------ВИДЖЕТЫ------- */
    Gtk::Frame frame_scribble_, letter_, result_test_;
    Gtk::Box draw_box_, learn_box_, test_box_, box_, buttons_box_;
    Gtk::Box box_test_result_;
    Gtk::DrawingArea drawing_area_scribble_;
    Glib::RefPtr<Gtk::FileChooserNative> selected_image_, selected_file_weight_;
    Glib::RefPtr<Gtk::FileChooserNative> selected_file_learn_, selected_file_test_;
    Glib::RefPtr<Gtk::GestureDrag> drag_;
    Cairo::RefPtr<Cairo::ImageSurface> surface_;
    Gtk::Button button_image_, button_clear_image_, load_image_;
    Gtk::Button load_learn_file_, load_test_file_;
    Gtk::Button learn_, learn_new_, test_, learn_cross_group_;
    Gtk::Button save_weights_, read_weights_;
    Gtk::Button save_report_;
    Gtk::ComboBox combo_methods_;
    Gtk::Grid grid_buttons_;
    Gtk::SpinButton num_layers_, num_ephoch_, parametr_test_;
    Gtk::SpinButton num_group_;
    Gtk::Label label_accuracy_, label_precision_, label_recall_, label_measure_, label_time_;
    Gtk::Label learn_file_, test_file_;
    Gtk::TextView text_view_, text_cross_valid_;
    Glib::RefPtr<Gtk::TextBuffer> error_ephoch_, res_cross_valid_;
};

}  // namespace study

#endif  // SRC_VIEWER_VIEWER_H_
