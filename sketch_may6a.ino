import tkinter as tk
import RPi.GPIO as GPIO

# ---------------------------
# GPIO Setup
# ---------------------------
GPIO.setmode(GPIO.BOARD)

# Define physical pins for RGB LEDs
LED_PINS = {
    "Red": 12,
    "Green": 16,
    "Blue": 18
}

# Set up GPIO pins as output and initialize LOW
for pin in LED_PINS.values():
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, GPIO.LOW)

# Initialize PWM for each LED at 100 Hz
pwm_red = GPIO.PWM(LED_PINS["Red"], 100)
pwm_green = GPIO.PWM(LED_PINS["Green"], 100)
pwm_blue = GPIO.PWM(LED_PINS["Blue"], 100)

# Start PWM with 0% duty cycle
pwm_red.start(0)
pwm_green.start(0)
pwm_blue.start(0)

# ---------------------------
# GUI Setup
# ---------------------------
window = tk.Tk()
window.title("LED Light Intensity Control")
window.geometry("300x300")  # Optional: set window size

# ---------------------------
# LED Control Functions
# ---------------------------
def update_led_intensity():
    """Update LED intensity based on slider values."""
    red_intensity = red_slider.get()
    green_intensity = green_slider.get()
    blue_intensity = blue_slider.get()

    pwm_red.ChangeDutyCycle(red_intensity)
    pwm_green.ChangeDutyCycle(green_intensity)
    pwm_blue.ChangeDutyCycle(blue_intensity)

def exit_program():
    """Stop PWM, cleanup GPIO, and close the GUI."""
    pwm_red.stop()
    pwm_green.stop()
    pwm_blue.stop()
    GPIO.cleanup()
    window.destroy()

# ---------------------------
# GUI Widgets
# ---------------------------
red_slider = tk.Scale(window, from_=0, to=100, orient="horizontal", label="Red Intensity")
red_slider.pack(pady=5)

green_slider = tk.Scale(window, from_=0, to=100, orient="horizontal", label="Green Intensity")
green_slider.pack(pady=5)

blue_slider = tk.Scale(window, from_=0, to=100, orient="horizontal", label="Blue Intensity")
blue_slider.pack(pady=5)

update_button = tk.Button(window, text="Update Intensity", command=update_led_intensity)
update_button.pack(pady=10)

exit_button = tk.Button(window, text="Exit", command=exit_program, bg="red", fg="white")
exit_button.pack(pady=10)

# ---------------------------
# Start GUI Loop
# ---------------------------
window.mainloop()
