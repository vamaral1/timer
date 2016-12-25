// Kevin Rowland, Victor Jose Amaral, Sarah Azody

#include <iostream>
#include "mywindow.h"
#include "optionsbox.h"
#include "timer.h"
#include <gtkmm/printcontext.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <pangomm/layout.h>


Timer* t;

MyWindow::MyWindow()
:table(11, 1, true),
 frame("Exam Timer"),
 title("Options")
{
    set_title("Team GX -- Victor, Sarah, Kevin");
    set_size_request(100, 100);

    table.attach(frame, 0, 1, 0, 10);

	OptionsBox* options_box = new OptionsBox(title);
    options_box->set_size_request(20, 20);

    table.attach(*options_box, 0, 1, 10, 11);
    
    // add table container to window
    t = new Timer();
    frame.add(*t);
    add(table);

    show_all_children();
}

MyWindow::~MyWindow() {
   
}

void MyWindow::set_time(int hour, int mins, int secs) {
    int a = hour*3600 + mins*60 + secs;
    t->initialize(a);
}

void MyWindow::on_pause_clicked() {
    
    //pop-up dialog box for a resume buttom
    Gtk::Dialog* dialog = new Gtk::Dialog();
    dialog->set_size_request(100, 20);
    Gtk::Box* box = dialog->get_content_area();

    //create a resume button inside the pop-up window
    Gtk::Button* resume = new Gtk::Button("\t\t\tResume\t\t\t");
    resume->signal_clicked().connect(sigc::bind<Gtk::Dialog*>(sigc::mem_fun(*this, 
        &MyWindow::on_resume_clicked), dialog));
    resume->set_size_request(100,20);
    resume->show();
    box->add(*resume);
    box->set_size_request(100, 20);
    box->show();
    dialog->set_size_request(100, 20);
    dialog->set_title("Paused");
    dialog->show();

    t->stopped();
}

void MyWindow::toggle_up() {
}

void MyWindow::toggle_down() {
}

void MyWindow::on_resume_clicked(Gtk::Dialog* d) {
    d->hide();
    t->started();
}

void MyWindow::on_start() { t->started(); }
void MyWindow::on_stop()  { t->stopped(); }

void MyWindow::color1() { t->color1(); }
void MyWindow::color2() { t->color2(); }
void MyWindow::color3() { t->color3(); }
void MyWindow::color4() { t->color4(); }