# WebSimulation

#### A visual simulation written in C++ with [OpenGL](https://www.opengl.org/) of something that resembles a spider web that can be interacted with.

## Background
Imagine you have a grid of points, all connected to their four closest neighbors with an invisible string. At each iteration of the simulation, the points
move towards the general direction of its connected neighbors. Let the outer ring of points in the grid be fixed. More specifically, the simulation works 
like this at each step:
```
let grid = a list of points in 2D space forming a grid
let ACCELERATION_FACTOR = 0.01 // Something small

loop (at each frame):
    for each point P in grid:
        if P is an edge point: // If P is fixed, don't move it
            continue
        let general_direction = null 2D vector
        for each point P2 in P's connected neighbors:
            general_direction += P2 - P // Vector from point to neighbor
        // Move point towards an average position of its neighbors
        P += general_direction * ACCELERATION_FACTOR
```

The reason we need to fix the edge points in the grid is to keep the configuration of points stable. Otherwise the points would collapse into the center. At this point not much would happen to the points, as the average direction from a point to its neighbors is still a null vector. All the points would stay at their initial position. It becomes interesting when we reposition a point and let the simulation run. Nearby points get dragged closer to the moved point. If we visually plot all points in the grid as geometrical objects and let the user drag points around freely, we can see something that starts to resemble a spider web. For large grids, it even looks like a cloth simulation - see animated gifs below. Running this in 100+ frames per second looks even better than the gifs though.

## Development

I followed [this video](https://www.youtube.com/watch?v=45MIykWJ-C4) which uses [GLFW](https://www.glfw.org/) and [GLAD](https://glad.dav1d.de/) to get OpenGL graphics running.

## Example visuals

![](https://github.com/ludvig-sandh/WebSimulation/blob/main/resources/single_colored.gif)
![](https://github.com/ludvig-sandh/WebSimulation/blob/main/resources/multi_colored.gif)

## Improvement / Ideas
- Could this be simulated in 3D?
- Do we have to position the points in a grid? Are there any other possible patterns that lead to a stable formation of points?
- Would the simulation look significantly different if we defined a point's connected neighbors to be the eight surrounding points instead of four? Or perhaps another configuration?
