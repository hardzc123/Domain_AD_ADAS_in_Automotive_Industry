# ADAS_in_Automotive_Industry
This repo illustrates how ADAS project becomes succesful with AI and automotive-industry regulations

## Perception

Criterion for automation: OEDR Object and Event Detection and Response

What is perception: two things: identification and understanding motion -> to inform out driving decisions

Goals for perception: 
1. Static objects: 
    - road and lane markings 
    - curbs 
    - traffic lights
    - road signs
    - construction signs, obstruction
2. dynamic objects:
    - vehicles (4 wheels, 2 wheels)
    - pedestrians
3. Ego localization: (data from GPS, IMU, odometry sensors)
    - Position
    - Velocity, acceleration
    - orientation, angular motion

Challenges to perception:
- robust detection and segmentation
- sensor uncertainty
- occulusion, reflection
- illumination, lens flare
- weather, precipitation (radar and lidar are immune to different weather conditions)


## Hardware setup 
| reference: http://wavelab.uwaterloo.ca/sharedata/ME597/ME597_Lecture_Slides/ME597-4-Measurement.pdf

1. Sensors (exterocpetive)
    - carema (comparison metrics: resolution, field of view, dynamic range, focal length, depth of field, frame rate)
    - stereo camera (not common)
    - lidar (comparison metrics: number of beams (sources, 8, 16, 32, 64), points per second, rotation rate, detection range, field of view, emerging high-resolution, solid-state LIDAR.)( by measuring the amount of returned light and time of flight of the beam, both an intensity and range to the reflecting object can be estimated )
    - radar (radio detection and ranging) (robust object detection and relative speed estimation ) (Comparison metrics: detection range, field of view, position and speed accuracy , WFOV short range V.S. NFOV long range)
    - ultrasonic (short-range all-weather distance measure, low-cosst, immune to weather) (for parking scenario) (comparison metrics: range, FOV, Cost)
2. Sensors (proprioceptive)
   - GNSS Global navigation satellite systems: (such as GPS) (Direct measure of ego vehicle states: **position, velocity**) (varying accuracies: RTK, PPP, DGPS)
   - IMU inertial measurement units: (angular rotation rate, acceleration)
   - GNSS + IMU: (measure heading)
   - Wheel odometry: (tracks wheel velocities and orientation) (used to calculate overall speed and orientation of the car, and help speed accuracy and position drift) 
3. Computeing hardware
   - function: (take in all sensor data, computes action and output action) (Drive PX/AGX, Mobileeye EyeQ)
   - different realization: GPU(graph processing unit), FPGA(field programmable gate array), ASIC(application specific integrated chip)
   - Synchronization: (synchronize different modules and provide a common clock) (GPS can be a reference clock, because it relies on extremely accurate timing to function )


## GNSS / IMU
SwiftNav Platform Runable:

- GNSS Receiver -> GNSS Measurement -> GNSS Engine ->
- Correction Provider (Skylark Cloud Correction Service) -> GNSS Correction -> GNSS Engine -> PTV data (Position, Velocity, Time) -> Fution Engine ->
- Vehicle Sensors (IMU, Wheel Odometry) -> Fusion Engine -> PVAT data  ( Position, Velocity, Attitude and Time)

for GNSS Engine
- Observation: Incoming data (i.e. observations, ephemerides and corrections) can be provided in RTCM v3, SBP or
UBX formats. Output data can be generated in either SBP or NMEA 0183 formats.
  - RTCM v3:
  - SBP
  - UBX
  - NMEA 0183
- Correction: The GNSS Engine is capable of receiving correction data in either Observation State Representation
(OSR) or State Space Representation (SSR) formats.


The Fusion Engine needs to perform an alignment procedure before it can provide positioning
assistance to the system. The alignment process will begin once the following conditions are met


The minimum vehicle sensor input required by the Fusion Engine is a single 6 DoF IMU. The optional
Wheel Odometry input can be used to constrain error growth when operating in pure **dead
reckoning** mode, e.g. when driving through tunnels. Wheel Odometry input may be provided as
either an on-ground speed value (using MSG_ODOMETRY) or as a number of wheel ticks (using
MSG_WHEELTICK).
- Dead Reckoning (DR) is a navigation technique used to estimate the current position of an object (such as a vehicle or a person) based on a previously known position and estimated movements over time. This technique relies on continuously updated data about direction, speed, time, and sometimes altitude or depth to calculate the current position without needing to rely on external signals like GPS.

Key Components of Dead Reckoning:

	1.	Starting Point: Known initial position.
	2.	Direction: The direction of movement, often provided by a compass or gyroscope.
	3.	Speed/Velocity: The speed or velocity of movement, which can be obtained from speedometers or accelerometers.
	4.	Elapsed Time: The amount of time that has passed since the last known position.

How Dead Reckoning Works:

In dead reckoning, the current position is calculated by taking the last known position and adjusting it based on the distance traveled and direction since that point. This adjustment is repeated continuously to keep updating the current position estimate.

For example:

	1.	A vehicle starts at a known position.
	2.	Based on the vehicle’s direction, speed, and time elapsed, the system estimates the new position by calculating where the vehicle should be if it traveled in that direction at that speed for that period.

Applications:

Dead reckoning is commonly used in:

	•	Marine Navigation: Ships use dead reckoning when they cannot get GPS signals, such as in fjords or near tall structures that block signals.
	•	Aviation: Aircraft use dead reckoning as a backup or when flying over regions where GPS or other navigation signals are unavailable.
	•	Automotive and Robotics: Dead reckoning is used in autonomous vehicles, drones, and robots as part of their navigation systems, especially in environments with weak or no GPS signals, like tunnels or indoor spaces.
	•	Pedestrian Navigation: It can be used in smartphones and wearables to provide position tracking when GPS signals are unavailable, such as inside buildings.

Limitations:

	1.	Accumulated Error: Small errors in measuring speed, direction, or time can accumulate over time, leading to significant inaccuracies.
	2.	Lack of External Correction: Since dead reckoning doesn’t use external signals (like GPS) for correction, errors can grow over distance and time.
	3.	Dependence on Sensor Accuracy: The technique relies heavily on the accuracy of onboard sensors, like accelerometers, gyroscopes, and magnetometers.

Enhancing Dead Reckoning:

Dead reckoning is often combined with other methods to improve accuracy, such as:

	•	GPS (when available): Dead reckoning can fill gaps when GPS is temporarily lost.
	•	IMU (Inertial Measurement Unit): Using accelerometers and gyroscopes to improve movement tracking.
	•	SLAM (Simultaneous Localization and Mapping) in robotics: Dead reckoning data is combined with sensor data like lidar or cameras to reduce errors and maintain accuracy in mapping and navigation.

In summary, dead reckoning is an effective and useful method for estimating location in situations where GPS is unavailable or unreliable, although it is susceptible to accumulated error without external corrections.


----

With the default configuration, alignment should typically complete within a distance of 20 to 50 m
if **sky visibility ** remains good during the initialisation phase.

The Fast Start feature allows the state of the Fusion Engine to be persistently stored while Starling is
not active. This enables the Fusion Engine to enter an aligned state immediately after Starling is
started without needing to follow the alignment process outlined above.

These are referred to as endpoints. Each endpoint can be configured to use a given protocol. The
supported protocols are as follows:
● ixcom: Binary protocol supported by products from iMAR Navigation & Control; can be
used for IMU and wheel tick input only.
● nmea: NMEA 0183 ASCII sentences as defined in [NMEA]; can be used for position output
only.
● ntrip: Networked Transport of RTCM via Internet Protocol; can be used for correction
input only.
● rtcm: Version 3.2 of the RTCM standard as defined in [RTCM3]; can be used for GNSS
measurement and correction input only.
● sbp: Swift Binary Protocol as defined in [SBP]; can be used for all inputs and outputs.
● ubx: u-blox UBX Protocol (v27.11 or higher) as defined in [F9P]; can be used for GNSS and
IMU input only

- DR（Dead Reckoning）： 

## Senarios and requirements for hardware (sensors) and software
| reference: https://repository.tudelft.nl/file/File_ef45c131-fb7f-409a-a275-1f3bff100fb5?preview=1

1. Highway: 3 kinds of maneuvers (emergency stop, maintain speed, lane change)
   - emergency stop longitudinal coverage: 110 meter (assuming dring at 120 kph) -> sensor requirements 150 ~ 200m
   - emergency stop lateral coverage: 3.7 meter (adjacent lane)
   - maintain speed longitudinal coverage: 100 meter (assuming relative speed less than 30kph) -> sensor requirement 65 ~ 100m
   - maintain speed lateral coveragse: 3.7m for adjacent lane and merging vehicle
   - lane change longitudinal coverage: front and back
   - lane change lateral coverage: need wider sensing,
2. Urban analysis: 
   - Emergency stop, maintain speed, lane change: similar to highway analysis, but short range requirements
   - overtaking: 
   - turning, crossing at intersections
   - passing roundabouts: need wider FOV due to the shape of roundabout
3. -> sensor coverage ananysis, costs and blind spot, hardware setup
4. -> architecture of typical self-driving software system:
   1. Environment perception: ego vehicle localization + Object detection (including tracking and prediction)
   2. environment mapping: occupancy grid map, localization map, detailed road map (HD map)
   3. motion planning: mission planner -> behavior planning (rule-based or ML ) -> local planner (path planning: optimization-based or ML)
   4. controller: throttle percetange, brake percentage, steering angle
   5. system supervisor: hardware supervisor (from sensor outputs), software supervisor (from environment perception, environment mapping, motion planning, control)


## Benchmark
KITTI: 

200 Traninig and 200 test image pairs at a resolution of half a megapixel

difficulties include non0 lumbers and reflecting surfaces, different material and different lighting conditions

bounding box: bisible ocuuluded or trancated


## Common Math 
common parameters:
1. aggressive deceleration = 5 m/s^2
2. comfortable deceleration = 2 m / 2^2
3. stopping distance: d = v^2 / 2a

## Regulations or Norm
1. GDPR
2. ISO 26262
3. ASPICE

## Papers
### A Survey on Multimodal Large Language Models for Autonomous Driving （2023）
https://arxiv.org/abs/2311.12320



 ### Drive Like a Human: Rethinking Autonomous Driving with Large Language Models (2023)
https://arxiv.org/abs/2307.07162


### Distilling the Knowledge in a Neural Network (2015)
https://arxiv.org/abs/1503.02531

### CaspNet

### UniAD

### Attention is all you need

### Wayformer



 GPT-Driver [110] reformulated motion planning as a language modeling problem and utilized LLM
to describe highly precise trajectory coordinates and its internal decision-making process in natural language in motion planning. SurrealDriver [68] simulated MLLM-based
generative driver agents that can perceive complex traffic
scenarios and generate corresponding driving maneuvers.


DriveMLM: Aligning Multi-Modal Large Language Models with Behavioral Planning States for Autonomous Driving (2023) https://arxiv.org/abs/2312.09245

DriveVLM: The Convergence of Vision and Language Models for Autonomous Driving (2024) https://arxiv.org/abs/2402.12289

“Large Language Models for Autonomous Driving (LLM4AD): Concept, Benchmark, Simulation, and Real-Vehicle Experiment” （2024）https://arxiv.org/abs/2410.15281


“LanguageMPC: Large Language Models as Decision Makers for Autonomous Driving” （2023）https://arxiv.org/abs/2310.03026


The Waymo Open Sim Agents Challenge
https://arxiv.org/abs/2305.12032

End-to-end Autonomous Driving: Challenges and Frontiers
https://arxiv.org/abs/2306.16927

End-to-End Autonomous Driving in CARLA: A Survey
https://ieeexplore.ieee.org/document/10704612


https://www.jiqizhixin.com/articles/2023-12-18-4


Planning: UniAD, DIPP, DTPP, Para-Drive, VAD, QCNet, Attention is All You Need, Wayformer

3D Reconstruction: SCube

![image](https://github.com/user-attachments/assets/ebee81bf-c095-40c8-b6db-4441b824e22e)

nGPT

Foundation Reinforcement Learning: towards Embodied Generalist Agents with Foundation Prior Assistance


## Open Source Tool
HighywayEnv: A minimalist environment for decision-making in autonomous driving
https://github.com/Farama-Foundation/HighwayEnv


Gymnasium: An API standard for single-agent reinforcement learning environments, with popular reference environments and related utilities (formerly Gym) https://github.com/Farama-Foundation/Gymnasium


## Open Source Data