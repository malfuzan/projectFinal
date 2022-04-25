
#include "Simulator.h"
#include "Plotter.h"
#include "motor.h"
#include "VoltageSource.h"
#include "Diode.h"
#include "Resistor.h"


int main()
{
	const double h = 1e-2;
	const double tmax = 5;
	const double R = 0; // 0.1 N.m.s
	// 10 mH for inductor 
	

	Plotter plotter1("Project", 1000, 600);
	plotter1.SetLabels("speed", "Ia");


	Simulator simulator(2,0);
	VoltageSource V1(1, 0, 10);
	Motor M1(1, 0, 2, 0.5, 0.01, 0.1, 0.005, 0.1, 0.1);
	Resistor R1 (2, 0, R);

	simulator.AddDevice(V1);
	simulator.AddDevice(R1);
	simulator.AddDevice(M1);

	simulator.Init(h, tmax);

	while (simulator.IsRunning())
	{
		plotter1.AddRow(simulator.GetTime(), M1.GetShaftSpeed(), M1.GetArmatureCurrent());

		simulator.Step();
		
	}

	plotter1.Plot();


	return 0;
}