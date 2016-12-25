//Kevin Rowland, Victor Jose Amaral, Sarah Azody
#ifndef TIMER_H
#define TIMER_H

#include <gtkmm/drawingarea.h>

class Timer : public Gtk::DrawingArea {

  int counter = 0;
  int time_step;
  double line_width = 0.003;
  double colon_rgba = 1.0;
  double radius = 0.015;
  bool ticking = false, reset = true;
  int color = 1;


  const double HEIGHT = 200.0;
  const double WIDTH = 400.0;
  const double FONT_SIZE = 40.0;
  const double TEXT_ORIGIN_Y = (HEIGHT / 3) + (FONT_SIZE / 2.0);
  const double TEXT_ORIGIN_X = 40.0; // arbitrary

  //domino dots (2 & 6 aren't ever used)
  bool d1 = false;
  bool d3 = false;
  bool d4 = false;
  bool d5 = false;
  bool d6 = false;
  bool d7 = false;
  bool d9 = false; 

  void circle_fill_top(int time_unit);
  void circle_fill_bottom(int time_unit);
  bool on_timeout();
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& timer);
  void circle(const Cairo::RefPtr<Cairo::Context>& timer, 
    double center_x, double center_y, double radius, bool to_fill);
  void background(const Cairo::RefPtr<Cairo::Context>& timer, 
    double move_start, double move_end, double line_start, double line_end);
  void circle_patterns(const Cairo::RefPtr<Cairo::Context>& timer, 
    double center_x, double center_y, double radius);
  void digital_clock(const Cairo::RefPtr<Cairo::Context>& timer, 
    int time_unit, double move_start, double move_end);


public:
  Timer();
  virtual ~Timer();
  void initialize(int a);
  void started();
  void stopped();
  void color1();
  void color2();
  void color3();
  void color4();


};

#endif
