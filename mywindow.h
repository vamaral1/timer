// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/table.h>
#include <gtkmm/dialog.h>
#include <gtkmm/spinbutton.h>

class optionsbox;
class timer;

class MyWindow : public Gtk::Window {

    Gtk::Table table;
    Gtk::Frame frame;
    const Glib::ustring title;
      
  public:
    MyWindow();
    virtual ~MyWindow();

    void set_time(int a, int b, int c);
  	void on_pause_clicked();
    void toggle_up();
    void toggle_down();
    void on_resume_clicked(Gtk::Dialog* d);
    void on_start(); void on_stop();
    void color1(); void color2(); void color3(); void color4();

};

#endif
