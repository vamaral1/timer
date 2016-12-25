// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#ifndef OPTIONS_BOX_H
#define OPTIONS_BOX_H

#include <gtkmm/table.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>

class settingswindow;
class mywindow;

class OptionsBox : public Gtk::Frame {

	Gtk::Table options_box;
  Gtk::Button button_pause;
  Gtk::Button button_settings;
  Gtk::Button button_start;
  Gtk::Button button_reset;
  Gtk::Entry hour_entry;
  Gtk::Entry mins_entry;
  Gtk::Entry secs_entry;

  public:
    OptionsBox(const Glib::ustring&);
    virtual ~OptionsBox();

  protected:
  	void on_pause_clicked();
    void on_settings_clicked();
    void on_start_clicked();
    void on_reset_clicked();
    int  get_hour();
    int  get_mins();
    int  get_secs();

}; 
#endif