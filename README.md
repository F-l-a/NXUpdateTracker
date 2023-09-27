# NXUpdateTracker
<p align="center">
  <img src="/icon.jpg" alt="NXUpdateTracker icon">
  <br><br>
  A local HTML page that helps you track the version numbers of [Switch] homebrew applications
</p>

# Installation Guide
- STEP 1: Download the .zip file
- STEP 2: Extract the .zip and copy its contents inside the root of your SD card
- STEP 3: To use all the functions of the app, you need to modify `/switch/NXUpdateTracker/githubInfo.ini`. Go to [Usage Guide](https://github.com/F-l-a/NXUpdateTracker#Usage-Guide)

# Usage Guide
Set the app up by following the steps [here](https://github.com/F-l-a/NXUpdateTracker/blob/main/Guides/README.md).

# Building Guide
- STEP 1: Set up the environment. [Here](https://blog.teamneptune.net/getting-started-with-nintendo-switch-homebrew-development/)'s a guide.
- STEP 2: [Download](https://github.com/F-l-a/NXUpdateTracker/archive/refs/heads/main.zip) this repository inside the docker environment.
- STEP 3: start the container, go inside the repository folder and run `make`.

This will create a `open_and_copy_to_sd/switch/NXUpdateTracker` folder containing the .nro

# How it works
- HTML part:

  The app is a simple HTML(+JS+CSS) page accessed from the Nintendo Switch's web applet. The HTML page is hosted locally using Mongoose to create a local web server.
  The page consists of a list of Applications contained in some tables. Each app is paired with two version numbers, for the latest available version and for the installed one. The latest version is taken directly from Github's official repository, while the installed one is taken from a JSON file hosted in a GitHub repository. (Each user needs to create his own repository, [here](https://github.com/F-l-a/NXUpdateTracker/blob/main/Guides/README.md)'s a guide to creating one). The installed version in the JSON can be modified using a button.
  <p align="center">
    <img src="/Guides/screenshot.png" alt="App screenshot">
  </p>

- Switch part:
  
  On boot, the app writes the needed files (HTML, JS) in `sdmc:/switch/NXUpdateTracker/`, which will be the server's root folder. The needed files are taken from `romfs:/webapp/` and are hardcoded inside the .nro. To avoid overwriting current files, create an empty  file named `.keep` inside `/switch/NXUpdateTracker/`. (Missing files are copied anyway. The GitHub credentials .ini file -`githubInfo.ini`- is not overwritten if already present).
  <p align="center">
    <img src="/Guides/logic.png" alt="Logic diagram">
  </p>
