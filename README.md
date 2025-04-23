# AI-Powered Cybersecurity Threat Detection Dashboard 🛡️

A real-time network security monitoring dashboard that uses machine learning to detect potential threats in network traffic. The system captures network packets, analyzes them using a trained ML model, and displays results in a modern, interactive web interface.

## 🌟 Features

- **Real-time Network Monitoring**: Live packet capture and analysis
- **ML-based Threat Detection**: Uses Random Forest classifier to identify potential threats
- **Interactive Dashboard**: Modern UI with real-time updates
- **Visual Analytics**: 
  - Live traffic visualization
  - Threat vs. Safe packet statistics
  - Packet details table
  - Real-time graph updates
- **Packet Analysis**:
  - Source/Destination IP tracking
  - Protocol analysis
  - Packet size monitoring
  - Threat classification

## 🔧 Prerequisites

- Python 3.8+
- TShark (Wireshark CLI)
- sudo/root privileges (for packet capture)

## 📦 Installation

1. **Clone the Repository**:
```bash
git clone https://github.com/yourusername/ai-cybersecurity-threat-detection.git
cd ai-cybersecurity-threat-detection
```

2. **Install System Dependencies**:
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install -y tshark python3-pip python3-dev

# Fedora
sudo dnf install wireshark python3-pip python3-devel

# macOS
brew install wireshark
```

3. **Install Python Dependencies**:
```bash
sudo pip3 install -r requirements.txt
```

## 🚀 Usage

1. **Train the ML Model**:
```bash
python3 train_model.py
```

2. **Start the Dashboard**:
```bash
sudo python3 app.py
```

3. **Access the Dashboard**:
- Open your web browser
- Navigate to: `http://localhost:5000`
- Click "Start Capture" to begin monitoring

## 📊 Dashboard Features

### 1. Main Statistics
- Total Packets Analyzed
- Threats Detected
- Safe Packets Count

### 2. Real-time Visualizations
- Live Traffic Graph
- Threat vs Safe Packet Ratio
- Protocol Distribution

### 3. Packet Details Table
- Timestamp
- Source IP
- Destination IP
- Protocol
- Packet Size
- Threat Status

## 🔍 How It Works

1. **Packet Capture**:
   - Uses TShark to capture network packets
   - Monitors specified network interface
   - Captures key packet information

2. **Threat Analysis**:
   - ML model analyzes each packet
   - Features: protocol type, packet size
   - Classifications: SAFE or THREAT

3. **Real-time Updates**:
   - WebSocket connections for live updates
   - Dynamic UI updates
   - Real-time graph rendering

## 🛠️ Technical Architecture

```
ai-cybersecurity-threat-detection/
├── app.py                  # Flask application & main logic
├── train_model.py         # ML model training
├── requirements.txt       # Python dependencies
├── templates/            
│   └── index.html        # Dashboard UI template
├── static/               
│   └── css/             # Custom styling
└── models/              
    └── *.pkl            # Trained ML models
```

## 🔐 Security Considerations

1. **Privileges**:
   - Requires sudo for packet capture
   - Minimal necessary permissions

2. **Data Handling**:
   - Local processing only
   - No external data transmission
   - Temporary packet storage

3. **Network Impact**:
   - Passive monitoring only
   - No packet injection
   - Minimal performance impact

## 🐛 Troubleshooting

1. **Permission Issues**:
```bash
# If you get permission errors
sudo chmod +x packet_sniffer
sudo setcap cap_net_raw,cap_net_admin=eip /usr/bin/python3
```

2. **Port Conflicts**:
```bash
# If port 5000 is in use
sudo python3 app.py --port=5001
```

3. **TShark Issues**:
```bash
# Verify TShark installation
which tshark
# List available interfaces
sudo tshark -D
```

## 📝 Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Wireshark/TShark team
- Flask framework
- scikit-learn
- Socket.IO

## 📧 Contact

Your Name - your.email@example.com
Project Link: [https://github.com/yourusername/ai-cybersecurity-threat-detection](https://github.com/yourusername/ai-cybersecurity-threat-detection)

## ⚠️ Disclaimer

This tool is for educational and defensive security purposes only. Users are responsible for complying with applicable laws and regulations regarding network monitoring and security testing.

🔥 Built by OMER KILIC
🔥Neural & Wires YouTube Channel 
