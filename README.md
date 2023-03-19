# [ToolExample - ScottKirvan/ToolExample fork](https://github.com/ScottKirvan/ToolExample)
This project contains UX/UI C++ examples for adding tools and UI elements to the [Unreal Engine](https://github.com/epicgames) editor - which means, these are editor tools for the artist, and not an example of how to write the runtime game code that a player would interact with.  

If you're looking for an example to show how to add an item to the existing menu, or a new edit mode, or how to create a dockable window, this is a really thorough, [step-by-step example](https://lxjk.github.io/2019/10/01/How-to-Make-Tools-in-U-E.html) that starts from an empty code project, immediately jumps into the base modules needed, and then clearly and easily walks through the steps to code up various UI elements, hooking them to functionality as you go.

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

This repo is an updated fork of [Eric Zhang's](https://github.com/lxjk) original [UE4 project](https://github.com/lxjk/ToolExample).  The excellent step-by-step documentation can be found here: [How to Make Tools in UE4](https://lxjk.github.io/2019/10/01/How-to-Make-Tools-in-U-E.html)   I've included a stripped down version of that tutorial in this repo in case anything happens to that URL in the future.  

This tutorial has become the most valuable one I've run across in my Unreal C++ journey.  It got me started in an area of programming in Unreal that I found pretty impenetrable at first, and it has continued to be a reference point that I return to frequently whenever I'm thinking I want some new functionality (or just some easier-to-get-at functionality) inside Unreal.  My deepest gratitude to Eric for his contribution here.

## Branches
- master
    - current development branch - this will likely have the most recent code
- 5.1
	- UE 5.1 Compatible
	- There was some header changes, a new module dependency, and class FEditorStyle was deprecated and replaced with FAppStyle.
	- I tested this very briefly, but it all seems to be working in UE5!
- 4.26
  - UE 4.26 Compatible.
  - Example Editor Mode is working in this version, so I'm not going to bother trying to figure out what broke in 4.25.  If anyone takes this on as a project, please toss up a Pull Request.
  - initial branch source is identical to 4.24/4.25
- 4.25
    - UE 4.25 Compatible.
    - builds and runs, but the Example Editor Mode isn't working.  It shows up in the Modes list, but the UI never gets built when selected.  I didn't see any errors or warnings anywhere.
        - NOTE:  The editor mode issue works in 4.26 without any code changes.
    - as it stands, this source is identical to the 4.24 branch
- 4.24
    - UE 4.24 Compatible.
    - updates build.cs to V2 target.
        - implements [IWYU](https://docs.unrealengine.com/en-US/ProductionPipelines/BuildTools/UnrealBuildTool/IWYU/index.html) standard.
- 4.23
    - original fork from [lxjk/ToolExample](https://github.com/lxjk/ToolExample).
    - UE 4.23 compatible.
