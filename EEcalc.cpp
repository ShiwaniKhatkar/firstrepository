#include <iostream>
#include <cmath>
#include <unordered_map>
#include <complex>
#include <vector>

using namespace std;

const double PI = 3.14159265358979323846;

// Function to calculate the Fourier series coefficients
vector<complex<double>> calculateFourierCoefficients(const vector<double>& signal) {
    int N = signal.size();
    vector<complex<double>> coefficients;

    for (int k = 0; k < N; ++k) {
        complex<double> sum = 0.0;
        for (int n = 0; n < N; ++n) {
            double angle = 2.0 * PI * k * n / N;
            sum += signal[n] * polar(1.0, -angle);
        }
        coefficients.push_back(sum/static_cast<double>(N));
    }

    return coefficients;
}

class ElectricalCalculator {
public:
    // Ohm's Law Calculator
    static double calculateVoltage(double current, double resistance) {
        return current * resistance;
    }

    static double calculateCurrent(double voltage, double resistance) {
        return voltage / resistance;
    }

    static double calculateResistance(double voltage, double current) {
        return voltage / current;
    }

    // Power Calculator
    static double calculatePower(double voltage, double current) {
        return voltage * current;
    }

    static double calculatePower2(double current, double resistance) {
        return pow(current, 2) * resistance;
    }

    // Capacitance and Inductance Calculator
    static double calculateImpedance(double resistance, double reactance) {
        return sqrt(pow(resistance, 2) + pow(reactance, 2));
    }

    static double calculateReactance(double impedance, double resistance) {
        return sqrt(pow(impedance, 2) - pow(resistance, 2));
    }

    static double calculatePhaseAngle(double resistance, double reactance) {
        return atan(reactance / resistance);
    }

    // Resistor Color Code Decoder
    static double decodeResistorColorCode(string color1, string color2, string color3) {
        unordered_map<string, int> colorMap = {
            {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3}, {"yellow", 4},
            {"green", 5}, {"blue", 6}, {"violet", 7}, {"gray", 8}, {"white", 9}
        };

        int value = colorMap[color1] * 10 + colorMap[color2];
        double multiplier = pow(10, colorMap[color3]);

        return value * multiplier;
    }

    // Series and Parallel Resistor Calculator
    static double calculateEquivalentResistanceSeries(double resistances[], int count) {
        double totalResistance = 0;
        for (int i = 0; i < count; ++i) {
            totalResistance += resistances[i];
        }
        return totalResistance;
    }

    static double calculateEquivalentResistanceParallel(double resistances[], int count) {
        double totalInverseResistance = 0;
        for (int i = 0; i < count; ++i) {
            totalInverseResistance += 1.0 / resistances[i];
        }
        return 1.0 / totalInverseResistance;
    }

    // Time Constant Calculator
    static double calculateTimeConstantRC(double resistance, double capacitance) {
        return resistance * capacitance;
    }

    static double calculateTimeConstantRL(double resistance, double inductance) {
        return resistance * inductance;
    }

    // Frequency and Wavelength Calculator
    static double calculateFrequency(double speedOfLight, double wavelength) {
        return speedOfLight / wavelength;
    }

    static double calculateWavelength(double speedOfLight, double frequency) {
        return speedOfLight / frequency;
    }

    // Power Factor Calculator
    static double calculatePowerFactor(double realPower, double apparentPower) {
        return realPower / apparentPower;
    }

    // Three-Phase Power Calculator
    static double calculateThreePhasePower(double voltage, double current, double powerFactor, int numberOfPhases) {
        return sqrt(3.0) * voltage * current * powerFactor * numberOfPhases;
    }

    // Voltage Divider Calculator
    static double calculateVoltageDivider(double sourceVoltage, double resistance1, double resistance2) {
        return sourceVoltage * (resistance2 / (resistance1 + resistance2));
    }

    // Current Divider Calculator
    static double calculateCurrentDivider(double sourceCurrent, double conductance1, double conductance2) {
        return sourceCurrent * (conductance2 / (conductance1 + conductance2));
    }

    // Fourier Series Calculator
    static void calculateFourierSeries(const vector<double>& signal, int numHarmonics) {
        int N = signal.size();
        vector<complex<double>> coefficients = calculateFourierCoefficients(signal);

        // Display the Fourier series components
        cout << "Fourier Series Components:\n";
        for (int k = 0; k <= numHarmonics; ++k) {
            complex<double> coeff = coefficients[k];
            double magnitude = abs(coeff);
            double phase = arg(coeff);

            cout << "Harmonic " << k << ": Magnitude = " << magnitude << ", Phase = " << phase << " radians\n";
        }
    }

    // Function to display menu and get user choice
    static int getUserChoice() {
        int choice;
        cout << "\nChoose a calculation:\n";
        cout << "1. Ohm's Law Calculator\n";
        cout << "2. Power Calculator\n";
        cout << "3. Capacitance and Inductance Calculator\n";
        cout << "4. Resistor Color Code Decoder\n";
        cout << "5. Series and Parallel Resistor Calculator\n";
        cout << "6. Time Constant Calculator\n";
        cout << "7. Frequency and Wavelength Calculator\n";
        cout << "8. Power Factor Calculator\n";
        cout << "9. Three-Phase Power Calculator\n";
        cout << "10. Voltage Divider Calculator\n";
        cout << "11. Current Divider Calculator\n";
        cout << "12. Fourier Series Calculator\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }
};

int main() {
    int choice;
    do {
        choice = ElectricalCalculator::getUserChoice();

        switch (choice) {
            case 1: {
                // Ohm's Law Calculator
                double current, resistance, voltage;
                cout << "Enter current (A): ";
                cin >> current;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                voltage = ElectricalCalculator::calculateVoltage(current, resistance);
                cout << "Voltage (V): " << voltage << endl;
                break;
            }
            case 2: {
                // Power Calculator
                double voltage, current;
                cout << "Enter voltage (V): ";
                cin >> voltage;
                cout << "Enter current (A): ";
                cin >> current;
                double powerIV = ElectricalCalculator::calculatePower(voltage, current);
                double powerI2R = ElectricalCalculator::calculatePower(current, 1.0); // Assuming R = 1 Ohm
                cout << "Power (IV): " << powerIV << " watts" << endl;
                cout << "Power (I^2R): " << powerI2R << " watts" << endl;
                break;
            }
            case 3: {
                // Capacitance and Inductance Calculator
                double resistance, reactance, impedance, phaseAngle;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter reactance (Ohms): ";
                cin >> reactance;
                impedance = ElectricalCalculator::calculateImpedance(resistance, reactance);
                cout << "Impedance (Ohms): " << impedance << endl;
                phaseAngle = ElectricalCalculator::calculatePhaseAngle(resistance, reactance);
                cout << "Phase Angle (radians): " << phaseAngle << endl;
                break;
            }
            case 4: {
                // Resistor Color Code Decoder
                string color1, color2, color3;
                cout << "Enter color bands (e.g., black, red, green, brown, orange, blue, violet, gray, white, yellow): ";
                cin >> color1 >> color2 >> color3;
                double resistance = ElectricalCalculator::decodeResistorColorCode(color1, color2, color3);
                cout << "Decoded Resistance (Ohms): " << resistance << endl;
                break;
            }
            case 5: {
                // Series and Parallel Resistor Calculator
                int count;
                cout << "Enter the number of resistors: ";
                cin >> count;

                double resistances[count];
                for (int i = 0; i < count; ++i) {
                    cout << "Enter resistance " << i + 1 << " (Ohms): ";
                    cin >> resistances[i];
                }

                cout << "Equivalent Resistance (Series): " << ElectricalCalculator::calculateEquivalentResistanceSeries(resistances, count) << " Ohms" << endl;
                cout << "Equivalent Resistance (Parallel): " << ElectricalCalculator::calculateEquivalentResistanceParallel(resistances, count) << " Ohms" << endl;
                break;
            }
            case 6: {
                // Time Constant Calculator
                double resistance, capacitance, inductance;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter capacitance (Farads): ";
                cin >> capacitance;
                cout << "Time Constant (RC): " << ElectricalCalculator::calculateTimeConstantRC(resistance, capacitance) << " seconds" << endl;

                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter inductance (Henrys): ";
                cin >> inductance;
                cout << "Time Constant (RL): " << ElectricalCalculator::calculateTimeConstantRL(resistance, inductance) << " seconds" << endl;
                break;
            }
            case 7: {
                // Frequency and Wavelength Calculator
                double speedOfLight, frequency, wavelength;
                cout << "Enter speed of light (m/s): ";
                cin >> speedOfLight;

                cout << "Enter frequency (Hz): ";
                cin >> frequency;
                cout << "Wavelength (meters): " << ElectricalCalculator::calculateWavelength(speedOfLight, frequency) << endl;

                cout << "Enter wavelength (meters): ";
                cin >> wavelength;
                cout << "Frequency (Hz): " << ElectricalCalculator::calculateFrequency(speedOfLight, wavelength) << endl;
                break;
            }
            case 8: {
                // Power Factor Calculator
                double realPower, apparentPower;
                cout << "Enter real power (watts): ";
                cin >> realPower;
                cout << "Enter apparent power (VA): ";
                cin >> apparentPower;
                cout << "Power Factor: " << ElectricalCalculator::calculatePowerFactor(realPower, apparentPower) << endl;
                break;
            }
            case 9: {
                // Three-Phase Power Calculator
                double voltage, current, powerFactor;
                int numberOfPhases;
                cout << "Enter line voltage (V): ";
                cin >> voltage;
                cout << "Enter line current (A): ";
                cin >> current;
                cout << "Enter power factor: ";
                cin >> powerFactor;
                cout << "Enter number of phases: ";
                cin >> numberOfPhases;

                cout << "Three-Phase Power: " << ElectricalCalculator::calculateThreePhasePower(voltage, current, powerFactor, numberOfPhases) << " VA" << endl;
                break;
            }
            case 10: {
                // Voltage Divider Calculator
                double sourceVoltage, resistance1, resistance2;
                cout << "Enter source voltage (V): ";
                cin >> sourceVoltage;
                cout << "Enter resistance 1 (Ohms): ";
                cin >> resistance1;
                cout << "Enter resistance 2 (Ohms): ";
                cin >> resistance2;

                cout << "Voltage Across Resistance 2: " << ElectricalCalculator::calculateVoltageDivider(sourceVoltage, resistance1, resistance2) << " V" << endl;
                break;
            }
            case 11: {
                // Current Divider Calculator
                double sourceCurrent, conductance1, conductance2;
                cout << "Enter source current (A): ";
                cin >> sourceCurrent;
                cout << "Enter conductance 1 (Siemens): ";
                cin >> conductance1;
                cout << "Enter conductance 2 (Siemens): ";
                cin >> conductance2;

                cout << "Current Through Conductance 2: " << ElectricalCalculator::calculateCurrentDivider(sourceCurrent, conductance1, conductance2) << " A" << endl;
                break;
            }
            case 12: {
                // Fourier Series Calculator
                int numHarmonics;
                cout << "Enter the number of harmonics to compute: ";
                cin >> numHarmonics;
                
                // Get the signal from the user
                vector<double> signal;
                cout << "Enter the signal values (space-separated): ";
                for (int i = 0; i < numHarmonics; ++i) {
                    double value;
                    cin >> value;
                    signal.push_back(value);
                }

                // Perform Fourier series calculation
                ElectricalCalculator::calculateFourierSeries(signal, numHarmonics);
                break;
            }
            case 0:
                cout << "Exiting the calculator. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
