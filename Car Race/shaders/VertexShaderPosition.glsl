#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 3) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 car_position;
uniform vec3 object_color;

// Output
out vec3 color;

void main()
{
    vec3 world_position = vec3 (Model* vec4(v_position, 1));
    world_position.y = world_position.y - ((car_position.x - world_position.x)*(car_position.x - world_position.x) + 
    (car_position.y - world_position.y)*(car_position.y - world_position.y) + (car_position.z - world_position.z)*(car_position.z - world_position.z))*0.01;
    color = object_color;
    gl_Position = Projection * View * vec4(world_position, 1.0);

}
