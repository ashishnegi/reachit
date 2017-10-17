# ReachIt

Help people who have difficulty controlling mouse movements reach any corner of window in minimum keyboard steps.

Also useful for people who don't have mouse or don't prefer using it aka some programmers.

## Idea :
Divide the screen into smaller pieces with each user input to take her to the desired position.

## Demo :

![Demo gif](https://github.com/ashishnegi/reachit/raw/master/demo.gif)

## Implementation :
1. Done. Use a transparent window.
2. Done. Create four quadrants in current selected step.
3. Done. Use left/right to go to next quadrant
         and up/down to go to next/previous step.
3.a Done. Create sub-grids inside a grid at any location.
4. Done. Use enter to move out of binReach_mode.
5. OnHold : Shift-Tab can work here : Long press another key to come back in binReach_mode.
6. Done. Show mouse cursor movement.
7. Highligh button which gets the focus. Or keep highlighting the mouse position.
8. Give user a way to set the keys for app.

## Binaries :
Look in [bin](https://github.com/ashishnegi/reachit/tree/master/bin) directory for your platform. Use release version.

## Building on mac :
Use `setup_mac.sh` for setup and build information.
