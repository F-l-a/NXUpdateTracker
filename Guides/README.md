# NXUpdateTracker - USAGE GUIDE
- STEP 1: Create a repository and the `Versions.json` file -> Follow [How to create a Github repository](https://github.com/F-l-a/NXUpdateTracker/blob/main/Guides/Repository/README.md#How-to-create-a-Github-repository)

- STEP 2: Get a Github API token -> Follow [How to generate a Github API token](https://github.com/F-l-a/NXUpdateTracker/blob/main/Guides/Token/README.md#how-to-generate-a-github-api-token)

- STEP 3: Download and extract the latest relase from [here]()

- STEP 4: Open `/switch/NXUpdateTracker/githubInfo.ini` with a text editor (like Notepad) and insert your repository info and your API token.

   example `githubInfo.ini` content (this is only an example. use your own info):
  
      API_TOKEN = qwertyuiopasdfghjklzxcvbnm1234567890
      OWNER = F-l-a
      REPO = NXUpdateTracker
      FILE_PATH = Versions.json

- STEP 5: Put the files inside the SD card. Your SD tree needs to be like this:

      SD  (ROOT)
      └──switch  (FOLDER)
         └──NXUpdateTracker  (FOLDER)
            ├──githubInfo.ini  (FILE)
            └──NXUpdateTracker.nro  (FILE)
