🏙️ 3D City - OpenGL Simulation
A realistic 3D city visualization built with OpenGL and C++ using the GLUT framework. This project features animated buildings, moving vehicles, dynamic lighting, and interactive camera controls.
✨ Features

16 3D Buildings with various heights and realistic window details
Animated Car moving on city roads with rotating wheels
Dynamic Sun with rotating animation and realistic lighting effects
Road System with main road and yellow lane markings
Real-time 3D Lighting and shadows using OpenGL
Interactive Camera with full control via mouse and keyboard
Smooth Animation running at 60 FPS

🎮 Controls
Keyboard:

W - Move camera forward
S - Move camera backward
A - Move camera left
D - Move camera right
Q - Move camera up
E - Move camera down
ESC - Exit application

Mouse:

Left Click + Drag - Rotate camera view

🛠️ Requirements

macOS (10.12 or later)
Xcode (12.0 or later)
OpenGL.framework
GLUT.framework
C++11 or higher

📦 Installation
Clone the Repository:
bashgit clone https://github.com/YourUsername/3D-City-OpenGL.git
cd 3D-City-OpenGL
Open in Xcode:

Create a new Command Line Tool project in Xcode
Copy the main.cpp file into your project

Add Frameworks:

Select your project in the navigator
Go to Build Phases → Link Binary With Libraries
Click + and add OpenGL.framework and GLUT.framework

Fix Code Signing (if needed):

Go to Build Settings
Search for Code Signing Identity
Set to Sign to Run Locally or -

Build and Run:

Press Command+R or click the Run button

🎨 Technical Details
Graphics Components:

Buildings: Custom cube geometry with procedural window generation
Lighting: OpenGL GL_LIGHT0 with ambient and diffuse properties
Materials: GL_COLOR_MATERIAL for realistic surface rendering
Camera: Custom camera system with rotation and translation

Animation System:

Timer-based rendering at 60 FPS using glutTimerFunc()
Car movement with linear translation along Z-axis
Sun rotation with continuous animation around X-axis

🚀 Future Enhancements

Add more vehicle types and traffic simulation
Implement street lights for night scenes
Create day/night cycle with sky color changes
Add textured buildings for more realism
Include trees and parks
Add animated pedestrians
Multiple camera modes (free, follow, bird's eye)
Collision detection system

🐛 Troubleshooting
Code Signing Error:
If you get empty code signing identity error, go to Build Settings → Code Signing Identity → Set to - and Code Signing Required → Set to No
Frameworks Not Found:
Make sure both OpenGL.framework and GLUT.framework are added in Target → Build Phases → Link Binary With Libraries
Black Screen:
Check that lighting is enabled, camera position is correct, and buildings are initialized in the code
📝 License
This project is open source and available under the MIT License.
👨‍💻 Author
Created with OpenGL, C++, and GLUT framework for macOS/Xcode
🙏 Acknowledgments

OpenGL Documentation
GLUT Framework
Xcode Development Tools
