// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#ifndef SETTINGS_WINDOW_H
#define SETTINGS_WINDOW_H

#include <gtkmm.h>

class SettingsWindow : public Gtk::Window {
	Gtk::Frame frame;
	Gtk::HBox colors_box;

	Gtk::RadioButton rb1, rb2, rb3, rb4;

	void on_rb1_clicked();
	void on_rb2_clicked();
	void on_rb3_clicked();
	void on_rb4_clicked();

public:
	SettingsWindow();
	~SettingsWindow();

};

#endif