#version 120
uniform sampler2D currentTexture;
uniform float time;

void main()
{
	//gets the coordinates of our pixel 
	vec2 coord = gl_TexCoord[0].xy;
	if(time<.4)
	{
	//increase the position of our Y coordinate
    	coord.y += cos(radians(93.75*(time * 10) + coord.y * 0)) * 0.025*sin(time * 10);
	}    	
	//Applies our colour
	vec4 pixel_color = texture2D(currentTexture, coord);
    gl_FragColor = pixel_color;
}