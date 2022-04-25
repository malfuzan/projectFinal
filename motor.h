// Simplified Motor Model
#include "Simulator.h"

class Motor : public Device
{
public:

    // Constructor (external nodes and params):
    Motor(int positive, int negative, int shaft, double Ra, double La, double Jr,
        double Br, double Ke, double Kt);

    // Device interface:
    void Step(double t, double dt); // Stamp the Jacobian and B-Equivalent
    void Init(); // Add internal nodes with GetNextNode()

    // Viewable functions:
    double GetArmatureVoltage(); // Get instantaneous armature voltage (V)
    double GetArmatureCurrent(); // Get instantaneous armature current (A)
    double GetTerminalPower(); // Get total power into device (W)
    double GetShaftSpeed(); // Get mechanical shaft angular velocity (rad/s)
    double GetShaftTorque(); // Get torque delivered to axile (N.m)
    double GetShaftPower(); // Get total power out of device via shaft (W)

    // Member variables:
    int positive;
    int negative;
    int shaft; 
    double Ra;
    double La;
    double Jr;
    double Br;
    double Ke;
    double Kt;
    int int0;
    int int1;
    int int2;
    int int3;
};

Motor::Motor(int positive, int negative, int shaft, double Ra, double La, double Jr,
    double Br, double Ke, double Kt)
{
    this->positive = positive;
    this->negative = negative;
    this->shaft = shaft;
    this->Ra = Ra;
    this->La = La;
    this->Jr = Jr;
    this->Br = Br;
    this->Ke = Ke;
    this->Kt = Kt;
}
void Motor::Init()
{
       
         int0 = GetNextNode();
   //      int1 = GetNextNode();
         int2 = GetNextNode();
     //    int3 = GetNextNode();
               
}

void Motor::Step(double t, double h)
{
    // Ra:
    AddJacobian(positive, int0, -1 / Ra);
    AddJacobian(positive, positive, 1 / Ra);
    AddJacobian(int0, positive, -1 / Ra);
    AddJacobian(int0, int0, 1 / Ra);

    // La:
    AddJacobian(int0, int2, 1);
    AddJacobian(negative, int2, -1);
    AddJacobian(int2, int0, 1);
    AddJacobian(int2, negative, -1);
    AddJacobian(int2, int2, -La / h);
    AddBEquivalent(int2, ( - La / h )* GetState(int2));

    // Voltage Controlled Voltage Source
  //  AddJacobian(int1, int3, 1);
    //AddJacobian(negative, int3, -1);
    //AddJacobian(int3, shaft, -Ke);
    //AddJacobian(int3, int1, 1);
    //AddJacobian(int3, negative, -1);


    // Current Controlled Current Source:
    //AddJacobian(int1, int3, 1);
    //AddJacobian(negative, int3, -1);
    //AddJacobian(shaft, int3, Kt);
    //AddJacobian(int3, int1, 1);
    //AddJacobian(int3, negative, -1);


    // Bm:
    AddJacobian(shaft, shaft, 1 / Br);

    // Jm:
    AddJacobian(shaft, shaft, Jr / h);
    AddBEquivalent(shaft, (Jr / h) * GetState(shaft));

    AddBEquivalent(int2, Ke * GetState(shaft));
    AddBEquivalent(shaft, Kt * GetState(int2));



    //sim->J.Print();
     
}

double Motor::GetArmatureVoltage()
{
    return GetStateDifference(positive, negative);
}
double Motor::GetArmatureCurrent()
{
    return GetState(int2);
}
double Motor::GetTerminalPower()
{
    return GetArmatureCurrent() * GetArmatureVoltage();
}
double Motor::GetShaftSpeed()
{
    return GetState(shaft);
}
double Motor::GetShaftTorque()
{
    return Kt*GetState(int2);
}
double Motor::GetShaftPower()
{
    return GetShaftTorque() * GetShaftSpeed();
}