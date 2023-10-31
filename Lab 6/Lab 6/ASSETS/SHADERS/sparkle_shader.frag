uniform float time;
uniform sampler2D texture;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec4 color = texture2D(texture, uv);

    float sparkle = abs(sin(time * 10.0)); // A simple sparkle effect

    // Apply sparkle effect to the color
    color.rgb *= sparkle;

    gl_FragColor = color;
}