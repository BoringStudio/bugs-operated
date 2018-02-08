uniform sampler2D texture;

void main()
{
	vec4 color = texture2D(texture, gl_TexCoord[0].xy);
	if (mod(gl_FragCoord.y, 2.0) >= 1) {
		color *= vec4(0.9);
	}
    else {
        color *= vec4(1.05);
	}

    gl_FragColor = color * gl_Color;
}