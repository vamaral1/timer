// Kevin Rowland, Victor Jose Amaral, Sarah Azody
#include <iostream>
#include "optionsbox.h"
#include "mywindow.h"
#include "settingswindow.h"
#include <gtkmm/button.h>
#include <gtkmm/container.h>
#include <gtkmm/box.h>

OptionsBox::OptionsBox(const Glib::ustring& title) // a type of frame
: Gtk::Frame(title),
  options_box(1, 11, false),
  button_pause("Pause"),
  button_settings("Settings"),
  button_start("Start"),
  button_reset("Reset")
 {
    set_size_request(-1, -1);

    // attach signals to our five buttons
    button_pause.signal_clicked().connect(sigc::mem_fun(*this, &OptionsBox::on_pause_clicked));
    button_settings.signal_clicked().connect(sigc::mem_fun(*this, &OptionsBox::on_settings_clicked));
    button_start.signal_clicked().connect(sigc::mem_fun(*this, 
      &OptionsBox::on_start_clicked));
    button_reset.signal_clicked().connect(sigc::mem_fun(*this, &OptionsBox::on_reset_clicked));

    //adjust size of options box and attach buttons
    options_box.set_size_request(500, -1);
    options_box.attach(button_pause, 0, 2, 0, 1, Gtk::EXPAND);
    options_box.attach(button_settings, 2, 4, 0, 1, Gtk::EXPAND);
    options_box.attach(button_start, 4, 6, 0, 1, Gtk::EXPAND);
    options_box.attach(button_reset, 6, 8, 0, 1, Gtk::EXPAND);


    hour_entry.set_max_length(2);
    hour_entry.set_text("hh");
    hour_entry.set_width_chars(2);
    mins_entry.set_max_length(2);
    mins_entry.set_text("mm");
    mins_entry.set_width_chars(2);
    secs_entry.set_max_length(2);
    secs_entry.set_text("ss");
    secs_entry.set_width_chars(2);
    options_box.attach(hour_entry, 8, 9, 0, 1);
    options_box.attach(mins_entry, 9, 10, 0, 1);
    options_box.attach(secs_entry, 10, 11, 0, 1);

    options_box.show_all();
    add(options_box);
 }

 OptionsBox::~OptionsBox() {

 }

 void OptionsBox::on_pause_clicked() {
    MyWindow* parent = (MyWindow*)this->get_toplevel();
    parent->on_pause_clicked();
 }
  
  void OptionsBox::on_settings_clicked() {
    SettingsWindow* set = new SettingsWindow();
    set->show();
 }
  
void OptionsBox::on_start_clicked() {
  MyWindow* parent = (MyWindow*)this->get_toplevel();

  if((this->get_hour() >= 0) && (this->get_mins() >= 0) && (this->get_secs() >= 0)) {
    parent->set_time(this->get_hour(), this->get_mins(), this->get_secs());
    parent->on_start();
  }
}

void OptionsBox::on_reset_clicked() {
  MyWindow* parent = (MyWindow*)this->get_toplevel();
  parent->set_time(0, 0, 0);
  parent->on_stop();

}

int OptionsBox::get_hour() {
  Glib::ustring str = hour_entry.get_text();
  const char* s = str.c_str();
  //convert string to int
  int a = atol(s);
 
  return a;
}

int OptionsBox::get_mins() {
  Glib::ustring str = mins_entry.get_text();
  const char* s = str.c_str();
  //convert string to int
  int b = atol(s);
 
  return b;
}

int OptionsBox::get_secs() {
  Glib::ustring str = secs_entry.get_text();
  const char* s = str.c_str();
  //convert string to int
  int b = atol(s);
 
  return b;
}