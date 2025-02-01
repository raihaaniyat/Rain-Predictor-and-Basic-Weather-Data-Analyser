#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>  // For Windows serial communication

using namespace std;
const int MAX_READINGS = 5;  // Store the last 5 readings
float temperatures[MAX_READINGS] = {0};
float humidities[MAX_READINGS] = {0};
float pressures[MAX_READINGS] = {0};
int index = 0;

// Function to process the sensor data
void processSensorData(const string& data) {
    stringstream ss(data);
    string temp, hum, pres;

    // Parse the data (Format: temperature,humidity,pressure)
    getline(ss, temp, ',');
    getline(ss, hum, ',');
    getline(ss, pres);

    // Convert to numeric values with error checking
    try {
        float temperature = stof(temp);
        float humidity = stof(hum);
        float pressure = stof(pres);

        // Store the data in arrays
        temperatures[index] = temperature;
        humidities[index] = humidity;
        pressures[index] = pressure;

        // Display the latest readings
        cout << "Latest Reading (Index " << index << "):" << endl;
        cout << "Temperature: " << temperatures[index] << " °C" << endl;
        cout << "Humidity: " << humidities[index] << " %" << endl;
        cout << "Pressure: " << pressures[index] << " hPa" << endl;

        // Display the past readings
        cout << "\nPast Readings:" << endl;
        for (int i = 0; i < MAX_READINGS; ++i) {
            cout << "Reading " << i + 1 << ": "
                 << "Temp: " << temperatures[i] << " °C, "
                 << "Hum: " << humidities[i] << " %, "
                 << "Press: " << pressures[i] << " hPa" << endl;
        }
        // Rain Prediction Logic (Example)
        if (temperature < 25 && humidity > 60 && pressure < 1000) {
            cout << "Rain is predicted." << endl;
        } else {
            cout << "No rain predicted." << endl;
        }
        cout << "--------------------------" << endl;

        // Update index and reset it if needed
        index = (index + 1) % MAX_READINGS;  // Loop back to 0 after 5 readings

    } catch (const exception& e) {
        cerr << "Error: Invalid data received. Could not convert to numbers." << endl;
    }
}

int main() {
    // Open the serial port for communication with the Arduino
    string port = "COM3";  // Update this to match your Arduino's port
    unsigned long baudrate = 9600;

    HANDLE hSerial = CreateFile(port.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        cerr << "Error: Unable to open the serial port." << endl;
        return 1;
    }

    // Set up serial communication
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Error: Unable to get serial port state." << endl;
        return 1;
    }

    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        cerr << "Error: Unable to set serial port state." << endl;
        return 1;
    }

    // Set timeouts to prevent hanging if no data is received
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    SetCommTimeouts(hSerial, &timeouts);

    char szBuff[1024];
    DWORD dwBytesRead;

    while (true) {
        if (ReadFile(hSerial, szBuff, sizeof(szBuff), &dwBytesRead, NULL)) {
            szBuff[dwBytesRead] = '\0';  // Null-terminate the string
            string data(szBuff);

            // Check if data is not empty
            if (!data.empty()) {
                processSensorData(data);  // Process the sensor data
            }
        }
    }

    CloseHandle(hSerial);  // Close the serial port
    return 0;
}
