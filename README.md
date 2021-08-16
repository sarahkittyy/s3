# s3

3D graphics & general application library inspired by SFML.

## Dependencies

- GLFW3
- GLEW
- OpenGL 3.3
- glm
- [Assimp](https://github.com/assimp/assimp)

## Examples

## TODO

- [x] mesh loader from common file formats
- [ ] sounds
- [ ] common primitive shapes
- [x] lighting
- [ ] shadows
- [ ] transparency
- [ ] billboard template container
- [ ] fonts, text
- [x] timing / clock utility
- [x] events, hooks
- [x] keyboard & mouse i/o
- [x] test cases
- [x] orbital camera
- [ ] multi window support, with multi-threading capabilities
- [ ] documentation detailing shader requirements
- [ ] finalize how to provide access to the resource manager
- [ ] 2d rendering support
- [x] framebuffers, abstract rendertarget
- [ ] ui support
- [ ] compute shaders
- [ ] documentation
- [ ] parameters given to the window (face culling, etc)
- [ ] per-renderable opengl settings (face culling, etc)
- [x] skybox!
- [ ] more intricate documentation, fixing inconsistency in commenting style
- [ ] copyable opengl objects (VAOs, VBOs, textures, shaders, meshes)
- [ ] meta-headers for grouping headers
- [ ] refactor camera get_pos() and position() confusion
- [ ] sort out surfaceable, transformable, etc, into prop:: namespace
- [ ] anti-aliasing configuration (currently locked at 4)
- [ ] reflection mapping
- [ ] refraction mapping
- [ ] dynamic environment mappings (real reflections)
- [ ] assimp model loading

## Known Issues

- ~~Changing freecam position causes a sudden jump when the mouse is next moved.~~
- ~~Pointing freecam straight down causes W and S movement acceleration to become painfully slow.~~
- No way to scale UVS in textures.
