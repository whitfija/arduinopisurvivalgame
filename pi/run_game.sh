#!/bin/bash
# nav
cd ~/Documents/4150project/arduinopisurvivalgame/pi/serial2display

# run
python serial2display.py

while true; do
    python serial2display.py

    # failure
    if [ $? -ne 0 ]; then
        echo "Python script exited with a non-zero status. Retrying in 5 seconds..."
        sleep 5
    else
        # success
        break
    fi
done