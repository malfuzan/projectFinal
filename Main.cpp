
#include "Simulator.h"
#include "Plotter.h"
#include "motor.h"
#include "VoltageSource.h"
#include "Diode.h"
#include "Resistor.h"
#include "Capacitor.h"

/*

  Example circuit (rectifier):

     (1)   D1      (2)
       .--->|---.-------.
      +|        |       |     +
  vin (~)    R1 <   C1 ===   vout
       |        |       |     -
       '--------+-------'
               -+- (0)
                '

  time step = 1e-5 s
  simulation time = 5 ms
  
  vin = 10 * sin(2*pi*1000*t)
  R1 = 10 Ohm
  C1 = 1.0 mF

*/

int main()
{
	const double h = 1e-2;
	const double tmax = 5;
	const double R = 1; // 0.1 N.m.s
	// 10 mH for inductor 
	

	Plotter plotter("Project", 1000, 600);
	plotter.SetLabels("vin (V)", "speed");

	Simulator simulator(2, 0);

	VoltageSource V1(1, 0, 10);
	Motor M1(1, 0, 2,0.5,10e-3,0.1,0.005,0.1,0.1);
	Resistor R1 (2, 0, R);

	simulator.AddDevice(V1);
	simulator.AddDevice(R1);
	simulator.AddDevice(M1);

	simulator.Init(h, tmax);

	while (simulator.IsRunning())
	{
		plotter.AddRow(simulator.GetTime(), M1.GetShaftSpeed());
			
		M1.GetShaftSpeed();
		
		
	}

	plotter.Plot();

	return 0;
}