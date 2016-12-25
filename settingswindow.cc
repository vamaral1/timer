// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#include <iostream>
#include "settingswindow.h"
#include "mywindow.h"

SettingsWindow::SettingsWindow()
:frame("Settings: Backgrounds"),
 rb1("Black"),
 rb2("Pink"),
 rb3("Blue"),
 rb4("Purple")
{
	set_size_request(500, 200);
	set_title("Settings");
	add(frame);
	frame.add(colors_box);

	// group all radio buttons together
	Gtk::RadioButton::Group group = rb1.get_group();
	rb2.set_group(group);
	rb3.set_group(group);
	rb4.set_group(group);
	
	// add radio buttons to vertical box for aesthetics
	Gtk::VBox* vbox = new Gtk::VBox();
	vbox->add(rb1);
	vbox->add(rb2);
	vbox->add(rb3);
	vbox->add(rb4);
	
	// add vertical box and other settings buttons to the window
	colors_box.add(*vbox);
	rb1.set_active();

	// signal handlers
	rb1.signal_clicked().connect(sigc::mem_fun(*this, 
		&SettingsWindow::on_rb1_clicked));
	rb2.signal_clicked().connect(sigc::mem_fun(*this, 
		&SettingsWindow::on_rb2_clicked));
	rb3.signal_clicked().connect(sigc::mem_fun(*this, 
		&SettingsWindow::on_rb3_clicked));
	rb4.signal_clicked().connect(sigc::mem_fun(*this, 
		&SettingsWindow::on_rb4_clicked));
	
	// show the window and it's child widgets
	show_all_children();
}

SettingsWindow::~SettingsWindow() {

}

void SettingsWindow::on_rb1_clicked() {
	if(!rb1.get_active()) {
	}
	else {
		MyWindow* parent = (MyWindow*)this->get_toplevel();
		parent->color1();
	}
}

void SettingsWindow::on_rb2_clicked() {
	if(!rb2.get_active()) {
	}
	else {
		MyWindow* parent = (MyWindow*)this->get_toplevel();
		parent->color2();

	}
}

void SettingsWindow::on_rb3_clicked() {
	if(!rb3.get_active()) {
	}
	else {
		MyWindow* parent = (MyWindow*)this->get_toplevel();
		parent->color3();
	}
}

void SettingsWindow::on_rb4_clicked() {
	if(!rb4.get_active()) {
	}
	else {
		MyWindow* parent = (MyWindow*)this->get_toplevel();
		parent->color4();
	}
}
