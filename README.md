# Automated-Employee-Attendance-System-Using-RFID
RFID-based automated employee attendance system using LPC2129 ARM7, EM-18 RFID reader, RTC, LCD, UART, I²C, and Linux for real-time attendance logging.
Automated Employee Attendance System Using RFID

An embedded systems project that automates employee attendance using RFID technology. The system uses an EM-18 RFID reader to identify employees through unique RFID cards, an LPC2129 ARM7 microcontroller to process the data, and an RTC module to record accurate date and time. Attendance status is displayed on a 16×2 LCD, while attendance records are transmitted to a Linux PC via UART for storage and reporting.

Key Features
RFID-based contactless employee identification
LPC2129 ARM7 microcontroller-based processing
Real-time date and time tracking using RTC
16×2 LCD for attendance status and user prompts
UART communication between RFID reader, MCU, and PC
I²C communication between MCU and RTC
Digital attendance data logging on Linux PC
Helps reduce manual errors and proxy attendance
Technologies Used

Embedded C | LPC2129 ARM7 | RFID | EM-18 | RTC | UART | I²C | GPIO | LCD | Linux | GCC | Keil µVision

Project Workflow

RFID Card → EM-18 Reader → LPC2129 → RTC + LCD → UART → Linux PC → Attendance Database

The system is designed as a low-cost, reliable, and scalable attendance solution for offices, educational institutions, and industrial environments.
