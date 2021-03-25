# ToolExample - ScottKirvan/ToolExample fork

This project contains UX/UI example code for [Unreal Engine](https://github.com/epicgames) engine developers.

The example covers the following:
- adding modules
- adding menus to the editor interface with:
  - sections
  - menu items
  - sub menus
  - adding custom widgets and controls (button and text input) to the menu
- adding a dockable tab Window
- custom details panel
- defining and adding your own custom asset data type (data factory)
- importing/reimporting custom data
- custom editor mode
- custom editor viewport widget
- viewport object context sensitive right-click & menus
- custom project settings/preferences
- additional tricks and tips

The original project and step-by-step documentation can be found here: [How to Make Tools in UE4](https://lxjk.github.io/2019/10/01/How-to-Make-Tools-in-U-E.html)  
I've included a plain-text version of that article in the project in case anything happend to that url in the future.  
The origial project will build for 4.23 but not [4.17](https://github.com/lxjk/ToolExample/issues/2). 
I couldn't build for 4.25 or 4.26, so I created this fork to go through the process
of updating the codebase to 4.26.

## Branches
- master
    - current development branch - this will likely have the most recent code
- 4.26
  - UE 4.26 Compatible.
  - Example Editor Mode is working in this version, so I'm not going to bother trying to figure out what broke in 4.25.  If anyone takes this on as a project, please toss up a Pull Request.
  - initial branch source is identical to 4.24/4.25
- 4.25
    - UE 4.25 Compatible.
    - builds and runs, but the Example Editor Mode isn't working.  It shows up in the Modes list, but the UI never gets built when selected.  I didn't see any errors or warnings anywhere.
        - NOTE:  The editor mode issue works in 4.26 without any code changes.
    - as it stands, this source is identical to th 4.24 branch
- 4.24
    - UE 4.24 Compatible.
    - updates build.cs to V2 target.
        - implements [IWYU](https://docs.unrealengine.com/en-US/ProductionPipelines/BuildTools/UnrealBuildTool/IWYU/index.html) standard.
- 4.23
    - original fork from [lxjk/ToolExample](https://github.com/lxjk/ToolExample).
    - UE 4.23 compatible.
