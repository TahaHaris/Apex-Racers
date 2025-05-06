Byte Racers: Embedded Car Racing Game
Byte Racers is a fast-paced, horizontally scrolling racing game built entirely in C for the MSPM0 microcontroller platform, rendered on a 128x160 ST7735 TFT LCD. Designed as a standalone embedded systems project, it demonstrates real-time input handling, direct hardware control, and efficient graphics rendering — all without an operating system or external libraries.

🏎️ Gameplay Overview
Players steer a car using a slide potentiometer, shift gears using push-buttons, and avoid oncoming enemy vehicles as the game progressively speeds up. A SysTick-based timer tracks survival time, which serves as the player’s score. Gameplay ends upon collision, triggering a crash animation, a sound effect, and a game-over screen.

🔧 Core Features
🎮 Real-Time Controls

Analog steering via potentiometer (ADC)

Gear shifting via digital button inputs (GPIO)

Game logic driven by timer interrupts (SysTick, TimerG12)

📺 Graphics

Bitmap sprite rendering with transparency

Optimized partial redraws for flicker-free performance

Bilingual start screen (English / Español)

🔊 Sound

Piezo speaker output for gear shifts and collisions

📐 Collision Detection

Boundary-based sprite collision handling for responsive gameplay

⚙️ Technologies & Concepts
MSPM0 microcontroller programming in bare-metal C

Direct register access for ADC, GPIO, SPI, timers, and interrupts

Fixed-point math for performance on constrained hardware

Modular architecture with clean separation of logic, input, graphics, and sound

No OS, no libraries — just raw embedded programming

🎯 Project Purpose
Byte Racers isn’t just a game — it's a hands-on showcase of embedded systems engineering. It demonstrates low-level hardware interaction, real-time event handling, and graphical performance optimization on a memory- and speed-constrained platform. Ideal for students, educators, or hobbyists exploring microcontroller capabilities in a fun and visual way.

