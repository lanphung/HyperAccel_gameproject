precision highp float;
uniform mat4 u_wvp, u_w, u_v;
uniform sampler2D u_texture4;

attribute vec3 a_posL;
attribute vec2 a_uv;

varying vec2 v_uv;
varying vec3 v_posL;
void main()
{
	vec4 posL = vec4(a_posL, 2.0);
	gl_Position =  texture2D(u_texture4, a_uv);
	gl_Position.y *= 10.0;
	gl_Position.x = posL.x;
	gl_Position.z = posL.z;
	gl_Position.w = posL.w;
	gl_Position = u_wvp * gl_Position; 
	v_uv = a_uv;
	v_posL = vec3 (u_v * vec4(a_posL,1.0));
}
   