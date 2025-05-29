# PIXELSTRIKE 🎮  
*A 1v1 Top-Down Shooter Built on a Custom Embedded System*

## Overview  
PIXELSTRIKE is a real-time, embedded systems video game developed in C++ for a custom-designed PCB using a TI MSPM0 microcontroller. It features responsive joystick-controlled movement, sprite collision, health tracking, and sound effects.

This project was built as part of my final embedded systems coursework at UT Austin, demonstrating low-level programming, hardware-software integration, and real-time game engine logic.

---

## Features  
- 🕹️ **Multi-directional joystick movement** (analog via ADC sampling)  
- 💥 **Sprite collision detection** and hit tracking  
- 🔊 **DAC-based sound generation** for shooting and damage events  
- ⏱️ **Hardware timers & interrupts** for animation and control loops  
- 📺 **LCD rendering** for real-time display of game state  
- 🧠 **Memory-efficient game engine** written in C++  

---

## Hardware Used  
- TI MSPM0 LaunchPad microcontroller  
- Custom-designed PCB (KiCad)  
- ST7735 LCD display  
- Joysticks (analog)  
- Pushbuttons, LEDs, passive buzzer  
- DAC & ADC peripherals
