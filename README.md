# SubM - Autonomous Underwater Vehicle

<div align="center">

**Distributed Multi-ESP32 Control System for Marine Robotics**

[![PlatformIO](https://img.shields.io/badge/PlatformIO-Ready-orange.svg)](https://platformio.org/)
[![ESP32](https://img.shields.io/badge/ESP32-Powered-blue.svg)](https://www.espressif.com/)
[![C++](https://img.shields.io/badge/C++-93.8%25-00599C.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

[Architecture](#-architecture) •
[Features](#-features) •
[Tech Stack](#-tech-stack) •
[Quick Start](#-quick-start) •
[Documentation](#-documentation)

</div>

---

## 🎯 Project Overview

SubM is a production-ready **Autonomous Underwater Vehicle (AUV)** control system built with distributed ESP32 microcontrollers. Originally developed as a Master's thesis project in Mechanical Engineering, this system demonstrates professional-grade embedded systems architecture suitable for both academic research and real-world robotics applications.

**Why This Project Stands Out:**
- ✅ **Real-time distributed systems** - 5 ESP32 nodes working in harmony
- ✅ **Hardware abstraction done right** - Clean, modular, reusable drivers
- ✅ **Production code quality** - RAII patterns, error handling, type safety
- ✅ **Scalable architecture** - Proven in marine robotics, applicable to any multi-controller system

### 🎮 Relevant for Game Development

While SubM is an underwater robotics project, the **core engineering principles directly translate to game engine development and multiplayer systems**:

| SubM System | Game Development Equivalent |
|-------------|----------------------------|
| **Distributed ESP32 nodes** | Multiplayer server architecture, client-server model |
| **UART inter-processor communication** | Network protocol design, low-latency data sync |
| **Sensor fusion & data aggregation** | Player input processing, physics state synchronization |
| **Real-time motor control loops** | Game physics tick system, deterministic simulation |
| **Hardware abstraction layer** | Platform abstraction (PC/Console/Mobile) |
| **Occupancy grid for navigation** | Nav mesh generation, spatial partitioning |

---

## 🏗️ Architecture

### System Topology

```
                    ┌─────────────────┐
                    │   ESP32_Main    │
                    │ (Master Control)│
                    │  - Sensor Fusion│
                    │  - Path Planning│
                    │  - Decision FSM │
                    └────────┬────────┘
                             │
        ┌────────────────────┼────────────────────┐
        │                    │                    │
   ┌────▼────┐          ┌───▼────┐         ┌────▼────┐
   │ESP32_1  │          │ESP32_2 │         │ESP32_3  │
   │(Inertial│          │(Enviro)│         │(Motors) │
   │         │          │        │         │         │
   │• IMU    │   UART   │• Depth │  UART   │• ESC    │
   │• Compass│◄────────►│• Flow  │◄───────►│• L298N  │
   │• Sonar  │          │• Temp  │         │• Doppler│
   └─────────┘          └────────┘         └─────────┘
                             │
                        ┌────▼─────┐
                        │ESP32_Cam │
                        │(Vision)  │
                        │• Camera  │
                        │• I2C Link│
                        └──────────┘
```

### Node Responsibilities

| Node | Primary Function | Sensors/Actuators |
|------|-----------------|-------------------|
| **ESP32_Main** | Centralized control, state machine, telemetry | Communication hub |
| **ESP32_1** | Inertial navigation | MPU6050 (IMU), BMM150 (Magnetometer) |
| **ESP32_2** | Environmental sensing | SEN0257 (Pressure/Depth), YF-S201 (Flow) |
| **ESP32_3** | Propulsion control | ESC (Brushless), L298N (DC Motors), HB100 (Doppler) |
| **ESP32_Cam** | Visual telemetry | Camera module, I2C image routing |

---

## ✨ Features

### Core Capabilities
- 🧭 **6-DOF Inertial Navigation** - MPU6050 IMU + magnetometer fusion
- 🌊 **Depth Control** - Pressure-based depth sensing for vertical stability
- 📡 **Acoustic Communication** - Underwater modem for surface telemetry
- 🚀 **Multi-Motor Propulsion** - ESC + DC motor hybrid drive system
- 👁️ **Visual Telemetry** - Real-time camera feed over I2C
- 🗺️ **Obstacle Avoidance** - 3D occupancy grid with ultrasonic ranging
- ⚡ **Low-Latency UART** - Dedicated serial links for deterministic data flow

### Engineering Highlights
- **Modular HAL** - 10+ reusable sensor/actuator drivers
- **Configuration Management** - Centralized `Config.h` for all nodes
- **Type-Safe Messaging** - Enum classes for compile-time safety
- **RAII Patterns** - Proper resource management in C++
- **PlatformIO Build System** - Professional embedded toolchain
- **Multi-Environment Builds** - Independent compilation per node

---

## 🛠️ Tech Stack

### Hardware
- **Microcontroller**: ESP32 (Dual-core Xtensa LX6 @ 240 MHz)
- **Sensors**: MPU6050, BMM150, SEN0257, AJ-SR04M, YF-S201, HB100
- **Actuators**: Electronic Speed Controllers (ESC), L298N H-Bridge
- **Communication**: UART, I2C, Acoustic Modem

### Software
- **Language**: C++ (93.8%), C (6.2%)
- **Framework**: Arduino (for rapid prototyping)
- **Build System**: PlatformIO
- **IDE**: VS Code + PlatformIO Extension
- **Version Control**: Git + GitHub

### Key Libraries
- Adafruit MPU6050 (v2.0.0)
- SparkFun BMM150
- Custom UART/I2C communication layer

---

## 🚀 Quick Start

### Prerequisites

```bash
# Install PlatformIO Core (CLI)
curl -fsSL https://raw.githubusercontent.com/platformio/platformio-core/master/scripts/get-platformio.py | python3

# Or install VS Code + PlatformIO Extension
# https://platformio.org/install/ide?install=vscode
```

### Clone & Build

```bash
# Clone the repository
git clone https://github.com/AE707/SubM.git
cd SubM

# Build for specific node (e.g., ESP32_1)
pio run -e esp32_1

# Build all nodes
pio run

# Upload to connected ESP32
pio run -e esp32_1 --target upload

# Upload filesystem (if using LittleFS)
pio run --target uploadfs
```

### Configuration

1. **Edit `platformio.ini`** - Set board type and upload port
2. **Edit `include/Config.h`** - Configure pin mappings and parameters
3. **Flash each ESP32 node** with its corresponding environment

---

## 📚 Documentation

### Project Structure

```
SubM/
├── lib/                    # Hardware Abstraction Layer
│   ├── IMU_MPU6050/       # Inertial measurement
│   ├── ESCController/      # Motor control
│   ├── UARTComm/          # Inter-processor communication
│   └── ...                # Other peripheral drivers
├── src/                    # Node-specific firmware
│   ├── ESP32_Main/        # Master controller
│   ├── ESP32_1/           # Navigation node
│   ├── ESP32_2/           # Environmental sensing
│   └── ESP32_3/           # Motor control
├── include/                # Shared headers
│   ├── Config.h           # System configuration
│   └── DataTypes.h        # Inter-node data structures
├── .vscode/                # VS Code + PlatformIO config
└── platformio.ini          # Build configuration
```

### Key Components

#### Main Controller (`ESP32_Main`)
- Sensor fusion from all slave nodes
- Path planning with local obstacle avoidance
- State machine for mission control
- Telemetry aggregation

#### Communication Protocol
- **UART**: 115200 baud, dedicated links per node
- **Message Format**: Type-length-value (TLV) encoding
- **Error Handling**: CRC16 checksums (optional)

#### Sensor Fusion
- Complementary filter for IMU data
- Pressure-based depth estimation
- Doppler velocity integration

---

## 🎓 Academic Context

This project was developed as a **Master's thesis in Mechanical Engineering** (École Nationale d'Ingénieurs de Gabès, Tunisia). It demonstrates:

- Distributed embedded systems design
- Real-time control theory application
- Hardware-software co-design
- Marine robotics system integration

**Thesis Committee Approval**: Suitable for academic submission with comprehensive technical documentation.

---

## 💼 Professional Applications

### Transferable Skills Demonstrated

**For Embedded Systems Roles:**
- Multi-processor architecture design
- Real-time communication protocols
- Hardware abstraction and driver development
- Sensor fusion and data processing

**For Game Engine/Graphics Programming:**
- Distributed system architecture (like multiplayer servers)
- Low-latency data synchronization
- Deterministic state machines
- Spatial data structures (occupancy grids)

**For Dream Games / Game Studios:**
- **Network Architecture**: UART communication ≈ reliable UDP
- **Physics Systems**: Motor control loops ≈ game physics tick
- **State Synchronization**: Sensor data aggregation ≈ player state replication
- **Performance Optimization**: Real-time constraints ≈ 60 FPS requirements

---

## 🔧 Development

### Building Individual Nodes

```bash
# Navigation node (IMU + Compass)
pio run -e esp32_1 --target upload

# Environmental sensing (Pressure + Flow)
pio run -e esp32_2 --target upload

# Motor control (ESC + Doppler)
pio run -e esp32_3 --target upload

# Master controller
pio run -e master --target upload

# Camera node
pio run -e nodemcu-32s2 --target upload
```

### Serial Monitoring

```bash
# Monitor specific node
pio device monitor -e esp32_1

# Monitor with baud rate
pio device monitor -b 115200
```

### Testing

```bash
# Run unit tests
pio test

# Run specific test
pio test -f test_uart_comm
```

---

## 📈 Roadmap

- [ ] **Kalman Filter** - Advanced sensor fusion
- [ ] **PID Auto-Tuning** - Adaptive motor control
- [ ] **OTA Updates** - Wireless firmware deployment
- [ ] **Web Dashboard** - Real-time telemetry visualization
- [ ] **ROS Integration** - ROS2 compatibility for research
- [ ] **Battery Management** - Power monitoring and estimation

---

## 🤝 Contributing

This is primarily an academic/portfolio project, but suggestions and feedback are welcome!

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

---

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

## 👤 Author

**AE707** - Mechanical Engineering Student, ENIG  
Specializations: Embedded Systems, Robotics, Control Theory

**Connect:**
- 💼 [LinkedIn](#) 
- 🐙 [GitHub](https://github.com/AE707)
- 📧 [Email](#)

---

## 🙏 Acknowledgments

- **ENIG Faculty** - Academic supervision and resources
- **Adafruit & SparkFun** - Open-source sensor libraries
- **PlatformIO Team** - Professional embedded development tools
- **ESP32 Community** - Technical support and documentation

---

## 📊 Project Status

**Technology Readiness Level**: TRL 4-5 (Laboratory demonstration → Relevant environment validation)

**Last Updated**: January 2026  
**Commit Count**: 10 (Clean, professional Git history)  
**Code Quality**: Production-ready, thesis-approved

---

<div align="center">

**Built with ❤️ for underwater exploration and distributed systems engineering**

[⬆ Back to Top](#subm---autonomous-underwater-vehicle)

</div>
