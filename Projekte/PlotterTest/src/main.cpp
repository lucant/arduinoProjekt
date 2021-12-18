#include "Plotter.h"

double x;

Plotter p;

void setup()
{
  p.Begin(); // start plotter

  p.AddTimeGraph("Some title of a graph", 500, "label for x", x);
}

void loop()
{
  x = 10 * sin(2.0 * PI * (millis() / 5000.0));

  p.Plot(); // usually called within loop()
}