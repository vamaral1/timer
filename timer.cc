//Kevin Rowland, Victor Jose Amaral, Sarah Azody
#include <iostream>
#include <ctime>
#include <cmath>
#include <cairomm/cairomm.h>
#include <glibmm/main.h>
#include <pangomm.h>
#include "timer.h"


Timer::Timer()
{
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &Timer::on_timeout), 1000 );
}

Timer::~Timer()
{
}

void Timer::background(const Cairo::RefPtr<Cairo::Context>& timer, 
  double move_start, double move_end, double line_start, double line_end) {
  timer->set_line_width(line_width);
  timer->set_source_rgba(1.0, 1.0, 1.0, 1.0);//white
  timer->move_to(move_start, move_end);
  timer->line_to(line_start, line_end);
  timer->stroke();
  timer->restore();
  timer->save();

}

void Timer::circle(const Cairo::RefPtr<Cairo::Context>& timer, 
  double center_x, double center_y, double radius, bool toFill) {
    timer->set_source_rgba(0.5, 0.5, 0.5, 0.5);
    timer->set_line_width(line_width/2);
    timer->arc(center_x, center_y, radius, 0, 2 * M_PI);
    if(toFill) {
      timer->fill();
    }
    timer->stroke();
    timer->restore();
    timer->save();
}


void Timer::circle_patterns(const Cairo::RefPtr<Cairo::Context>& timer, 
  double center_x, double center_y, double radius) {
  double start_x = center_x;
  for(int i = 1; i < 10; i++) {
    if((i == 4) || (i == 7)) {
      center_y += 0.05;
      center_x = start_x;
    }
	
  switch (i) {
    default: 
      break;
    case 1: if (d1) { circle(timer, center_x, center_y, radius, true);}
      break;
    case 2: 
      break;
    case 3: if (d3) { circle(timer, center_x, center_y, radius, true);}
      break;
    case 4: if (d4) { circle(timer, center_x, center_y, radius, true);}
      break;
    case 5: if (d5) { circle(timer, center_x, center_y, radius, true);}
      break;
    case 6: if (d6) { circle(timer, center_x, center_y, radius, true);}
      break;
    case 7: if (d7) { circle(timer, center_x, center_y, radius, true);}
     break;
    case 8:
      break;
    case 9: if (d9) { circle(timer, center_x, center_y, radius, true);}
      break;
} 
   circle(timer, center_x, center_y, radius, false);
   center_x += 0.04;
  }

}



void Timer::digital_clock(const Cairo::RefPtr<Cairo::Context>& timer, 
  int time_unit, double move_start, double move_end) {
  char buffer[4];
  if (time_unit < 10) { sprintf(buffer, "%c%d%c", '0', time_unit, ':');}
  else { sprintf(buffer, "%d%c", time_unit, ':');}
    // draw the text
  timer->move_to(move_start, move_end);

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  Cairo::RefPtr<Cairo::ToyFontFace> font =
    Cairo::ToyFontFace::create("Bitstream Charter",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_BOLD);
  timer->set_font_face(font);
  timer->set_font_size(FONT_SIZE);
  timer->show_text(buffer);
  timer->save();
  timer->restore();
}

void Timer::circle_fill_top(int time_unit) 
{
  d1 = d3 = d4 = d5 = d6 = d7 = d9 = false;
  if (time_unit == 2 || time_unit == 3 || time_unit == 6 || time_unit == 7 ||
       time_unit == 10 || time_unit == 11) {
    d5 = true;
   }
   if (time_unit > 3) {
     d1 = true;
     d9 = true;
   }
   if (time_unit > 7) {
     d3 = true;
     d7 = true;
   }
   if (time_unit == 12) {
     d4 = true;
     d6 = true;
   }

}

void Timer::circle_fill_bottom(int time_unit)
{
  d1 = d3 = d4 = d5 = d6 = d7 = d9 = false;
  if (time_unit == 1 || time_unit == 2 || time_unit == 5 || time_unit == 6 ||
        time_unit == 9 || time_unit == 10) {
    d5 = true;
  }
  if (time_unit > 2) {
    d1 = true;
    d9 = true;
  }
  if (time_unit > 6 ) {
    d3 = true;
    d7 = true;
  }
  if (time_unit == 11 || time_unit == 12) {
    d4 = true;
    d6 = true;
  }
}

bool Timer::on_draw(const Cairo::RefPtr<Cairo::Context>& timer)
{  
  //sets color
  if (color == 1) { timer->set_source_rgba(0.00, 0.00, 0.00, 1.000); }
  if (color == 2) { timer->set_source_rgba(255/255, 51/255, 102.0/255, 1.000); }
  if (color == 3) { timer->set_source_rgba(55.0/255, 0.0/255, 255.0/255, 1.000); }
  if (color == 4) { timer->set_source_rgba(153.0/255, 51.0/255, 255.0/255, 1.0); }
  timer->paint();

  timer->arc(TEXT_ORIGIN_X, TEXT_ORIGIN_Y, FONT_SIZE / 3.0, 0, 2*M_PI);
  timer->set_source_rgba(246.00/255, 116.00/255, 116.00/255, 1.000);
  timer->fill();

  // draw the text
  timer->move_to(TEXT_ORIGIN_X, TEXT_ORIGIN_Y);

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  Cairo::RefPtr<Cairo::ToyFontFace> font =
    Cairo::ToyFontFace::create("Bitstream Charter",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_BOLD);
  timer->set_font_face(font);
  timer->set_font_size(FONT_SIZE);
  Glib::ustring s = "Exam Timer 3000!";
  timer->show_text(s);
  timer->save();
  timer->restore();

  if(ticking) {
    time_step--;
  }

  if(time_step == 0 && !reset) {
    char buf[10];
    sprintf(buf, "%s", "Time Up!");
    timer->move_to(150, 435);

    timer->set_source_rgba(1, 0, 0, 1);
    Cairo::RefPtr<Cairo::ToyFontFace> f =
      Cairo::ToyFontFace::create("Bitstream Charter",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_BOLD);
    timer->set_font_face(f);
    timer->set_font_size(FONT_SIZE);
    timer->show_text(buf);
    timer->save();
    timer->restore();
    this->stopped();
    reset = false;
    colon_rgba = 1.0;
  }

  int hour = time_step / 3600;
  int mins = (time_step / 60) % 60;
  int secs = time_step % 60;

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  digital_clock(timer, hour, 150, 390);
  digital_clock(timer, mins, 220, 390);
  
  char buffer2[3];
  if (secs < 10) { sprintf(buffer2, "%c%d", '0', secs);}
  else { sprintf(buffer2, "%d", secs);}
    // draw the text
  timer->move_to(290, 390);

  Cairo::RefPtr<Cairo::ToyFontFace> font3 =
    Cairo::ToyFontFace::create("Bitstream Charter",
                               Cairo::FONT_SLANT_ITALIC,
                               Cairo::FONT_WEIGHT_BOLD);
  timer->set_font_face(font3);
  timer->set_font_size(FONT_SIZE);
  timer->show_text(buffer2);
  timer->save();
  timer->restore();

  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  // scale to unit square and translate (0, 0) to be (0.5, 0.5), i.e.
  // the center of the window
  timer->scale(width, height);
  //centers the clock to the window provided
  //timer->translate(0.5, 0.5);
  timer->set_line_width(0.05);
  //saves the current image
  timer->save();
  

  //puts the color on the screen


  // colons
  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  timer->set_line_width(line_width);
  timer->arc(.225, .455, .01, 0, 2 * M_PI);
  timer->fill();
  timer->stroke();
  timer->save();

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  timer->set_line_width(line_width);
  timer->arc(.225, .545, .01, 0, 2 * M_PI);
  timer->fill();
  timer->stroke();
  timer->save();

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  timer->set_line_width(line_width);
  timer->arc(.595, .455, .01, 0, 2 * M_PI);
  timer->fill();
  timer->stroke();
  timer->save();

  timer->set_source_rgba(156.00/255, 195.00/255, 240.00/255, 1.000);
  timer->set_line_width(line_width);
  timer->arc(.595, .545, .01, 0, 2 * M_PI);
  timer->fill();
  timer->stroke();
  timer->save();  

  //hour
  background(timer, 0.05, 0.3, 0.05, 0.7);
  background(timer, 0.05, 0.3, 0.2, 0.3);
  background(timer, 0.2, 0.3, 0.2, 0.7);
  background(timer, 0.2, 0.7, 0.05, 0.7);
  background(timer, 0.07, 0.5, 0.18, 0.5);
  circle_fill_top(hour);  
  circle_patterns(timer, 0.085, 0.335, radius);
  circle_fill_bottom(hour);
  circle_patterns(timer, 0.085, 0.555, radius);

  //min
  background(timer, 0.25, 0.3, 0.4, 0.3);
  background(timer, 0.25, 0.3, 0.25, 0.7);
  background(timer, 0.4, 0.3, 0.4, 0.7);
  background(timer, 0.4, 0.7, 0.25, 0.7);
  background(timer, 0.27, 0.5, 0.38, 0.5);
  circle_fill_top(mins/10);
  circle_patterns(timer, 0.285, 0.335, radius);
  circle_fill_bottom(mins/10);
  circle_patterns(timer, 0.285, 0.555, radius);
  
  //min2
  background(timer, 0.42, 0.3, 0.57, 0.3);
  background(timer, 0.42, 0.3, 0.42, 0.7);
  background(timer, 0.57, 0.3, 0.57, 0.7);
  background(timer, 0.57, 0.7, 0.42, 0.7);
  background(timer, 0.44, 0.5, 0.55, 0.5);
  circle_fill_top(mins%10);
  circle_patterns(timer, 0.455, 0.335, radius);
  circle_fill_bottom(mins%10);
  circle_patterns(timer, 0.455, 0.555, radius);

  //sec
  background(timer, 0.62, 0.3, 0.77, 0.3);
  background(timer, 0.62, 0.3, 0.62, 0.7);
  background(timer, 0.77, 0.3, 0.77, 0.7);
  background(timer, 0.77, 0.7, 0.62, 0.7);
  background(timer, 0.75, 0.5, 0.64, 0.5);
  circle_fill_top(secs/10);
  circle_patterns(timer, 0.655, 0.335, radius);
  circle_fill_bottom(secs/10);
  circle_patterns(timer, 0.655, 0.555, radius);

  //sec2
  background(timer, 0.79, 0.3, 0.94, 0.3);
  background(timer, 0.79, 0.3, 0.79, 0.7);
  background(timer, 0.94, 0.3, 0.94, 0.7);
  background(timer, 0.94, 0.7, 0.79, 0.7);
  background(timer, 0.81, 0.5, 0.92, 0.5);
  circle_fill_top(secs%10);
  circle_patterns(timer, 0.825, 0.335, radius);
  circle_fill_bottom(secs%10);
  circle_patterns(timer, 0.825, 0.555, radius);

  return true;
}

bool Timer::on_timeout()
{
    // force our program to redraw the entire clock.
    Glib::RefPtr<Gdk::Window> win = get_window();
    if (win)
    {
        Gdk::Rectangle r(0, 0, get_allocation().get_width(),
                get_allocation().get_height());
        win->invalidate_rect(r, false);
    }
    return true;
}

void Timer::initialize(int t_s) {
  time_step = t_s;
}

void Timer::started() { ticking = true; reset = false;}
void Timer::stopped() { ticking = false; reset = true;}

void Timer::color1 () {color = 1; }
void Timer::color2 () {color = 2; }
void Timer::color3 () {color = 3; }
void Timer::color4 () {color = 4; }
