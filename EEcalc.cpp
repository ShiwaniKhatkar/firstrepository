#include <iostream>           //Calculator
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <iomanip>

using namespace std;

class ElectricalCalculator {
public:
    static int getUserChoice() {
        int choice;
        cout << "\n===== Electrical Calculator =====\n";
        cout << "1. Calculate Voltage (V = I * R)\n";
        cout << "2. Calculate Power (P = V * I and P = I^2 * R)\n";
        cout << "3. Calculate Impedance and Phase Angle\n";
        cout << "4. Decode Resistor Color Code\n";
        cout << "5. Equivalent Resistance (Series and Parallel)\n";
        cout << "6. Time Constant (RC and RL)\n";
        cout << "7. Wavelength and Frequency\n";
        cout << "8. Power Factor\n";
        cout << "9. Three-Phase Power\n";
        cout << "10. Voltage Divider\n";
        cout << "11. Current Divider\n";
        cout << "12. Fourier Series Coefficients\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        return choice;
    }

    static double calculateVoltage(double current, double resistance) {
        return current * resistance;
    }

    static double calculatePower(double voltage, double current) {
        return voltage * current;
    }

    static double calculatePower2(double current, double resistance) {
        return current * current * resistance;
    }

    static double calculateImpedance(double resistance, double reactance) {
        return sqrt(resistance * resistance + reactance * reactance);
    }

    static double calculatePhaseAngle(double resistance, double reactance) {
        return atan2(reactance, resistance);
    }

    static double decodeResistorColorCode(string color1, string color2, string color3) {
        map<string, int> colors = {
            {"black", 0}, {"brown", 1}, {"red", 2}, {"orange", 3}, {"yellow", 4},
            {"green", 5}, {"blue", 6}, {"violet", 7}, {"grey", 8}, {"gray", 8}, {"white", 9}
        };

        if (colors.find(color1) == colors.end() || colors.find(color2) == colors.end() || colors.find(color3) == colors.end()) {
            cout << "Invalid color entered. Use lowercase color names.\n";
            return -1;
        }

        int firstDigit = colors[color1];
        int secondDigit = colors[color2];
        int multiplier = colors[color3];

        return (firstDigit * 10 + secondDigit) * pow(10, multiplier);
    }

    static double calculateEquivalentResistanceSeries(const double resistances[], int count) {
        double total = 0;
        for (int i = 0; i < count; ++i) {
            total += resistances[i];
        }
        return total;
    }

    static double calculateEquivalentResistanceParallel(const double resistances[], int count) {
        double reciprocalSum = 0;
        for (int i = 0; i < count; ++i) {
            if (resistances[i] == 0) {
                return 0;
            }
            reciprocalSum += 1.0 / resistances[i];
        }
        return reciprocalSum == 0 ? 0 : 1.0 / reciprocalSum;
    }

    static double calculateTimeConstantRC(double resistance, double capacitance) {
        return resistance * capacitance;
    }

    static double calculateTimeConstantRL(double resistance, double inductance) {
        if (resistance == 0) {
            cout << "Resistance cannot be zero for RL time constant.\n";
            return 0;
        }
        return inductance / resistance;
    }

    static double calculateWavelength(double speedOfLight, double frequency) {
        if (frequency == 0) {
            cout << "Frequency cannot be zero.\n";
            return 0;
        }
        return speedOfLight / frequency;
    }

    static double calculateFrequency(double speedOfLight, double wavelength) {
        if (wavelength == 0) {
            cout << "Wavelength cannot be zero.\n";
            return 0;
        }
        return speedOfLight / wavelength;
    }

    static double calculatePowerFactor(double realPower, double apparentPower) {
        if (apparentPower == 0) {
            cout << "Apparent power cannot be zero.\n";
            return 0;
        }
        return realPower / apparentPower;
    }

    static double calculateThreePhasePower(double voltage, double current, double powerFactor, int numberOfPhases) {
        if (numberOfPhases == 3) {
            return sqrt(3) * voltage * current * powerFactor;
        }
        return voltage * current * powerFactor;
    }

    static double calculateVoltageDivider(double sourceVoltage, double resistance1, double resistance2) {
        if (resistance1 + resistance2 == 0) {
            cout << "Total resistance cannot be zero.\n";
            return 0;
        }
        return sourceVoltage * resistance2 / (resistance1 + resistance2);
    }

    static double calculateCurrentDivider(double sourceCurrent, double conductance1, double conductance2) {
        if (conductance1 + conductance2 == 0) {
            cout << "Total conductance cannot be zero.\n";
            return 0;
        }
        return sourceCurrent * conductance2 / (conductance1 + conductance2);
    }

    static void calculateFourierSeries(const vector<double>& signal, int numHarmonics) {
        int n = static_cast<int>(signal.size());
        if (n == 0 || numHarmonics <= 0) {
            cout << "Invalid signal size or number of harmonics.\n";
            return;
        }

        cout << "Fourier coefficients:\n";
        for (int k = 0; k <= numHarmonics; ++k) {
            double real = 0, imag = 0;
            for (int t = 0; t < n; ++t) {
                double angle = 2 * M_PI * k * t / n;
                real += signal[t] * cos(angle);
                imag -= signal[t] * sin(angle);
            }
            real /= n;
            imag /= n;
            cout << "Harmonic " << k << ": Real = " << real << ", Imaginary = " << imag << endl;
        }
    }
};

int main() {
    int choice;
    cout << fixed << setprecision(4);

    do {
        choice = ElectricalCalculator::getUserChoice();

        switch (choice) {
            case 1: {
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
                double voltage, current, resistance;
                cout << "Enter voltage (V): ";
                cin >> voltage;
                cout << "Enter current (A): ";
                cin >> current;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                double powerIV = ElectricalCalculator::calculatePower(voltage, current);
                double powerI2R = ElectricalCalculator::calculatePower2(current, resistance);
                cout << "Power (IV): " << powerIV << " watts" << endl;
                cout << "Power (I^2R): " << powerI2R << " watts" << endl;
                break;
            }

            case 3: {
                double resistance, reactance, impedance, phaseAngle;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter reactance (Ohms): ";
                cin >> reactance;
                impedance = ElectricalCalculator::calculateImpedance(resistance, reactance);
                phaseAngle = ElectricalCalculator::calculatePhaseAngle(resistance, reactance);
                cout << "Impedance (Ohms): " << impedance << endl;
                cout << "Phase Angle (radians): " << phaseAngle << endl;
                break;
            }

            case 4: {
                string color1, color2, color3;
                cout << "Enter color bands: ";
                cin >> color1 >> color2 >> color3;
                double resistance = ElectricalCalculator::decodeResistorColorCode(color1, color2, color3);
                if (resistance >= 0) {
                    cout << "Decoded Resistance (Ohms): " << resistance << endl;
                }
                break;
            }

            case 5: {
                int count;
                cout << "Enter the number of resistors: ";
                cin >> count;
                if (count <= 0) {
                    cout << "Number of resistors must be positive.\n";
                    break;
                }
                vector<double> resistances(count);
                for (int i = 0; i < count; ++i) {
                    cout << "Enter resistance " << i + 1 << " (Ohms): ";
                    cin >> resistances[i];
                }
                cout << "Equivalent Resistance (Series): "
                     << ElectricalCalculator::calculateEquivalentResistanceSeries(resistances.data(), count)
                     << " Ohms" << endl;
                cout << "Equivalent Resistance (Parallel): "
                     << ElectricalCalculator::calculateEquivalentResistanceParallel(resistances.data(), count)
                     << " Ohms" << endl;
                break;
            }

            case 6: {
                double resistance, capacitance, inductance;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter capacitance (Farads): ";
                cin >> capacitance;
                cout << "Time Constant (RC): "
                     << ElectricalCalculator::calculateTimeConstantRC(resistance, capacitance)
                     << " seconds" << endl;
                cout << "Enter resistance (Ohms): ";
                cin >> resistance;
                cout << "Enter inductance (Henrys): ";
                cin >> inductance;
                cout << "Time Constant (RL): "
                     << ElectricalCalculator::calculateTimeConstantRL(resistance, inductance)
                     << " seconds" << endl;
                break;
            }

            case 7: {
                double speedOfLight, frequency, wavelength;
                cout << "Enter speed of light (m/s): ";
                cin >> speedOfLight;
                cout << "Enter frequency (Hz): ";
                cin >> frequency;
                cout << "Wavelength (meters): "
                     << ElectricalCalculator::calculateWavelength(speedOfLight, frequency) << endl;
                cout << "Enter wavelength (meters): ";
                cin >> wavelength;
                cout << "Frequency (Hz): "
                     << ElectricalCalculator::calculateFrequency(speedOfLight, wavelength) << endl;
                break;
            }

            case 8: {
                double realPower, apparentPower;
                cout << "Enter real power (watts): ";
                cin >> realPower;
                cout << "Enter apparent power (VA): ";
                cin >> apparentPower;
                cout << "Power Factor: "
                     << ElectricalCalculator::calculatePowerFactor(realPower, apparentPower) << endl;
                break;
            }

            case 9: {
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
                cout << "Power: "
                     << ElectricalCalculator::calculateThreePhasePower(voltage, current, powerFactor, numberOfPhases)
                     << " W" << endl;
                break;
            }

            case 10: {
                double sourceVoltage, resistance1, resistance2;
                cout << "Enter source voltage (V): ";
                cin >> sourceVoltage;
                cout << "Enter resistance 1 (Ohms): ";
                cin >> resistance1;
                cout << "Enter resistance 2 (Ohms): ";
                cin >> resistance2;
                cout << "Voltage Across Resistance 2: "
                     << ElectricalCalculator::calculateVoltageDivider(sourceVoltage, resistance1, resistance2)
                     << " V" << endl;
                break;
            }

            case 11: {
                double sourceCurrent, conductance1, conductance2;
                cout << "Enter source current (A): ";
                cin >> sourceCurrent;
                cout << "Enter conductance 1 (Siemens): ";
                cin >> conductance1;
                cout << "Enter conductance 2 (Siemens): ";
                cin >> conductance2;
                cout << "Current Through Conductance 2: "
                     << ElectricalCalculator::calculateCurrentDivider(sourceCurrent, conductance1, conductance2)
                     << " A" << endl;
                break;
            }

            case 12: {
                int sampleCount, numHarmonics;
                cout << "Enter number of signal values: ";
                cin >> sampleCount;
                if (sampleCount <= 0) {
                    cout << "Number of signal values must be positive.\n";
                    break;
                }
                vector<double> signal(sampleCount);
                cout << "Enter the signal values (space-separated): ";
                for (int i = 0; i < sampleCount; ++i) {
                    cin >> signal[i];
                }
                cout << "Enter the number of harmonics to compute: ";
                cin >> numHarmonics;
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
