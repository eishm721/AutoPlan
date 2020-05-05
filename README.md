# AutoPlan++

This is an item allocation interface for creating customized exercise/food schedules based on self-developed shuffling algorithms.

This application takes in a set of items entered in my a user and automatically creates allocation sequences based on user specifications and self-manages data. Implemented to prevent two items from showing up on back-to-back days. Random shuffling algorithm created that spaces elements out based on total number of items to choose from. Items can be assigned a rarity parameter to show up less frequently.

Features:
- Input/remove items easily, data managed by platform
- Develop schedules of specified length with optimized allocation frequencies
- Advanced testing platform with pre-built functions for simulation

Initial designs were implemented in C++ by creating a RandomPQueue class to represent a set of items to allocate. Randomization algorithms were determined through heavy simulation and mathematical modeling. RPQueue was tested for reallocation size (how long before a given item is repeated), rarity (tests for items that the user wants to appear less frequently), "randomness" from the specific engine used, and overall efficiency.

Current work is being done on front-end iOS application framework in Swift. UI/UX is currently under design.
