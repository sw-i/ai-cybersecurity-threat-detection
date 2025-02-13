import pandas as pd
import cv2
import numpy as np
import matplotlib.pyplot as plt
from collections import Counter
import time

# ✅ Function to update the visualization
def update_visualization():
    threat_history = []

    while True:
        try:
            # ✅ Load network data (latest results)
            df = pd.read_csv("network_data.csv")

            # ✅ Count threats vs. safe packets
            threat_count = df["threat_status"].value_counts().to_dict()
            safe_count = threat_count.get("SAFE", 0)
            threat_count = threat_count.get("THREAT", 0)

            # ✅ Store threat count for timeline plot
            threat_history.append(threat_count)
            if len(threat_history) > 10:  # Keep last 10 readings
                threat_history.pop(0)

            # ✅ Create an empty image for visualization
            img = np.zeros((500, 800, 3), dtype=np.uint8)

            # ✅ Display threat summary
            cv2.putText(img, "Real-Time Cybersecurity Threats", (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
            cv2.putText(img, f"Safe Packets: {safe_count}", (50, 100), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
            cv2.putText(img, f"Threat Packets: {threat_count}", (50, 130), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 0, 255), 2)

            # ✅ Show visualization
            cv2.imshow("Threat Visualization", img)

            # ✅ Close when "Q" is pressed
            key = cv2.waitKey(2000) & 0xFF
            if key == ord("q"):
                print("✅ Closing visualization window...")
                break

        except Exception as e:
            print(f"❌ OpenCV Error: {e}")
            break  # ✅ Exit loop if error occurs

    cv2.destroyAllWindows()
    print("✅ Window closed successfully.")

# ✅ Run visualization
update_visualization()


