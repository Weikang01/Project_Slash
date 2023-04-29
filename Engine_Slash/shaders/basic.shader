% vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 ourColor;
out vec2 TexCoord;

void main()
{
	FragPos = aPos;
    ourColor = aColor;
    TexCoord = aTexCoord;
	gl_Position = vec4(aPos, 1.0);
}

% fragment
#version 330 core

in vec3 FragPos;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

uniform float uTime;
uniform vec2 uResolution;
uniform vec2 uMouse;

out vec4 FragColor;


float random(vec2 st)
{
	return fract(sin(dot(st.xy, vec2(12.9898, 78.233))) * 43758.5453123);
}

float noise(in vec2 st) {
    vec2 i = floor(st);
    vec2 f = fract(st);

    // Four corners in 2D of a tile
    float a = random(i);
    float b = random(i + vec2(1.0, 0.0));
    float c = random(i + vec2(0.0, 1.0));
    float d = random(i + vec2(1.0, 1.0));

    // Smooth Interpolation

    // Cubic Hermine Curve.  Same as SmoothStep()
    vec2 u = f * f * (3.0 - 2.0 * f);
    // u = smoothstep(0.,1.,f);

    // Mix 4 coorners percentages
    return mix(a, b, u.x) +
        (c - a) * u.y * (1.0 - u.x) +
        (d - b) * u.x * u.y;
}

#define OCTAVES 6
float fbm(in vec2 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < OCTAVES; i++) {
        value += amplitude * noise(st);
        st *= 2.;
        amplitude *= .5;
    }
    return value;
}

vec3 FX_noise()
{
    vec2 st = FragPos.xy * uResolution;
    vec2 mouse = uMouse * uResolution;
    st += 1.f;
    st *= 2.f;

    vec3 color = vec3(0.0);

    vec2 q = vec2(0.);
    q.x = fbm(st + 0.00);
    q.y = fbm(st + vec2(1.0));

    vec2 r = vec2(0.);
    r.x = fbm(st + 1.0 * q + vec2(1.7, 9.2) + 0.15);
    r.y = fbm(st + 1.0 * q + vec2(8.3, 2.8) + 0.126);

    float f = fbm(st + r);

    color = mix(vec3(0.666667, 0.666667, 0.666667),
        vec3(0.666667, 0.666667, 0.666667),
        clamp((f * f) * 4.0, 0.0, 1.0));

    color = mix(color,
        vec3(0.164706, 0.164706, 0.164706),
        clamp(length(q), 0.0, 1.0));

    color = mix(color,
        vec3(0.666667, 0.666667, 0.666667),
        clamp(length(r.x), 0.0, 1.0));

    return color;
}

void main()
{
    FragColor = (texture(ourTexture, TexCoord) + texture(ourTexture2, TexCoord)) * .5f;
}
