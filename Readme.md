# ReachIt

Help people who have difficulty controlling mouse movements reach any corner of window in minimum keyboard steps.

Also useful for people who don't have mouse or don't prefer using it aka some programmers.

## Use case :
Sometimes we want to precisely click on a checkbox, or a text field. However, people with hand tremors/lack of fine motor skills will find it extremely difficult. In that case, this app will help them to get the job done.

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

## How to use :
* Download the executable and start it from command window.
* You will see a window with 4 blocks.
* Press `left/right` to move from one block to another.
* Press `down` to split the current block into 4 blocks. Use `left/right` now to move in these blocks.
* Press `up` to join the 4 blocks into 1 block.
* Your mouse pointer will also move as you travel through the blocks.
* When your mouse pointer has reached right spot, press `Enter` to start working on actual application.
* Use mouse to click on the button.
* Use `Atl-Tab` on windows to bring back the `reachit` window once you want to move to new location.

## Building on mac :
Use `setup_mac.sh` for setup and build information.
