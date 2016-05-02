#version 330 core

in vec3 VERTCOLOR;
in vec2 UV;

uniform sampler2D TextureSampler;

out vec4 color;

vec3 saturate(vec3 rgb, float adjustment)
{
    const vec3 W = vec3(0.2125, 0.7154, 0.0721);
    vec3 intensity = vec3(dot(rgb, W));
    return mix(intensity, rgb, adjustment);
}


void main()
{

	vec4 t = texture( TextureSampler, vec2(UV.x, UV.y) ).rgba;
	t.rgb = saturate(t.rgb, 1.0);
	vec4 m = vec4(VERTCOLOR, 1.0);
	color = t * m;
	
}
