import os  # ✅ Set before importing NumPy
os.environ["OMP_NUM_THREADS"] = "1"
os.environ["OPENBLAS_NUM_THREADS"] = "1"
os.environ["MKL_NUM_THREADS"] = "1"
os.environ["VECLIB_MAXIMUM_THREADS"] = "1"
os.environ["NUMEXPR_NUM_THREADS"] = "1"



import pandas as pd #  Loads and processes the network packet data from network_data.csv
import joblib #Saves the trained model so you can use it later.

import numpy as np
from sklearn.model_selection import train_test_split # Splits data into training and testing sets.
from sklearn.ensemble import RandomForestClassifier # The machine learning model used to classify normal vs. anomaly packets.
from sklearn.preprocessing import LabelEncoder
from sklearn.metrics import accuracy_score ##Measures how well the model performs.


# ✅ Function to Predict Threats
def predict_threat(protocol, packet_size):
    try:
        # ✅ Load the trained model
        model = joblib.load("anomaly_detection_model.pkl")
        feature_data = pd.DataFrame([[protocol, packet_size]], columns=['protocol', 'packet_size'])
        prediction = model.predict(feature_data)
        return int(prediction[0])  # ✅ 1 = Threat, 0 = Safe
    except Exception as e:
        print(f"❌ Error in prediction: {e}")
        return -1  # ❌ Error

#Load dataset
df = pd.read_csv("network_data.csv")
#Reads the CSV file containing packet capture data (exported from your C++ program).
#df (DataFrame) now holds the structured packet data.

#Drop rows with missing values
df.dropna(inplace=True)

#convert categorical 'protocol' to numerical using label Encoding
encoder = LabelEncoder()
df['protocol'] = encoder.fit_transform(df['protocol'])

# Ensure 'packet_size' is numeric
df['packet_size'] = pd.to_numeric(df['packet_size'], errors='coerce')

# Drop rows where 'packet_size' is NaN after conversion
df.dropna(subset=['packet_size'], inplace=True)

#Define features and labels (assuming anomalies are larger packets)

X = df[['protocol', 'packet_size']]
y = (df['packet_size'] > 500).astype(int)  # Label 1 = Anomaly, 0 = Normal

# Split data
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

# Train model
model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X_train, y_train)

# Test the model
y_pred = model.predict(X_test)
accuracy = accuracy_score(y_test, y_pred)

# ✅ Save trained model **(CORRECT NAME)**
joblib.dump(model, "anomaly_detection_model.pkl")
print("✅ Model Training Completed")
print(f"📊 Model Accuracy: {accuracy:.2f}")
print("💾 Model saved as anomaly_detection_model.pkl")



# Print results
print(f"✅ Model Training Completed")
print(f"📊 Model Accuracy: {accuracy:.2f}")

# Save the trained model for future use

joblib.dump(model, "anomaly_detection_model.pkl")
print("💾 Model saved as anomaly_detection_model.pkl")
