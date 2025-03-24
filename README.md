# Elevator Simulation in C++

This is a 2D elevator simulation written in C++ using WinAPI and GDI+. It models the movement of passengers between four floors using an elevator with limited capacity and a visual representation of walking, boarding, and deboarding.

### Project Overview
- Passengers appear on each floor and request to go to another floor.

- Elevator moves between floors, picking up and dropping off passengers.

- Passengers walk in and out of the elevator with smooth animations.

- Capacity limit: Elevator holds up to 8 passengers.

- Idle logic: If the elevator is empty and no requests exist, it returns to the ground floor after 5 seconds.

- Smart call handling: Destination floors and calls are calculated based on passenger requests.

### How It Works
- Each floor has buttons where passengers request to go to a specific floor.

- Once a button is clicked:

  - A passenger appears on the floor with a number indicating their destination.

  - The elevator services requests in order, picking up as many as it can (up to 8).

  - Passengers visually enter or exit the elevator using walking animations.

- The elevator logic:

  - Determines the next destination based on current passengers and waiting calls.

  - Decides direction (up/down) based on request priorities.

  - Animates floor-by-floor movement.
