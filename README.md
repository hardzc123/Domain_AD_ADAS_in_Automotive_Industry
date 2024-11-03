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