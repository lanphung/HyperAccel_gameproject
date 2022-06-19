precision mediump float;

uniform sampler2D u_texture;
uniform float u_Time;

varying vec2 v_uv;
varying vec3 v_posL;

void main()
{
	//vec2 UV = vec2(v_uv.x*0.5 + u_Time*0.5, v_uv.y);
	vec2 UV = vec2(v_uv.x,  v_uv.y*0.50 + u_Time*0.50);
	gl_FragColor = texture2D(u_texture, UV);
}