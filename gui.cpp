// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#include "mywindow.h"


int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

   MyWindow window;
   
  return app->run(window);
}
