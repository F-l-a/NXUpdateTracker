# NXUpdateTracker
<p align="center">
  <img src="/icon.jpg" alt="NXUpdateTracker icon">
  <br><br>
  A local HTML page that helps you track the version numbers of [Switch] homebrew applications
</p>

---
# Start here!
- Guide and Documentation [here](https://github.com/F-l-a/NXUpdateTracker/wiki)

- Demo Version [here](https://f-l-a.github.io/NXUpdateTracker/) - Try it! (Since it's a demo, it's heavily limited, but it's good to have)

## Features
- Lists the latest version number of the supported homebrews
- Loads the currently installed version number from a JSON file hosted on Github, like [this](https://github.com/F-l-a/FlaSwitch/blob/main/Versions.json)
- Compares the installed and the latest version numbers, with the possibility to only list the outdated apps that have an update available
- Updates the installed version numbers modifying the JSON directly from the app
- Lists some important files needed by the apps to work properly. Some of the files are accessible via Google Drive links
- Accessible everywhere: .nro version for the switch, standalone .html version for every browser
- Customizable: you can modify the html to include other apps/assets/links
- Does NOT install the updates itself, nor it downloads them
  
---
## Credits
I would like to thank these people who gave me the possibility to bring this project to you:

- switchbrew for [libnx](https://github.com/switchbrew/libnx)
- BernardoGiordano for [nx-spa](https://github.com/BernardoGiordano/nx-spa), the project I partially used as a reference for mine. I used his approach to open a web server with Mongoose and I used some of his files for some parts of the process
- F-l-a ([me](https://www.youtube.com/watch?v=NfF3bThOW0Q)) for the html and javascript (and some c++) parts. I learned a lot doing this (and spending half the time on some stupid things because I couldn't get it to work. But that's what the game is about, right?)

---
### Other links
- [GBAtemp thread](https://gbatemp.net/threads/nxupdatetracker.640650/)
