# Colliders

This is a set of 2d colliders, and an overloaded `Intersect()` function to detect when any two of them collide. It's intended to be used in larger projects.

The shapes available in this library are:

* Line
* Circle
* Box
* Point

# Implementation Details

Each shape has it's own class:

* ColliderLine
* ColliderCircle
* ColliderBox
* ColliderPoint

These are all built on top of the `Vector2` class, which is included.

`ColliderLine` has two members: `center` and `projection`. This naming makes it seem as though `projection` is relative to `center`, but this is not the case. This issue may be fixed in the future.

`ColliderCircle` has a center point and a radius.

`ColliderBox` has two members: `center` and `halfSize`, the latter of which holds **HALF** the full width and height of the box.

`ColliderPoint` has only a center point.

`Intersect()` is overloaded, and can take each collider as either the left or right argument.

There are also `+` and `+=` operators for adding instances of `Vector2` to the colliders, to shift the collider's world positions around.

# Unit Testing

Simply run `make` in the root directory to produce the `out` executable, which runs the unit tests stored in `test`.

