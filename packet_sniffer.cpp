#define PY_SSIZE_T_CLEAN
#include <Python.h>  // Python C API for calling ML model
#include <iostream>  // For input/output (cout, cin)
#include <cstdlib>   // For system() to run terminal commands
#include <fstream>   // For reading packet data from a file (packets.txt)
#include <sstream>   // For parsing structured data
using namespace std;
#include <string>
#include <vector>    // For storing multiple packets in memory
#include <map>       // For protocol encoding (string -> numeric)

// ✅ Step 1: Define a structure to hold packet details
struct Packet {
    string timestamp;
    string src_ip;
    string dest_ip;
    string protocol;
    string packet_size;
    int threat_level;  // 1 = Threat, 0 = Normal
};

// ✅ Step 2: Function to map protocol names to numeric values
std::map<std::string, int> protocol_map = {
    {"TCP", 1},
    {"UDP", 2},
    {"ICMP", 3},
    {"ICMPv6", 4},
    {"TLSv1.2", 5},
    {"ARP", 6},
    {"SSL", 7},
    {"DNS", 8},
    {"QUIC", 9},
    {"IGMPv3", 10}
};

// ✅ Step 3: Function to call Python ML Model for Threat Detection
// Function to detect anomalies using the trained ML model
static PyObject *pModule = nullptr;
static PyObject *pFunc = nullptr;

void initializePython() {
    if (!Py_IsInitialized()) {
        Py_Initialize();

        // ✅ Add Python script directory to sys.path
        PyObject *sysPath = PySys_GetObject("path");
        PyObject *path = PyUnicode_DecodeFSDefault("/Users/kevinomerkilic/ai-cybersecurity-threat-detection");
        PyList_Append(sysPath, path);
        Py_DECREF(path);

        // ✅ Import Python module only once
        PyObject *pName = PyUnicode_DecodeFSDefault("train_model");
        pModule = PyImport_Import(pName);
        Py_XDECREF(pName);

        if (pModule != nullptr) {
            pFunc = PyObject_GetAttrString(pModule, "predict_threat");
            if (!pFunc || !PyCallable_Check(pFunc)) {
                cerr << "❌ Error: Python function not found!\n";
                Py_XDECREF(pModule);
                pModule = nullptr;
            }
        } else {
            cerr << "❌ Error: Failed to load Python module!\n";
        }
    }
}

// ✅ Function to Call Python ML Model for Threat Detection
int detectThreat(float protocol, float packet_size) {
    if (!pModule || !pFunc) {
        return -1;  // ❌ Python module not initialized
    }

    PyObject *pArgs = PyTuple_Pack(2, PyFloat_FromDouble(protocol), PyFloat_FromDouble(packet_size));
    PyObject *pValue = PyObject_CallObject(pFunc, pArgs);
    Py_XDECREF(pArgs);

    if (pValue != nullptr) {
        int result = PyLong_AsLong(pValue);
        Py_XDECREF(pValue);
        return result;
    }

    return -1;  // ❌ Error
}

// ✅ Function to Finalize Python at End of Program
void finalizePython() {
    if (pModule) {
        Py_XDECREF(pModule);
        pModule = nullptr;
    }
    Py_Finalize();
}




// ✅ Step 4: Function to process the captured packets
vector<Packet> processPackets() {
    ifstream file("packets.txt");
    if (!file) {
        cerr << "❌ Error: Failed to open packet log file!\n";
        return vector<Packet>();  // Explicitly return an empty vector
    }
    
    string line;
    vector<Packet> packets;
    
    while (getline(file, line)) {
        istringstream ss(line);
        Packet p;
        string temp_size, temp_eth_src, temp_eth_dst, temp_ipv6_src, temp_ipv6_dst;

        // Read values from the line
        getline(ss, p.timestamp, ',');
        getline(ss, p.src_ip, ',');
        getline(ss, p.dest_ip, ',');
        getline(ss, temp_ipv6_src, ',');
        getline(ss, temp_ipv6_dst, ',');
        getline(ss, temp_eth_src, ',');
        getline(ss, temp_eth_dst, ',');
        getline(ss, p.protocol, ',');
        getline(ss, temp_size, ',');

        // Use IPv4 if available, otherwise use IPv6, then fallback to MAC
        if (p.src_ip.empty() || p.src_ip == "Unknown") {
            p.src_ip = !temp_ipv6_src.empty() ? temp_ipv6_src : temp_eth_src;
        }
        if (p.dest_ip.empty() || p.dest_ip == "Unknown") {
            p.dest_ip = !temp_ipv6_dst.empty() ? temp_ipv6_dst : temp_eth_dst;
        }

        // Convert Protocol name to numeric value
        int protocol_numeric = protocol_map.count(p.protocol) ? protocol_map[p.protocol] : 0;

        // Ensure packet size is valid
        if (temp_size.empty()) {
            p.packet_size = "0";
        } else {
            p.packet_size = temp_size;
        }
        
        // Convert string packet size to integer for ML model
        int packet_size_numeric = stoi(p.packet_size);

        // Call ML model to check for threats
        p.threat_level = detectThreat(protocol_numeric, packet_size_numeric);

        packets.push_back(p);
    }
    
    // ✅ Step 5: Display all processed packets with Threat Status
    cout << "\n📡 **Network Packet Analysis & Threat Detection**\n";
    for (const auto& p : packets) {
        cout << "🔹 Time: " << p.timestamp
             << " | Src: " << p.src_ip
             << " | Dest: " << p.dest_ip
             << " | Protocol: " << p.protocol
             << " | Size: " << p.packet_size << " bytes"
             << " | Threat: " << (p.threat_level == 1 ? "⚠️ THREAT DETECTED" : "✅ Safe") << "\n";
    }

    return packets;
}

// ✅ Step 6: Function to save packets to a CSV file
void saveToCSV(const vector<Packet>& packets) {
    ofstream file("network_data.csv");
    if (!file) {
        cerr << "❌ Error: Unable to create CSV file!\n";
        return;
    }
    
    // Write CSV header
    file << "timestamp,src_ip,dest_ip,protocol,packet_size,threat_status\n";
    
    // Write packet data to CSV
    for (const auto& p : packets) {
        file << p.timestamp << "," << p.src_ip << "," << p.dest_ip << ","
             << p.protocol  << "," << p.packet_size << ","
             << (p.threat_level == 1 ? "THREAT" : "SAFE") << "\n";
    }
    
    file.close();
    cout << "✅ Data saved to network_data.csv\n";
}

// ✅ Step 7: Main function to capture packets
int main() {
    cout << "📡 Starting packet capture using Tshark...\n";

        // ✅ Set environment variables before running Python
        setenv("OMP_NUM_THREADS", "1", 1);
        setenv("OPENBLAS_NUM_THREADS", "1", 1);
        setenv("MKL_NUM_THREADS", "1", 1);
        setenv("VECLIB_MAXIMUM_THREADS", "1", 1);
        setenv("NUMEXPR_NUM_THREADS", "1", 1);

        // ✅ Initialize Python once at startup
        initializePython();

        // ✅ Capture packets using TShark
        string command = "tshark -i en0 -c 10 -T fields -E separator=, -e frame.time_epoch -e ip.src -e ip.dst -e ipv6.src -e ipv6.dst -e eth.src -e eth.dst -e _ws.col.Protocol -e frame.len > packets.txt";
        int result = system(command.c_str());

        if (result != 0) {
            cerr << "❌ Error: Failed to capture packets.\n";
            return 1;
        }

        cout << "✅ Packet capture completed! Saved to packets.pcap\n";

        // ✅ Process packets and detect threats using ML model
        vector<Packet> packets = processPackets();

        // ✅ Save results to CSV
        saveToCSV(packets);

    // ✅ Ensure visualization is not already running
    cout << "✅ Checking if visualization is already running...\n";
    int vis_check = system("pgrep -f visualize_threats.py > /dev/null");

    if (vis_check != 0) {  // ✅ Only start if not running
        cout << "✅ Launching real-time visualization...\n";
        system("python3 visualize_threats.py &");
    } else {
        cout << "✅ Visualization is already running.\n";
    }

    
        // ✅ Finalize Python at the end
        finalizePython();
    
        


        return 0;
    }
