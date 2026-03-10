# Autonomous Line Following Robot

Hi! I wanted to make a Line Following Robot(LFR) and I visited some shops and online marketplaces but I couldn't find a good, fast, compact and accurate robot with a reasonable price. 
So, I created a LFR from scratch including the PCBs for main board and sensor array for the hardware part and code in 5 separate files.
Now I will explain Components, Wiring, Coding, and sensor array separately. 

![Corner_View](3D%20assembly/exports/View%203.JPG)

|||
| :---: | :---: |
| ![Top_view](3D%20assembly/exports/View%202.JPG) | ![Back_View](3D%20assembly/exports/Top%20View.JPG) |

# How to assemble and Opperate this LFR

**1. Hardware Assembly :** To Use this robot first you need to get the PCBs printed and then solder the components to them and then attach these to the chasis. Now plug and connect everything into its place and then you can move to software part.

**2. Uploading the Code :** Now connect Raspberry Pi Pico to your computer and open the **LFR_Code.ino** file and upload that to the Pico.

**3. Tuning the Constants :** Place the robot on a Black line with a White Background and adjust the Kp and Kd values such that the robot stops wobbling and runs smoothly.

**4. Ready to Race :** Now the robot is ready, You just need to turn it on and Race.

# Components

I've decided the components based on affordability, speed, availability and ease of use.
Starting with the micro controller I've selected **Raspberry Pi Pico RP2040** because it has much more processing power than Arduino nano and I've not selected ESP 32 because I wanted to make the robot completely offline and autonomous and for motors I've selected **600rpm 6v N20 motors with encoders** for fast speed and high torque to drive these motors I've chosen **TB6612FNG** motor driver because it has low voltage drop and also it is way lighter than L298N. I've used decided to use a 2S Li-Po battery which is about 7.4v which can power the motors with ease and to power Pico I'd use a step down buck converter to convert these 7.4v into 5v so we don't damage the Pico to charge the battery I'd use a 2S charger and for the sensors I've designed a custom sensor array.

##  PCB and Connections

To talk about the connections, I'd Start with the Power connections. The battery provides 7.4v which goes to VMOT pin of motor driver and buck converter. the buck converter then outputs 5v which goes to VSYS on Pico. Now we have 3 voltages. i.e. 7.4v, 5v and 3.3v. now the 3.3v goes to VCC and STBY pin of TB6612FNG and VCC pin on Sensor Array. 
Now lets talk about the Data and Logic Signals. The GPIO pins from 0 to 18 will be connected to sensor array and GPIO pins 19,20, 21, 22, 26, 27 will be connected to PWMA, AIN1, AIN2, PWMB, BIN1 and BIN2 respectively.
At the end the AO1,  AO2 and BO1, BO2 will be connected to left and right motors respectively.
|Schematics|Tracks|
| :---: | :---: |
| ![schemetics](PCB/Images/Schematics.JPG) | ![Tracks](PCB/Images/Tracks.JPG) |

[![3D](PCB/Images/3D.JPG)](PCB/PCB.glb)


## Custom Built Sensor Array

Now for the most difficult problem that I've faced in this project. I wanted to get analog sensor readings but Raspberry Pi Pico had only 3 analog pins. So I could add a Multiplexer chip which would make the PCB bulky. So I designed a workaround using an RC discharge Circuit.
Instead of reading analog voltages, I paired 16 TCRT5000 sensors with 10nF capacitors and 220-Ohm Resistors. This converts the analog voltage signal to a digital timing signal.
**Working:** The pico sends a brief signal to charge all 16 capacitors. Then it acts as a high-speed stopwatch to measure how fast each capacitors discharges.
 - If the sensor detects **white surface**, the capacitor discharges **very fast**
 - If the sensor detects **black surface**, the capacitor discharges **slowly**
By doing this, I was able to read 16 analog sensors on 16 digital pins.
To make the array even better, I also integrated two SPDT micro limit switch to use as bump sensors on left and right corners of the PCB. 

|Schematics|Tracks|
| :---: | :---: |
| ![schemetics](Sensor%20Array/Images/Schematics.JPG) | ![Tracks](Sensor%20Array/Images/Tracks.JPG) |

[![3D](Sensor%20Array/Images//3D.JPG)](Sensor%20Array/Sensor%20Array.glb)


# Bill of Materials (BOM)
After doing my research, the most affordable components I've got are as follows,

| Component | Quantity | Est. Cost (USD) | Purchase Links | 
| :--- | :---: | :--- | :--- | 
| **Custom PCBs (JLCPCB)** | 2 Sets | $15.00 | https://jlcpcb.com/quote | 
| **Raspberry Pi Pico** | 1 | $5.00 | https://ln.run/yanB3 | 
| **TCRT5000 Transceivers** | 16 | $4.00 | https://ln.run/hACwF | 
| **SMD Passives (0805)** | 32 | $2.00 | https://ln.run/qddHJ | 
| **SPDT Limit Switches** | 2 | $1.00 | https://ln.run/QSFtx | 
| **TB6612FNG Module** | 1 | $3.00 | https://ln.run/ssqYa | 
| **6V N20 Motors (600 RPM)** | 4 | $50.00 | https://ln.run/JM7nX | 
| **N20 Wheels & Brackets** | 4 | $6.00 | https://ln.run/CkKDZ ---- https://ln.run/MqKmx | 
| **2S Battery (7.4V)** | 1 | $3.00 | https://ln.run/iZsS- | 
| **Power Modules** | 2 | $2.00 | https://ln.run/E-0I9 ---- https://ln.run/bBDg- | 
| **Misc. Hardware** | 1 | $5.00 | N/A | 
| **Total Build Cost:** |  | **~$96.00 USD** |

Because I designed the electronics to use standard, readily available modules, The robot is highly modular. If a motor driver or battery charger ever burns out during a competition, I can just unplug it and swap in a $3 replacement without having to desolder or rebuild the entire robot.

