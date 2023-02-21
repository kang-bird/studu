
#include "viewer/viewer.h"

int main(int argc, char** argv) {
    auto app = Gtk::Application::create();
    study::GraphPreceptron graph;
    study::MatrixModel matrix;
    study::Controller ctrl(&matrix, &graph);
    study::MainWindow win(&ctrl);
    app->signal_activate().connect([&]() {
        app->add_window(win);
        win.show();
      });
    return app->run(argc, argv);
}
