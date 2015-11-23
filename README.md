# ElectromagneticsApp
Final Project for my Electromagnetics class, it is an app to help high school students learn E&amp;M concepts better.

The actual full app has two projects in it: the UI as defined by XAML and C#, and the "game" portion written using DirectX and DirectXTK.  This repository contains only the DirectX project.

This game is meant to help students more intuitively grasp the idea of Lorentz's force, which is the force exerted on a charged particle by both an electric field and a magnetic field.  The electric field gradient is visible in-game, as you can see below:

![screenshot of the game](/Images/game_snapshot.jpg)

However, because magnetic fields exert force based on a different principle (it depends on the velocity of the particle), it cannot be simply drawn to the screen and added to the electric field vectors - rather, it is calculated in real time, as the particle is moving.

The electric field is createad by the positive red charges and the negative blue charges, meant to signify the approximate strength of an electron.  The magnetic field (not shown in-game) is created by infinitely long wires with current flowing through them to the right.

In the full version of the app, there is also a section that describes the equations used to calculate the electric and magnetic fields, as well as the resultant force that gets exerted on the particle.  This section is meant to form the final link between the concepts that people use in real-time in the game, and the equations and math that are seen in class.
