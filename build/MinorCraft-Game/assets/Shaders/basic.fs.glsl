#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
uniform sampler2D u_AtlasID;

void main()
{
    // FragColor = vec4(1.0, 0.0, 0.0, 1.0); // red
    FragColor = texture(u_AtlasID, TexCoords); // red
}
