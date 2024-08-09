## 🗒️ DD Robocon 2024 Robot-2 (Fully Automatic)

### Introduction

Welcome to the repository for Fully Automatic Robot-2, designed specifically for the ABU Robocon 2024 and the Indian national competition DD Robocon 2024. This robot was created to meet the challenges of the "Harvest Day" theme, simulating the tasks of planting rice seedlings and collecting seeds.

### Project Overview

**Robot-2** is engineered to:
1. **Differentiate** between paddy rice (blue or red ball) and empty grain (purple ball) using two Pixy2 cameras and a pan-tilt mechanism.
2. **Collect** the paddy rice.
3. **Store** the collected paddy rice in a designated silo.

The robot performs these tasks autonomously, leveraging advanced algorithms and precise control mechanisms.

### Repository Structure

- **Robot_2/**: Main folder containing the code for both red and blue areas and common functions.
  - **Libraries/**: Libraries used in the project.
  - **Robot_2_Slave/**: Code for the slave microcontroller.
  - **Orientation_Shield/**: Code for the orientation shield.
  - **red_area/**: Functions specific to the red area.
  - **blue_area/**: Functions specific to the blue area.
  - **common_functions/**: Shared functions such as Debugging, TF_Mini, Communication, Pixy_function, PID_Correct_functions, Millies, Silo, Directions, PID_Functions.
- **docs/**: Includes documentation, schematics, and design plans.

### Installation

1. Clone the repository:
    ```sh
    git clone https://github.com/pratikwayal01/Robot-2_DD_Robocon.git
    ```
2. Navigate to the project directory:
    ```sh
    cd Robot-2_DD_Robocon
    ```
3. Open the Arduino IDE and load the `Robot_2.ino` file.
4. Ensure all necessary libraries are installed (see `Libraries` folder).
5. Upload the code to your Arduino board.

### Libraries Used

- **[CytronMotorDriver-master](https://github.com/CytronTechnologies/CytronMotorDriver)**: For controlling the motor drivers.
- **[LSA08](https://github.com/shashank3199/LSA08r)**: Used for line following sensors.
- **[pixy2-master](https://github.com/charmedlabs/pixy2)**: For interfacing with the Pixy2 camera.

Please download and install these libraries via the provided links.

### Usage

To run the robot's main program:
1. Power on the robot.
2. Ensure the Pixy2 cameras are calibrated and connected.
3. Start the main program via the Arduino IDE or directly from the microcontroller.

### Features

- **Autonomous Navigation**: The robot uses a combination of sensors and computer vision to navigate the field and identify targets.
- **Object Differentiation**: Advanced image processing algorithms via Pixy2 cameras to distinguish between paddy rice and empty grains.
- **Collection Mechanism**: Efficient and precise collection system to gather the paddy rice.
- **Storage System**: Secure and organized storage of collected rice in the silo.

### Code Highlights

- **Pixy_function.ino**: Handles the differentiation between paddy rice and empty grain using Pixy2 cameras.
- **Directions.ino**: Manages the autonomous movement and pathfinding of the robot.
- **PID_Correct_functions.ino**: Controls the mechanisms using PID control.
- **silo.ino**: Oversees the storage process in the silo.

### Media

- **[Competition Highlights Video](https://www.ddrobocon.in/index.php/game-video)**
- Robot -2 [Design](https://a360.co/3vybZxy) all credit goes to mechanical Team.

### More Information

For more details about the ABU Robocon 2024 theme, visit:
- [ABU Robocon 2024](https://aburobocon2024.vtv.gov.vn/)
- [DD Robocon 2024](https://www.ddrobocon.in/)


### License

This project is licensed under the MIT License. See the `LICENSE` file for more details.

### Contact

For any queries or further information, please reach out to [Pratik](https://www.linkedin.com/in/pratikwayal/).

---

## 🚀 Journey of Robocon: DD Robocon 2024 🚀

As a programmer, the biggest joy is seeing your code come to life. In robotics, you witness how your code works in real-world scenarios. Seeing your code working is worth having all those sleepless nights and problem-solving troubleshooting days. I had the honor of coding for Robot 2 in DD Robocon 2024, an autonomous robot tasked with reaching Area 3, differentiating between paddy rice (blue or red ball) and empty grain (purple ball), and collecting the paddy rice to store in a silo (basket).

This journey has been incredibly rewarding, not only because of the technical skills I developed but also because of the many non-technical lessons I learned along the way. I learned the importance of teamwork, perseverance, and effective communication. The challenges we faced and the problem-solving required pushed my skills and understanding to new heights. Although our robot did not perform as expected during the competition, the learning journey was incredibly rewarding. The challenges we faced and the problem-solving required pushed my skills and understanding to new heights.

### 🏆 Achievements:

- Stage 1: AIR 5
- Stage 2: AIR 5
- Stage 3 (Finals): AIR 6 in the league stage
- Quarterfinalists
- MathWorks Modeling Award Winner
- Robotics Society Award Winner

Our team's perseverance and innovation led us to these remarkable accomplishments. I am immensely proud of what we achieved together, despite the setbacks. This journey has truly been a testament to hard work, learning, and teamwork.

Here’s to more milestones and groundbreaking achievements! 🚀🤖

## 🌐 Sources

1. [DD Robocon India 2024](https://www.ddrobocon.in/)
2. [Game Video](https://www.ddrobocon.in/index.php/game-video)
3. [Stage 1](https://www.ddrobocon.in/index.php/stage-1-2024)
4. [Economic Times - DD Robocon 2024](https://m.economictimes.com/news/india/dd-robocon-2024-epic-showdown-of-indias-top-engineering-minds/articleshow/111748903.cms)
5. [Times of India - Robocon 2024](https://timesofindia.indiatimes.com/city/delhi/students-from-india-compete-in-robocon-2024-for-the-ultimate-robotics-showdown/articleshow/111738699.cms)
6. [Stage 2](https://www.ddrobocon.in/index.php/stage-4)
