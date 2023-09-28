#version 330

// Input
in vec2 fragTexCoord;
in vec4 fragColor;

// Uniforms
uniform sampler2D texture0;
uniform vec3      palette[24];

// Output
out vec4 finalColor;

void main() {
    vec4 color     = texture(texture0, fragTexCoord) * fragColor;
    vec4 new_color = vec4(1.0);

    for (int i = 0; i < palette.length(); ++i) {
        vec4 pal_color = vec4(palette[i], 1.0);
        if (distance(pal_color, color) < distance(new_color, color)) {
            new_color = pal_color;
        }
    }

    finalColor = new_color;
}
