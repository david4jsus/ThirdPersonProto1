# My first game prototype made with Unreal

The goal of this project was to learn to use the Unreal Engine 4, as well as practice C++.
The result is aesthetically ugly but I did manage to make some cool third person platformer movement gameplay mechanics.
You can download and play the game yourself (if for whatever reason you want to) but please read the **controls section** first, as there is no tutorial in this prototype.

## Demo

Here is a video showing the main ideas in the prototype:

[![Demo video](https://img.youtube.com/vi/5WhLoKV4kgs/0.jpg)](https://youtu.be/5WhLoKV4kgs)

## Project Goals

- [x] Learn to navigate the Unreal Editor
- [x] Get a refresher on C++
- [x] Learn the types of objects and classes that are used in game development for Unreal
- [x] Implement third person platforming gameplay
- [x] Create classes and objects in C++ to use in the prototype
- [x] Learn the relation between C++ classes and Unreal's Blueprint system
- [x] Create and release some form of playable project (this prototype right here 😊)

## Movement Features

The gameplay that I implemented focuses on movement. From the start, the player can:
- Run around
- Jump
- Climb and hang from a ledge
- Crouch

Through picking up upgrades, the player can then:
- Double jump
- Triple jump
- Sprint
- Dash
- Swing with a hook from a pre-placed hook point

## Classes

All the C++ classes I made in this prototype are available inside the "Source/ThirdPersonProto1" folder. Here is a simple description of each class:
- **Character_PlayMontageNotify**: A custom animation montage notify object that allows programmable behavior once an animation reaches a frame. Used to transition from hanging from a wall to climbing it and standing on a plane.
- **CustomAnimNotify_PlaySound**: A custom animation notify that plays 3D audio and allows some customization of the sound to play when the animation reaches a frame. Used for character sounds and allows jumping and footsteps to use the same sound but reproduce different randomized pitches to allow for sound variety.
- **EMovementUpgrade**: An enum used between the character and movement upgrades to describe what movement upgrade the character is interacting with.
- **HookPoint**: An actor object that can be placed in the level and serves as point to hook to and swing from.
- **InGameHUD**: A custom HUD class that takes care of showing menus and on-screen text.
- **InteractionTextWidget**: A custom UI widget that shows text (originally just the text that shows when the character is in front of a movement upgrade, but then modified to also show objective text).
- **InteractiveKey**: An abstract class that will interact with an object created from the **InteractiveObstacle** class and will allow for this obstacle to be locked/unlocked.
- **InteractiveObstacle**: An abstract class that will serve as an obstacle or puzzle object in the level and can be locked/unlocked.
- **KeyPressurePlate**: A pressure plate derived form the **InteractiveKey** class that can be linked to any obstacle object (created from the **InteractiveObstacle** class) to unlock it while the character is standing on the pressure plate.
- **LevelEndTeleporter**: A teleporter that will load the next level when the character stands on it. The next level will only load when the objective system says that all objectives in the level are complete.
- **MovementUpgrade**: An actor object that can be placed in the level to provide the character with a movement upgrade. By default, the upgrade is empty, so interaction is null until its upgrade property is changed to one of the possible movement upgrade options (specified in the **EMovementUpgrade** enum).
- **Objective**: An asbtract object representing an objective. This object contains some basic information about an objective, such as name and description (which is the corresponding text that the HUD will show).
- **ObjectiveComponent**: An actor component that can be added to any object within the level. This component will allow that object to interact with the objective system: check on the status of an objective, mark an objective as complete/incomplete...
- **ObjectiveSystem**: An abstract class that takes care of organizing objectives and managing them. Other objects will interact with this system through the **ObjectiveComponent** class.
- **ObjectiveTrigger**: An actor object that can be placed in the level and will interact with the objective system. This shows as an invisible box and is triggered when the character enters this box.
- **ObstacleDoor**: An actor object derived from the **InteractiveObstacle** class that will function as a door. An object within the level created from the **InteractiveKey** class (in this case, the **KeyPressurePlate**) can open and close this door.
- **TeleportVolume**: An actor object that can be placed in the level and teleport the character to a specified location when the character enters its volume. This object is shown as an invisible box and its placed in each level, under all geometry, to teleport the player back to level if the player falls from the level (this is similar to a kill volume, except there is no killing in this prototype).
- **Teleporter**: An actor object that can be placed in the level and allows the character to teleport to a specified location when the player is standing on it and presses the interaction key.
- **ThirdPersonProto1Character**: This class was automatically generated when the third person template was generated, but it is heavily modified to allow the new movement functionality.
- **ThirdPersonProto1GameMode**: This class was automatically generated when the third person template was generated, but it is slightly modified to allow easier interaction with the objective system (because actor classes already have a function to get the gamemode of the level, so by attaching the objective system to the gamemode actors can just get the gamemode to easily get access to the objective system; I would probably spend more time to make this process more secure in an actual game, as not just any actor should have access to the objective system).

There were a few things, mostly dealing with the UI and menus, that were implemented with Blueprints. While I like using C++ and everything in Unreal can be done with C++, some things are just nicer to work with in a more visual way.

## Other things I made for this prototype

Some sounds are from [freesound.org](https://freesound.org) while others (jumping, door opening and closing, dashing and attaching to a hook point) I made. I also modeled the simple teleporter 3D model, which I liberally used for multiple objects in this prototype. The door 3D model, along with its opening and closing animations, I also made. It was not one of the goals of this prototype to implement music (since I decided to leave that to its own project for me to play around with), to have a good sound mix, or to produce many assets to use within the game. As a result, this prototype is ugly. Instead, the main goal was functionality.

## Controls

There is no tutorial in this prototype, so a knowledge of the controls is assumed for anyone who (for whatever reason) decides to play this game. While Unreal's third person template allows for controls with mouse and keyboard, gamepad, and VR controls, all the functionality I implemented works only with mouse and keyboard.

- **Move mouse**: Look around.
- **W**: Move forward or climb up, if hanging from a ledge.
- **A**: Move left.
- **S**: Move backwards.
- **D**: Move right.
- **Spacebar**: Jump or climb up, if hanging from a ledge, or let go of a hook point if swinging.
- **Left Control**: Crouch or drop from a ledge, if hanging from a ledge. You can still move with **WASD** when crouching.
- **E**: Interact (with teleporters to teleport, and movement upgrade objects to obtain a movement upgrade if the object is not set to an "empty upgrade").
- **Q**: Hook onto a hook point to start swinging, if close enough to a hook point, if the player has obtained the hook upgrade.
- **Left Shift**: Hold to sprint, if the player has obtained the sprint upgrade.
- **F**: Dash, if the player has obtained the dash upgrade.
- **Shift + Escape**: Pause menu (I set it as **Shift + Escape** and not just **Escape** because **Escape** conflicted with "**stop testing**" in the Unreal editor, which I could have changed but I left it like this because this is a prototype and I'm done here).
