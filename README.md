# imgd4000-boids
 My work for the agent-based simulation assignment (https://github.com/charlieroberts/imgd4000-2024/blob/main/agents_assignment.md) for IMGD 4000 in D-Term 2024, which implements flocking behavior in UE5 using C++.

## References
 I used pseudocode written by Conrad Parker (http://www.kfish.org/) in order to implement the boid rules; That pseudocode can be found here: http://www.kfish.org/boids/pseudocode.html.
 
 I also referenced this term's flocking tutorial (https://github.com/charlieroberts/imgd4000-2024/blob/main/day_4_flocking.md).

## Important Notes
 I've created two C++ classes, and haven't used any blueprints. The two new classes contain the only C++ code I wrote; I didn't write any in the C++ gamemode file automatically generated. The two classes are BoidAgent and BoidManager; the latter does most of the heavy lifting. The manager spawns the agents and moves them around according to the boid's rules. These classes are located in Source --> IMGD4000_BoidAgents, with the .h files being in that directory's Public folder. 
 
 I also created the UE5 project with the starter content included, but now realize that wasn't really necessary.

## Implemented Tweak
 Along with the three boid rules, I implemented the speed limiter tweak. This keeps the boids from going out of control when they move around. This is calculated after the rule vectors are added together, not technically added as a rule itself.

## Demo Video
 The demo below demonstrates multiple program runs. The initial velocities of the boids are individually randomized (with the z-direction always made positive, so they don't just fly into the ground), which causes each run to be slightly different; however, the behavior of the boids remains the same.

 https://github.com/aegross/imgd4000-boids/assets/48368165/5ec56271-b161-446c-97fb-cd086a5845ad
 
