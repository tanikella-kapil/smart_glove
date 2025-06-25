import serial
import pyttsx3

# Replace 'COM3' with your Arduino's actual COM port
ser = serial.Serial('COM7', 9600, timeout=1)

# Initialize TTS engine
tts = pyttsx3.init()
tts.setProperty('rate', 150)  # Speech speed
tts.setProperty('volume', 1.0)  # Max volume

print("👂 Listening to Arduino...")

while True: 
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print("From Arduino:", line)

        if "GESTURE DETECTED:" in line:
            # Extract the gesture name only+-
            gesture = line.split("GESTURE DETECTED:")[1].strip()
            tts.say(gesture)
            tts.runAndWait()
