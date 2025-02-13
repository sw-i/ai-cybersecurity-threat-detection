AI-Powered Cybersecurity Threat Detection System

🚀 Project Overview

This project is an AI-powered real-time cybersecurity threat detection system that:

Captures network traffic using Wireshark's TShark API.

Analyzes packets with machine learning (Random Forest model).

Detects and classifies packets as SAFE or THREAT.

Visualizes real-time network activity using OpenCV.

📂 Project Structure

📂 ai-cybersecurity-threat-detection
│── 📂 src                  # Source code
│   │── packet_sniffer.cpp   # C++ packet capture program
│   │── train_model.py       # Machine Learning model training
│   │── detect_threat.py     # Python function for real-time threat detection
│   │── visualize_threats.py # OpenCV real-time visualization
│── 📂 data
│   │── network_data.csv     # Stored packet data (live or real dataset)
│── 📂 models
│   │── anomaly_detection_model.pkl  # Trained ML model
│── 📂 docs
│   │── README.md            # GitHub documentation
│   │── tutorial_script.md   # YouTube tutorial script
│── .gitignore               # Ignore unnecessary files
│── requirements.txt         # Python dependencies
│── LICENSE                  # Open-source license
│── setup.sh                 # (Optional) Script to install dependencies

🛠️ Installation Guide

Step 1: Clone the Repository

git clone https://github.com/your-username/ai-cybersecurity-threat-detection.git
cd ai-cybersecurity-threat-detection

Step 2: Install Dependencies

Install the required Python packages:

pip3 install -r requirements.txt

Step 3: Install TShark (Wireshark CLI)

You need Wireshark’s TShark installed to capture network packets.

brew install wireshark

(For Linux users: sudo apt install tshark)

Step 4: Compile the C++ Packet Sniffer

g++ src/packet_sniffer.cpp -o packet_sniffer -I/usr/include/python3.9 -lpython3.9

Step 5: Capture Network Traffic

Run the following command to capture live network packets:

sudo ./packet_sniffer

This will save packet data into network_data.csv.

Step 6: Train the Machine Learning Model

Train the ML model on captured network data:

python3 src/train_model.py

This will generate a trained model saved as models/anomaly_detection_model.pkl.

Step 7: Run Real-Time Threat Detection & Visualization

To detect threats in real-time and visualize them:

python3 src/visualize_threats.py

Safe packets → Green ✅

Threat packets → Red ⚠️

Press 'Q' to exit visualization or run sudo pkill -f visualize_threats.py

📊 How It Works

C++ (packet_sniffer.cpp) captures network traffic using Wireshark’s TShark API.

Python (train_model.py) trains an ML model to detect suspicious activity.

C++ calls Python (detect_threat.py) to classify packets in real-time.

Threat results are saved to network_data.csv.

Python (visualize_threats.py) dynamically updates a real-time visualization dashboard.

🎯 Features

✅ Real-time network packet capture
✅ Machine Learning-based anomaly detection
✅ Live OpenCV visualization of network threats
✅ Auto-closing visualization window with 'Q' key
✅ Expandable with more datasets & ML models

🚀 Future Improvements

Train with a larger real-world cybersecurity dataset.

Implement deep learning-based threat detection.

Add email alerts for detected threats.

📜 License

This project is open-source under the MIT License.

🤝 Contributing

Contributions are welcome! Feel free to fork this repository and submit a pull request.

🔥 Built by OMER KILIC
🔥Neural & Wires YouTube Channel 
