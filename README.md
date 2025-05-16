# Byte Racers 🚗💥

**Byte Racers** is a 2D racing game designed for the **MSPM0G3507** microcontroller platform, combining real-time embedded programming, hardware interfacing, and arcade-style gameplay. The objective is simple: survive as long as possible by dodging incoming traffic, switching lanes, and adjusting gears—using real hardware inputs, audio feedback, and a graphical LCD.

---

## 🎮 Gameplay Overview

- Navigate your car across **3 lanes** using physical switches.
- Dodge **randomly spawning enemy cars** that scroll across the screen.
- Use a **gear system** to change speed (slow, medium, fast).
- Watch for **LED indicators** and **sound effects** as you play.
- The longer you survive, the higher your **score** (tracked in ticks).

---

## 🧠 Features

- 🔁 **Interrupt-based game loop** (30 Hz tick rate)
- ⚙️ **Gear system** to change car speed
- 🧍 Player vs. 2 AI-controlled traffic cars
- 🔊 **Audio feedback** via DAC
- 💡 **LED toggling** to indicate gear changes and events
- 📺 Real-time rendering to an **ST7735 1.8" TFT LCD**
- 🎲 **Random lane generation** using ADC-based seeding

---

## 🔧 Hardware Overview

### Required Components

| Component            | Purpose                             |
|---------------------|-------------------------------------|
| MSPM0G3507 MCU       | Game engine / logic processing       |
| ST7735 TFT Display   | Visual output (cars, road, score)    |
| Push Buttons         | Gear input and controls              |
| Red/Green/Yellow LEDs| Event indicators                    |
| DAC0 + Speaker       | Sound playback (ignition, crash)     |
| TimerG0 & TimerG12   | Handle ticks & enemy logic           |
| Power Supply         | USB or 3.3V external                 |

### GPIO Pin Mapping

| Signal      | Pin     |
|-------------|---------|
| Switches    | PA8, PA17, PA18, PA31 |
| LEDs        | PA26 (Red), PA27 (Green), PA28 (Yellow) |
| TFT Display | SPI (MOSI, SCLK, CS, DC, RST) |
| DAC Output  | DAC0 (via DAC5) |
| ADC Input   | PB18 (used for RNG seed) |

---

## 🧩 Code Structure

| File           | Description                                                                 |
|----------------|-----------------------------------------------------------------------------|
| `Lab9Main.c`   | Main game loop, rendering, interrupt handlers                               |
| `LED.c`        | Controls LED output on GPIO                                                 |
| `Sound.c`      | Plays PCM audio through DAC                                                 |
| `Switch.c`     | Initializes and polls button states                                         |
| `Random.h`     | RNG engine based on a linear congruential generator                         |
| `SmallFont.c`  | Small bitmap font for score display                                         |

---

## 📦 Gameplay Logic

- Two enemy cars (`enemyX`, `enemy2X`) move from right to left on fixed lanes.
- Upon moving off-screen, they respawn in new lanes using `Random()` with lane collision avoidance.
- `gear` variable controls game speed: 2, 5, or 8 pixels/frame.
- Player score is stored in `survivalTicks`, incremented every tick (30 Hz).
- LEDs blink on events, and the DAC plays sounds using `Sound_Shoot()`, `Sound_Killed()`, and others.

---

## 🔌 Hardware Design (PCB)

A custom PCB was designed using **KiCad** to support all Byte Racers peripherals and interfaces.

### PCB Highlights

- Connects MSPM0 LaunchPad to:
  - ST7735 LCD via SPI
  - Push buttons for lane/gear input
  - Onboard RGB LEDs
  - DAC output (to amp or speaker)
- Designed as a **2-layer board** for ease of routing
- Silkscreen labels for debug and I/O headers
- Includes decoupling caps and DAC-ready analog stage
- Powered via USB or 3.3V LDO regulator

> ✅ Ideal for permanent arcade setups or demo day use.

---

## 🛠️ Installation & Setup

1. Flash `Lab9Main.c` to your MSPM0 using Code Composer Studio.
2. Connect your display, buttons, LEDs, and speaker to the board or PCB.
3. Open the Serial Monitor (optional for debug).
4. Press a button to begin — shift gears and dodge traffic!

---

## 🧪 Test Modes

- `main3()` – Tests LEDs and switch inputs
- `main4()` – Tests DAC sound playback
- `main()` – Full game

Ensure only one `main()` variant is active during build.

---

## 🚀 Future Improvements

- Game over screen + restart flow
- OLED or score-saving via EEPROM
- Pause functionality
- Wireless high-score leaderboard via UART or Wi-Fi

---

## 📄 License

MIT License  
Free to modify, extend, and integrate in your embedded systems portfolio.

---

## 👤 Author

Created by Taha Haris and Neil Agarwal 
Part of the ECE319K Lab Series  
KiCad project: `tmh3834.kicad_pro`

---

*Byte Racers combines arcade-style fun with real-time embedded systems. Built from the silicon up.*  
