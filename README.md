# NXUpdateTracker
<p align="center">
  <img src="/icon.jpg" alt="NXUpdateTracker icon">
  <br><br>
  A local HTML page that helps you track the version numbers of [Switch] homebrew applications
</p>

# Installation Guide
- STEP 1: Download the .zip file
- STEP 2: Extract the .zip and copy its contents inside the root of your SD card
- STEP 3: To use all the functions of the app, you need to modify `/switch/NXUpdateTracker/githubInfo.ini`. Go to [Usage Guide](https://github.com/F-l-a/NXUpdateTracker#usageguide)

# Usage Guide
Set the app up following the steps [here](https://github.com/F-l-a/NXUpdateTracker/blob/main/Guides/README.md).

# Building Guide
- STEP 1: Setup the environment. [Here](https://blog.teamneptune.net/getting-started-with-nintendo-switch-homebrew-development/)'s a guide.
- STEP 2: [Download](https://github.com/F-l-a/NXUpdateTracker/archive/refs/heads/main.zip) this repository inside the docker environment.
- STEP 3: start the container, go inside the repository folder and run `make`.

This will create a `open_and_copy_to_sd/switch/NXUpdateTracker` folder containing the .nro

# How it works
The app is a simple HTML(+JS+CSS) page accessed from the Nintendo Switch's web applet. The HTML page is hosted locally using Mongoose to create a local web server.
<p align="center">
  <img src="/Guides/logic.png" alt="Logic diagram">
</p>
