NEEDS TO BE IMPLEMENTED:

Create classes describing geometric figures as circle, ellipse, helix. Create set of arbitrary figures with random radius and Y-step for helixes.

For each arbitrary figure generated print:
  a) cartesian coordinates of figure point for PI/4 polar angle;
  b) cartesian coordinates of first derivative also for PI/4 polar angle.

After this select only circles from previously generated figures, sort them by ascending radius and print and find total sum of radiuses.


SOLUTION:

ICurve-interface describing figure;
Helixe-ICurve implementation for helix;
Ellipse-ICurve implementation for ellipse. Derived from Helixe-ellipse is partial case of helix, in fact;
Circle-ICurve implementation for circle. Derived from Ellipse-circle is partial case of ellipse;
CurvesTest.cpp-test cases from NEEDS TO BE IMPLEMENTED.
